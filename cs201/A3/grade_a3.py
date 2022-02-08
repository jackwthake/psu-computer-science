#!/usr/bin/env python3

'''This program runs required tests for Assignment 3 for CS201

    Copyright (c) 2021, Ted Cooper <ted.r.cooper@gmail.com>
    Licensed under GPLv3: https://www.gnu.org/licenses/gpl-3.0.txt
'''

from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals

import code
import math
import os
import pexpect
import random
import re
import string
import sys
import time

from grading_common import TestResult, avoid_range, bits_s_to_hex_s, clear_files, is0, is1, is_sorted, log_filename_prefix, random_1_prefixed_bin_digits, random_bin_digit, random_bin_digits, random_hex_string, random_interleave_2_lists, random_invalid_hex_string, random_n_m_bin_s, run_and_log_tests, spawn_and_log, str_n_1s, str_n_0s
import grading_common

n_runs = 30

def build_test_1(test_result):
    def f():
        # test with no arguments
        cmd = './fp_parse'
        p = spawn_and_log(cmd, 1, test_result=test_result)
        regex = r'.*'
        p.expect(regex) # don't care what the error output is, don't even try to capture it.
                        # if we try to capture the output, we force students to produce output,
                        # which is not required by the assignment.
        p.wait()
        p.close()
        if(p.exitstatus == 0):
            test_result.fail_append('fp_parse succeeded (had a 0 exit status) despite no arguments.', command=cmd, output=p.after)
        test_result.succeed()

    return(f)

def build_test_2(test_result):
    def f():
        last_p = None
        for i in range(0,n_runs):
            # test with invalid frac_bits
            frac_bits=avoid_range(2, 10, random.randrange(-50, 50), test_result)
            cmd = f'./fp_parse {str(frac_bits)} 4 33f'
            p = spawn_and_log(cmd, 2, last_p=last_p, test_result=test_result)
            last_p = p
            p.expect(r'.*') # don't care what the error output is, just check the code
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('fp_parse succeeded (had exit status 0) despite invalid frac_bits.', command=cmd)
        test_result.succeed()

    return(f)

def build_test_3(test_result):
    def f():
        last_p = None
        for i in range(0,n_runs):
            # test with invalid exp_bits
            exp_bits=avoid_range(3, 5, random.randrange(-50, 50), test_result)
            cmd = f'./fp_parse 4 {str(exp_bits)} 33f'
            p = spawn_and_log(cmd, 3, last_p=last_p, test_result=test_result)
            last_p = p
            p.expect(r'.*') # don't care what the error output is, just check the code
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('fp_parse succeeded (had exit status 0) despite invalid exp_bits.', command=cmd)
        test_result.succeed()

    return(f)

def random_good_exp_bits():
    return(random.randrange(3,6))

def random_good_frac_bits():
    return(random.randrange(2,11))

def bits_total(frac_bits, exp_bits):
    return(1 + frac_bits + exp_bits)

def bits_to_nibbles(bits):
    return(math.ceil(bits/4.0))

def build_test_4(test_result):
    def f():
        last_p = None
        for i in range(0,n_runs):
            # test with invalid exp_bits
            frac_bits=random_good_frac_bits()
            exp_bits=random_good_exp_bits()
            bits = bits_total(frac_bits,exp_bits)
            too_many_bits = bits + random.randrange(1,8)
            too_many_bits_s = random_1_prefixed_bin_digits(too_many_bits)
            too_long_hex_s = bits_s_to_hex_s(too_many_bits_s)
            cmd = f'./fp_parse {str(frac_bits)} {str(exp_bits)} {too_long_hex_s}'
            p = spawn_and_log(cmd, 4, last_p=last_p, test_result=test_result)
            last_p = p
            p.expect(r'.*') # don't care what the error output is, just check the exit code
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('fp_parse succeeded (had exit status 0) despite too long hex number.', command=cmd)
        test_result.succeed()

    return(f)

def build_test_5(test_result):
    def f():
        last_p = None
        for i in range(0,n_runs):
            # test with invalid exp_bits
            frac_bits=random_good_frac_bits()
            exp_bits=random_good_exp_bits()
            bits = bits_total(frac_bits,exp_bits)
            # make the input string the correct length (too-long is tested in
            # test 4), just with one or more invalid characters
            nibbles = bits_to_nibbles(bits)
            invalid_hex_string = random_invalid_hex_string(nibbles)
            cmd = f'./fp_parse {str(frac_bits)} {str(exp_bits)} {invalid_hex_string}'
            p = spawn_and_log(cmd, 5, last_p=last_p, test_result=test_result)
            last_p = p
            p.expect(r'.*') # don't care what the error output is, just check the code
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('fp_parse succeeded (had exit code 0) despite invalid hex number.', command=cmd)
        test_result.succeed()

    return(f)

