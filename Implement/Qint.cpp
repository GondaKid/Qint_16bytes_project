#include "../Header/Qint.h"

//------------------ULTILITIES--------------------

void QInt::set(const size_t& pos, const int& setValue) {
    if (setValue == 1 || setValue == 0)
        arrayBits.set(pos, setValue);
    else
        cout << "setValue is invalid!" << endl;
}

void QInt::push_front(const bool& bit, const int& n = 1) {
    for (int i = 0; i < n; i++) {
        arrayBits = arrayBits >> 1;        //shift right 1 time
        arrayBits.set(MAX_SIZE - 1, bit);  //set the start digit to (bit)
    }
}
void QInt::push_back(const bool& bit, const int& n = 1) {
    for (int i = 0; i < n; i++) {
        arrayBits = arrayBits << 1;  //shift left 1 time
        arrayBits.set(0, bit);       //set the end digit to (bit)
    }
}

//-----------------DEFAULT CONSTRUCT & DESTRUCT FUNCTION-------------------
QInt::QInt() {
    arrayBits.reset();
}

QInt::QInt(const string& numString, const int& base) {
    string binString = numString;               //assign src string to a temp string => immutable
    Conversion::removeLeadingZeros(binString);  //remove leading zeros in input if it has
    //convert source string to binary string
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
    //set arrayBits based on binary string
    for (int i = binString.length() - 1; i >= 0; i--) {
        arrayBits.set(binString.length() - 1 - i, bool(binString.at(i) - '0'));
    }
}

QInt::~QInt() {
}
//------------------GET FUNCTIONS--------------------
string QInt::getBin() {
    string resString = arrayBits.to_string();
    Conversion::removeLeadingZeros(resString);
    return resString;
}

string QInt::getDec() {
    return this->convertFromBinTo(10);
}

string QInt::getHex() {
    return this->convertFromBinTo(16);
}

int QInt::getSize() {
    string res = this->arrayBits.to_string();  //convert to string
    Conversion::removeLeadingZeros(res);       //remove leading zeros
    return res.length();                       //return it's length
}

bool QInt::isNegative() {
    return (arrayBits.test(MAX_SIZE - 1) == 1);
}

bool QInt::equalZero() {
    return (arrayBits.none());
}

bool QInt::isGreaterThan(QInt other) {
    if (this->isNegative() && !other.isNegative())  //if *this is negative and other is positive
        return false;
    else if (!this->isNegative() && other.isNegative())  //if *this is positive and other is negative
        return true;
    else if (!this->isNegative() && !other.isNegative()) {  //if both is positive
        for (int i = MAX_SIZE - 1; i >= 0; i--) {
            if (this->arrayBits.test(i) > other.arrayBits.test(i))
                return true;
            else if (this->arrayBits.test(i) < other.arrayBits.test(i))
                return false;
            else
                continue;
        }
    } else {  //if both is negative
        for (int i = MAX_SIZE - 1; i >= 0; i--) {
            if (this->arrayBits.test(i) > other.arrayBits.test(i))
                return false;
            else if (this->arrayBits.test(i) < other.arrayBits.test(i))
                return true;
            else
                continue;
        }
    }
    return false;
}

bool QInt::isMulOverflow(QInt& other) {
    if (this->getSize() + other.getSize() < MAX_SIZE - 1)  //check if sum of both's first digit 1 postion is greater than 127 or not
        return false;                                      //if it's not, the result is alway underflow
    //else
    QInt max = QInt(MAX_QINT, 2);
    max = max / other;
    return this->isGreaterThan(max);  //compare *this value to result of (MAX_QINT / other's value)
}

// //-------------------OPERATORS-----------------------------
QInt& QInt::operator=(const QInt& other) {
    this->arrayBits = other.arrayBits;
    return *this;
}

