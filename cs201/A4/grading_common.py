#!/usr/bin/env python3

'''Common code for CS201 grading

    Copyright (c) 2021, Ted Cooper <ted.r.cooper@gmail.com>
    Licensed under GPLv3: https://www.gnu.org/licenses/gpl-3.0.txt
'''

import argparse
import inspect
import os
import pexpect
import random
import string
import sys

import __main__
(log_filename_prefix, _) = os.path.splitext(__main__.__file__) if hasattr(__main__, '__file__') else ('', '')

class TestResult:
    def __init__(self, description, deduction, logfile, test_number=None):
        self.description = description
        self.message = ''
        self.attempted = False
        self.succeeded = False
        self.logfile = logfile
        self.outs = [self.logfile]
        self.deduction = deduction
        self.exception = None
        self.test_number = test_number

    def succeed(self):
        self.attempted = True
        self.succeeded = True

    def fail(self, m=None, d=None, exception=None):
        if(m is None): m = self.message
        if(d is None): d = self.deduction
        if(exception): self.exception = exception
        self.message = m
        self.deduction = d
        self.attempted = True
        self.succeeded = False
        raise Exception('Test failed, skipping remaining subtests.\n\n')

    def fail_append(self, error, d=None, exception=None, output=None, command=None):
        command_s = f'\n\n  Command: {command}' if command and not output else ''
        command_output_s = f'\n\n  Command and output: {command}\n{output}' if command and output else ''
        output_s = f'\n\n  Output:\n{output}' if output and not command else ''
        self.fail(m=self.message + '\n\n  Error: ' + error + command_s + command_output_s + output_s, d=d, exception=exception)

    def log_and_print(self, short_message, long_message=None):
        if(long_message):
            for f in self.outs:
                print(long_message, file=f, flush=True)
            print(short_message, file=sys.stdout, flush=True)
        else:
            for f in self.outs + [sys.stdout]:
                print(short_message, file=f, flush=True)


    def log(self):
        test_description_s = f'\nTest {str(self.test_number)}: ' + self.description
        if(not self.succeeded):
            def gen_message(middle):
                status = 'failed' if self.attempted else 'not reached'
                return(self.message + middle + f'\n\n  Test {status} -' + str(self.deduction) + '\n')
            short_message = test_description_s + gen_message('')
            long_message = test_description_s + gen_message(('\n\n' + str(self.exception)) if self.exception else '')
            self.log_and_print(short_message, long_message=long_message)
        else:
            self.log_and_print(test_description_s + '  Passed!')

def clear_files(paths):
    for path in paths:
        try:
            os.remove(path)
        except OSError:
            pass

def log_test_results(ff_path, test_results):
    print("logging to " + ff_path + ":")
    total_points = 0
    total_deductions = 0
    i = 1
    for test_result in test_results:
        d = test_result.deduction
        total_points += d
        if(not test_result.succeeded):
            total_deductions += d
        test_result.log()
        i = i + 1
    # assume that all test results are logging to the same feedback file
    # compute total for these items
    score = total_points - total_deductions
    test_result.log_and_print('\nScore for automatic tests: [%d/%d]' % (score, total_points))

def read_log_filename(i):
    return(log_filename_prefix + f'_test_{i}.read.log')

def spawn_and_log(cmd, i, last_p=None, test_result=None):
    p = pexpect.spawnu(cmd, timeout=1)
    if last_p is None: 
        rf_path = read_log_filename(i)
        sf_path = log_filename_prefix + '_test_%d.send.log' % i
        clear_files([rf_path, sf_path])
        rf = open(rf_path, 'w')
        sf = open(sf_path, 'w')
        if test_result is not None:
            for f in [rf, sf]:
                f.write(test_result.description + '\n')
                f.flush()
    else:
        rf = last_p.logfile_read
        sf = last_p.logfile_send
    p.logfile_read = rf
    p.logfile_send = sf

    # log the command
    for f in [rf, sf]:
      f.write(cmd + '\n')
      f.flush()

    return(p)

catch_test_exception = True
continue_on_failure = False

def run_and_log_tests(test_tuples, test_results, log_filename_prefix, ff_path, time_test_result=None):
    for (test, test_result, test_spawn, is_closure) in test_tuples:
        print(f'Running test {test_result.test_number}...')
        if not is_closure:
            def f():
                p = spawn_and_log(test_spawn, test_result.test_number, test_result=test_result)

                if time_test_result is None:
                    test(p, test_result) 
                else:
                    test(p, test_result, time_test_result) 
        else:
            def f():
                test()

        if catch_test_exception:
            try:
                f()
            except Exception as e:
                error_path = read_log_filename(test_result.test_number)
                print('Test %d failed, logging full error to %s , continuing...' % (test_result.test_number,error_path))
                with open(error_path, 'a') as error_file:
                    test_result.outs.append(error_file)
                    test_result.log()
                    test_result.outs.remove(error_file)
                test_result.succeeded = False
                if not continue_on_failure: break
        else:
            f()

    log_test_results(ff_path, test_results)

