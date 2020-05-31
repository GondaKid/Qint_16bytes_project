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

QInt::QInt(const string& numString, const int& base) {
    arrayBits.resize(0);
    string binString = numString;
    switch (base) {
        case 10:
            binString = Conversion::convertDecToBin(numString);
            break;
        case 16:
            binString = Conversion::convertHexToBin(numString);
            break;
        case 2:
            break;
    }

    for (const char bit : numString) {
        arrayBits.push_back(bit - '0');
    }
}

QInt::~QInt() {
    arrayBits.clear();
}
//------------------GET FUNCTIONS--------------------
string QInt::getBin() {
    string result;
    for (auto bit = cbegin(arrayBits); bit != cend(arrayBits); bit++) {
        result.push_back((*bit == true) ? '1' : '0');
    }
    return result;
}

string QInt::getDec() {
    string binString = getBin();
    return Conversion::convertFromBin(binString, 10);
}

string QInt::getHex() {
    string binString = getBin();
    return Conversion::convertFromBin(binString, 16);
}

// //-------------------OPERATORS-----------------------------
// QInt QInt::operator+(const QInt& other) {
//     bool flag = 0;
// }

// QInt QInt::operator-(const QInt& other) {
// }

// QInt QInt::operator*(const QInt& other) {
// }

// QInt QInt::operator/(const QInt& other) {
// }

// QInt QInt::operator>>(const unsigned int) {
// }

// QInt QInt::operator<<(const unsigned int) {
// }

// QInt QInt::operator&(QInt&) {
// }

// QInt QInt::operator^(QInt&) {
// }

// QInt QInt::operator|(QInt&) {
// }

// QInt operator~(QInt&) {
// }

// QInt QInt::rol() {
// }

// QInt QInt::ror() {
// }
