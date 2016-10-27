#include "header.h"
#include "instruction.h"
#include <string>
#include <iostream>
#include <sstream>


Instruction::Instruction(string s){
	string a[3];
	int k = 0;
	for(int i = 0; i < s.size(); i++){
		a[k] += s[i];
		if(s[i] == ' ')
			k++;
	}
	type = a[0];
	rawAddress = a[1];
	stringstream convert(a[2]);
	convert >> count;
	MemoryAddress m("s", "s", "s");
	binaryAddress.push_back(m);
}
	 
string Instruction::getInstructionType(){
	return type;
}
int Instruction::getInstructionCount(){
	return count;
}
MemoryAddress Instruction::getInstructionAddress(){
	return binaryAddress[0];
}

string Instruction::getRawAddress(){
	return rawAddress;
}

void Instruction::setInstructionType(char type){
	type = type;
}
void Instruction::setInstructionCount(int c){
	count = c;
}
void Instruction::setInstructionAddress(int tagSize, int setIndexSize){
	string binaryString = hextoBinary(rawAddress);
	// cout << binaryString << endl;
	string tag, setIndex, blockOffset;
	 for (int i = 0; i < 32; i++){
        if(i < tagSize)
            tag += binaryString[i];
        else if(i < tagSize + setIndexSize)
            setIndex += binaryString[i];
        else
            blockOffset += binaryString[i];
    }
    binaryAddress[0].setAddressTag(tag);
    binaryAddress[0].setAddressOffset(blockOffset);
    binaryAddress[0].setAddressIndex(setIndex);


}
void Instruction::setRawAddress(string a){
	rawAddress = a;
}

string Instruction::parseAddress(){
	string binaryString = hextoBinary(rawAddress);
	return binaryString;//Return in binary form
}