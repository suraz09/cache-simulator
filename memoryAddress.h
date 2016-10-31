/*************************************************************************
/
/   filename: memoryAddress.h
/
/   description: Header for MemoryAddress Class
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

#include <string>
class MemoryAddress{
public:
    string tag;
    string offset;
    string index;
    MemoryAddress(string t, string o, string i);
    
    void setAddressTag(string addressTag);

    void setAddressOffset(string addressOffset);

    void setAddressIndex(string addressIndex);

    string getAddressTag();

    string getAddressOffset();

    string getAddressIndex();
};