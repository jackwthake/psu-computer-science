#!/usr/local/bin/python3
import subprocess
import os

def check_exec(fname):
    print("Checking", fname)
    cmd = "valgrind --tool=memcheck --leak-check=yes --error-exitcode=-1 ./" + \
          fname + " >/dev/null 2>&1"
    result = os.system(cmd)
    if result != 0:
        print(fname, "\033[91mFailed Memory Checks.\033[0m")
        return False
    else:
        print(fname, "\033[92mPassed Memory Checks.\033[0m")
        return True

def check_dir(directory):
    has_failed = False
    for filename in os.listdir(directory):
        if filename.endswith(".out"):
            if not check_exec(os.path.join(directory, filename)):
                has_failed = True


    return has_failed

if __name__ == "__main__":
    has_failed = False

    # were not checking cs162 because all the program requires user input this
    # script can't suply. Nor do we check lab executables because those will
    # almost definitely have memory leaks that aren't my fault and I can't
    # necessarily fix
    
    if check_dir("bin/163") == 1:
        has_failed = True

    if has_failed:
        os._exit(1)
