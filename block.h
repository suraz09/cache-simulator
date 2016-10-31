/*************************************************************************
/
/   filename: block.h
/
/   description: Header for cache blocks
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

class Block {
public:
    int valid;
    string tag;
    int dirty;
    int timeStamp;
    Block(int v, int d, string s);

    void setValid(int v);

    void setDirty(int d);

    void setTag(string t);

    void setTimeStamp(int time);

    int getValid();

    int getDirty();

    string getTag();

    int getTimeStamp();
};