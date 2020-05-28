#include <bitset>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define DEFAULT_SIZE 128

/*
Khai báo bit set:

	bitset<4> foo; // foo = 0000
	bitset<4> foo2(string("1001")); // foo2 =1001
	bitset<4> foo3(7); // foo3 = 0111

Các hàm cơ bản:

size(): trả về kích thước của bitset.
count(): Đếm các bit 1 (hoặc rả về tổng tất cả các bit).
test(): trả về giá trị true hoặc false tại một bit.
any(): kiểm tra có bit 1 trong setbit hay không, trả về true nếu có và ngược lại.
none(): kiểm tra một bitset có phải toàn bit 0 hay không, trả về true nếu có và ngược lại.
all(): kiểm tra một bitset có phải toàn bit 1 hay không, trả về true nếu có và ngược lại.
Thao tác trên bitset:

set(): Chuyển bit tại ví trí chỉ định thành bit mong muốn, mặc định chuyển thành bit 1.
  std::bitset<4> foo; //foo = 0000
  foo.set();    // foo = 1111
  foo.set(1,0);   // foo = 1101
  foo.set(2,0); // foo = 1001
  foo.set(1)   // foo = 1011​
reset(): Chuyển bit chỉ định hoặc tất cả các bit thành bit 0.
	std::bitset<4> foo; 
	foo = 7; // foo = 0111
	foo.reset(1); // foo = 0101
	foo.reset(); // foo = 0000​
flip(): Chuyển bit chỉ định hoặc tất cả các bit thành bit khác ( bit 0 thành bit 1 và ngược lại.
Các hàm chuyển đổi:

to_string(): Chuyển bitset về dạng chuỗi nhị phân.
	std::bitset<4> foo; 
	foo = 7;
	cout << "String = " << foo.to_string();
// Kết quả là: String = 0111​
to_ulong(): Chuyển bitset về dạng số nguyên.
	std::bitset<4> foo(string("0111"));
	cout << foo.to_ulong();
// kết quả là: 7​
to_ullong(): Tương tự to_ulong() (Chỉ hỗ trợ cho C++ 11).

*/

class QInt {
   private:
    deque<bool> arrayBits;

   public:
    //-----------------DEFAULT CONSTRUCT & DESTRUCT FUNCTION-------------------
    QInt(const int& nSize = DEFAULT_SIZE);
    QInt(const string& numString, int base);  //Create a Qint from a string with it's base
    ~QInt();

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