CC=g++
CXXFLAGS=-O0 -fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized  -Winit-self -std=c++11
UNAME_S := $(shell uname -s)

default: cs162

################
# cs162
################

ifeq ($(UNAME_S),Darwin)
cs162: program1 program2 program3 lab4 # We don't compile lab 6 and 7, because the .o files aren't compatible
else 
cs162: program1 program2 program3 lab4 lab6 lab7
endif

#Programs
program1: cs162/prog1/main.cpp
	$(CC) $(CXXFLAGS) -o bin/prog1.out  cs162/prog1/main.cpp

program2: cs162/prog2/main.cpp
	$(CC) $(CXXFLAGS) -o bin/prog2.out  cs162/prog2/main.cpp

program3: cs162/prog3/main.cpp cs162/prog3/list.cpp cs162/prog3/commands.cpp
	$(CC) $(CXXFLAGS) -o bin/prog3.out  cs162/prog3/*.cpp

# Labs
lab4: cs162/labs/*4/*lab4.cpp
	$(CC) $(CXXFLAGS) -o bin/lab4.out  cs162/labs/*4/*lab4.cpp

lab6: cs162/labs/*6/*lab6.cpp
	$(CC) $(CXXFLAGS) -o bin/lab6.out  cs162/labs/*6/*.cpp cs162/labs/*6/*.o

lab7: cs162/labs/*7/*lab7.cpp
	$(CC) $(CXXFLAGS) -o bin/lab7.out  cs162/labs/*7/*.cpp cs162/labs/*7/*.o

clean:
	rm -rf *.out
