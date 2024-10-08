# Create the interpreter for the gramado language.
# Usage:
# $ ./gramado -s THEME1.CNF --stats 
# Created by Fred Nora.

linkTarget = gramado

Objects = main.o globals.o view.o compiler.o lexer.o parser.o tree.o 

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
# Create the 'gramado' executable.
	gcc -Wall -o $(linkTarget) $(Objects) 

# Build the final destination.
	-mkdir build/
	-cp ./$(linkTarget)                build/
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
	-rm ./gramado 
	-rm -rf build
clean-all:
	-rm *.o  
	-rm ./gramado 
	-rm -rf build

