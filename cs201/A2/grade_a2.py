#!/usr/bin/env python3

'''This program runs required tests for Assignment 2 for CS201

    Copyright (c) 2021, Ted Cooper <ted.r.cooper@gmail.com>
    Licensed under GPLv3: https://www.gnu.org/licenses/gpl-3.0.txt
'''

from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals

import code
import os
import pexpect
import random
import re
import string
import sys
import time

from grading_common import TestResult, clear_files, is_sorted, log_filename_prefix, run_and_log_tests, spawn_and_log
import grading_common

executables = ['setBits', 'showBits']

executables_built = []

TEST_SHOWBITS_ARG_PARSING = False

def build_test_1(test_result):
    def f():
        # clean up so we know we're building anew
        p = spawn_and_log('make clean', 1, test_result=test_result)
        #p.expect_exact('rm -f ' + ' '.join([x for x in executables]) + '  *.o ~* a.out')
        p.expect(r'.+')
        p.wait()
        p.close()
        if(p.exitstatus != 0):
            test_result.fail_append('make clean didn\'t exit successfully (code %s, signal status %s)' % (str(p.exitstatus), str(p.signalstatus)))
        for x in executables:
          if os.path.exists(x):
              test_result.fail_append('make clean didn\'t work (%s is present, should be absent)' % x)

        # build this executable, and check that the file was generated
        p = spawn_and_log('make', 1, last_p=p)
        p.expect(r'.+')
        #for x in executables:
        #    p.expect(r'.+gcc\s+[\w -]+\s+' + x + '.c -o ' + x)
        p.wait()
        p.close()
        if(p.exitstatus != 0):
            test_result.fail_append('make didn\'t exit successfully (exit with status 0).')
        an_executable_was_built = False
        for x in executables:
            if os.path.exists(x):
                an_executable_was_built = True
                executables_built.append(x)
        if not an_executable_was_built: 
            test_result.fail_append('make didn\'t produce an expected executable (%s is absent, should be present)' % x)

        test_result.succeed()

    return(f)

def cmd_args(cmd, args):
    return(cmd + ' ' + ' '.join(args))

def setBits_cmd(args):
    return(cmd_args('./setBits', args))

def build_setBits_test_2(test_result):
    def f():
        if 'setBits' not in executables_built:
            return()
        last_p = None
        l0=''
        l1=str(random.randrange(16, 3001))
        l2=str(random.randrange(-3000, 0))
        for bad_input in [l0, l1, l2]:
            cmd = setBits_cmd([bad_input])
            p = spawn_and_log(cmd, 2, last_p=last_p, test_result=test_result)
            last_p = p
            # assume some error message is printed. this will break if there is
            # no output (but using .* doesn't appear to do maximal munch in
            # this context, so we don't eat any output if we just use .*)
            p.expect(r'.+')
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('setBits didn\'t fail (exit with a non-zero code) on bad input.', command=cmd)

        test_result.succeed()

    return(f)

n_good_test_runs = 20

def random_good_setBits_input():
    return(str(random.randrange(1,16)))

def build_setBits_test_3(test_result):
    def f():
        if 'setBits' not in executables_built:
            return()
        last_p = None
        for j in range(0,n_good_test_runs):
            n_inputs = random.randrange(1, 17)
            inputs = []
            for k in range(0,n_inputs):
                # not worrying about uniqueness for the moment, code should be
                # robust when presented with non-unique inputs
                inputs.append(random_good_setBits_input())
            inputs_set = set(inputs)
            expected_output = ''
            idxs = list(range(0,16))
            idxs.reverse()
            for k in idxs:
                kS = str(k)
                expected_output += '1' if kS in inputs_set else '0'
                if k > 0 and k % 4 == 0:
                    expected_output += ' '
            
            cmd = setBits_cmd(inputs)
            p = spawn_and_log(cmd, 3, last_p=last_p, test_result=test_result)
            last_p = p
            try:
                # allow but do not require a trailing space
                p.expect(expected_output + r' *')
                p.wait()
                p.close()
            except Exception as e:
                test_result.fail_append(f'For good input, setBits did not produce expected output:\n{expected_output}', output=p.before, exception=e, command=cmd)
            if(p.exitstatus != 0):
                test_result.fail_append('For good input, setBits failed (had a non-zero exit status).', command=cmd)

        test_result.succeed()

    return(f)

MIN_INT32 = -2147483648
MAX_INT32 = 2147483647

def random_good_showBits_input():
    return(random.randrange(MIN_INT32,MAX_INT32+1))

def random_bad_showBits_input():
    return(str(random.randrange(MIN_INT32,MAX_INT32+1)) + 
            ''.join([random.choice(string.ascii_letters) for _ in range(1,5)]))

