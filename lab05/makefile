all: bitmatrix_editor

bitmatrix_editor: bitmatrix_editor.o bitmatrix.o
	g++ -o bitmatrix_editor bitmatrix_editor.o bitmatrix.o

bitmatrix_editor.o: bitmatrix_editor.cpp bitmatrix.h
	g++ -c bitmatrix_editor.cpp

bitmatrix.o: bitmatrix.cpp bitmatrix.h
	g++ -c bitmatrix.cpp
