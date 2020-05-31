#include <deque>
#include <fstream>
#include <vector>

#include "Conversions.h"

/*
  -------DEQUE FUNCTIONS-----------
  push_front/back
  pop_front/back
  front/back : return value of front/back element
  size
  empty: check if empty
  clear
  resize
*/

/*
QInt luu chuoi bit o dang Little Endian
vd:  1   1   0   1   0   1
   |[0]|[1]|[2]|[3]|[4]|[5]|
*/

class QInt {
   private:
    deque<bool> arrayBits;  //dynamic bitset arrays

   public:
    //-----------------DEFAULT CONSTRUCT & DESTRUCT FUNCTION-------------------
    QInt();
    QInt(const string& numString, const int& base);  //Create a Qint from a string with it's base
    ~QInt();

    //------------------ULTILITIES--------------------
    void flip();  //flip all the bits
    void set(const size_t& pos, const int& setValue);

    //------------------GET FUNCTIONS--------------------
    string getBin();
    string getDec();
    string getHex();

    //-------------------OPERATORS-----------------------------
    QInt operator+(const QInt& other);
    QInt operator-(const QInt& other);
    QInt operator*(const QInt& other);
    QInt operator/(const QInt& other);

    QInt operator>>(const unsigned int);
    QInt operator<<(const unsigned int);
    QInt operator&(QInt&);
    QInt operator^(QInt&);
    QInt operator|(QInt&);
    friend QInt operator~(QInt&);

    QInt rol();
    QInt ror();
};