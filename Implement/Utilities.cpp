#include "../Header/Utilities.h"

bool isOperator(string Opr_check) {
    return (Opr_check == "=" || Opr_check == "+" || Opr_check == "-" || Opr_check == "*" || Opr_check == "/" || Opr_check == "&" || Opr_check == "|" || Opr_check == "^" || Opr_check == "~" || Opr_check == "rol" || Opr_check == "ror");
}

int ParseInput(string line, vector<QInt> &numbers, string &opr, vector<string> &numsys) {
    vector<string> string_holders;
    size_t holders_size = 0;
    string_holders.resize(holders_size);
    size_t pos = 0;                                   //idex of space
    while ((pos = line.find(" ")) != string::npos) {  //While still have space in line
        string token = line.substr(0, pos);
        string_holders.resize(++holders_size);
        string_holders.push_back(token);
        line.erase(0, pos + 1);
    }

    numsys.push_back(string_holders[0]);
    if (string_holders.size() == 3) {
        if (isOperator(string_holders[1]))
            opr = string_holders[1];
        else
            numsys.push_back(string_holders[1]);
    } else if (string_holders.size() == 4) {
    }
}