def random_ieee754_hex_string_and_value(n_exp_bits, n_frac_bits, sign_bit=None, norm_or_denorm=False, only_norm=False, only_denorm=False, only_inf=False, only_nan=False, any_case=False, only_zero=False):
    if sign_bit is None:
        sign_s = random_bin_digit()
        sign_bit = int(sign_s,2)
    else:
        sign_s = str(sign_bit)

    if norm_or_denorm:
        # ensure that exp not all 1s
        n_zero_bits = random.randrange(1,n_exp_bits+1)
        n_one_bits = n_exp_bits - n_zero_bits
        exp_bits = random_n_m_bin_s(n_zero_bits, n_one_bits)
        frac_bits = random_bin_digits(n_frac_bits)
    elif only_norm:
        # ensure that exp not all 0s or all 1s
        n_zero_bits = random.randrange(1,n_exp_bits)
        n_one_bits = n_exp_bits - n_zero_bits
        exp_bits = random_n_m_bin_s(n_zero_bits, n_one_bits)
        frac_bits = random_bin_digits(n_frac_bits)
    elif only_denorm:
        exp_bits = str_n_0s(n_exp_bits)
        frac_bits = random_bin_digits(n_frac_bits)
    elif only_inf:
        exp_bits = str_n_1s(n_exp_bits)
        frac_bits = str_n_0s(n_frac_bits)
    elif only_nan:
        exp_bits = str_n_1s(n_exp_bits)
        # ensure that frac not all 0s
        n_one_bits = random.randrange(1,n_exp_bits+1)
        n_zero_bits = n_frac_bits - n_one_bits
        frac_bits = random_n_m_bin_s(n_zero_bits, n_one_bits)
    elif any_case:
        exp_bits = random_bin_digits(n_exp_bits)
        frac_bits = random_bin_digits(n_frac_bits)
    elif only_zero:
        exp_bits = str_n_0s(n_exp_bits)
        frac_bits = str_n_0s(n_frac_bits)
    
    #print(f'bits_s types: {type(sign_s)} {type(exp_bits)} {type(frac_bits)}')
    bits_s = sign_s + exp_bits + frac_bits
    hex_s = bits_s_to_hex_s(bits_s)

    def add_up_frac(bits):
        v = 1.0/2.0
        f = 0.0;
        for b in bits:
            if(b == '1'):
                f = f + v
            v = v / 2.0
        return(f)

    bias = 2.0**float(n_exp_bits - 1) - 1.0

    def sign_of(sign_bit): return('+' if sign_bit == 0 else '-')
    def render_float(f): return('%.6f' % f)

    # compute floating point number
    if all(map(is0,exp_bits)): 
        # denormalized
        #print('generated denormalized')
        big_M = add_up_frac(frac_bits)
        big_E = 1.0 - bias
        result_float = (-1.0 if sign_bit == 1 else 1.0) * big_M * 2.0**big_E
        result_s = render_float(result_float)
    elif all(map(is1,exp_bits)):
        if all(map(is0,frac_bits)):
            # inf
            result_s = sign_of(sign_bit) + 'inf'
        else:
            # NaN
            result_s = 'NaN'
    else:
        # normalized number, exp_bits is neither all 0s nor all 1s
        #print('generated normalized')
        big_M = 1.0 + add_up_frac(frac_bits)
        exp = int(exp_bits,2)
        exp_f = float(exp)
        big_E = exp_f - bias
        #print(f'exp_bits: {exp_bits}, exp: {exp}, exp_f: {exp_f}, bias: {bias}, big_E: {big_E}')
        result_float = (-1.0 if sign_bit == 1 else 1.0) * big_M * 2.0**big_E
        result_s = render_float(result_float)

    return(result_s,hex_s)

def build_valid_float_result_handler(validfloat_s):
    def f(test_result, cmd, p, value_s, hex_s):
        def wrong_exit_status_message_f(exitstatus):
            return(f'fp_parse exited with a failure code despite valid {validfloat_s} hex number.')
        def wrong_value_message_f(output_value_s, ovs_stripped, vs_stripped):
            return(f'for hex input {hex_s} , fp_parse did not print expected valid {validfloat_s} hex number {value_s} (stripped: {vs_stripped}), printed {output_value_s} (stripped: {ovs_stripped}) instead.')
        return(expected_exit_status_result_handler(test_result, cmd, p, value_s, hex_s, 0, wrong_exit_status_message_f, wrong_value_message_f))
    return(f)

def expected_exit_status_result_handler(test_result, cmd, p, value_s, hex_s, expected_exit_status, wrong_exit_status_message_f, wrong_value_message_f):
    try:
        p.expect(r'(.+)') 
    except Exception as e:
        test_result.fail_append("fp_parse didn't produce any output.", command=cmd, exception=e)
    p.wait()
    p.close()
    output=p.after
    if(p.exitstatus != expected_exit_status):
        test_result.fail_append(wrong_exit_status_message_f(p.exitstatus), command=cmd, output=output)
    output_value_s = p.match.groups()[0].rstrip(string.whitespace)
    ovs_stripped = output_value_s.rstrip('0\n') 
    vs_stripped = value_s.rstrip('0\n')
    if(ovs_stripped != vs_stripped):
        test_result.fail_append(wrong_value_message_f(output_value_s, ovs_stripped, vs_stripped), command=cmd, output=output)

