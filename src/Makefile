# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

CFLAGS=-g
SOURCES=main.o game.o board.o move.o player.o strategy.o learning_player.o

all: gameai

gameai: $(SOURCES)
	gcc -g -o gameai $(SOURCES)

clean:
	-rm *.o gameai
