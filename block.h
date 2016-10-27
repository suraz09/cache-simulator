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