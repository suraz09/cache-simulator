# CC=g++
# CFLAGS=-I.

# hello: hellomake.o hellofunc.o
# 	$(CC) hello hellomake.o hellofunc.o -I.

all: simulator

simulator:	hellomake.o hellofunc.o
		g++ hellomake.o hellofunc.o -o simulator
