#include "../Header/Conversions.h"

string Conversion::convertDecToBin(const string& DecimalSrc) {
    //convert non-negative decimal string
    string dividedString = DecimalSrc;  //assign divided string
    string resString = "";              //result string
    while (dividedString != "0") {
        resString = char((dividedString.back() - '0') % 2 + '0') + resString;  //check whether divided string is an odd or even number,
                                                                               //then push the digit to front of result string
        dividedString = DivDecByTwo(dividedString);
    }
    //check if its negative
    if (DecimalSrc.at(0) == '-') {
        resString = convertTo2Comp(resString);
    }

    return resString;
}
string Conversion::convertHexToBin(const string& HexSrc) {
    string result = "";
    for (char chr : HexSrc) {
        switch (chr) {
            case '0':
                result += "0000";
                break;
            case '1':
                result += "0001";
                break;
            case '2':
                result += "0010";
                break;
            case '3':
                result += "0011";
                break;
            case '4':
                result += "0100";
                break;
            case '5':
                result += "0101";
                break;
            case '6':
                result += "0110";
                break;
            case '7':
                result += "0111";
                break;
            case '8':
                result += "1000";
                break;
            case '9':
                result += "1001";
                break;
            case 'A':
            case 'a':
                result += "1010";
                break;
            case 'B':
            case 'b':
                result += "1011";
                break;
            case 'C':
            case 'c':
                result += "1100";
                break;
            case 'D':
            case 'd':
                result += "1101";
                break;
            case 'E':
            case 'e':
                result += "1110";
                break;
            case 'F':
            case 'f':
                result += "1111";
                break;
        }
    }

    return result;
}

string Conversion::convertTo2Comp(const string& BinarySrc) {
    string resString;

    int i = BinarySrc.length() - 1;
    //First loop, copy source string to result string until meet first digit 1
    do {
        resString = BinarySrc.at(i) + resString;
        i--;
    } while (BinarySrc.at(i + 1) != '1');

    //Second loop, flip all bit in source string and add to result string
    for (; i >= 0; i--) {
        if (BinarySrc.at(i) == '1')
            resString = '0' + resString;
        else
            resString = '1' + resString;
    }
    //check if src string is negative
    if (BinarySrc.length() == MAX_SIZE && BinarySrc.front() == '1')
        removeLeadingZeros(resString);  //remove leading 0s
    else
        //Add 1(s) to start of result string
        resString = string(MAX_SIZE - resString.length(), '1') + resString;

    return resString;
}

//------------------ULTILITIES FUNCTIONS-------------------------
string Conversion::DivDecByTwo(const string& DecimalSrc) {
    string dividedString;
    int next_additive = 0;
    for (const char curr : DecimalSrc) {
        if (curr == '-')  //Ignoring negative symbol
            continue;
        else {
            int additive = next_additive;
            next_additive = ((curr - '0') % 2 ? 5 : 0);
            int tempCurr = (curr - '0') / 2 + additive;
            dividedString.push_back(char(tempCurr + '0'));
        }
    }
    //delete leading 0s
    removeLeadingZeros(dividedString);

    return ((dividedString != "") ? dividedString : "0");
}
void Conversion::removeLeadingZeros(string& BinarySrc) {
    int count = 0;
    for (auto bit : BinarySrc) {
        if (bit != '0')
            break;
        count++;
    }

    if (BinarySrc != string(count, '0')) {  //if source is not a string of 0. Ex: 0000000
        BinarySrc.erase(0, count);
    } else                              //if source is a string of 0.
        BinarySrc.erase(0, count - 1);  //left the last 0
}