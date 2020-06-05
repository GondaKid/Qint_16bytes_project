#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

#define MAX_SIZE 128

class Conversion {
   public:
    static string convertDecToBin(const string& DecimalSrc);
    static string convertHexToBin(const string& HexSrc);

    static string convertTo2Comp(const string& BinarySrc);

    //------------------ULTILITIES FUNCTIONS-------------------------
    static string DivDecByTwo(const string& DecimalSrc);  //Divide positive Decimal string by two
    static void removeLeadingNums(string& BinarySrc, const char& bit);
};