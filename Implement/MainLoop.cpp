#include "../Header/MainLoop.h"

CalculatedLine::CalculatedLine() {
    srcBase = destBase = Operator = parameter1 = parameter2 = "";
    elementCount = 0;
}

bool MainLoop::isOperator(string Opr_check) {
    return (Opr_check == "~" || Opr_check == "rol" || Opr_check == "ror");
}

void MainLoop::ParseInput(string line) {
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
    cLine.elementCount = string_holders.size();
    cLine.srcBase = string_holders[0];
    if (cLine.elementCount == 3) {
        if (isOperator(string_holders[1]))
            cLine.Operator = string_holders[1];
        else
            cLine.destBase = string_holders[1];
        cLine.parameter1 = string_holders[2];
    } else if (cLine.elementCount == 4) {
        cLine.parameter1 = string_holders[1];
        cLine.Operator = string_holders[2];
        cLine.parameter2 = string_holders[3];
    }
}

void MainLoop::MainProcess(string pathFileInput, string pathFileOutput) {
    ifstream inFile(pathFileInput);
    ofstream outFile(pathFileOutput);
    if (inFile.is_open() && outFile.is_open()) {
        string line;                     //Line holder
        while (getline(inFile, line)) {  //reading line to line
            ParseInput(line);
            ProcessLine();
            outFile << result;  //writing result into output file
        }

    } else
        cout << "Input file is not valid! Please try again" << endl;
    inFile.close();
    outFile.close();
}

void MainLoop::ProcessLine() {
}
