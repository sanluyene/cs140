ALL = dl_hash_test list_editor dlistrev-1 dlistrev-2 dlistrev-3 dlistrev-4 dlistrev-5 dlistrev-6

all: $(ALL)

clean:
	rm -f *.o $(ALL)

.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $*.cpp

dlist.o: dlist.h
dl_hash.o: dl_hash.h dlist.h

dl_hash_test.o: dlist.h dl_hash.h
dl_hash_test: dl_hash_test.o dl_hash.o dlist.o
	g++ -o dl_hash_test dl_hash_test.o dl_hash.o dlist.o

list_editor.o: dlist.h
list_editor: list_editor.o dlist.o
	g++ -o list_editor list_editor.o dlist.o

dlistrev-1.o: dlist.h
dlistrev-1: dlistrev-1.o dlist.o
	g++ -o dlistrev-1 dlistrev-1.o dlist.o

dlistrev-2.o: dlist.h
dlistrev-2: dlistrev-2.o dlist.o
	g++ -o dlistrev-2 dlistrev-2.o dlist.o

dlistrev-3.o: dlist.h
dlistrev-3: dlistrev-3.o dlist.o
	g++ -o dlistrev-3 dlistrev-3.o dlist.o

dlistrev-4.o: dlist.h
dlistrev-4: dlistrev-4.o dlist.o
	g++ -o dlistrev-4 dlistrev-4.o dlist.o

dlistrev-5.o: dlist.h
dlistrev-5: dlistrev-5.o dlist.o
	g++ -o dlistrev-5 dlistrev-5.o dlist.o

dlistrev-6.o: dlist.h
dlistrev-6: dlistrev-6.o dlist.o
	g++ -o dlistrev-6 dlistrev-6.o dlist.o

