class Block {
public:
    int valid;
    string tag;
    int dirty;
    Block(int v, int d, string s);

    void setValid(int v);

    void setDirty(int d);

    void setTag(string t);

    int getValid();

    int getDirty();

    string getTag();
};