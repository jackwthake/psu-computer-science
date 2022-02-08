#!/usr/bin/env python3

'''This program runs required tests for Assignment 4 for CS201

    Copyright (c) 2021, Ted Cooper <ted.r.cooper@gmail.com>
    Licensed under GPLv3: https://www.gnu.org/licenses/gpl-3.0.txt
'''

from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals

import argparse
import code
import collections
import functools
import math
import os
import pexpect
import random
import re
import string
import sys
import time

import grading_common
from grading_common import TestResult, avoid_range, build_test_i, clear_files, continue_on_failure, log_filename_prefix, random_hex_string, random_int, random_interleave_2_lists, random_invalid_hex_string, random_string, run_and_log_tests, signed_to_unsigned, spawn_and_log, unsigned_to_signed

n_runs = 12

re_flags = re.MULTILINE | re.IGNORECASE

menu_res = [ re.compile(r'\s*0\s*\.\s+Exit\s+',flags=re_flags)
           , re.compile(r'\s*1\s*\.\s+Addition\s+',flags=re_flags)
           , re.compile(r'\s*2\s*\.\s+Subs?traction\s+',flags=re_flags)
           , re.compile(r'\s*3\s*\.\s+Multiplication\s+',flags=re_flags)
           , re.compile(r'\s*4\s*\.\s+Division\s+',flags=re_flags)
           , re.compile(r'\s*5\s*\.\s+Modulo\s+',flags=re_flags)
           , re.compile(r'\s*6\s*\.\s+Reverse\s+Input\s+',flags=re_flags) ] 

n_menu_items = len(menu_res)
non_exit_menu_items = list(range(1,n_menu_items))
non_exit_menu_items_set = set(non_exit_menu_items)
menu_items = [0] + non_exit_menu_items
menu_items_set = set(menu_items)

def eat_menu(p, test_result, cmd):
    for r in menu_res:
        try:
            index = p.expect([r, r'\s*TODO'])
            if index == 1:
                test_result.fail_append(f'TODO output, indicating not yet implemented.')
        except Exception as e:
            if p.flag_eof:
                test_result.fail_append(f'a4 exited when we expected it to print the menu again.  See read log for the session leading up to this unexpected exit.', command=cmd)
            test_result.fail_append(f'Expected a menu item to be printed, but the output below was printed instead.  Could be an issue with how the menu looks, or could be that your program did something besides printing the menu when we expected a menu.  a4 did not produce expected menu item output matching regular expression:\n{r.pattern}', command=cmd, output=p.before, exception=e)
    return(True)

def enter_menu_item(p, test_result, cmd, item):
    r = re.compile(r'\s*Menu\s+item:\s*', flags=re_flags)
    try:
        p.expect(r)
    except Exception as e:
        test_result.fail_append(f'a4 did not print expected menu item prompt matching regular expression:\n{r.pattern}', command=cmd, output=p.before, exception=e)
    p.sendline(str(item))
    p.expect(str(item))

def gen_valid_menu_item():
    return(random.randrange(0,n_menu_items))

def exit_handler(p, test_result, cmd, args, guaranteed):
    try:
        p.wait()
        p.close()
    except Exception as e:
        if guaranteed:
            test_result.fail_append('Timed out waiting to exit', command=cmd, output=p.before, exception=e)
    if guaranteed and p.exitstatus != 0:
        test_result.fail_append('Exit didn\'t exit with success status (expected exit status 0)', command=cmd, output=p.after)
    return(False)

def reverse_handler(p, test_result, cmd, args, guaranteed):
    r = re.compile(r'\s*((?:[' + ''.join(string.ascii_letters) + '0-9-]+ *)+)', flags=re.IGNORECASE)
    try:
        p.expect(r, timeout=1)
    except Exception as e:
        test_result.fail_append(f'Output didn\'t match regular expression:\n{r.pattern}', command=cmd, output=p.before, exception=e)
    output = p.match.groups()[0]
    output = output.rstrip(' \n')
    #print(f'reverse_handler: matched, output is {output}')
    ss = output.split()
    v_ss = [s[::-1] for (_, s) in args][::-1]
    if ss != v_ss:
        print(f'ss:\n{str(ss)}\nv_ss:\n{str(v_ss)}')
        if len(ss) != len(v_ss):
            print(f'len(ss): {len(ss)} not same as len(v_ss): {len(v_ss)}')
        for (s,v_s) in zip(ss,v_ss):
            if s != v_s:
                print(f's: "{s}" not the same as v_s: "{v_s}"')
        expected_example = ' '.join(v_ss)
        test_result.fail_append(f'Output didn\'t match output such as:\n{expected_example}', command=cmd, output=p.after)
    return(False)

