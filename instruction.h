/*************************************************************************
/
/   filename: instruction.h
/
/   description: Header for Instruction class
/
/   authors: Acharya, Suraj
/
/   class:  CSE 331
/   instructor: Zheng
/   assignment: Lab Project #1
/
/   assigned: Oct 17, 2016
/   due:    Oct 31, 2016
/
/************************************************************************/

#include "memoryAddress.h"
#include <string>
#include <vector>
class Instruction{
public:
	string type;
	string rawAddress;
	int count;
	vector<MemoryAddress> binaryAddress;

	Instruction(string s);
	string parseAddress(); //Return in binary form

	string getInstructionType();
	int getInstructionCount();
	MemoryAddress getInstructionAddress();
	string getRawAddress();

	void setInstructionType(char s);
	void setInstructionCount(int i);
	void setInstructionAddress(int tagSize, int setIndexSize);
	void setRawAddress(string raw);
};