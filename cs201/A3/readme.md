# CS 201 Computer Systems Programming, A3 Floating Point
- Original lab by markem, tweaked by naak. 
- Test suite by theod.

# Specification Overview
The goal of this program is to implement an IEEE floating point parser for an arbitrary number of bit settings.

# Program Requirements
- Your program will take 3 arguments.  
- The first argument is the number of fraction bits (n) between 2 and 10 to be used in the representation. (argv[1])
- The second argument is the number of exponent bits (k) between 3 and 5 to be used in the representation. (argv[2])
- The third argument is the hexadecimal representation of the number you want to parse assuming the settings given in the first two arguments. (argv[3])
- Since E,M,V, etc feature in the IEEE formula, you may choose use these as variable names without fear of deduction for poor coding practice (provided they are correctly named for that they are).
- Check number of arguments and their ranges.  Exit program upon detecting errors.
- Use strtoul or sscanf to convert argv arguments into the desired format. For scanf, use %d to parse integer strings, %x to parse hexadecimal strings. Note that strtoul() may be more natural when checking the input for correctness.
- Calculate the Bias programmatically as 2(k-1) - 1
- Use shift operations to generate appropriate bit masks to isolate the sign, exp, and fraction fields.  (Hint: What does (1 << n) - 1 generate?)
- Use the pow() function to find the numeric value for M and the final output. 
- Ensure proper handling of normalized, denormalized, infinity (both), and NaN
- For example, consider the program execution "fp_parse 4 4 a8".  
    1. The bit breakdown of the corresponding representation is : ```|s|e e e e|f f f f|```
    1. That's 1 sign bit, 4 exponent bits, and 4 fractional bits.
    1. Based on the 3rd argument, "a8", the program should parse the hex digits into corresponding bit fields.  
    1. Separating out "a8" gives you 0 1010 1000 for the 3 fields.  
    1. (Note that we 0-pad the most-significant bits as needed).  
    1. From this, the exp field is 10 (in decimal), the fraction field is 1⁄2, and the Bias field is 7. 
    1. The resulting value M*2E will be M = 1+1⁄2 = 3⁄2 , E = 10 - 7 = 3.  Thus, the output will be 12.0.

# Make

- There is no provided Makefile.
- You will need to include math.h in your source program and link in the math library -lm during compilation (which should be part of the linking flags. This was LD_FLAGS in the A1 and A2 assignment).
- make must build an executable named 'fp_parse' and have a clean function to meet the rubric.


# Hints and Suggestions
1. If you are seg faulting or stack smashing, your code is in a lot of trouble. Seek help ASAP.
1. Revisiting the formulas in the lecture might be wise.
1. The user is still evil. Expect it and use what you've learned from A2 to counter naughty inputs.
1. If you are not using bitmasks and the operators from A2, you've probably gone off the rails somewhere.
1. Straying from, or getting creative with the calculation is a bad idea.
1. Carefully reviewing and testing with the examples in the rubric is a very good idea.



# Rubric
Your assignment will be graded according to this rubric. The maximum number of points is within brackets for each item. This assignment is worth 50 points. 

Bad coding practice may be additional deductions.

The grader will also run the test section and may use different input than the tests.


    [2] Assignment correctly submitted.
    [4] A valid make file provided.
    [8] Code is sufficiently modular. Not all code is in main().
    [5] Code comments must be readable and understandable. Code must not be over commented. Only use comments where necessary. No blocks of unused code, even in comments.
    [5] Correct checks for the number of arguments.
    [5] Bounds checking: fraction bits 2-10, exponent bits 3-5.
    [5] Correct use of sscanf/strtoul to convert arguments to desired format.
    [5] Error checking if hex value can be represented in specified number of bits. Checks to ensure that if the input is larger than the number of bits specified that an error is generated.
    [5] Error checking of input for success / failure.
    [10] Correct use of bit masks to isolate exp, frac and sign fields.
    [12] IEEE interpretation
        [2] Correct Bias calculation.
        [2] Correct V calculation.
        [3] Correct normalized M and E calculations.
        [3] Correct dormalized M and E calculations.
        [2] Correct special value calculations.
    [2] Correct use of pow().
    [32] Tests:
        [2] No arguments.
        % fp_parse
        Usage: fp_parse <# of frac_bits> <# of exp_bits>
        [2] Invalid number of fraction bits
        % fp_parse 11 4 33f
        Invalid number of fraction bits (11). Should be between 2 and 10
        [2] Invalid number of exponent bits
        % fp_parse 4 8 33f
        Invalid number of exponent bits (8). Should be between 3 and 5
        [2] Correct values for exponent and fraction bits but number itself contains too many bits.
        $ fp_parse 3 3 a334
        Number a334 exceeds maximum number of bits. Only 7 allowed here.
        [2] Correct values for exponent and fraction bit but 3rd argument is not a valid hexadecimal number.
        $ ./fp_parse 3 4 23skidoo
        Argument 3 is not a hexadecimal number (23skidoo).
        [2] Correct input, yielding a negative number
        % fp_parse 4 4 1af
        -15.500000
        [2] Correct input, yielding a positive number
        % fp_parse 4 4 af
        15.500000
        [2] Correct input yielding NaN
        % fp_parse 3 3 3c
        NaN
        [2] Correct input yielding +inf
        % fp_parse 3 3 38
        +inf
        [2] Correct input yielding -inf
        % fp_parse 3 3 78
        -inf
        [2] Correct input yielding a correct value
        % fp_parse 3 3 26
        3.500000
        [2] Correct input yielding a correct value
        % fp_parse 3 3 18
        1.000000
        [2] Correct input yielding NaN
        % fp_parse 3 3 3f
        NaN
        [2] Correct input yielding correct output
        % fp_parse 3 3 37
        15.000000
        [2] Correct input yielding a positive zero
        % fp_parse 4 4 0
        0.000000
        [2] Correct input yielding a negative zero
        % fp_parse 4 4 100
        -0.000000




# Grading Script

Grading scripts, for checking to ensure that your submission meets minimum stardards of execution are located in this directory. After downloading, use the command "chmod +x *.py" to make both scripts executable. The file grading_common.py is required by all the grading scripts.

Copys the python script for the correct assignment, plus the python script grading_common.py, to your source code directory. Run the grading script for this assignment as:

```
make fp_parse
./grade_a3.py
```

While testing you might find that one part has issues. You can ask the test suite to test as much as it can, by 
```
./grade_a2.py --continueonfailure 

```

If there are no errors, then you are ready to focus on the clean up, documentation, and review of your code.


Note that the rubric contains other aspects of your program, such as style, that are graded in addition to the score of the grading script. 

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

# Submission for A3
Same process as A1 and A2. 

1. Always doublecheck that your submission looks and behaves the way you expect on the CS Linux server (this is our 'production' environment).
1. For each program, you will submit your C source code (properly documented), header files, and Makefile. Do not include any binaries, test loigs, or non-necessary files with your submissions.
1. Zip file: Your electronic submission will be packaged as a zip file with your CS login name containing a single folder.
    - For example, suppose your CS login name is "john". Your zip file will be called "john.zip". 
    - Once the TA unzips the file, a directory "john/" will be created and your submitted material will be extracted to the directory "john". 
1. Submit assignment through the course Canvas site