QInt QInt::operator+(QInt other) {
    int tempRes = 0;
    QInt res;

    for (int i = 0; i < MAX_SIZE; i++) {  //loop from back to start
        tempRes += arrayBits.test(i) + other.arrayBits.test(i);
        //put it in result
        res.set(i, bool(tempRes % 2));
        //stored memory bit
        tempRes /= 2;
    }
    //overflow handle
    //overflow only happened when both input have the same sign and the result has the opposite sign
    if ((this->isNegative() && other.isNegative() && !res.isNegative()) || (!this->isNegative() && !other.isNegative() && res.isNegative())) {
        cout << "overflow happened! ";
        QInt zero;
        return zero;
    }

    return res;
}

QInt QInt::operator-(QInt other) {
    int tempRes = 0;
    QInt res;

    other.convertTo2Comp();  //convert it to two's complement
    res = *this + other;     //do the plus
    //no need to handled overflow cuz we've done that in '+' operation
    return res;
}

QInt QInt::operator*(QInt other) {
    QInt zero;

    if (this->equalZero() || other.equalZero())  //if one of the inputs is equal 0 => the result is equal 0
        return zero;

    int negativeCount = 0;  //keep track of result's sign
    //if input is negative, convert to two's complement number
    if (this->isNegative()) {
        this->convertTo2Comp();
        negativeCount++;
    }
    if (other.isNegative()) {
        other.convertTo2Comp();
        negativeCount++;
    }

    //non-negative multiplication
    QInt res, temp;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (other.arrayBits.test(i)) {         //if bit at position (i) = 1
            temp.arrayBits = this->arrayBits;  //assign value of this to temp
            temp.push_back(0, i);              //shift left i bit == push back i digit 0
            res = res + temp;                  //add temp to res
        } else
            continue;
    }
    //convert result to two's complement if inputs don't have the same sign
    if (negativeCount % 2 == 1)
        res.convertTo2Comp();
    //overflow handle
    if (isMulOverflow(other)) {
        cout << "overflow happened! ";
        return zero;
    } else
        return res;
}

QInt QInt::operator/(QInt other) {
    QInt zero;
    if (this->equalZero())  //check if the dividend is equal zero
        return zero;

    QInt res, tempDividend;
    bool tempRes = 0;
    //keep track of result's sign
    int negativeCount = 0;

    //if input is negative => convert to positive
    if (other.isNegative()) {
        other.convertTo2Comp();
        negativeCount++;
    }
    if (this->isNegative()) {
        this->convertTo2Comp();
        negativeCount++;
    }
    //non-negative division
    for (int i = this->getSize() - 1; i >= 0; i--) {
        tempDividend.push_back(this->arrayBits.test(i));
        tempRes = (tempDividend.isGreaterThan(other) ? 1 : 0);
        res.push_back(tempRes);
        if (tempRes == 1)
            tempDividend = tempDividend - other;
    }
    //convert result to two's complement if inputs don't have the same sign
    if (negativeCount % 2 == 1)
        res.convertTo2Comp();
    // don't need overflow handle cuz input is valid and output is always smaller than input
    return res;
}

QInt QInt::operator>>(const unsigned int& Sbit) {
    QInt res;
    //copy all the bits from *this except Sbit LSBs
    for (int i = Sbit; i < this->getSize(); i++) {
        res.arrayBits.set(i - Sbit, this->arrayBits.test(i));
    }
    //add Sbit MSBs to the front of result
    for (int i = 0; i < Sbit; i++)
        res.arrayBits.set(MAX_SIZE - 1 - i, this->arrayBits.test(MAX_SIZE - 1));

    return res;
}

QInt QInt::operator<<(const unsigned int& Sbit) {
    QInt res;

    //copy all the bits from *this except Sbit MSBs
    for (int i = 0; i < MAX_SIZE - Sbit; i++) {
        res.arrayBits.set(i + Sbit, this->arrayBits.test(i));
    }
    //add 0s to the back of result
    for (int i = 0; i < Sbit; i++)
        res.arrayBits.set(0 + i, 0);

    return res;
}

