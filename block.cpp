#include "header.h"
#include "block.h"
#include <string>


Block::Block(int v, int d, string s){
    valid = v;
    dirty = d;
    tag = s;
    timeStamp = 0;
}

void Block::setValid(int v){
    valid = v;
}

void Block::setDirty(int d){
    dirty = d;
}

void Block::setTag(string t){
    tag = t;
}
void Block::setTimeStamp(int time){
    timeStamp = time;
}

int Block::getValid(){
    return valid;
}
int Block::getDirty(){
    return dirty;
}

string Block::getTag(){
    return tag;
}

int Block::getTimeStamp(){
    return timeStamp;
}
