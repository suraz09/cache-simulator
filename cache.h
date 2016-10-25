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
    void increaseStoreCount();
    void increaseLoadCount();


    int getMemRefs();
    int getHits();
    int getLoadHits();
    int getStoreHits();
    int getLoad();
    int getStore();
    int getMiss();

    int getBlockOffsetSize();

    int getSetIndexSize();
    int getLineNumbers();

    int getNumberofBlocks();
    int getIndex(int index);

    int getAssociativity();
    // void initializeBlocks(int lineNumbers);
    
};