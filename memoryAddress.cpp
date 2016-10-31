/*************************************************************************
/
/   filename: memoryAddress.cpp
/
/   description: Implements the class MemoryAddress
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

#include "header.h"
#include "memoryAddress.h"
#include <string>

MemoryAddress::MemoryAddress(string t, string o, string i){
    tag = "";
    offset = "";
    index = "";
}
void MemoryAddress::setAddressTag(string addressTag){
    tag = addressTag;
}

void MemoryAddress::setAddressOffset(string addressOffset){
    offset = addressOffset;
}

void MemoryAddress::setAddressIndex(string addressIndex){
    index = addressIndex;
}

string MemoryAddress::getAddressTag(){
    return tag;
}
string MemoryAddress::getAddressOffset(){
    return offset;
}
string MemoryAddress::getAddressIndex(){
    return index;
}
