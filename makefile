# CC=g++
# CFLAGS=-I.

# hello: hellomake.o hellofunc.o
# 	$(CC) hello hellomake.o hellofunc.o -I.

all: simulator

simulator:	main.o utilities.o cache.o block.o memoryAddress.o instruction.o
		g++ main.o utilities.o cache.o block.o memoryAddress.o instruction.o -o simulator
