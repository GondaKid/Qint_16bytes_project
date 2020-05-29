#include <typeinfo>

#include "./Header/MainLoop.h"

int main() {
    string num = "10110111010110";
    string dec = Conversion::convertBinToDec(num);
    cout << dec << endl;
    return 0;
}