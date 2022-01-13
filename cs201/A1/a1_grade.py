#!/usr/bin/env python3

'''This program runs required tests for Assignment 1 for CS201

    Copyright (c) 2021, Ted Cooper <ted.r.cooper@gmail.com>
    Licensed under GPLv3: https://www.gnu.org/licenses/gpl-3.0.txt
'''

from __future__ import absolute_import
from __future__ import print_function
from __future__ import unicode_literals

import os
import pexpect
import random
import re
import string
import sys
import time

from grading_common import TestResult, clear_files, run_and_log_tests

import __main__
(log_filename_prefix, _) = os.path.splitext(__main__.__file__)

encoding = sys.stdout.encoding
n_words = 9

TIME_TOLERANCE = 0.5 # half a second
MIN_INPUT_LENGTH = 2
MAX_INPUT_LENGTH = 10
SLOW = False # turn this on to make sure seconds work (otherwise always 0)

re_flags = re.IGNORECASE | re.MULTILINE

def eat_top(p, test_result):
    r = re.compile('\s*This\s+is\s+a\s+game\s+that\s+tests\s+typing\s+speed\s+Type\s+the\s+following\s+words:\s*', flags=re_flags)
    try:
        p.expect(r)
    except Exception as e: 
        test_result.fail_append(f'Initial session output missing, expected output that matches this regular expression:\n{r.pattern}.', output=p.before, exception=e)

def parse_time(p, time_test_result):
    r = re.compile(r'\s*You\s+took\s+(\d+)\s+seconds\s+and\s+(\d+)\s+microseconds', flags=re_flags)
    try: 
        p.expect(r)
        return(p.match.groups())
    except Exception as e: 
        time_test_result.fail_append('Expected output similar to "You took 24 seconds and 857382 microseconds" at the end, and either didn\'t find it at all, or couldn\'t parse it.', output=p.before, exception=e)

def run_test(p, f, f_test_result, time_test_result):
    eat_top(p, f_test_result)
    t1 = time.time()
    x = f()
    (secs_s, usecs_s) = parse_time(p, time_test_result)
    t2 = time.time()

    secs = int(secs_s)
    usecs = int(usecs_s)
    inner_time = secs + (usecs / 1000000)
    outer_time = t2 - t1

    time_diff = abs(outer_time - inner_time)
    if(time_diff > TIME_TOLERANCE):
        time_test_result.fail_append(f'Difference between reported and observed time {str(time_diff)} is larger than tolerance {str(TIME_TOLERANCE)}, incorrect time calculation.', output=p.after)
    time_test_result.succeed()

def parse_word_line(p, test_result):
    if(SLOW): time.sleep(random.uniform(0,1))
    try: 
        r = re.compile(r'word #(\d+) is (\w+):', flags=re_flags)
        p.expect(r)
        (number_s, word) = p.match.groups()
        return((int(number_s), word))
    except Exception as e: 
        test_result.fail_append(f'Parsing word line failed.  Expected output matching this regex:\n{r.pattern}', output=p.before)

def f_until_False(number, word): return(False)
def f_until_the(number, word):
    if(word == 'the' or word == 'The'): return(True)
    else: return(False)

def f_id(x): return(x)

def run_word_lines_until(p, i, test_result, f_until, last_word='', last_number=0, f_word=f_id):
    number = last_number
    word = last_word
    for i in range(i,n_words+1):
        (number, word) = parse_word_line(p, test_result)
        if(word == last_word): test_result.fail_append('Word repeated despite correct input.', output=p.after)
        last_word = word
        if(number != last_number + 1): test_result.fail_append('Number doesn\'t follow sequence despite correct input (%d, should be %d).' % (number, last_number + 1), output=p.after)
        last_number = number
        if(f_until(number, word)): return((number, word))
        w = f_word(word)
        p.sendline(w)
        p.expect(w)
    return((number, word))

def finish_session_correctly(p, i, test_result, last_word='', last_number=0, f_word=f_id):
    run_word_lines_until(p, i, test_result, f_until_False, last_word=last_word, last_number=last_number, f_word=f_word)

    test_result.succeed()

def test_1(p, test_result, time_test_result):
    def f(): finish_session_correctly(p,1,test_result, last_word='', last_number=0)

    run_test(p, f, test_result, time_test_result)

def random_char():
    return(random.choice(string.ascii_letters))

def gen_not_partial_match(s):
    r=''
    l=random.randrange(MIN_INPUT_LENGTH, MAX_INPUT_LENGTH)
    while(len(r) < l):
        c = random_char()
        if(c not in s): r += c
    return(r)

def gen_prefix(s):
    return(s[:random.randrange(1,len(s)-1)])

