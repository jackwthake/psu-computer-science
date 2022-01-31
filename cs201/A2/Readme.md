# CS 201 Computer Systems Programming, A2 Bitwise Operators
- Original lab by markem, tweaked by naak. 
- Test suite by theod.

# Specification Introduction
This assignment will have students write two programs: showBits and setBits. Your programs will rely on bit operations (&, |, <<) for the majority of the work. For converting command line arguments to numbers for showBits use strtol() or strtoul() from the C library.

# Program Requirements
## General
- With the exception of argv[] for command line arguments, the use of arrays in any part of this lab will result in a score of zero for that part. The focus in on the bit level operators.
- Error checking, validation, return code checking, is still required. The user might be evil. The library might fail. 
- The test suite forms part of the specification. 

## setBits
- Your program will accept a list of integers in the range [0...15] and turn on the corresponding bits in an unsigned short to output a result that shows set membership. 
    1. For example, if you run "setBits 2 3 4" then your output will print 0000000000011100. 
- Your program must ensure that each integer is in the correct range. 
- If any integer is not in the correct range, an error message must be printed and the program aborted before displaying any results.

## showBits
- Your program will accept two hexadecimal 32-bit integers and display which bits the two numbers both have set to 1. 
- You will print the bit numbers (remember we count from 0) as well as the resulting number in hexadecimal, signed integer and unsigned integer formats. 
- You may assume that if the user gives you correct input, then the user gives you correct hexadecimal input but you may not assume that the correct number of program arguments (read about the argc argument to main()). 
    1. For example, if you run "showBits 0x0F 0x05" the output will be "Bits 0,2 in common. Hexadecimal: 5, Signed: 5, Unsigned: 5". 
    1.  For "showBits 0xFF00FF00" the output will be "Error: please provide two hexadecimal numbers as arguments to the program." and then the program will terminate.

# Make
- You are welcome to make your own, but you may use this one as a base. This one will require two C files, setBits.c and showBits.c 
- It must have at least a make and a clean.
- It must have the same flags as the example A1 (-Wall), etc
- You are welcome to add other commands, but it is at your own risk.
```
# A2 makefile example
# NOTE: All indented lines are indented with a tab character. This is required.
CC=gcc
CFLAGS=-Wall
DFLAGS=-g
PROGS= setBits showBits

all: $(PROGS)

%: %.c
        $(CC) $(CFLAGS) $(DFLAGS) $< -o $@

clean:
        rm -f $(PROGS) *.o ~*
```

# Hints and Suggestions
1. If you are seg faulting or stack smashing, your code is in a lot of trouble.
1. You will not need the math library, pow(), recursion, or arhimetic operators to solve. Your algorithm is to only use the operators
1. Solve these on paper and figure out your algorithm/approach first. Work with 4 bit examples. If you start coding before you've got the process figured out, things will not go well. 
1. Pay close attention to the documentation for printf/scanf. Remember that humans give patterns of bits meaning. 
1. Read the documentation for use strtol()/strtoul() carefully. Pay close attention to the parameters. 
1. atoi() is not safe. 
1. The reference solution is about ~35 lines per file. If either file is more than 100 LOC (excluding comments), you've gone off the rails somewhere. Bitwise operators are fast and compact. 
1. The new test suite flag might be useful to you. 


# Rubric
Your assignment will be graded according to this rubric. The maximum number of points is within brackets for each item. This assignment is worth 50 points. 

Bad coding practice may be additional deductions.

The grader will also run the test section and may use different input than the tests.

    [2] Assignment correctly submitted.
    [3] A valid make file provided.
    [2] Code is modular. Not all code is in main().
    [2] Code comments must be readable and understandable. Code must not be over commented. Only use comments where necessary. No blocks of unused code, even in comments.
    [2] setBits makes correct use of shift and logical operations, per assignment description.
    [3] setBits has correct checks for invalid input.
    [3] setBits prints results using appropriate shift and logical operations.
    [2] showBits makes correct use of shift and logical operations, per assignment description.
    [3] showBits has correct checks for invalid input.
    [3] showBits prints results using appropriate shift and logical operations.
    [3] Code correctly checks return codes.
    [2] Does not use non-secure versions of function calls.
    [20] Tests:
        [2] Example showing setBits and showBits being created using make command.
        [3] Example run for setBits showing invalid input properly handled.
        [6] At least 2 example runs for setBits showing correct output on valid input.
        [3] Example run showBits showing invalid input properly handled.
        [6] At least 2 example runs for showBits showing correct output on valid input.


# Grading Script

Grading scripts, for checking to ensure that your submission meets minimum stardards of execution are located in this directory. After downloading, use the command 
```
$ chmod +x *.py
``` 
to make both scripts executable. The file grading_common.py is required by all the grading scripts.

Copys the python script for the correct assignment, plus the python script grading_common.py, to your source code directory. Run the grading script for this assignment as:

```
make setBits
make showBits
./grade_a2.py
```

While testing you might find that one part has issues. You can ask the test suite to test as much as it can, by 
```
./grade_a2.py --continueonfailure 

```

If there are no errors, then you are ready to focus on the clean up and review of your code.


Note that the rubric contains other aspects of your program, such as style, that are graded in addition to the score of the grading script. Please run "make reallyclean" before making your zip file.
# Example Game Session (what the test suite is based on)
The test suite forms part of your specification. Pay careful attention to the spelling, formatting, and spacing. Computers are very literal.

```
% ls
Makefile  setBits.c  showBits.c

% make setBits
gcc -m32 -g -o setBits setBits.c

% ./setBits 3 13 8 14 15
1110 0001 0000 1000

% make showBits
gcc -m32 -g -o showBits showBits.c

% ./showBits 0xE0C874A3 0xD49157FF
Bits 0,1,5,7,10,12,14,23,30,31, in common. Hexadecimal: c08054a3, Signed: -1065331549, Unsigned: 3229635747.

% 
```

# Submission for A2
Same process as A1. 

Always doublecheck that your submission looks and behaves the way you expect on the CS Linux server (this is our 'production' environment).

1. For each program, you will submit your C source code (properly documented), header files, and Makefile. Do not include any binaries, test loigs, or non-necessary files with your submissions.
1. Zip file: Your electronic submission will be packaged as a zip file with your CS login name containing a single folder.
    - For example, suppose your CS login name is "john". Your zip file will be called "john.zip". 
    - Once the TA unzips the file, a directory "john/" will be created and your submitted material will be extracted to the directory "john". 
1. Submit assignment through the course Canvas site