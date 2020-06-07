#include <bitset>
#include <fstream>
#include <vector>

#include "Conversions.h"

#define MAX_QINT "01111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"

class QInt {
   private:
    bitset<MAX_SIZE> arrayBits;  //bitset arrays

   public:
    //-----------------DEFAULT CONSTRUCT & DESTRUCT FUNCTION-------------------
    QInt();
    QInt(const string& numString, const int& base);  //Create a Qint from a string with it's base
    ~QInt();

    //------------------ULTILITIES--------------------
    void set(const size_t& pos, const int& setValue = 1);  //set value of a bit
    void push_front(const bool& bit, const int& n);        //push a bit to front
    void push_back(const bool& bit, const int& n);         //push a bit to back

    //------------------GET FUNCTIONS--------------------
    string getBin();  //convert to binary string
    string getDec();  //convert to decimal string
    string getHex();  //convert to hexadecimal string
    int getSize();    //get actual size of arraybits (leading 0s is not included)
    bool isNegative();
    bool equalZero();                 //check if QInt is equal zero or not
    bool isGreaterThan(QInt other);   //return true if this >= other, false if this < other
    bool isMulOverflow(QInt& other);  //check if the result of multiplucation is overflow or not

    //-------------------OPERATORS-----------------------------
    QInt operator+(QInt other);
    QInt operator-(QInt other);
    QInt operator*(QInt other);
    QInt operator/(QInt other);
    QInt& operator=(const QInt& other);

    QInt operator>>(const unsigned int& Sbit);
    QInt operator<<(const unsigned int& Sbit);
    QInt operator&(const QInt& other);
    QInt operator^(const QInt& other);
    QInt operator|(const QInt& other);
    friend QInt operator~(QInt& srcNum);

    QInt rol();
    QInt ror();

    //------------------CONVERT FUNCTIONS--------------------
    void convertTo2Comp();                         //convert to two's compliment number
    string convertFromBinTo(const int& destBase);  //convert from QInt to decimal string or hexadecimal string
};