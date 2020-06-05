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
        arrayBits.at(pos) = setValue;
    else
        cout << "setValue is invalid!" << endl;
}

void QInt::removeLeadingZeros() {
    while (arrayBits.front() == 0)
        arrayBits.pop_front();
}

void QInt::push_front(const bool& bit) {
    arrayBits.push_front(bit);
}
void QInt::push_back(const bool& bit) {
    arrayBits.push_back(bit);
}

bool QInt::isGreaterThan(const QInt& other) {
    QInt compareRes = *this - other;
    if (compareRes.isNegative())
        return 0;
    else
        return 1;
}

bool QInt::isOverflow() {
    return (this->getSize() > MAX_SIZE);
}

//-----------------DEFAULT CONSTRUCT & DESTRUCT FUNCTION-------------------
QInt::QInt() {
    arrayBits.resize(0);
}

QInt::QInt(const string& numString, const int& base) {
    arrayBits.resize(0);
    if (numString.length() > MAX_SIZE)
        return;
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

    for (const char bit : binString) {
        arrayBits.push_back(bit - '0');
    }
    //remove leading 0s if it has
    if (!equalZero()) {
        removeLeadingZeros();
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
    return this->convertFromBinTo(10);
}

string QInt::getHex() {
    return this->convertFromBinTo(16);
}

int QInt::getSize() {
    return arrayBits.size();
}

bool QInt::isNegative() {
    return (arrayBits.size() == MAX_SIZE && arrayBits.front() == 1);
}

bool QInt::equalZero() {
    return (arrayBits.size() == 1 && arrayBits.back() == 0);
}

// //-------------------OPERATORS-----------------------------
QInt& QInt::operator=(const QInt& other) {
    for (auto bit = cbegin(other.arrayBits); bit != cend(other.arrayBits); bit++)
        arrayBits = other.arrayBits;
    return *this;
}

QInt QInt::operator+(const QInt& other) {
    int tempRes = 0;
    string resString;  //result string
    QInt res;

    int i = this->arrayBits.size() - 1;
    int j = other.arrayBits.size() - 1;
    while (i >= 0 || j >= 0 || tempRes == 1) {  //loop reversely
        //calculated sum of last digits
        tempRes += ((i >= 0) ? this->arrayBits.at(i) : 0);
        tempRes += ((j >= 0) ? other.arrayBits.at(j) : 0);
        //put it in result
        if (res.getSize() < 128)
            res.push_front(bool(tempRes % 2));
        //stored memory bit
        tempRes /= 2;
        //move to next digit
        i--;
        j--;
    }
    //overflow handle
    if (res.isOverflow()) {
        QInt zero("0", 2);
        return zero;
    }

    return res;
}

QInt QInt::operator-(const QInt& other) {
    int tempRes = 0;
    QInt res;

    int i = this->arrayBits.size() - 1;
    int j = other.arrayBits.size() - 1;
    while (i >= 0 || j >= 0) {  //loop reversely
        //calculated sum of last digits
        tempRes = ((i >= 0) ? this->arrayBits.at(i) : 0) - ((j >= 0) ? other.arrayBits.at(j) : 0) - tempRes;
        //put it in result
        res.push_front(bool(tempRes % 2));
        //calculate memory bit
        if (tempRes < 0)
            tempRes = 1;
        else
            tempRes = 0;
        //move to next digit
        i--;
        j--;
    }
    //if tempRes is still 1, it's mean result is an negative number
    if (tempRes == 1) {
        res.arrayBits.insert(res.arrayBits.begin(), MAX_SIZE - res.getSize(), 1);  //add digit 1 on start to fill
    }

    //overflow handle
    if (res.isOverflow()) {
        QInt zero("0", 2);
        return zero;
    }

    return res;
}

QInt QInt::operator*(const QInt& other) {
    QInt res("0", 2), temp;                           //construct a result QInt-zero and a temp QInt
    for (int i = this->getSize() - 1; i >= 0; i--) {  //loop reversely
        if (this->arrayBits.at(i) == 1) {
            temp.arrayBits = other.arrayBits;                                         //assign other to temp
            temp.arrayBits.insert(temp.arrayBits.end(), this->getSize() - 1 - i, 0);  //insert 0s at the back of temp
            res = res + temp;                                                         //do the + operator
        } else
            continue;
    }
    //overflow handle
    if (res.isOverflow()) {
        QInt zero("0", 2);
        return zero;
    } else
        return res;
}

QInt QInt::operator/(const QInt& other) {
    QInt res, tempDividend;
    bool tempRes = 0;
    QInt divisor = other;  //assign other to divisor => immutable
    //count quantity of negative input
    int negativeFlagCount = 0;

    //if input is negative => convert to positive
    if (divisor.isNegative()) {
        divisor.convertTo2Comp();
        negativeFlagCount++;
    }
    if (this->isNegative()) {
        this->convertTo2Comp();
        negativeFlagCount++;
    }
    //non-negative divided
    for (auto bit = cbegin(this->arrayBits); bit != cend(this->arrayBits); bit++) {  //loop in this
        tempDividend.push_back(*bit);                                                //push the bit to dividend's back
        tempRes = (tempDividend.isGreaterThan(divisor) ? 1 : 0);                     //if dividend is greater than divisor => quotient = 1 else quotient = 0
        res.push_back(tempRes);
        if (tempRes == 1)
            tempDividend = tempDividend - divisor;
    }

    res.removeLeadingZeros();  //remove leading 0s if it has
    //check if result is negative or not, switch if needed
    if (negativeFlagCount % 2 == 1)
        res.convertTo2Comp();

    // overflow handle
    if (res.isOverflow()) {
        QInt zero("0", 2);
        return zero;
    } else
        return res;
}

QInt QInt::operator>>(const unsigned int& Sbit) {
    QInt res = *this;
    res.arrayBits.erase(res.arrayBits.end() - Sbit, res.arrayBits.end());  //erase Sbit digit at the end

    if (this->isNegative()) {                                  //check if source is negative
        res.arrayBits.insert(res.arrayBits.begin(), Sbit, 1);  //insert back Sbit digit 1 at begin
    }

    return res;
}

QInt QInt::operator<<(const unsigned int& Sbit) {
    QInt res = *this;

    res.arrayBits.insert(res.arrayBits.end(), Sbit, 0);  //add Sbit digit 0 to the end of result
    if (res.getSize() > MAX_SIZE)
        res.arrayBits.erase(res.arrayBits.begin(), res.arrayBits.begin() + (res.getSize() - MAX_SIZE));  //erase Sbit first digit of result if it overflow
    //remove leading zeros if it has
    res.removeLeadingZeros();
    return res;
}

QInt QInt::operator&(const QInt& other) {
    QInt res;

    int i = this->arrayBits.size() - 1;
    int j = other.arrayBits.size() - 1;
    while (i >= 0 || j >= 0) {  //loop reversely
        //calculated last digits
        int tempRes = ((i >= 0) ? this->arrayBits.at(i) : 0) & ((j >= 0) ? other.arrayBits.at(j) : 0);
        //put it in result
        res.push_front(bool(tempRes));
        //move to next digit
        i--;
        j--;
    }

    return res;
}

QInt QInt::operator^(const QInt& other) {
    QInt res;

    int i = this->arrayBits.size() - 1;
    int j = other.arrayBits.size() - 1;
    while (i >= 0 || j >= 0) {  //loop reversely
        //calculated last digits
        int tempRes = ((i >= 0) ? this->arrayBits.at(i) : 0) ^ ((j >= 0) ? other.arrayBits.at(j) : 0);
        //put it in result
        res.push_front(bool(tempRes));
        //move to next digit
        i--;
        j--;
    }

    return res;
}

QInt QInt::operator|(const QInt& other) {
    QInt res;

    int i = this->arrayBits.size() - 1;
    int j = other.arrayBits.size() - 1;
    while (i >= 0 || j >= 0) {  //loop reversely
        //calculated last digits
        int tempRes = ((i >= 0) ? this->arrayBits.at(i) : 0) | ((j >= 0) ? other.arrayBits.at(j) : 0);
        //put it in result
        res.push_front(bool(tempRes));
        //move to next digit
        i--;
        j--;
    }

    return res;
}

QInt operator~(QInt& srcNum) {
    QInt res = srcNum;
    bool negativeFlag = false;
    if (srcNum.isNegative()) {
        negativeFlag = true;
    }
    //flip result;
    res.flip();
    if (negativeFlag)  //if source num is negative
        res.removeLeadingZeros();
    else                                                                           //if source num is positive
        res.arrayBits.insert(res.arrayBits.begin(), MAX_SIZE - res.getSize(), 1);  //after flip, it become negative => add leading 1

    return res;
}

QInt QInt::rol() {
    QInt res = *this;

    if (this->isNegative()) {
        res.push_back(1);           //push the front element to the back (digit 1)
        res.arrayBits.pop_front();  //delete the first element
    } else
        res.push_back(0);  //if it's positive, 0 is the front element

    return res;
}

QInt QInt::ror() {
    QInt res = *this;

    if (res.arrayBits.back() == 1) {                                                   //if last element is 1
        if (!res.isNegative())                                                         //if res is not negative
            res.arrayBits.insert(res.arrayBits.begin(), MAX_SIZE - res.getSize(), 0);  //we have to add leading 0s and then push 1 to the front
        res.push_front(1);                                                             //push the last element to the front
    }
    res.arrayBits.pop_back();  //delete the last element

    return res;
}

//------------------CONVERT FUNCTIONS--------------------
void QInt::convertTo2Comp() {
    bool negativeFlag = false;
    if (this->isNegative())
        negativeFlag = true;

    bool firstOne = false;  //mark if we have met the first digit 1 or not
    for (auto bit = rbegin(arrayBits); bit != rend(arrayBits); bit++) {
        if (firstOne == true) {
            *bit = !*bit;  //flip
        }
        if (*bit == 1)
            firstOne = true;
    }
    //check if src is negative
    if (negativeFlag)
        removeLeadingZeros();
    else {  //add 1 to the front
        while (arrayBits.size() != MAX_SIZE)
            arrayBits.push_front(1);
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

    while (count(arrayBits.begin(), arrayBits.end(), true)) {
        unsigned int remainder = 0;
        // Temporary result of integer division
        deque<bool> dividedNumber;

        // Do the division
        for (const bool bit : arrayBits) {
            // Claculate the remainder
            remainder = remainder * 2 + bit;

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

        arrayBits = dividedNumber;
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
