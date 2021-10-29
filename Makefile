CC=g++
CXXFLAGS= -Wall -ansi -std=c++11
UNAME_S := $(shell uname -s)

default: cs162 cs163 cs202

################
# cs162
################

ifeq ($(UNAME_S),Darwin)
cs162: 162_program1 162_program2 162_program3 162_program3-v2 162_program4  # We don't compile lab 6 and 7, because the .o files aren't compatible
else
cs162: 162_program1 162_program2 162_program3 162_program3-v2 162_program4 162_lab4 162_lab6 162_lab7 162_lab8 162_lab10
endif

#Programs
162_program1: cs162/prog1/main.cpp
	$(CC) $(CXXFLAGS) -o bin/162/prog1.out  cs162/prog1/main.cpp

162_program2: cs162/prog2/main.cpp
	$(CC) $(CXXFLAGS) -o bin/162/prog2.out  cs162/prog2/main.cpp

162_program3: cs162/prog3/main.cpp cs162/prog3/list.cpp cs162/prog3/commands.cpp
	$(CC) $(CXXFLAGS) -o bin/162/prog3.out  cs162/prog3/*.cpp

162_program3-v2: cs162/prog3-v2/main.cpp cs162/prog3-v2/file.cpp cs162/prog3-v2/commands.cpp
	$(CC) $(CXXFLAGS) -o bin/162/prog3-v2.out  cs162/prog3-v2/*.cpp

162_program4: cs162/prog4/main.cpp cs162/prog4/input.cpp
	$(CC) $(CXXFLAGS) -o bin/162/prog4.out  cs162/prog4/*.cpp

# Labs
162_lab4: cs162/labs/*4/*lab4.cpp
	$(CC) $(CXXFLAGS) -o bin/162/lab/lab4.out  cs162/labs/*4/*lab4.cpp

162_lab6: cs162/labs/*6/*lab6.cpp
	$(CC) $(CXXFLAGS) -o bin/162/lab/lab6.out  cs162/labs/*6/*.cpp cs162/labs/*6/*.o

162_lab7: cs162/labs/*7/*lab7.cpp
	$(CC) $(CXXFLAGS) -o bin/162/lab/lab7.out  cs162/labs/*7/*.cpp cs162/labs/*7/*.o

162_lab8: cs162/labs/*8/*.cpp
	$(CC) $(CXXFLAGS) -o bin/162/lab/lab8.out  cs162/labs/*8/*.cpp cs162/labs/*8/*.o

162_lab10: cs162/labs/*10/*.cpp
	$(CC) $(CXXFLAGS) -o bin/162/lab/lab10.out  cs162/labs/*10/*.cpp cs162/labs/*10/*.o

################
# cs163
################

ifeq ($(UNAME_S),Darwin)
cs163: 163_program1 163_program1_v2 163_program2 163_program3 163_program4 163_program5 # We don't compile labs, because the .o files aren't compatible
else
cs163: 163_program1 163_program1_v2 163_program2 163_program3 163_program4 163_program5 163_lab1
endif

# programs
163_program1: cs163/*1/*.cpp
	$(CC) $(CXXFLAGS) -o bin/163/prog1.out cs163/*1/*.cpp

163_program1_v2: cs163/*1_v2/*.cpp
	$(CC) $(CXXFLAGS) -g -o bin/163/prog1_v2.out cs163/*1_v2/*.cpp

163_program2: cs163/*g2/*.cpp
	$(CC) $(CXXFLAGS) -o bin/163/prog2.out cs163/*g2/*.cpp

163_program3: cs163/*g3/*.cpp
	$(CC) $(CXXFLAGS) -o bin/163/prog3.out cs163/*g3/*.cpp
	cp *3/*3/items.dat bin/163/items.dat

163_program3_v2: cs163/*3_v2/*.cpp
	$(CC) $(CXXFLAGS) -o bin/163/pro3_v2.out cs163/*3_v2/*.cpp
	cp *3/*g3_v2/items.dat bin/163/items.dat

163_program4: cs163/*g4/*.cpp
	$(CC) $(CXXFLAGS) -o bin/163/prog4.out cs163/*g4/*.cpp

163_program5: cs163/*g5/*.cpp
	$(CC) $(CXXFLAGS) -o bin/163/prog5.out cs163/*g5/*.cpp

# labs
163_lab1: cs163/labs/*1/*lab1.cpp
	$(CC) $(CXXFLAGS) -o bin/163/lab/lab1.out cs163/labs/*1/*.cpp cs163/labs/*1/*.o

#############
# cs202
#############

cs202 : 202_program1 202_program2

#############
# cs202 program 1
#############
202_program1: 202_program1_snapshot1 202_program1_snapshot2 202_program1_snapshot3 202_program1_snapshot4

202_program1_snapshot1: cs202/*1/g/*1/*.h
	$(CC) $(CXXFLAGS) -fsyntax-only cs202/*1/*1/*.h 

202_program1_snapshot2: cs202/*1/g/*2/*.cpp
	$(CC) $(CXXFLAGS) -o bin/202/prog1_v1.out cs202/*g1/*2/*.cpp

202_program1_snapshot3: cs202/*1/g/*3/*.cpp
	$(CC) $(CXXFLAGS) -o bin/202/prog1_v2.out cs202/*g1/*3/*.cpp

202_program1_snapshot4: cs202/*1/g/*4/*.cpp
	$(CC) $(CXXFLAGS) -o bin/202/prog1_final.out cs202/*g1/*4/*.cpp

#############
# cs202 program 2
#############
202_program2: 202_program2_snapshot1 202_program2_snapshot2

202_program2_snapshot1: cs202/*2/*1/*.h
	$(CC) $(CXXFLAGS) -fsyntax-only cs202/*2/*2/*.h 

202_program2_snapshot2: cs202/*2/*2/*.cpp
	$(CC) $(CXXFLAGS) cs202/*2/*2/*.cpp 

clean:
	rm -rf bin/
