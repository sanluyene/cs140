ALL = avltree_test
    

all: $(ALL)

clean:
	rm -f *.o $(ALL)

.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $*.cpp

avltree_test: avltree_test.o avltree.o
	g++ -o avltree_test avltree_test.o avltree.o

