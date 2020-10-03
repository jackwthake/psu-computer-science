CC=g++
CXXFLAGS=-Wall -ansi
UNAME_S := $(shell uname -s)

default: cs162

################
# cs162
################

ifeq ($(UNAME_S),Darwin)
cs162: program1 program2 program3 program3-v2 program4 lab4 # We don't compile lab 6 and 7, because the .o files aren't compatible
else 
cs162: program1 program2 program3 program3-v2 program4 lab4 lab6 lab7 lab8 lab10
endif

#Programs
program1: cs162/prog1/main.cpp
	$(CC) $(CXXFLAGS) -o bin/prog1.out  cs162/prog1/main.cpp

program2: cs162/prog2/main.cpp
	$(CC) $(CXXFLAGS) -o bin/prog2.out  cs162/prog2/main.cpp

program3: cs162/prog3/main.cpp cs162/prog3/list.cpp cs162/prog3/commands.cpp
	$(CC) $(CXXFLAGS) -o bin/prog3.out  cs162/prog3/*.cpp

program3-v2: cs162/prog3-v2/main.cpp cs162/prog3-v2/file.cpp cs162/prog3-v2/commands.cpp
	$(CC) $(CXXFLAGS) -o bin/prog3-v2.out  cs162/prog3-v2/*.cpp

program4: cs162/prog4/main.cpp cs162/prog4/input.cpp
	$(CC) $(CXXFLAGS) -o bin/prog4.out  cs162/prog4/*.cpp

# Labs
lab4: cs162/labs/*4/*lab4.cpp
	$(CC) $(CXXFLAGS) -o bin/lab4.out  cs162/labs/*4/*lab4.cpp

lab6: cs162/labs/*6/*lab6.cpp
	$(CC) $(CXXFLAGS) -o bin/lab6.out  cs162/labs/*6/*.cpp cs162/labs/*6/*.o

lab7: cs162/labs/*7/*lab7.cpp
	$(CC) $(CXXFLAGS) -o bin/lab7.out  cs162/labs/*7/*.cpp cs162/labs/*7/*.o

lab8: cs162/labs/*8/*.cpp
	$(CC) $(CXXFLAGS) -o bin/lab8.out  cs162/labs/*8/*.cpp cs162/labs/*8/*.o

lab10: cs162/labs/*10/*.cpp
	$(CC) $(CXXFLAGS) -o bin/lab10.out  cs162/labs/*10/*.cpp cs162/labs/*10/*.o

clean:
	rm -rf *.out
