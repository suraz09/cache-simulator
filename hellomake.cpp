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

    // Block(int v, int d, string t){
    //     valid = v;
    //     dirty = d;
    //     tag = t;
    // }

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
    int blockSize;
    int associativity;
    int size;
    int replacement_policy;
    int miss_penalty;
    int write_type;
    
    public:

        // Block blocks[10];
        std::vector<Block> blocks;
        Cache(int b, int a, int s, int r, int m,int w){
            blockSize = b;
            associativity = a;
            size = s;
            replacement_policy = r;
            miss_penalty = m;
            write_type = w;
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


void readFromCache(Cache c){
    cout << endl;
    for (int i = 0 ; i < 20; i++){
    // cout << endl;
    }
}




int main(){
	
	string str = "0xffffff50";
	cout << "str3 : " << str << endl;
    string binaryString = hextoBinary(str);
    Cache cache(8,1,16,1,100,1);
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
    readFromCache(cache);

    cout << "Memory address Format-------------------------------------------------------------|"<<endl;

    
    for (int i = 0; i < binaryString.size(); i++){
        if(i < tagSize)
            tag += binaryString[i];
        else if(i < tagSize + setIndexSize)
            setIndex += binaryString[i];
        else
            blockOffset += binaryString[i];
    }

    cout << "TAG " << tagSize << "\t" << hextoDec(tag) << "\t";
    printAddress(tag);
    cout << "SetIndex " << setIndexSize << "\t" << hextoDec(setIndex) << "\t";
    printAddress(setIndex);
    cout << "Offset " << blockOffsetSize << "\t" << hextoDec(blockOffset) << "\t";
    printAddress(blockOffset);
    index = hextoDec(setIndex) % cache.getLineNumbers();

    cout << "\nRow in which the block is placed is" << index << endl;

    string address = "ffffff50";
    readFromCache(cache, address);

	return 0;
}