# Mount tabor for Linux
# Usage:
# $ ./mt -s THEME1.CNF --stats 
# Created by Fred Nora.

all:

# Controller
	gcc -c main.c     -o main.o
	gcc -c globals.c  -o globals.o
# View
	gcc -c view/view.c     -o view.o
# Model
	gcc -c model/compiler.c -o compiler.o
	gcc -c model/lexer.c    -o lexer.o
	gcc -c model/parser.c   -o parser.o
	gcc -c model/tree.c     -o tree.o

# Link
	gcc -Wall -o mt main.o globals.o view.o compiler.o lexer.o parser.o tree.o 

# Build the final destination.
	-mkdir build/
	-cp ./mt                           build/
	-cp ./assets/css/gramado.css       build/ 
	-cp ./assets/js/gramado.js         build/
	-cp ./assets/examples/THEME1.CNF   build/
	-cp ./assets/examples/TEST1.CNF    build/
	-cp ./assets/usage.txt             build/
	-cp ./assets/Makefile              build/
	rm *.o  

	@echo "Go to build/ folder and type make";
clean:
	-rm *.o  
	-rm ./mt 
	-rm -rf build


