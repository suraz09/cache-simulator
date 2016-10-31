/*************************************************************************
/
/   filename: main.cpp
/
/   description: Implements the cache simulator.
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
#include "cache.h"
#include "instruction.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <iomanip>


using namespace std;
int count;
void directMappedCache(Cache &c, MemoryAddress address, string operation){
    c.increaseMemRefs();
    int indexToSearch = bin2Dec(address.getAddressIndex()) % c.getLineNumbers(); 
    string st = "s";
    Block cur_block = c.blocks[indexToSearch];
    if(cur_block.getTag() == address.getAddressTag() && cur_block.getValid() == 1){
        count++;
        if(st.compare(operation) < 0){
            c.increaseStoreHit();
            cur_block.setTag(address.getAddressTag());
            cur_block.setDirty(1);
        }
        else{
            c.increaseLoadHit();
        }
        c.increaseHit();
    }
    else{
        if(st.compare(operation) < 0){
            c.increaseStoreMiss();
            if(c.getWriteType() == 1){
                cur_block.setTag(address.getAddressTag());
                cur_block.setDirty(1);
                cur_block.setValid(1);
            }
        }
        else{
            c.increaseLoadMiss();
            cur_block.setTag(address.getAddressTag());
            cur_block.setValid(1);
        }
        c.increaseMiss();

    }
    c.blocks[indexToSearch] = cur_block;
}


void fullyAssociativeCache(Cache &c, MemoryAddress address, string operation){
    c.increaseMemRefs();
    int lineNumber = c.getLineNumbers();
    bool hit = false;
    string st = "s";

    Block cur_block(0,0," ");
    int numberofvalidEntry = 0;;
    for (int i = 0; i < lineNumber ; i++){
        cur_block = c.blocks[i];
        if(cur_block.getTag() == address.getAddressTag() && cur_block.getValid() == 1){
            c.increaseHit();
            if(st.compare(operation) < 0){
                c.increaseStoreHit();
            }
            else{
                c.increaseLoadHit();
            }
            cur_block.setTag(address.getAddressTag());
            hit = true;
            cur_block.setDirty(1);            
            cur_block.setValid(1);
            c.blocks[i] = cur_block;
            break;
            return;
        }
        else if(cur_block.getValid() == 0){
            c.increaseMiss();
            if(st.compare(operation) < 0){
                c.increaseStoreHit();
            }
            else{
                c.increaseLoadHit();
            }
            cur_block.setTag(address.getAddressTag());
            hit = true;
            cur_block.setDirty(1);            
            cur_block.setValid(1);
            break;
            return;
        }
    }
    if(!hit){
        c.increaseMiss();
        float a = rand() % c.getLineNumbers();

        if(c.getReplacementPolicy() == 0){ //random replacement
            if(st.compare(operation) < 0){
                c.increaseStoreMiss();
                if(c.getWriteType() == 1){ //write allocate
                    cur_block = c.blocks[a];
                    cur_block.setTag(address.getAddressTag());
                    cur_block.setDirty(1);
                    cur_block.setValid(1);
                    c.blocks[a] = cur_block;
                }
            }
            else{ //read operation miss
                c.increaseLoadMiss();
                cur_block = c.blocks[a];
                cur_block.setTag(address.getAddressTag());
                cur_block.setValid(1);
                c.blocks[a] = cur_block;
            }
        }
        else{
            for (int i = 0; i < lineNumber -1 ; i++){
                c.blocks[i] = c.blocks[i+1];
            }
            c.blocks[lineNumber - 1].setTag(address.getAddressTag());
            c.blocks[lineNumber - 1].setDirty(1);
            c.blocks[lineNumber - 1].setValid(1);
        }
    }
    
}

void nWaySetAssociative(Cache &c, MemoryAddress address, string operation, Instruction ins){
    c.increaseMemRefs();
    string st = "s";
    bool hit = false;
    Block cur_block(0,0," ");
    int ways = c.getAssociativity();
    int startIndex = ways  * bin2Dec(address.getAddressIndex());
    int endIndex = startIndex + (ways - 1);
    int counter = 0;
    int numberofvalidEntry;
    for (int i = startIndex; i <= endIndex; i++){
        cur_block = c.blocks[i];
        if(cur_block.getValid() ==1)   
            counter++;
        if(cur_block.getTag() == address.getAddressTag() && cur_block.getValid() == 1){
            c.increaseHit();
            if(st.compare(operation) < 0){
                c.increaseStoreHit();
            }
            else{
                c.increaseLoadHit();
            }
            cur_block.setTag(address.getAddressTag());
            hit = true;
            cur_block.setDirty(1);            
            cur_block.setValid(1);
            cur_block.setTimeStamp( i % ways);

            c.blocks[i] = cur_block;
            counter = 0;

            break;
            return;
        }
        else if(cur_block.getValid() == 0){
            // cout << c.getMiss() << endl;
            c.increaseMiss();
            if(st.compare(operation) < 0){
                c.increaseStoreHit();
            }
            else{
                c.increaseLoadHit();
            }
            cur_block.setTag(address.getAddressTag());
            hit = true;
            cur_block.setDirty(1);            
            cur_block.setValid(1);
            cur_block.setTimeStamp( i % ways);

            c.blocks[i] = cur_block;
            counter = 0;
            break;
            return;
        }   
    }
    int indexTostart = startIndex;

    if(counter >= ways){
        c.increaseMiss();
        
        int a = (int)(rand() % (startIndex - (endIndex) ) + startIndex );
        //This is a miss condition read or write
        if(c.getReplacementPolicy() == 0){ //random replacement
             if(st.compare(operation) < 0){
                c.increaseStoreMiss();
                if(c.getWriteType() == 1){ //write allocate
                    cur_block = c.blocks[a];
                    cur_block.setTag(address.getAddressTag());
                    cur_block.setDirty(1);
                    cur_block.setValid(1);
                    c.blocks[a] = cur_block;
                }
            }
            else{ //read operation miss
                c.increaseLoadMiss();
                cur_block = c.blocks[a];
                cur_block.setTag(address.getAddressTag());
                cur_block.setValid(1);
                c.blocks[a] = cur_block;
            }
        }
        else{ 
             if(st.compare(operation) < 0){
                c.increaseStoreMiss();
                if(c.getWriteType() == 1){ //write allocate
                    for (int i = startIndex; i < endIndex; i++){
                    c.blocks[i] = c.blocks[i+1];
                }
                cur_block.setTag(address.getAddressTag());
                    // cur_block.setDirty(1);
                    cur_block.setValid(1);
                c.blocks[endIndex].setTag(address.getAddressTag());
                c.blocks[endIndex].setDirty(1);
                c.blocks[endIndex].setValid(1);

                                 
                }
            }
            else{
                c.increaseLoadMiss();
                for (int i = startIndex; i < endIndex; i++){
                    c.blocks[i] = c.blocks[i+1];
                }
                c.blocks[endIndex].setTag(address.getAddressTag());
                c.blocks[endIndex].setDirty(1);
                c.blocks[endIndex].setValid(1);
                                
            }
        }

    }
}

void readFromCache(Cache &c, MemoryAddress address){
    int indexToSearch;
    int operation = 0;
}



void cacheResults(Cache &c, string fileName, int insCount){
    int ins = insCount;
    cout << "Total Hits => " << c.getHits() << endl;
    cout << "Total Miss => " << c.getMiss() << endl;

    float hitRate = (float)(c.getHits() * 100  / (float)c.getMemRefs()); // Multiply by 100 for percentage
    float missRate = (float)(c.getMiss()  / (float)c.getMemRefs()); // Multiply by 100 for percentage

    float loadHitRate = (float)c.getLoadHits() * 100 / (float)c.getLoad();
    float storeHitRate = (float)c.getStoreHits() * 100 / (float)c.getStore();

    cout << "Total Hit rate =>" << hitRate << "\%" << endl;
    cout << "Load hit rate =>" << loadHitRate << "\%" << endl;
    cout << "Store hit rate =>" << storeHitRate << "\%" << endl;
    cout << "Total miss rate => " << missRate << endl;

    
    float memRefs = (float)c.getMemRefs();
    int miss_penalty = c.getMissPenalty();

    int TotalRunTime = memRefs + (c.getMiss() * miss_penalty ) + insCount;

    float amal = (1) + (missRate * miss_penalty);
    cout << "Total Run time => " << TotalRunTime  << " cycles" << endl;

    cout    << "AMAl => " << amal << " cycles" << endl;


    ofstream myfile;
    string outPutFile = "./output/" + fileName.substr(9) + ".out";
    myfile.open (outPutFile.c_str());
    myfile << "Total Hit rate: " << hitRate << "\%\n" ;
    myfile << "Load hit rate: " << loadHitRate << "\%" << endl;
    myfile << "Store hit rate: " << storeHitRate << "\%" << endl;
    myfile << "Total Run Time: " << TotalRunTime << " cycles" << endl;
    myfile << "Average Memory Access Latency: " << amal  << " cycles" << endl;

    myfile.close();
}

void writeIntoCache(Cache &c, MemoryAddress address){
    int indexToSearch;
}

int main(int argc,  char* argv[]){

    int TotalCount = 0;
    cout << "-------CACHE SIMULATOR--------"<<endl;
    cout << "Simulating the results"<<endl;
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
    
    int mapWays = cache.getAssociativity();
    int setIndexSize = cache.getSetIndexSize(), blockOffsetSize = cache.getBlockOffsetSize();
    int tagSize = 32 - setIndexSize - blockOffsetSize, index;

    if(mapWays == 0){
        cout<< "fullyAssociativeCache" << endl;     
    }
    else if(mapWays == 1){
        cout<< "Direct Mapped Cached" << endl;     
    }else{
        cout<< "Set Associative Cache" << endl;     
    }

    if(cache.getReplacementPolicy() == 0){
        cout<< "Random Replacement" << endl;     
    }else{
        cout<< "FIFO replacement" << endl;     
    }

    if(cache.getWriteType() == 0){
        cout<< "No write allocate" << endl;     
    }else{
        cout<< "Write Allocate" << endl;     
    }

    string f2 = argv[2];
    fstream f;
    f.open(f2.c_str());
    string inst;
    while (getline( f, inst)){
        
        Instruction ins(inst);
        TotalCount+= ins.getInstructionCount();
        ins.setInstructionAddress(tagSize, setIndexSize);

        string st = "s";
        if(st.compare(ins.getInstructionType()) < 0){ //Write operation
            cache.increaseStoreCount();
        }
        else{
            cache.increaseLoadCount();
        }   
        if(mapWays == 0){
            fullyAssociativeCache(cache, ins.getInstructionAddress(), ins.getInstructionType());
        }
        else if(mapWays == 1){
            directMappedCache(cache, ins.getInstructionAddress(),ins.getInstructionType());
        }else{
            nWaySetAssociative(cache, ins.getInstructionAddress(), ins.getInstructionType(), ins);
        }

    }
    cacheResults(cache , argv[2],TotalCount);
    f.close();

	return 0;
}