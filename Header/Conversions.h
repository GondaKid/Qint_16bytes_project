#include "./Qint.h"

class Conversion {
   public:
    static void RepairString(string& str);
    static void convertDecimalToBinary(string& DecimalSrc, string& BinaryDest);
    static void convertBinaryToDecimal(string& BinarySrc, string& DecimalDest);
    static void convertHexToBinary(string& HexSrc, string& BinDest);
};