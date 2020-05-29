#include <iostream>
#include <string>

using namespace std;

class Conversion {
   public:
    static string convertDecToBin(const string& DecimalSrc);
    static string convertHexToBin(const string& HexSrc);
    static string convertBinToDec(const string& BinarySrc);
    static string convertBinToHex(const string& BinarySrc);
};