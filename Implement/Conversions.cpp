#include "../Header/Conversions.h"
string Conversion::convertFromBin(string BinarySrc, const int& destBase) {
    string result = "";
    const unsigned int numberBase = destBase;

    while (count(BinarySrc.begin(), BinarySrc.end(), '1')) {  //check if BinarySrc still have '1' in string
        unsigned int remainder = 0;
        // Temporary result of integer division
        string dividedNumberAsString = "";

        // Do the division
        for (const char bit : BinarySrc) {
            // Claculate the remainder
            remainder = remainder * 2 + (bit - '0');

            // If we have a overflow (e.g. number is bigger than 10
            if (remainder >= numberBase) {
                // Handle overflow
                remainder -= numberBase;
                // Add 1 to the "devidedString"
                dividedNumberAsString += "1";
            } else {
                dividedNumberAsString += "0";
            }
        }

        BinarySrc = dividedNumberAsString;
        // The remainder is the number that we are interested in
        result.insert(0, 1, '0' + remainder);
    }

    return (result == "") ? "0" : result;
}

string Conversion::convertDecToBin(const string& DecimalSrc) {
    return "";
}
string Conversion::convertHexToBin(const string& HexSrc) {
    return "";
}