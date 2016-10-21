#include <string>
class MemoryAddress{
public:
    string tag;
    string offset;
    string index;
    // MemoryAddress();
    MemoryAddress(string t, string o, string i);
    void setAddressTag(string addressTag);

    void setAddressOffset(string addressOffset);

    void setAddressIndex(string addressIndex);

    string getAddressTag();

    string getAddressOffset();

    string getAddressIndex();
};