#include "../Header/Qint.h"

QInt::QInt(const int& nSize) {
    if (nSize >= 0) {
        arrayBits.resize(nSize / 8);
    } else
        cout << "Input size is invalid!";
}
QInt::QInt(const string& Binary) {
    arrayBits.resize(Binary.length() / 8);
    for (size_t i = 0; i < Binary.length(); i++) {
        if (Binary[i] == '1') {
            arrayBits[_POSITION] = arrayBits[_POSITION] | (1 << _SHIFT_OFFSET);
        }
    }
}

vector<__int64> QInt::getData() const {
    return arrayBits;
}

QInt QInt::operator+(const QInt& other) const {
}

QInt QInt::operator-(const QInt& other) const {
}

QInt QInt::operator*(const QInt& other) const {
}

QInt QInt::operator/(const QInt& other) const {
}
