CC=g++
CXXFLAGS=-O0 -fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized  -Winit-self -std=c++11

default: cs162

################
# cs162
################
cs162: program1 program2 program3 lab4

#Programs
program1: cs162/prog1/main.cpp
	$(CC) $(CXXFLAGS) -o bin/prog1.out  cs162/prog1/main.cpp

program2: cs162/prog2/main.cpp
	$(CC) $(CXXFLAGS) -o bin/prog2.out  cs162/prog2/main.cpp

program3: cs162/prog3/main.cpp cs162/prog3/list.cpp cs162/prog3/commands.cpp
	$(CC) $(CXXFLAGS) -o bin/prog3.out  cs162/prog3/*.cpp

# Labs
lab4: cs162/labs/*lab4.cpp
	$(CC) $(CXXFLAGS) -o bin/lab4.out  cs162/labs/*lab4.cpp

clean:
	rm -rf *.out
