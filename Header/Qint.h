#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define DEFAULT_SIZE 16                                                                                            //16 bytes
#define _POSITION ((Binary.size() - 1 - i) / (sizeof(__int64) * CHAR_BIT))                                         //Vị trí Vùng 4 Byte cần ghi vào.
#define _SHIFT_OFFSET (((Binary.size() - 1) % (CHAR_BIT * sizeof(__int64))) - (i % (CHAR_BIT * sizeof(__int64))))  //Số bit cần dời.

/*
- Vị trí của a[i] trong mảng được xác dịnh như sau:
((Độ dài chuỗi - 1 - i) / kích thước bit của một vùng nhớ (ở đây là 32 bit).
Hình vẽ:
Chuỗi bit nhị phân: 11011110111110110000000000000000000000000000011
|	                        a[3]								   |...|	                        a[1]								  ||	                        a[0]								  |
|0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7|...|0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7|
|0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0|...|0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|1|1|0|1|1||1|1|0|1|1|1|1|1|0|1||1|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|0|0||0|0|0|0|0|0|1|1|
- Độ dời của bit về bên trái để thực hiện đưa bit vào số được tính như sau:
((Độ dài chuỗi - 1) % Kích thước bit của 1 vùng nhớ đang xét) - (i % Kích thước bit của 1 vùng nhớ)
Công thức này được tạo thành do chuỗi có vị trí bắt đầu ngược so với chuổi bit thực sự
Ví dụ: 1101 thì 1 trong chuỗi ký tự là phần tử đầu tiên tuy nhiên đây sẽ là bit thứ 3 trong một chuỗi bit
có độ dài 4 bit.
*/

class QInt {
   private:
    vector<__int64> arrayBits;

   public:
    //-----------------DEFAULT CONSTRUCT & DESTRUCT FUNCTION-------------------
    QInt(const int& nSize = DEFAULT_SIZE);
    QInt(const string& Binary);
    ~QInt();

    //------------------GET FUNCTION--------------------
    vector<__int64> getData() const;

    //-------------------OPERATORS-----------------------------
    QInt operator+(const QInt& other) const;
    QInt operator-(const QInt& other) const;
    QInt operator*(const QInt& other) const;
    QInt operator/(const QInt& other) const;

};