QInt QInt::operator&(const QInt& other) {
    QInt res;
    for (int i = 0; i < MAX_SIZE; i++) {
        //calculated last digits
        int tempRes = this->arrayBits.test(i) & other.arrayBits.test(i);
        //put it in result
        res.set(i, bool(tempRes));
    }
    return res;
}

QInt QInt::operator^(const QInt& other) {
    QInt res;
    for (int i = 0; i < MAX_SIZE; i++) {
        //calculated last digits
        int tempRes = this->arrayBits.test(i) ^ other.arrayBits.test(i);
        //put it in result
        res.set(i, bool(tempRes));
    }
    return res;
}

QInt QInt::operator|(const QInt& other) {
    QInt res;
    for (int i = 0; i < MAX_SIZE; i++) {
        //calculated last digits
        int tempRes = this->arrayBits.test(i) | other.arrayBits.test(i);
        //put it in result
        res.set(i, bool(tempRes));
    }
    return res;
}

QInt operator~(QInt& srcNum) {
    QInt res = srcNum;
    res.arrayBits.flip();
    return res;
}

QInt QInt::rol() {
    QInt res;
    //copy all the bits from *this except the MSB
    for (int i = 0; i < MAX_SIZE - 1; i++)
        res.arrayBits.set(i + 1, this->arrayBits.test(i));
    //assign MSB of *this to the back of result
    res.arrayBits.set(0, this->arrayBits.test(MAX_SIZE - 1));
    return res;
}

QInt QInt::ror() {
    QInt res;
    //copy all the bits from *this except the LSB
    for (int i = 1; i < MAX_SIZE; i++)
        res.arrayBits.set(i - 1, this->arrayBits.test(i));
    //add the LSB bit of *this to the front of result
    res.arrayBits.set(MAX_SIZE - 1, this->arrayBits.test(0));
    return res;
}

//------------------CONVERT FUNCTIONS--------------------
void QInt::convertTo2Comp() {
    bool firstOne = false;  //mark if we have met the first digit 1 or not
    for (int i = 0; i < MAX_SIZE; i++) {
        if (firstOne == true) {
            arrayBits.set(i, !arrayBits.test(i));  //flip
        }
        if (arrayBits.test(i) == 1)  //we don't do anything until we met the first digit 1
            firstOne = true;
    }
}

string QInt::convertFromBinTo(const int& destBase) {
    string result = "";
    const unsigned int numberBase = destBase;
    bool negativeFlag = false;
    QInt srcHolder = *this;  //Hold the source bit string

    //check if source string is negative and it's destbase is 10
    if (isNegative() && destBase == 10) {
        negativeFlag = true;
        this->convertTo2Comp();  //convert it to positive number
    }

    while (arrayBits.any()) {  //while still have digit 1 in arraybits
        unsigned int remainder = 0;
        // Temporary result of integer division
        QInt dividedNumber;

        // Do the division
        for (int i = MAX_SIZE - 1; i >= 0; i--) {
            // Claculate the remainder
            remainder = remainder * 2 + arrayBits.test(i);

            // If we have a overflow (e.g. number is bigger than 10
            if (remainder >= numberBase) {
                // Handle overflow
                remainder -= numberBase;
                // Add 1 to the "devidedString"
                dividedNumber.push_back(1);
            } else {
                dividedNumber.push_back(0);
            }
        }

        *this = dividedNumber;
        // The remainder is the number that we are interested in
        if (remainder <= 9)
            result.insert(0, 1, '0' + remainder);
        else {  //if it's in numbase > 10
            result.insert(0, 1, remainder - 10 + 'A');
        }
    }

    if (negativeFlag && destBase == 10)
        result = '-' + result;

    this->arrayBits = srcHolder.arrayBits;  //assign the first bits value for this

    return (result == "") ? "0" : result;
}
