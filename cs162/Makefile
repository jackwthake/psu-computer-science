CC=g++
CXXFLAGS=-O0 -fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized  -Winit-self -std=c++11

default: program1 program2 program3 lab4


#Programs
program1: prog1/main.cpp
	$(CC) $(CXXFLAGS) -o prog1.out  prog1/main.cpp

program2: prog2/main.cpp
	$(CC) $(CXXFLAGS) -o prog2.out  prog2/main.cpp

program3: prog3/main.cpp prog3/list.cpp prog3/commands.cpp
	$(CC) $(CXXFLAGS) -o prog3.out  prog3/*.cpp

# Labs
lab4: labs/*lab4.cpp
	$(CC) $(CXXFLAGS) -o lab4.out  labs/*lab4.cpp


clean:
	rm -rf *.out
