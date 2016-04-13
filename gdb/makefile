EXECUTABLES =  segfault1 names_list bad_names_list bad_names_list1

all: segfault1 names_list bad_names_list bad_names_list1

names_list: list.o add_name.o
	g++ -g -o names_list list.o add_name.o

list.o: list.cpp list.h
	g++ -g -c list.cpp

add_name.o: add_name.cpp list.h
	g++ -g -c add_name.cpp

bad_names_list: list1.o 
	g++ -g -o bad_names_list list1.o 

list1.o: list1.cpp list.h
	g++ -g -c list1.cpp

add_name1.o: add_name1.cpp list.h
	g++ -g -c add_name1.cpp

bad_names_list1: list.o add_name1.o
	g++ -g -o bad_names_list1 list.o add_name1.o

segfault1: segfault1.cpp
	g++ -g -o segfault1 segfault1.cpp

clean:
	        rm -f core *.o $(EXECUTABLES) a.out