def build_valid_float_test(test_result, test_n, result_handler, sign_bit=None, norm_or_denorm=False, only_norm=False, only_denorm=False, only_inf=False, only_nan=False, any_case=False, only_zero=False):
    def f():
        last_p = None
        for i in range(0,n_runs):
            # test with invalid exp_bits
            frac_bits=random_good_frac_bits()
            exp_bits=random_good_exp_bits()
            bits = bits_total(frac_bits,exp_bits)
            (value_s, hex_s) = random_ieee754_hex_string_and_value(exp_bits, frac_bits, sign_bit=sign_bit, norm_or_denorm=norm_or_denorm, only_norm=only_norm, only_denorm=only_denorm, only_inf=only_inf, only_nan=only_nan, any_case=any_case, only_zero=only_zero)
            cmd = f'./fp_parse {str(frac_bits)} {str(exp_bits)} {hex_s}'
            p = spawn_and_log(cmd, test_n, last_p=last_p, test_result=test_result)
            last_p = p
            result_handler(test_result, cmd, p, value_s, hex_s)
        test_result.succeed()
    return(f)

def build_test_6(test_result):
    result_handler = build_valid_float_result_handler('negative normalized or denormalized')
    return(build_valid_float_test(test_result, 6, result_handler, sign_bit=1, norm_or_denorm=True))

def build_test_7(test_result):
    result_handler = build_valid_float_result_handler('positive normalized or denormalized')
    return(build_valid_float_test(test_result, 7, result_handler, sign_bit=0, norm_or_denorm=True))

def build_test_8(test_result):
    result_handler = build_valid_float_result_handler('NaN')
    return(build_valid_float_test(test_result, 8, result_handler, only_nan=True))

def build_test_9(test_result):
    result_handler = build_valid_float_result_handler('+inf')
    return(build_valid_float_test(test_result, 9, result_handler, sign_bit=0, only_inf=True))

def build_test_10(test_result):
    result_handler = build_valid_float_result_handler('-inf')
    return(build_valid_float_test(test_result, 10, result_handler, sign_bit=1, only_inf=True))

def build_test_11(test_result):
    result_handler = build_valid_float_result_handler('+0')
    return(build_valid_float_test(test_result, 11, result_handler, sign_bit=0, only_zero=True))

def build_test_12(test_result):
    result_handler = build_valid_float_result_handler('-0')
    return(build_valid_float_test(test_result, 12, result_handler, sign_bit=1, only_zero=True))

def main():
    grading_common.parse_arguments(3)

    os.system('rm -f fp_parse *.log feedback.txt && make')
    if not os.path.exists('fp_parse'):
        print('make didn\'t work (can\'t find a file called fp_parse), failing', file=sys.stderr)
        sys.exit(1)

    ff_path = 'feedback.txt'
    clear_files([ff_path])
    ff = open(ff_path, 'w')

    test_1_result = TestResult('No arguments.', 2, ff, test_number=1)
    test_2_result = TestResult('Invalid number of fraction bits.', 2, ff, test_number=2)
    test_3_result = TestResult('Invalid number of exponent bits.', 2, ff, test_number=3)
    test_4_result = TestResult('Correct values for exponent and '
                             + 'fraction bits but number itself '
                             + 'contains too many bits.'         , 2, ff, test_number=4)
    test_5_result = TestResult('Correct values for exponent and fraction bit but 3rd argument is not a valid hexadecimal number.', 2, ff, test_number=5)
    test_6_result = TestResult('Correct input, yielding a negative number.', 2, ff, test_number=6)
    test_7_result = TestResult('Correct input, yielding a positive number.', 2, ff, test_number=7)
    test_8_result = TestResult('Correct input, yielding NaN.', 2, ff, test_number=8)
    test_9_result = TestResult('Correct input, yielding +inf.', 2, ff, test_number=9)
    test_10_result = TestResult('Correct input, yielding -inf.', 2, ff, test_number=10)
    test_11_result = TestResult('Correct input, yielding a positive zero.', 2, ff, test_number=11)
    test_12_result = TestResult('Correct input, yielding a negative zero.', 2, ff, test_number=12)

    tests = [ build_test_1(test_1_result)
            , build_test_2(test_2_result)
            , build_test_3(test_3_result)
            , build_test_4(test_4_result)
            , build_test_5(test_5_result)
            , build_test_6(test_6_result)
            , build_test_7(test_7_result)
            , build_test_8(test_8_result)
            , build_test_9(test_9_result)
            , build_test_10(test_10_result)
            , build_test_11(test_11_result)
            , build_test_12(test_12_result) ]
    test_spawns = [None for _ in range(0,len(tests))]
    test_results = [ test_1_result
                   , test_2_result
                   , test_3_result
                   , test_4_result
                   , test_5_result
                   , test_6_result
                   , test_7_result
                   , test_8_result
                   , test_9_result
                   , test_10_result
                   , test_11_result
                   , test_12_result ]
    test_is_closures = [True for _ in range(0,len(tests))]
    test_tuples = list(zip(tests, test_results, test_spawns, test_is_closures))

    run_and_log_tests(test_tuples, test_results, log_filename_prefix, ff_path)

if __name__ == '__main__':
    main()
