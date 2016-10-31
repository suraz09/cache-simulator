all: simulator

simulator:	main.o utilities.o cache.o block.o memoryAddress.o instruction.o
		g++ main.o utilities.o cache.o block.o memoryAddress.o instruction.o -o simulator
