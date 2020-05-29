#include "../Header/Qint.h"

//------------------ULTILITIES--------------------
void QInt::flip() {
    for (auto bit = rbegin(arrayBits); bit != rend(arrayBits); bit++) {
        if (*bit == true)
            *bit = false;
        else
            *bit = true;
    }
}

void QInt::set(const size_t& pos, const int& setValue) {
    if (setValue == 1 || setValue == 0)
        arrayBits[pos] = setValue;
    else
        cout << "setValue is invalid!" << endl;
}

//-----------------DEFAULT CONSTRUCT & DESTRUCT FUNCTION-------------------
QInt::QInt() {
    arrayBits.resize(0);
}

QInt::QInt(const string& numString, int base) {
    arrayBits.resize(0);
    string binString = numString;
    switch (base) {
        case 2:
            break;
        case 10:
            binString = Conversion::convertDecToBin(numString);
            break;
        case 16:
            binString = Conversion::convertHexToBin(numString);
            break;
    }

    for (size_t i = 0; i < binString.length(); i++) {
        cout << binString[i];
        if (binString[i] == '1')
            arrayBits.push_back(1);
        else
            arrayBits.push_back(0);
    }
}

//------------------GET FUNCTIONS--------------------
string QInt::getBin() {
    string result;
    for (auto bit = cbegin(arrayBits); bit != cend(arrayBits); bit++) {
        result.push_back(*bit);
    }
    return result;
}

string QInt::getDec() {
    string binString = getBin();
    return Conversion::convertBinToDec(binString);
}

string QInt::getHex() {
    string binString = getBin();
    return Conversion::convertBinToHex(binString);
}

//-------------------OPERATORS-----------------------------
QInt QInt::operator+(const QInt& other) {
    bool flag = 0;
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
