all: cp_tester

cp_tester: cp_tester.o code_processor.o double_checker.o
	g++ -o cp_tester cp_tester.o code_processor.o double_checker.o

cp_tester.o: cp_tester.cpp code_processor.h
	g++ -c cp_tester.cpp

code_processor.o: code_processor.cpp code_processor.h
	g++ -c code_processor.cpp

double_checker.o: double_checker.cpp code_processor.h
	g++ -c double_checker.cpp

