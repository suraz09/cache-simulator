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