/*************************************************************************
/
/   filename: cache.cpp
/
/   description: Implements the class Cache
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
#include <cmath>
#include <string>
#include <iostream>

Cache::Cache(int b, int a, int s, int r, int m,int w){
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
    load = 0;
    store = 0;
    memRefs = 0;
    for(int i = 0; i < getLineNumbers();i++)
    {
        Block b(0,0,"");
        
        blocks.push_back(b);
    }
}

void Cache::increaseHit(){
    hit++;
}
void Cache::increaseLoadHit(){
    loadhit++;
}
void Cache::increaseStoreHit(){
    storehit++;
}

void Cache::increaseStoreMiss(){
    storemiss++;
}

void Cache::increaseLoadMiss(){
    loadmiss++;
}

void Cache::increaseMiss(){
    miss++;
}
void Cache::increaseMemRefs(){
    memRefs++;
}
void Cache::increaseStoreCount(){
    store++;
}
void Cache::increaseLoadCount(){
    load++;
}

int Cache::getLoadHits(){
    return loadhit;
}
int Cache::getStoreHits(){
    return storehit;
}
int Cache::getStoreMiss(){
    return storemiss;
}
int Cache::getLoadMiss(){
    return loadmiss;
}
int Cache::getMemRefs(){
    return memRefs;
}
int Cache::getLoad(){
    return load;
}
int Cache::getStore(){
    return store;
}
int Cache::getHits(){
    return hit;
}

int Cache::getMiss(){
    return miss;
}

int Cache::getAssociativity(){
    return associativity;
}

int Cache::getBlockOffsetSize(){
    return log2(blockSize);
}

int Cache::getSetIndexSize(){
    if(associativity == 0)
        return 0;
    return log2((size * 1024) / (blockSize) / associativity);
}
int Cache::getLineNumbers(){
    return (size * 1024) / (blockSize);
}

int Cache::getNumberofBlocks(){
     if(associativity == 0)
        return ((size * 1024) / (blockSize) / associativity);
    return ((size * 1024) / (blockSize) / associativity);
}
int Cache::getIndex(int index){

}
int Cache::getWriteType(){
    return write_type;
}
int Cache::getReplacementPolicy(){
    return replacement_policy;
}
int Cache::getMissPenalty(){
    return miss_penalty;
}

