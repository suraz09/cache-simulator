#include "hellomake.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Block {
public:
    int valid;
    string tag;
    int dirty;

    void setValid(int v){
        valid = v;
    }

    void setDirty(int d){
        dirty = d;
    }

    void setTag(string t){
        tag = t;
    }
    int getValid(){
        return valid;
    }
    int getDirty(){
        return dirty;
    }

    string getTag(){
        return tag;
    }
};



class Cache{    
public:
    int blockSize;
    int associativity;
    int size;
    int replacement_policy;
    int miss_penalty;
    int write_type;
    int miss;
    int hit;
    int loadhit;
    int loadmiss;
    int storemiss;
    int storehit;
        // Block blocks[10];
        std::vector<Block> blocks;
        Cache(int b, int a, int s, int r, int m,int w){
            blockSize = b;
            associativity = a;
            size = s;
            replacement_policy = r;
            miss_penalty = m;
            write_type = w;
            miss = 0;
            hit = 0;
            loadmiss = 0;
            loadhit = 0;
            storemiss = 0;
            storehit = 0;
        }
        
        void increaseHit(){
            hit++;
        }
        void increaseMiss(){
            miss++;
        }

        int getHits(){
            return hit;
        }

        int getMiss(){
            return miss;
        }

        int getBlockOffsetSize(){
            return log2(blockSize);
        }

        int getSetIndexSize(){
            return log2((size * 1024) / (blockSize)/  associativity);
        }
        int getLineNumbers(){
            return (size * 1024) / (blockSize * associativity);
        }
    
        int getBlock(string setIndex){
            
            return 1;
        }
        int getIndex(int index){

        }
        
};
class Address{
public:
    string tag;
    string offset;
    string index;

    void setAddressTag(string addressTag){
        tag = addressTag;
    }

    void setAddressOffset(string addressOffset){
        offset = addressOffset;
    }

    void setAddressIndex(string addressIndex){
        index = addressIndex;
    }

    string getAddressTag(){
        return tag;
    }
    string getAddressOffset(){
        return offset;
    }
    string getAddressIndex(){
        return index;
    }
};


void readFromCache(Cache &c, Address address){
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



int main(){
	
	string str = "0xffffff50";
	cout << "str3 : " << str << endl;
    string binaryString = hextoBinary(str);
    Cache cache(8,1,16,1,100,1);
    Address a;
    cout << "Cahe -------------------------------------------------\n";
    cout<< "Number of sets line \t" << cache.getLineNumbers() << endl;
    cout << "-------------------------------------------------------------|"<<endl;
    cout << str+"|\t" << binaryString  << "\t|" << binaryString.size() << endl;
    int setIndexSize = cache.getSetIndexSize(), blockOffsetSize = cache.getBlockOffsetSize();
    int tagSize = 32 - setIndexSize - blockOffsetSize, index;
    string tag;
    string setIndex;
    string blockOffset;
    cache.getBlock(setIndex);
    for(int i = 0; i < 20;i++)
    {
        Block b;
        b.setValid(0);
        b.setDirty(0);
        b.setTag("");
        cache.blocks.push_back(b);
    }
    cache.blocks[16].setTag("111111111111111111");

    cout << "Memory address Format-------------------------------------------------------------|"<<endl;

    
    for (int i = 0; i < binaryString.size(); i++){
        if(i < tagSize)
            tag += binaryString[i];
        else if(i < tagSize + setIndexSize)
            setIndex += binaryString[i];
        else
            blockOffset += binaryString[i];
    }
    ;
    a.setAddressTag(tag);
    a.setAddressOffset(blockOffset);
    a.setAddressIndex(setIndex);
    cout << "TAG " << tagSize << "\t" << hextoDec(tag) << "\t";
    printAddress(tag);
    cout << "SetIndex " << setIndexSize << "\t" << hextoDec(setIndex) << "\t";
    printAddress(setIndex);
    cout << "Offset " << blockOffsetSize << "\t" << hextoDec(blockOffset) << "\t";
    printAddress(blockOffset);
    index = hextoDec(setIndex) % cache.getLineNumbers();

    cout << "\nRow in which the block is placed is" << index << endl;

    readFromCache(cache, a);
    cacheResults(cache);
	return 0;
}