# CS 201 Computer Systems Programming
# A4 Structs & Function Pointers
- Original lab by markem, tweaked by naak. 
- Test suite by theod.

# Specification Overview
The goal of this assignment is to bring together several concepts discussed in class; namely, program arguments, data conversion, C structures, and pointers to functions. Your assignment is to write a menu-based program that will perform operations on a list of program arguments based on the menu item selected by the user. In the shell (terminal), it should look like
```
The operations to be performed on those arguments will be based on the following menu:
0. 	Exit
1. 	Addition
2. 	Subtraction
3. 	Multiplication
4. 	Division
5. 	Modulo
6. 	Reverse Input
```

# Program Requirements
1. Your program will take up to 15 arguments.
1. You may assume that any numbers in the input are 32-bit integers in either decimal or hexadecimal format. 
    - That is, any hex numbers will begin with '0x' or '0X' and all other numbers are decimal. 
    - The output of mathematical operations will be in decimal. 
    - The C library routine strtol() will be very useful for this assignment. 
1. For addition, you will produce the value of the program arguments when summed from left to right on the command line. The input may be in decimal, hexadecimal or a combination. Numbers may be positive or negative.
1. For subtraction, you will produce the value of the program arguments when subtracted from left to right on the command line. The input may be in decimal, hexadecimal or a combination. Numbers may be positive or negative.
1. For multiplication, you will produce the product of the program arguments when processed from left to right on the command line. The input may be in decimal, hexadecimal or a combination. Numbers may be positive or negative.
1. For division, your program will only process the first two numbers on the command line. The result will be the first number divided by the second number. Note that the result could be a floating point number.
1. For modulo, your program will only process the first two numbers on the command line. The result will be the first number modulo (%) by the second number. Note that the result can only be an integer.
1. For reverse input, your program will print out the command line arguments in reverse. By this, we mean that is the command line is "./a4 one two three" then the output will be "eerht owt eno".
1. For an invalid menu number, a suitable error message should be printed and then the menu redisplayed. 
1. Your design must use function pointers and structs.
    - A struct containing only an array will not suffice. You may optionally use multiple types of structs, but at least struct must be present and contain at least two fields.
1. Your program must have a function for printing the menu. The function is required to accept a structure containing the number of items in the menu and the menu text.
1. Your program will not store the item number with the menu item text. This must be computed when the menu is displayed. e.g.: char *choices[] = {"Exit", "Addition", "Subtraction", "Multiplication", "Division", "Modulo", "Reverse Input"}; 
    - Note that you are not required to use this exact order, but you may optionally choose to.
1. Your program must have a function that implements each menu item. The individual functions are allowed to call other functions. 
    - The exception is menu item 0 (exit) which may optionally be handled differently.
1. Your solution must you implicit indexing. The entries must be ordered such that when the menu item is selected by number, that implicit index selects the corresponding function, invoking the function pointer, to perform the action named in the menu.
1. Your program must work correctly for any valid combination of decimal and hexadecimal numbers. 
1. Special case for division. Your code should be able to handle this without a special check. 
1. Nongraded feedback from A1, A2, A3, will merit point deductions. This should be your best C code yet. 

# Make
- There is no provided Makefile.
- make must build an executable named 'a4' and have a 'make clean' function to meet the rubric.

# Hints and Suggestions
1. If you are seg faulting or stack smashing, your code is in a lot of trouble.
1. The C library routine strtol() will be very useful for this assignment.
1. There is design room in this lab. Whiteboard your design and discuss with someone. If you cannot articulate why it meets the criteria, it probably doesn't.
1. Think carefully about the signature of your function pointers. Doing this early can save you a lot of pain later.
1. If you have any hardcoded 0,1,2,3,4,5,6, you are violating the program requirements. A switch is not an implicit index.
1. Your solution should not be more than 800 lines of code long. If it is, you're probably going in a bad direction.
1. This lab builds on A1, A2, and A3. 

# Rubric
Your assignment will be graded according to this rubric. The maximum number of points is within brackets for each item. This assignment is worth 50 points. 

Bad coding practice may be additional deductions.

The grader will also run the test section and may use different input than the tests.

Your program must work correctly for any valid combination of decimal and hexadecimal numbers (the tests will use randomness).

    [5] A valid make file provided.
    [2] Assignment correctly submitted.
    [11] Code is sufficiently modular. Not all code is in main().
    [11] Code comments must be readable and understandable. Code must not be over commented. Only use comments where necessary. No blocks of unused code, even in comments.
    [10] Correct checks for the number of arguments.
    [60] Tests:
        [6] Exit works correctly.
        [10] Addition works correctly.
        [10] Substraction works correctly.
        [10] Multiplication works correctly.
        [10] Division works correctly. Must have at least one example showing a fractional result.
        [5] Modulo works correctly.
        [10] Reverse works correctly.



# Grading Script

Grading scripts, for checking to ensure that your submission meets minimum stardards of execution are located in this directory. After downloading, use the command "chmod +x *.py" to make both scripts executable. The file grading_common.py is required by all the grading scripts.

Copys the python script for the correct assignment, plus the python script grading_common.py, to your source code directory. Run the grading script for this assignment as:

```
make a4
./grade_a4.py
```

Note that since this is an interactive program, the 'continueonfailure' flag may do unexpected things for a4. You may use it, but it may produce unreliable or inconsistent behavior.

If there are no errors, then you are ready to focus on the clean up, documentation, and review of your code.

Note that the rubric contains other aspects of your program, such as style, that are graded in addition to the score of the grading script. 

# Example Game Session (what the test suite is based on)
The test suite forms part of your specification. Pay careful attention to the spelling, formatting, and spacing. Computers are very literal.

```
$ make
gcc -Wall  main.c -lm -o a4
$ ./a4 0x10 4

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 0
$ ./a4 0x10 4

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 1
16 + 4 = 20
0x10 + 0x4 = 0x14

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 2
16 - 4 = 12
0x10 - 0x4 = 0xC

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 3
16 * 4 = 64
0x10 * 0x4 = 0x40

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 4
16 / 4 = 4.000000

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 5
16 mod 4 = 0
0x10 mod 0x4 = 0x0

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 6
4 01x0

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 7
Invalid selection. Try again.

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 0
$
    

// Special case for division. Your code should be able to handle this without a special check.

$ ./a4 0 0

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 4
0 / 0 = -nan

0. Exit
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulo
6. Reverse Input

Menu item: 0
$
    
```

# Submission for A4
Same process as A1, A2, A3. 
1. Always doublecheck that your submission looks and behaves the way you expect on the CS Linux server (this is our 'production' environment).
1. For each program, you will submit your C source code (properly documented), header files, and Makefile. Do not include any binaries, test loigs, or non-necessary files with your submissions.
1. Zip file: Your electronic submission will be packaged as a zip file with your CS login name containing a single folder.
    - For example, suppose your CS login name is "john". Your zip file will be called "john.zip". 
    - Once the TA unzips the file, a directory "john/" will be created and your submitted material will be extracted to the directory "john". 
1. Submit assignment through the course Canvas site