def gen_prefixed(s):
    mx=random.randrange(len(s) + 1, MAX_INPUT_LENGTH)
    while(len(s) < mx):
        s += random_char()
    return(s)

def gen_other_the(s):
    if(s == 'The'):
        return('the')
    elif(s== 'the'):
        return('The')
    else:
        return(s)

def gen_space_prefixed(s):
    return(gen_prefixed(s + ' '))

def fail_then_succeed(p, test_result, f_word):
    (number1a, word1a) = parse_word_line(p, test_result)
    w = f_word(word1a)
    p.sendline(w)
    p.expect(w)
    (number1b, word1b) = parse_word_line(p, test_result)
    if(not (number1a == number1b and word1a == word1b)):
        test_result.fail_append(f'Expected repeated prompt after incorrect input, instead received number {str(number1a)} and word {word1a}, then number {str(number1b)} and word {word1b}', output=p.after)
    p.sendline(word1b)
    p.expect(word1b)
    finish_session_correctly(p, 2, test_result, last_word=word1b, last_number=int(number1b))
    test_result.succeed()

def test_2(p, test_result, time_test_result):
    def f(): fail_then_succeed(p, test_result, gen_not_partial_match)

    run_test(p, f, test_result, time_test_result)

def test_3(p, test_result, time_test_result):
    def f(): fail_then_succeed(p, test_result, gen_prefix)

    run_test(p, f, test_result, time_test_result)

def test_4(p, test_result, time_test_result):
    def f(): fail_then_succeed(p, test_result, gen_prefixed)

    run_test(p, f, test_result, time_test_result)

def test_5(p, test_result, time_test_result):
    def f():
        def handle_the(i, last_word, last_number):
            (numbera, worda) = run_word_lines_until(p, i, test_result, f_until_the, last_word=last_word, last_number=last_number)
            worda_ = gen_other_the(worda)
            p.sendline(worda_)
            p.expect(worda_)
            (numberb, wordb) = parse_word_line(p, test_result)
            if(numbera != numberb or worda != wordb): 
                test_result.fail_append(f'Expected repeated prompt after incorrect input, instead received number {str(numbera)} and word {worda}, then number {str(numberb)} and word {wordb}', output=p.after)
            p.sendline(wordb)
            p.expect(wordb)
            return((numberb, wordb))
        (numbera, worda) = handle_the(1, '', 0)
        (numberb, wordb) = handle_the(numbera+1, worda, numbera)
        finish_session_correctly(p, numberb+1, test_result, last_word=wordb, last_number=numberb)
        test_result.succeed()

    run_test(p, f, test_result, time_test_result)

def test_6(p, test_result, time_test_result):
    def f(): finish_session_correctly(p, 1, test_result, f_word=gen_space_prefixed)

    run_test(p, f, test_result, time_test_result)

def main():
    os.system('rm -f typing_word_game *.log feedback.txt && make')
    if not os.path.exists('typing_word_game'):
        print('make didn\'t work (can\'t find typing_word_game), failing', file=sys.stderr)
        sys.exit(1)

    ff_path = 'feedback.txt'
    clear_files([ff_path])
    ff = open(ff_path, 'w')

    inner_test_results = [
          TestResult('Example run showing all correct input.', 5, ff, test_number=1)
        , TestResult('Example run showing misspellings that do not partially match the correct word.', 4, ff, test_number=2)
        , TestResult('Example run showing a misspelling where only the first part of the word is typed. For example, entering "brow" when "brown" is displayed.', 4, ff, test_number=3)
        , TestResult('Example run showing a misspelling where the correct word is typed but additional characters are entered. For example, "lazyman" when "lazy" is typed.', 4, ff, test_number=4)
        , TestResult('Example run showing that comparisons are correctly performed. The only test here is to show that when "the" is displayed that "The" does not match and when "The" is displayed that "the" does not match.', 4, ff, test_number=5)
        , TestResult('Example run showing that extraneous input is flushed per the provided hint. For example, if the user enters "lazy dog", then only "lazy" should be used for comparison and " dog" is thrown away.', 4, ff, test_number=6) ]
    time_test_result = TestResult('Timing calculation correct.', 2, ff, test_number=0)
    test_results = [ time_test_result ] + inner_test_results
    n_tests = len(test_results)

    tests = [test_1, test_2, test_3, test_4, test_5, test_6]
    test_tuples = list(zip(tests, inner_test_results, ['./typing_word_game' for _ in range(0,len(tests))],[False for _ in range(0,len(tests))]))

    #tests = [test_6]
    #inner_test_results = [test_6_result]
    #test_tuples = list(zip(range(6,len(tests)+6), tests, inner_test_results))
    
    run_and_log_tests(test_tuples, test_results, log_filename_prefix, ff_path, time_test_result=time_test_result)

if __name__ == "__main__":
    main()