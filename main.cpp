#include "header.h"
#include "cache.h"
#include "instruction.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void readFromCache(Cache &c, MemoryAddress address){
    cout << endl;
    int indexToSearch;
    indexToSearch = hextoDec(address.getAddressIndex()) % c.getLineNumbers(); 
    cout<<address.getAddressTag() << "\n";
    cout << c.blocks[indexToSearch].getTag() + "123123123123";
     if(c.blocks[indexToSearch].getTag() == address.getAddressTag()){
            cout<< "Yeah I have a hit";
            c.increaseHit();
            cout << c.getHits();

        }
        else{
            cout << "I Miss";
            c.increaseMiss();
        }
    
}

void cacheResults(Cache c){
    cout << "\nCache hits" << c.getHits();
    cout << "\nCache miss" << c.getMiss() << endl;
}



int main(int argc,  char* argv[]){

    string f1 = argv[1];
    fstream t;
    t.open(f1.c_str());
    string c;
    int a[6], i = 0;
    while (getline( t, c)){
        stringstream convert(c);
        convert >> a[i];
        i++;
    }
    //Create a new cache according to the config.
    Cache  cache(a[0],a[1],a[2],a[3],a[4],a[5]);
    t.close();

    string f2 = argv[2];
    fstream f;
    f.open(f2.c_str());
    string inst;

    while (getline( f, inst)){

        // cout << inst << endl;
        Instruction ins(inst);
        int setIndexSize = cache.getSetIndexSize(), blockOffsetSize = cache.getBlockOffsetSize();
        int tagSize = 32 - setIndexSize - blockOffsetSize, index;
        ins.setInstructionAddress(tagSize, setIndexSize);
        // cout<< endl<<ins.binaryAddress[0].getAddressIndex() << endl;
        // cout << hextoDec(ins.binaryAddress[0].getAddressIndex()) << endl;

        cout << cache.getLineNumbers();

        index = hextoDec(ins.binaryAddress[0].getAddressIndex()) % cache.getLineNumbers();
        cout << "Index ->"<<index << endl;
    }
    
    // string inst = "s 0xffffdc66 1";    
    // string binaryString = ins.parseAddress();

    // ins.mem[0].setAddressTag("11121");
    // MemoryAddress a("s", "s", "s");
    
    

    // cache.blocks[16].setTag("111111111111111111"); //Test cases for hit or miss;

    // cout << ins.binaryAddress[0].getAddressIndex() << endl;
    // cout << hextoDec(ins.binaryAddress[0].getAddressIndex()) << endl;

    // cout << cache.getLineNumbers();

    // cout << "\nRow in which the block is placed is" << index << endl;

    // readFromCache(cache, a);
    // cacheResults(cache);
    f.close();

	return 0;
}