binop_fs = {}
binop_fs['+']   = '__add__'
binop_fs['-']   = '__sub__'
binop_fs['*']   = '__mul__'
binop_fs['mod'] = '__mod__'
binop_fs['/']   = '__truediv__'

int_binops = ['+','-','*','mod']
flt_binops = ['/']

n_bits=32
def get_binop_f(binop):
    if binop == 'mod':
        def f(l, r):
            absmod = abs(l) % abs(r)
            return (-absmod) if l < 0 else absmod
    else:
        def f(l, r):
            return(getattr(l, binop_fs[binop])(r))
    return(f)

def parse_dec(s): return(int(s,10))
def parse_float(s): return(float(s))

def parse_hex(s): 
    if s[0] == '-':
        v = int(s[1:], 16)
        v = -v
    else:
        v = unsigned_to_signed(int(s, 16), n_bits)
    return(v)


def parse_binop_exp_s(test_result, cmd, output, binop, binop_exp_s, prefix, digits, parse_f=parse_dec, parse_type='decimal'):
    #chunks = binop_exp_s.split(sep=binop)
    r_elem_s = r'\s*(-?' + prefix + digits + r'+)\s*'
    r_elem = re.compile(r_elem_s, flags=re.IGNORECASE)
    r_elem_op = re.compile(r_elem_s + re.escape(binop) + r'\s*(.*)', flags=re.IGNORECASE)
    s = binop_exp_s
    v_ss = []
    # we've already made it past the first regular expression, so these matches should always work
    m = None
    while True:
        m = r_elem_op.match(s)
        if m is None: break
        (elem, rest) = m.groups()
        #print(f'matched a chunk, elem is {elem}, rest is {rest}')
        v_ss.append(elem)
        s = rest
    # last element won't match r_elem_op regex because there's no binop
    elem = r_elem.match(s).groups()[0]
    v_ss.append(elem)
    vs = []
    for v_s in v_ss:
        try:
            v = parse_f(v_s)
        except Exception as e:
            test_result.fail_append(f'couldn\'t parse output string chunk {s} as {parse_type}', command=cmd, output=output, exception=e)
        vs.append(v)

    return(vs)

def render_dec_i(i, **kwargs): return(str(i))
def render_hex_i(i, signed=False): 
    magnitude = hex(signed_to_unsigned(i, n_bits))
    return(('-' if signed and i < 0 else '') + magnitude)
def render_flt(f, **kwargs):
    return('%.6f' % f)

