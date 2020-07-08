CC=g++
CXXFLAGS=-O0 -fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized  -Winit-self -std=c++11

default: program1 program2

program1: prog1/main.cpp
	$(CC) $(CXXFLAGS) -o prog1.out  prog1/main.cpp

program2: prog2/main.cpp
	$(CC) $(CXXFLAGS) -o prog2.out  prog2/main.cpp