def showBits_cmd(args):
    return(cmd_args('./showBits', args))

def build_showBits_test_4(test_result):
    def f():
        if 'showBits' not in executables_built:
            return()
        last_p = None
        # should fail without args
        cmd = showBits_cmd([])
        p = spawn_and_log(cmd, 4, last_p=last_p, test_result=test_result)
        last_p = p
        # assume there is an error message, see comment above
        p.expect(r'.+')
        p.wait()
        p.close()
        if(p.exitstatus == 0):
            test_result.fail_append('showBits succeeded (had exit code 0) on empty input, but should have failed (had non-zero exit code).', command=cmd)

        # should fail with one arg
        cmd = showBits_cmd([hex(random_good_showBits_input())])
        p = spawn_and_log(cmd, 4, last_p=last_p)
        last_p = p
        # assume there is an error message, see comment above
        p.expect(r'.+')
        p.wait()
        p.close()
        if(p.exitstatus == 0):
            test_result.fail_append('showBits succeeded (had exit code 0) with only one input, but should have failed (had non-zero exit code).', command=cmd)

        if TEST_SHOWBITS_ARG_PARSING:
            # should fail with one good arg and one bad arg
            cmd = showBits_cmd([hex(random_good_showBits_input()), random_bad_showBits_input()])
            p = spawn_and_log(cmd, 4, last_p=last_p)
            last_p = p
            # assume there is an error message, see comment above
            p.expect(r'.+')
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('showBits succeeded (had exit code 0) with one good input and one bad input, but should ahve failed (had non-zero exit code).', command=cmd)

            # should fail with one bad arg and one good arg (order flipped from above)
            cmd = showBits_cmd([random_bad_showBits_input(), hex(random_good_showBits_input())])
            p = spawn_and_log(cmd, 4, last_p=last_p)
            last_p = p
            # assume there is an error message, see comment above
            p.expect(r'.+')
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('showBits succeeded (had exit code 0) with one bad input and one good input, but should have failed (had non-zero exit code).', command=cmd)

            # should fail with two bad args
            cmd = showBits_cmd([random_bad_showBits_input(), random_bad_showBits_input()])
            p = spawn_and_log(cmd, 4, last_p=last_p)
            last_p = p
            # assume there is an error message, see comment above
            p.expect(r'.+')
            p.wait()
            p.close()
            if(p.exitstatus == 0):
                test_result.fail_append('showBits succeeded (had exit code 0) with two bad inputs, but should have failed (had non-zero exit code).', command=cmd)

        # should fail with three good args
        cmd = showBits_cmd([hex(random_good_showBits_input()), hex(random_good_showBits_input()), hex(random_good_showBits_input())])
        p = spawn_and_log(cmd, 4, last_p=last_p)
        last_p = p
        # assume there is an error message, see comment above
        p.expect(r'.+')
        p.wait()
        p.close()
        if(p.exitstatus == 0):
            test_result.fail_append('showBits succeeded (had exit code 0) with three good inputs, but should have failed (had non-zero exit code).', command=cmd)

        test_result.succeed()

    return(f)

