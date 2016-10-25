#include "header.h"
#include "cache.h"
// #include "block.h"

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
                Block b(1,0,"");
                
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
                // cout << associativity << "----?\n";
            // cout << "Block = " << ((size * 1024) / (blockSize) / associativity) << "+++" << endl;
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
        // void Cache::initializeBlocks(int lineNumbers){
        //     // for(int i = 0; i < lineNumbers;i++)
        //     // {
        //     //     Block b(0,0,"");
                
        //     //     blocks.push_back(b);
        //     // }
        // }