def build_binop_handler(binop):
    # returns whether or not we ate the next menu
    def binop_handler(p, test_result, cmd, args, guaranteed):
        if binop == '/' or binop == 'mod':
            args = args[:2]
        hex_prefix = '0x'
        def re_s(prefix, digits):
            # TODO handle % in addition to mod
            r = r'\s*((?:-?' + prefix + digits + '+\s*' + re.escape(binop) + '\s*)+\s*-?' + prefix + digits + '+\s*)=\s*(-?' + prefix + digits + '+)\s*'
            #print(f're_s: {r}')
            return(r)
        # don't make \n match spaces for this one
        re_flags = re.IGNORECASE
        dec_digits = '\d'
        flt_digits = '[0-9.infnan+-]'
        hex_digits = '[a-fA-F0-9]'
        r_dec_i = re.compile(re_s('',         dec_digits), flags=re_flags)
        r_dec_f = re.compile(re_s('',         flt_digits), flags=re_flags)
        r_hex   = re.compile(re_s(hex_prefix, hex_digits), flags=re_flags)
        r_dec   = r_dec_f if binop == '/' else r_dec_i
        vs = [float(v) if binop == '/' else v for (v,_) in args]
        result = functools.reduce(get_binop_f(binop), vs)
        signed_result = unsigned_to_signed(result, n_bits) if binop != '/' else result
        render_dec = render_flt if binop == '/' else render_dec_i
        rows = [        (r_dec, '',         parse_dec, 'decimal',     render_dec,   dec_digits) ]
        if binop != '/':
            rows.append((r_hex, hex_prefix, parse_hex, 'hexadecimal', render_hex_i, hex_digits))
        parse_type_renderer = {}
        passed_something = False
        patterns_tried = []
        for (r, prefix, parse_f, parse_type, render_f, digits) in rows:
            try:
                index = p.expect(r)
            except Exception as e:
                patterns_tried.append(r.pattern)
                output = p.before
                # make decimal output optional (as long as hex input is there)
                if parse_type == 'decimal':
                    continue
                # make hex output optional.  if this returns False, then n_correct_runs()
                # doesn't eat the menu on the next iteration.
                if parse_type == 'hexadecimal':
                    if not passed_something:
                        break
                    ret = eat_menu(p, test_result, cmd)
                    if ret: return(ret)
                patterns_s = '\n'.join(patterns_tried)
                test_result.fail_append(f'Output didn\'t match any of the following regular expression(s) (see Example Output in the assignment description for output that does match):\n{patterns_s}', command=cmd, output=output, exception=e)
            #print(f'r {r.pattern} parsed {p.after}')
            (binop_exp_s, result_s) = p.match.groups()
            output = p.after
            parsed_vs = parse_binop_exp_s(test_result, cmd, output, binop, binop_exp_s, prefix, digits, parse_f=parse_f, parse_type=parse_type)
            if parsed_vs != vs:
                expected_output_s = (' ' + binop + ' ').join([render_f(i) for i in vs])
                test_result.fail_append(f'Output for parse_type {parse_type} had different input numbers than expected.  We expected output such as:\n{expected_output_s}\nstr(parsed_vs): {str(parsed_vs)}\nstr(vs): {str(vs)}', command=cmd, output=output)
            parse_result_f = parse_float if binop == '/' else parse_f
            parsed_result = parse_result_f(result_s)
            expected_result_s = render_f(signed_result)
            #print(f'parsed ints {str(parsed_ints)}, result {str(parsed_result)}')
            parsed_result_s = render_f(parsed_result)
            if binop == '/':
                absdiff = abs(signed_result - parsed_result)
            if (binop != '/' and parsed_result != signed_result) or (binop == '/' and absdiff > 0.0001):
                test_result.fail_append(f'Output had sufficiently different result {parsed_result_s} than expected result {expected_result_s}', command=cmd, output=output)
            passed_something = True
        if not passed_something:
            test_result.fail_append(f'Neither decimal nor hexadecimal output', command=cmd, output=output)
        return(False)
    return(binop_handler)

item_handlers = {}
item_handlers[0] = exit_handler
item_handlers[1] = build_binop_handler('+')
item_handlers[2] = build_binop_handler('-')
item_handlers[3] = build_binop_handler('*')
item_handlers[4] = build_binop_handler('/')
item_handlers[5] = build_binop_handler('mod')
item_handlers[6] = reverse_handler

def n_correct_runs(p, test_result, cmd, args, n, guaranteed_items=[], excluded_items=[]):
    guaranteed_items_set = set(guaranteed_items)
    excluded_items_set = set(excluded_items)
    other_items_set = (non_exit_menu_items_set - guaranteed_items_set) - excluded_items_set
    other_items = list(other_items_set)
    guaranteed_items = list(guaranteed_items_set)
    m = max(n - len(guaranteed_items), 0)
    items = guaranteed_items + other_items[:m]
    random.shuffle(items)
    # ensure exit is at the end, so we hit all other guaranteed items
    if 0 in items:
        items.remove(0)
        items.append(0)
    #print(f'n_correct_runs_including: items: {items}, guaranteed_items: {str(guaranteed_items)}, other_items: {str(other_items)}')
    ret = True
    ate_menu = False
    #print(f'n_correct_runs: about to run items {str(items)}')
    for item in items:
        # eat_menu returns False if we encounter output "TODO"
        if ate_menu or eat_menu(p, test_result, cmd):
            # reset ate_menu so that it is only true if the next handler returns True
            ate_menu = False
            enter_menu_item(p, test_result, cmd, item)
            #try:
            ate_menu = item_handlers[item](p, test_result, cmd, args, item in guaranteed_items_set)
            #print(f'item_handlers[{str(item)}] returned ate_menu {str(ate_menu)}')
            
        # if we choose exit, the program exits, so we shouldn't
        # expect more output or another prompt
        if(item == 0):
            break
    return(ret)

def build_test_1(test_result, **kwargs):
    def f():
        last_p = None
        for i in range(0, n_runs):
            bad_n_args = [0, 1, 16, 18, 19]
            n_args = random.choice(bad_n_args)
            args = random_good_inputs(n_inputs=n_args)
            cmd = a4_cmd(args)
            p = spawn_and_log(cmd, 1, last_p=last_p, test_result=test_result)
            last_p = p
            time.sleep(0.2)
            p.expect(r'.*')
            #p.wait()
            p.close()
            if((p.exitstatus == 0) or p.signalstatus):
                test_result.fail_append(f'a4 did not fail (exit with non-zero status) when given an invalid number of arguments {n_args}.', command=cmd)
        test_result.succeed()
    return(f)