def build_showBits_test_5(test_result):
    def f():
        if 'showBits' not in executables_built:
            return()
        last_p = None
        for j in range(0, n_good_test_runs):
            # should succeed with two good args
            if j == 0:
                i1 = 0
                i2 = 0
            else:
                i1 = random_good_showBits_input()
                i2 = random_good_showBits_input()
            i1S = hex(i1)
            i2S = hex(i2)
            cmd = showBits_cmd([i1S, i2S])
            p = spawn_and_log(cmd, 5, last_p=last_p, test_result=test_result)
            last_p = p
            # assume there is an error message, see comment above
            # example output: Bits 8,10,14,16,23,25, in common. Hexadecimal: 2814500, Signed: 42026240, Unsigned: 42026240. 
            v = i1 & i2
            # why did I do this?
            #bits_pattern = r'.*\s*Bits ([0-9,]*) in common\.\s+' if v != 0 else r'[^.]+\.\s+'
            #bits_pattern = r'.*\s*Bits\s+((?:[0-9]{1,2},)*)\s+in common\.\s+' if v != 0 else r'.*\s*Bits\s+in common\.\s+'
            bits_pattern = r'.*\s*Bits\s+((?:[0-9]{1,2},)*)\s+in common\.\s+' if v!= 0 else r'.*\s*Bits\s+in common\.\s+'
            try:
                p.expect(bits_pattern)
            except Exception as e:
                test_result.fail_append(f'For good input, showBits did not produce expected output matching regular expression:\n{bits_pattern}', output=p.before, exception=e, command=cmd)
            output1 = p.after
            if v != 0:
                bit_listS = p.match.groups()[0]
            regex = r'Hexadecimal: ([a-fA-F0-9-]+),\s+Signed: ([0-9-]+),\s+Unsigned: (\d+)\.'
            try:
                p.expect(regex)
            except Exception as e:
                test_result.fail_append(f'For good input, setBits did not produce expected output matching regular expression:\n{regex}', output=p.before, exception=e, command=cmd)

            (hexS, signedS, unsignedS) = p.match.groups()

            p.close()
            output2 = p.after
            output = output1 + output2

            if v != 0:
              # check Bits
              bitS_list = bit_listS.split(',')
              if bitS_list[-1] == '':
                  del(bitS_list[-1])
              bit_list = [int(s) for s in bitS_list]
              if not is_sorted(bit_list):
                  test_result.fail_append('showBits didn\'t print out bits in order.', command=cmd, output=output)

              expected_bit_list = []
              for k in range(0,32):
                  if v & (1 << k):
                      expected_bit_list.append(k)
              if bit_list != expected_bit_list:
                  expected_bits_s = ','.join([str(l) for l in expected_bit_list]) + ','
                  #test_result.fail_append(f'expected showBits to print out these bits:\n{expected_bits_s}', command=cmd, output=bit_listS)
                  test_result.fail_append(f'Expected showBits to print out these bits:\n{expected_bits_s}', command=cmd, output=output)

            # check Unsigned
            expected_unsigned = v + ((1 << 32) if v < 0 else 0)
            expected_unsignedS = str(expected_unsigned)
            if expected_unsignedS != unsignedS:
                test_result.fail_append(f'Expected showBits to print out unsigned {expected_unsignedS} but it printed unsigned {unsignedS}', command=cmd, output=output)

            # check Hexadecimal
            # drop the leading optional - and 0x
            unstripped = hex(expected_unsigned)
            # removeprefix requires python3.9+
            #sign_stripped = unstripped.removeprefix('-')
            #expected_hexS = sign_stripped.removeprefix('0x')
            sign_stripped = unstripped[1:] if unstripped.startswith('-') else unstripped
            expected_hexS = sign_stripped[2:] if sign_stripped.startswith('0x') else sign_stripped
            if expected_hexS != hexS:
                test_result.fail_append('Expected showBits to print out '
                        + 'Hexadecimal %s but actual output was %s' % (expected_hexS, hexS), command=cmd, output=output)

            # check Signed
            expected_signedS = str(v)
            if expected_signedS != signedS:
                test_result.fail_append('Expected showBits to print out '
                        + 'Signed %s but actual output was %s' % (expected_signedS, signedS), command=cmd, output=output)

            if(p.exitstatus != 0):
                test_result.fail_append('showBits failed (had non-zero exit status) with two good inputs.', command=cmd, output=output)

        test_result.succeed()

    return(f)

def main():
    grading_common.parse_arguments(2)

    os.system('rm -f setBits showBits *.log feedback.txt && make')
    if not os.path.exists('setBits') and not os.path.exists('showBits'):
        print('make didn\'t work (can\'t find either setBits or showBits), failing', file=sys.stderr)
        sys.exit(1)

    ff_path = 'feedback.txt'
    clear_files([ff_path])
    ff = open(ff_path, 'w')

    test_1_result = TestResult('Example showing setBits and showBits being created using make command.', 2, ff, test_number=1)
    setBits_test_2_result = TestResult('Example run for setBits showing invalid input properly handled.', 3, ff, test_number=2)
    setBits_test_3_result = TestResult('At least 2 example runs for setBits showing correct output on valid input.', 6, ff, test_number=3)
    showBits_test_4_result = TestResult('Example run showBits showing invalid input properly handled.', 3, ff, test_number=4)
    showBits_test_5_result = TestResult('At least 2 example runs for showBits showing correct output on valid input.', 6, ff, test_number=5)

    tests = [build_test_1(test_1_result), build_setBits_test_2(setBits_test_2_result), build_setBits_test_3(setBits_test_3_result), build_showBits_test_4(showBits_test_4_result), build_showBits_test_5(showBits_test_5_result)]
    #test_spawns = ['bash', './setBits 16']
    test_spawns = [None, None, None, None, None]
    test_results = [test_1_result, setBits_test_2_result, setBits_test_3_result, showBits_test_4_result, showBits_test_5_result]
    test_is_closures = [True, True, True, True, True]
    test_tuples = list(zip(tests, test_results, test_spawns, test_is_closures))

    run_and_log_tests(test_tuples, test_results, log_filename_prefix, ff_path)

if __name__ == "__main__":
    main()