def is_sorted(l):
    return(all(l[i] <= l[i+1] for i in range(len(l)-1)))

def random_hex_string(nibbles):
    return(''.join([random.choice(string.hexdigits) for _ in range(0,nibbles)]))

def random_decimal_string(n):
    return(''.join([random.choice(string.digits) for _ in range(0,n)]))

bin_digits = ['0', '1']

def is0(c): return(c == '0')
def is1(c): return(c == '1')

def random_bin_digit(): return(random.choice(bin_digits))
def random_bin_digits(n): return(''.join([random_bin_digit() for _ in range(0,n)]))
def random_n_m_bin_s(n,m): return(''.join(random_interleave_2_lists(n, m, ['0'], ['1'])))
def random_1_prefixed_bin_digits(n): return('1' + random_bin_digits(n-1))

def str_n_cs(n,c): return(''.join([c for _ in range(0,n)])) 
def str_n_1s(n): return(str_n_cs(n,'1'))
def str_n_0s(n): return(str_n_cs(n,'0'))

def max_signed_integer(bits):
    return(2**(bits-1)-1)

def min_signed_integer(bits):
    return(-(2**(bits-1)))

max_signed_int = max_signed_integer(32)
min_signed_int = min_signed_integer(32)

def get_bits_s(i, n_bits):
    bits_s = bin(i)
    lower_bits = bits_s[3:] if bits_s[0] == '-' else bits_s[2:]
    n_leading_0s = n_bits - len(lower_bits) 
    leading_0s = n_leading_0s * '0'
    return(leading_0s + lower_bits)

def overflow(i, n_bits):
    return (i % (1 << n_bits))

def signed_to_unsigned(i, n_bits):
    return(x_to_y(overflow(i, n_bits), n_bits, base_sign=1))
    
def unsigned_to_signed(i, n_bits):
    return(x_to_y(overflow(i, n_bits), n_bits, base_sign=-1))

def x_to_y(i, n_bits, base_sign=-1):
    bits_s = get_bits_s(i, n_bits)
    y_int = i
    if bits_s[0] == '1':
        base = base_sign * (2**(n_bits-1))
        lower_bits_i = int(bits_s[1:], 2) 
        y_int = base + lower_bits_i
    return(y_int)

#def overflow_and_re_sign(i, n_bits):
#    return(unsigned_to_signed(overflow_to_unsigned(i, n_bits), n_bits))

def random_int(mx=None): 
    return(random.randrange(min_signed_int, mx+1 if mx is not None else max_signed_int+1))

def bits_s_to_hex_s(bits_s): return(hex(int(bits_s, 2))[2:])

def random_interleave_2_lists(n_a, n_b, chars_a, chars_b):
    a_chars = [random.choice(chars_a) for i in range(0,n_a)]
    b_chars = [random.choice(chars_b) for i in range(0,n_b)]
    nonempty = []
    if a_chars:
        nonempty.append(a_chars)
    if b_chars:
        nonempty.append(b_chars)
    chars = []
    for i in range(0,n_a+n_b):
        cs = random.choice(nonempty)
        c = cs.pop()
        chars.append(c)
        if not cs:
            nonempty.remove(cs)
    return(chars)

non_hex_letters = list(set(string.ascii_letters) - set(string.hexdigits))

def random_invalid_hex_string(n_characters):
    # at least one valid hex char, at least one invalid
    n_non_hex_chars = random.randrange(1,n_characters)
    n_hex_chars = n_characters - n_non_hex_chars
    chars = random_interleave_2_lists(n_non_hex_chars, n_hex_chars, non_hex_letters, string.hexdigits)
    return(''.join(chars))

def random_string(n_characters):
    return(''.join([random.choice(string.ascii_letters) for _ in range(0,n_characters)]))

def avoid_range(bottom, top, x, test_result):
    if(bottom >= top):
        test_result.fail_append(f'bottom ({bottom}) >= top ({top}), bad call to avoid_range, failing')
    if(x >= bottom and x <= top):
        return(x + (top - bottom + 1))
    else:
        return(x)

def build_test_i(i, test_result, time_test_result=None):
    # inspect magic from https://stackoverflow.com/questions/1095543/get-name-of-calling-functions-module-in-python
    frame = inspect.stack()[1]
    module = inspect.getmodule(frame[0])
    return(getattr(module, 'build_test_' + str(i))(test_result, time_test_result=time_test_result))

def parse_arguments(assignment_number):
    parser = argparse.ArgumentParser(description=f'Run an automated test suite that builds and grades Assignment {str(assignment_number)} for CS201.')
    parser.add_argument('--continueonfailure', help='continue running other tests after the first failure, instead of aborting', action='store_true')

    args = parser.parse_args()
    print(f'continueonfailure: {str(args.continueonfailure)}')
    sys.modules[__name__].continue_on_failure = args.continueonfailure