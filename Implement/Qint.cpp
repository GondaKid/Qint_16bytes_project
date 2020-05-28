#include "../Header/Qint.h"

QInt::QInt(const int& nSize) {
    if (nSize >= 0) {
        arrayBits.resize(nSize / 8);
    } else
        cout << "Input size is invalid!";
}

QInt::QInt(const string& numString, int base) {
}

QInt QInt::operator+(const QInt& other) {
}

QInt QInt::operator-(const QInt& other) {
}

QInt QInt::operator*(const QInt& other) {
}

QInt QInt::operator/(const QInt& other) {
}

QInt QInt::operator>>(const unsigned int) {
}

QInt QInt::operator<<(const unsigned int) {
}

QInt QInt::operator&(QInt&) {
}

QInt QInt::operator^(QInt&) {
}

QInt QInt::operator|(QInt&) {
}

QInt operator~(QInt&) {
}

QInt QInt::rol() {
}

QInt QInt::ror() {
}
