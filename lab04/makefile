all: hash_test

hash_test: hash_test.o hash140.o
	g++ -o hash_test hash_test.o hash140.o

hash_test.o: hash_test.cpp hash140.h
	g++ -c hash_test.cpp

hash140.o: hash140.cpp hash140.h
	g++ -c hash140.cpp
