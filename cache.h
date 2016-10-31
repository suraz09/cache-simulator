/*************************************************************************
/
/   filename: cache.h
/
/   description: Header for cache class.
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

#include "block.h"
#include <vector>

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
    int load;
    int store;
    int memRefs;
    vector<Block> blocks;

    Cache(int b, int a, int s, int r, int m,int w);
        
    void increaseHit();
    void increaseMemRefs();  
    void increaseMiss();
    void increaseLoadHit();
    void increaseStoreHit();

    void increaseLoadMiss();
    void increaseStoreMiss();


    void increaseStoreCount();
    void increaseLoadCount();


    int getMemRefs();
    int getHits();
    int getLoadHits();
    int getLoadMiss();
    int getStoreHits();
    int getStoreMiss();
    int getLoad();
    int getStore();
    int getMiss();

    int getBlockOffsetSize();

    int getSetIndexSize();
    int getLineNumbers();

    int getNumberofBlocks();
    int getIndex(int index);

    int getWriteType();
    int getReplacementPolicy();
    int getAssociativity();
    int getMissPenalty();
};