def a4_cmd(args):
    return('./a4 ' + ' '.join([s for (_,s) in args]))

def random_good_input(mx=None):
    i = random_int(mx=mx)
    render = random.choice([hex,str])
    return((i,render(i)))

def random_good_inputs(n_inputs=None,mx_first=None,mx_rest=None):
    if n_inputs is None: n_inputs = random.randrange(2, 16)
    first = random_good_input(mx=mx_first)
    return([first] + [random_good_input(mx=mx_rest) for _ in range(1,n_inputs)])

def random_good_strings(n_inputs=None):
    if n_inputs is None: n_inputs = random.randrange(2, 16)
    return([(None, random_string(n_inputs)) for _ in range(0,n_inputs)])

def n_correct_sessions(test_result, n_sessions, n_runs_per_session, guaranteed_items=[], excluded_items=[], non_numeric_args=False):
    last_p = None
    ret = True
    for i in range(0, n_sessions):
        #print(f'n_correct_sessions: guaranteed_items: {str(guaranteed_items)}, excluded_items: {str(excluded_items)}')
        args = random_good_strings() if non_numeric_args else random_good_inputs() 
        cmd = a4_cmd(args)
        p = spawn_and_log(cmd, test_result.test_number, last_p=last_p, test_result=test_result)
        last_p = p
        ret1 = n_correct_runs(p, test_result, cmd, args, n_runs_per_session, guaranteed_items=guaranteed_items, excluded_items=excluded_items)
        ret = ret and ret1
        if not ret: 
            break 
    return(ret)

def build_test_2(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[0], excluded_items=[4])
        if ret: test_result.succeed()
    return(f)

def build_test_3(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[1], excluded_items=[4])
        if ret: test_result.succeed()
    return(f)

def build_test_4(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[2], excluded_items=[4])
        if ret: test_result.succeed()
    return(f)

def build_test_5(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[3], excluded_items=[4])
        if ret: test_result.succeed()
    return(f)

def build_test_6(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[4], excluded_items=[0,1,2,3,5,6])
        if ret: test_result.succeed()
    return(f)

def build_test_7(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[5], excluded_items=[4])
        if ret: test_result.succeed()
    return(f)

def build_test_8(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[6], excluded_items=[4])
        if ret: test_result.succeed()
    return(f)

def build_test_9(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 10, guaranteed_items=[0], excluded_items=[])
        if ret: test_result.succeed()
    return(f)

def build_test_10(test_result, **kwargs):
    def f():
        ret = n_correct_sessions(test_result, n_runs, 1, guaranteed_items=[6], excluded_items=[4], non_numeric_args=True)
        if ret: test_result.succeed()
    return(f)

def main():
    grading_common.parse_arguments(4)

    os.system('rm -f a4 *.log feedback.txt && make')
    if not os.path.exists('a4'):
        print('make didn\'t work (can\'t find a file called a4), failing', file=sys.stderr)
        sys.exit(1)

    ff_path = 'feedback.txt'
    clear_files([ff_path])
    ff = open(ff_path, 'w')

    test_results = [ TestResult('Invalid number of arguments should fail.', 0, ff, test_number=1)
                   , TestResult('Exit works correctly.', 5, ff, test_number=2)
                   , TestResult('Addition works correctly.', 10, ff, test_number=3)
                   , TestResult('Subtraction works correctly.', 10, ff, test_number=4) 
                   , TestResult('Multiplication works correctly.', 10, ff, test_number=5)
                   , TestResult('Division works correctly.', 10, ff, test_number=6)
                   , TestResult('Modulo works correctly.', 10, ff, test_number=7)
                   , TestResult('Reverse works correctly.', 10, ff, test_number=8)
                   , TestResult('Sequence of operations works correctly.', 0, ff, test_number=9) 
                   , TestResult('Reverse works correctly with non-numeric arguments.', 0, ff, test_number=10) ]
    n_tests = len(test_results)

    tests = [ build_test_i(i + 1, test_results[i]) for i in range(0, n_tests) ]
    test_spawns = [None for _ in range(0,n_tests)]
    test_is_closures = [True for _ in range(0,n_tests)]
    test_tuples = list(zip(tests, test_results, test_spawns, test_is_closures))

    run_and_log_tests(test_tuples, test_results, log_filename_prefix, ff_path)

if __name__ == '__main__':
    main()
