ALL = laba_test
    

all: $(ALL)

clean:
	rm -f *.o $(ALL)

.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $*.cpp

laba_test: laba_test.o laba.o
	g++ -o laba_test laba_test.o laba.o

