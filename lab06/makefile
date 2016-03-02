
ALL = prod_tester keno

all: $(ALL)

clean:
	rm -f *.o $(ALL) core

product.o: product.h

prod_tester.o: product.h
prod_tester: prod_tester.o product.o
	g++ -o prod_tester prod_tester.o product.o

keno.o: product.h
keno: keno.o product.o
	g++ -o keno keno.o product.o

.SUFFIXES: .cpp .o 

.cpp.o: 
	g++ -c $*.cpp

.cpp:
	g++ -o $* -O $*.cpp

