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
            if(c.getWriteType() == 1){
                cur_block.setTag(address.getAddressTag());
                cur_block.setDirty(1);
                cur_block.setValid(1);
            }
        }
        else{
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
    bool hit;
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
            hit = true;
            break;
            cur_block.setDirty(1);            
        }
    }
    if(!hit){
        c.increaseMiss();
        float a = rand() % c.getLineNumbers();
        if(st.compare(operation) < 0){ // write condition
            while(c.blocks[a].getValid() != 0){
                numberofvalidEntry++;
                a = rand() % c.getLineNumbers();
                cur_block = c.blocks[a];
                if(numberofvalidEntry >= lineNumber){
                    for(int i = 0; i < lineNumber; i++){
                        if(c.blocks[i].getValid() == 0){
                            cur_block = c.blocks[i];
                        }
                    }
                    break;
                }
            }
            cur_block.setValid(1);
            cur_block.setTag(address.getAddressTag());
        }
        c.blocks[a] = cur_block;

    }
    
}

void nWaySetAssociative(Cache &c, MemoryAddress address, string operation){
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
            c.blocks[i] = cur_block;
            break;
        }
        else if(cur_block.getValid() == 0){
            c.increaseMiss();
            cur_block.setTag(address.getAddressTag());
            // hit = true;
            cur_block.setDirty(1);            
            cur_block.setValid(1);
            c.blocks[i] = cur_block;
            break;
        }   
    }
    int indexTostart = startIndex;

    if(counter >= ways){
        c.increaseMiss();
        
        int a = (int)(rand() % (startIndex - (endIndex) ) + startIndex );
        //This is a miss condition read or write
        if(c.getReplacementPolicy() == 0){ //random replacement
             if(st.compare(operation) < 0){
                if(c.getWriteType() == 1){ //write allocate
                    cur_block = c.blocks[a];
                    cur_block.setTag(address.getAddressTag());
                    cur_block.setDirty(1);
                    cur_block.setValid(1);
                    c.blocks[a] = cur_block;
                    // c.increaseStoreHit();
                }
            }
            else{ //read operation miss
                cur_block = c.blocks[a];
                cur_block.setTag(address.getAddressTag());
                cur_block.setValid(1);
                c.blocks[a] = cur_block;
            }
        }
        else{
            //FIFO replacement
        }

    }
}

void readFromCache(Cache &c, MemoryAddress address){
    int indexToSearch;
    int operation = 0;
}



void cacheResults(Cache &c, string fileName){
    cout << "Total Hits => " << c.getHits() << endl;
    cout << "Total Memory References => " << c.getMemRefs() << endl;
    cout << "Total Load Hits => " << c.getLoadHits() << endl;
    cout << "Total Store Hits => " << c.getStoreHits() << endl;

    cout << "Total Store => " << c.getStore() << endl;
    cout << "Total Load => " << c.getLoad() << endl;


    float hitRate = (float)c.getHits() * 100 / c.getMemRefs();
    float loadHitRate = (float)c.getLoadHits() * 100 / c.getLoad();
    float storeHitRate = (float)c.getStoreHits() * 100 / c.getStore();

    cout << "Total Hit rate =>" << hitRate << "\%" << endl;
    cout << "Load hit rate =>" << loadHitRate << "\%" << endl;
    cout << "Store hit rate =>" << storeHitRate << "\%" << endl;
    string outPutFile = fileName + ".out";
    ofstream myfile;
    myfile.open (outPutFile.c_str());
    myfile << "Total Hit rate =>" << hitRate << "\%\n" ;
    myfile << "Total Hit rate =>" << hitRate << "\%" << endl;
    myfile << "Load hit rate =>" << loadHitRate << "\%" << endl;
    myfile << "Store hit rate =>" << storeHitRate << "\%" << endl;
    myfile.close();
    cout  << count;

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
            nWaySetAssociative(cache, ins.getInstructionAddress(), ins.getInstructionType());
            // cout << (ins.getInstructionAddress().getAddressIndex()) << endl;
        }

    }
    cacheResults(cache , argv[2]);
    cout << "Total Ins Count =" << TotalCount << endl;
  
    f.close();

	return 0;
}