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
            for(int i = 0; i < getLineNumbers();i++)
            {
                Block b(0,0,"");
                
                blocks.push_back(b);
            }
        }
        
        void Cache::increaseHit(){
            hit++;
        }
        void Cache::increaseMiss(){
            miss++;
        }

        int Cache::getHits(){
            return hit;
        }

        int Cache::getMiss(){
            return miss;
        }

        int Cache::getBlockOffsetSize(){
            return log2(blockSize);
        }

        int Cache::getSetIndexSize(){
            return log2((size * 1024) / (blockSize)/  associativity);
        }
        int Cache::getLineNumbers(){
            return (size * 1024) / (blockSize * associativity);
        }
    
        int Cache::getBlock(string setIndex){
            
            return 1;
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
