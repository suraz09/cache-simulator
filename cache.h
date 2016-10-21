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
    vector<Block> blocks;

    Cache(int b, int a, int s, int r, int m,int w);
        
    void increaseHit();
        
    void increaseMiss();

    int getHits();

    int getMiss();

    int getBlockOffsetSize();

    int getSetIndexSize();
    int getLineNumbers();

    int getBlock(string setIndex);
    int getIndex(int index);
    // void initializeBlocks(int lineNumbers);
    
};