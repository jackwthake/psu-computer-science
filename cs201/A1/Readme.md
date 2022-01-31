
# CS 201 Computer Systems Programming, A1
Originally by markem, tweaked by naak. 
Test suite by theod.

# Typing speed game
You are to implement a game that tests a user's typing speed. The game randomly chooses words from an array of strings containing "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog". Each word must appear exactly once. The program should output the time it takes for the user to correctly enter the entire array of words. If the user incorrectly types a word, the program must prompt the user to retype the incorrect word. A good algorithm for achieving a good shuffle (permutation) is the Fisher-Yates Shuffle. A good shuffle is defined as one that does the minimal number of shuffle operations

## Program Requirements

1. Random permutation of words should be generated via calls to srand() and rand()
    - Seed srand() using the usec field from a call to gettimeofday().
    - All permutations of the words must be possible. This means that each run of the program should list the words in different orders.
1. Ensure that your random permutation is generated using a minimal number of rand() calls
1. Use timer macro "timersub()" for handling operations on struct timevals.
    - Timing should begin when the random permutation is first given to the user
    - Timing should end when the user correctly inputs the permutation correctly.

## Make

The Makefile for this assignment has been provided. As this was covered in the pre-req class, you'll be expected to make your own after this assignment.

## Hints and suggestions

1. Consult the linux man pages for more information on rand(), srand(), gettimeofday(), timersub(), printf(), scanf(), strlen(), strncmp() etc. For example, "man timersub", without quotes, will display the manual page for that C library call.
1. Once you have read in the input line, you will want to flush the rest of the line. Here is a small piece of code that reads in 10 characters of input and then throws away the rest of the line.
```scanf("%10s", word);
while((c = getchar()) != '\n' && c != EOF)
        ;     /* discard */
```
1. If you are seg faulting or stack smashing, your code is in a lot of trouble.

## Rubric
Your assignment will be graded according to this rubric. The maximum number of points is within brackets for each item. This assignment is worth 50 points. 

Bad coding practice may be additional deductions.

The grader will also run the test section and may use different input than the tests.

    [2] Assignment correctly submitted.
    [3] Correct use of the make command and file.
    [2] Code is modular. Not all code is in main().
    [2] Code comments must be readable and understandable. Code must not be over commented. Only use comments where necessary. Contains the 'neccessary comment'
    [2] Correctly seed the random number generator.
    [2] Correct, optimal/minimal number of calls to rand() function.
    [3] Good shuffle achieved. All permutatons possible.
    [2] Correct use of timersub and gettimeofday.
    [2] Timing calculation correct.
    [3] Correct error checking and processing of (potential) errors.
    [2] Does not use non-secure versions of function calls.
    [25] Tests (from grading script):
        [5] Example run showing all correct input.
        [4] Example run showing misspellings that do not partially match the correct word.
        [4] Example run showing a misspelling where only the first part of the word is typed. For example, entering "brow" when "brown" is displayed.
        [4] Example run showing a misspelling where the correct word is typed but additional characters are entered. For example, "lazyman" when "lazy" is typed.
        [4] Example run showing that comparisons are correctly performed. The only test here is to show that when "the" is displayed that "The" does not match and when "The" is displayed that "the" does not match.
        [4] Example run showing that extraneous input is flushed per the provided hint. For example, if the user enters "lazy dog", then only "lazy" should be used for comparison and " dog" is thrown away.

## Grading Script

Grading scripts, for checking to ensure that your submission meets minimum stardards of execution are located in this directory. After downloading, use the command "chmod +x *.py" to make both scripts executable. The file grading_common.py is required by all the grading scripts.

Copys the python script for the correct assignment, plus the python script grading_common.py, to your source code directory. Run the grading script for this assignment as:

```
make typing_word_game
./grade_a1.py
```

If there are no errors, then you are ready to submit! See the file feedback.txt. Note that the rubric contains other aspects of your program, such as style, that are graded in addition to the score of the grading script. Please run "make reallyclean" before making your zip file.

## Example Game Session (what the test suite is based on)
The test suite forms part of your specification. Pay careful attention to the spelling, formatting, and spacing. Computers are very literal.

```
% ls

Makefile typing_word_game.c

% make
gcc -Wall -Og -g -o typing_word_game typing_word_game.c

% ./typing_word_game

This is a game that tests typing speed

Type the following words:
word #1 is The: The
word #2 is dog: dog
word #3 is brown: brown
word #4 is over: over
word #5 is lazy: lazzy
word #5 is lazy: lazy
word #6 is the: The
word #6 is the: the
word #7 is quick: quick
word #8 is jumps: jumps
word #9 is fox: fox
You took 24 seconds and 857382 microseconds

```

# Submission for A1
Always doublecheck that your submission looks and behaves the way you expect on the cs linux server. Depending on your OS, you may not get what you think.

## Basics
1. For each program, you will submit your C source code (properly documented), header files, and Makefile. Do not include any binaries or non-necessary files with your submissions.
1. Zip file: Your electronic submission will be packaged as a zip file with your CS login name containing a single folder.
    - For example, suppose your CS login name is "john". Your zip file will be called "john.zip". 
    - Once the TA unzips the file, a directory "john/" will be created and your submitted material will be extracted to the directory "john". 
    - Note if the TA cannot recover the directory with your login name or cannot compile your program, you are not considered to have turned in your project.
1. Submit assignment through the course Canvas site

## Help
### Make a zip file of your program directory on the cs linux server
Below is an example that creates a zip file for submission. Again assume that your CS login name is "john". First, you will create the directory "john" (say, under /u/john/cs201) and copy all the files and directories to be submitted into the directory /u/john/cs201/john/. Copying is done via the command "cp". The "-p" flag will preserve the original time stamps of your files while the "-r" flag will copy directories recursively. Below shows a screen shot of making the zip.
```
    /u/john/cs201/> ls john/
    Makefile test.c typescript
    /u/john/cs201/> zip -r john.zip john/*
      adding: john/Makefile (stored 0%)
      adding: john/test.c (stored 0%)
      adding: john/typescript (stored 0%)

    /u/john/cs201/> ls -l john.zip
    -rw------- 1 john them 10240 Mar 31 10:00 john.zip 
```
### Related commands:

- To see what files are in a zip file, say "john.zip", do the following:
        ```unzip -l john.zip```
    - Note this command does not extract files from john.zip, but rather it shows what're inside it. This is very useful before you actually extract a zip file.
- To unzip a zip file, say "john.zip", do the following:
        ```unzip john.zip```
    - This will create the directory "john" with all the files that are inside it. Warning: whatever files and directories in john.zip will overwrite existing ones with the same names. To test this command, it's better that you do it under a temporary directory so that you don't overwrite anything by accident. 
