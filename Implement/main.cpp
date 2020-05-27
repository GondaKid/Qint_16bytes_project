#include "../Header/Qint.h"
#include "../Header/Utilities.h"

int main() {
    ifstream inFile("../Test_files/input.txt");
    if (inFile.is_open()) {
        string line;
        vector<QInt> numbers;   //dynamic array of QInt numbers
        string opr;             //operator
        vector<string> numsys;  //number system
        while (getline(inFile, line)) {
            cout << line << endl;
        }

    } else
        cout << "Input file is not valid! Please try again" << endl;
    inFile.close();

    return 0;
}