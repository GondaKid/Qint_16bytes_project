#include <bits/stdc++.h>

#include <iostream>
#include <string>

using namespace std;

class Conversion {
   public:
    static string convertDecToBin(const string& DecimalSrc);
    static string convertHexToBin(const string& HexSrc);
    static string convertBinToDec(const string& BinarySrc);
    static string convertBinToHex(const string& BinarySrc);

    //------------------ULTILITIES FUNCTIONS-------------------------
    static string StrDivTwo(const string&);
    //Hàm cộng hai chuỗi số.
    static string AddNumberString(string, string);
    //Hàm trừ hai chuỗi số dương.
    static string SubNumberString(string, string);
    //Hàm nhân hai chuỗi số.
    static string MultiplyNumberString(string, string);
    //Hàm tính a lũy thừa n (a, n là số nguyên không âm).
    static string Power(int, int);
};