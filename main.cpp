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

using namespace std;

void directMappedCache(Cache &c, MemoryAddress address, string operation){
    c.increaseMemRefs();

    int indexToSearch = bin2Dec(address.getAddressIndex()) % c.getLineNumbers(); 
    string st = "s";
    if(st.compare(operation) < 0){
        c.increaseStoreCount();
    }
    else{
        c.increaseLoadCount();
    }
    Block cur_block = c.blocks[indexToSearch];
    if(cur_block.getTag() == address.getAddressTag() && cur_block.getValid() == 1){
            if(st.compare(operation) < 0){
                c.increaseStoreHit();
            }
            else{
                c.increaseLoadHit();
            }
            c.increaseHit();
            cur_block.setDirty(1);
    }
    else{
        cur_block.setValid(1);

        c.increaseMiss();
        if(c.write_type == 1 && cur_block.getDirty() == 1){
            // write++
        }
        if(st.compare(operation) < 0){
            // c.increaseStoreHit();
            cur_block.setTag(address.getAddressTag());
        }
        else{

        }

    }
    c.blocks[indexToSearch] = cur_block;
}


void fullyAssociativeCache(Cache &c, MemoryAddress address, string operation){
    c.increaseMemRefs();
    int lineNumber = c.getLineNumbers();
    bool hit;
    string st = "s";
    if(st.compare(operation) < 0){
        c.increaseStoreCount();
    }
    else{
        c.increaseLoadCount();
    }
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
    bool hit;
    if(st.compare(operation) < 0){
            c.increaseStoreCount();
        }
        else{
            c.increaseLoadCount();
    }
    Block cur_block(0,0," ");
    int ways = c.getAssociativity();
    
    int startIndex = ways ;

    int endIndex = startIndex + (ways - 1);

    int numberofvalidEntry;
    for (int i = startIndex; i <= endIndex; i++){
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
    int indexTostart = startIndex;
    if(!hit){
        c.increaseMiss();
        //float a = rand() % c.getLineNumbers();
        if(st.compare(operation) < 0){ // write condition
            while(c.blocks[indexTostart].getValid() != 0){
                indexTostart++;
                numberofvalidEntry++;
                // a = rand() % c.getLineNumbers();
                cur_block = c.blocks[startIndex];
                if(numberofvalidEntry >= endIndex){
                    //no valid block so replace randomly of fifo
                    for(int i = startIndex; i <= endIndex; i++){
                        if(c.blocks[i].getValid() == 1){
                            indexTostart = i;
                            cur_block = c.blocks[i];
                        }
                    }
                    break;
                }
            }
            cur_block.setValid(1);
            cur_block.setTag(address.getAddressTag());
        }
        c.blocks[indexTostart] = cur_block;

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


    int hitRate = c.getHits() * 100 / c.getMemRefs();
    int loadHitRate = c.getLoadHits() * 100 / c.getLoad();
    int storeHitRate = c.getStoreHits() * 100 / c.getStore();

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

}

void writeIntoCache(Cache &c, MemoryAddress address){
    
    int indexToSearch;
    
}



int main(int argc,  char* argv[]){

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
        
        ins.setInstructionAddress(tagSize, setIndexSize);
        
        if(mapWays == 0){
            fullyAssociativeCache(cache, ins.getInstructionAddress(), ins.getInstructionType());
        }
        else if(mapWays == 1){
            directMappedCache(cache, ins.getInstructionAddress(),ins.getInstructionType());
        }else{
            nWaySetAssociative(cache, ins.getInstructionAddress(), ins.getInstructionType());
        }

    }
    cacheResults(cache , argv[2]);
  
    f.close();

	return 0;
}