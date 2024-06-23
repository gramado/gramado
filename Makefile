# Mount tabor for Linux
# Usage:
# $ ./mt -s THEME1.CNF --stats 

all:
	gcc -c main.c     -o main.o
	gcc -c globals.c  -o globals.o
	gcc -c compiler.c -o compiler.o
	gcc -c lexer.c    -o lexer.o
	gcc -c parser.c   -o parser.o
	gcc -c tree.c     -o tree.o
# Link
	gcc -Wall -o mt main.o globals.o compiler.o lexer.o parser.o tree.o 

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

	@echo "Got to build/ folder and type make";
clean:
	-rm *.o  
	-rm ./mt 
	-rm -rf build




