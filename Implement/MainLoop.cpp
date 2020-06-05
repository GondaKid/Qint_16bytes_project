#include "../Header/MainLoop.h"

void CalculatedLine::clear() {
    srcBase = destBase = Operator = parameter1 = parameter2 = "";
    elementCount = 0;
}
void CalculatedLine::getLine() {
    cout << "srcBase - " << srcBase << endl;
    cout << "destBase - " << destBase << endl;
    cout << "Operator - " << Operator << endl;
    cout << "parameter1 - " << parameter1 << endl;
    cout << "parameter2 - " << parameter2 << endl;
    cout << "elementCount - " << elementCount << endl;
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
        string_holders.push_back(token);
        holders_size++;
        line.erase(0, pos + 1);
    }
    string_holders.push_back(line);  //push last stand token

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

void MainLoop::clearInput() {
    cLine.clear();
}

void MainLoop::MainProcess(const string& pathFileInput, const string& pathFileOutput) {
    ifstream inFile;
    inFile.open(pathFileInput);
    ofstream outFile;
    outFile.open(pathFileOutput);
    int linecount = 1;
    if (inFile.is_open() && outFile.is_open()) {
        string line;                     //Line holder
        while (getline(inFile, line)) {  //reading line to line
            ParseInput(line);
            ProcessLine();
            outFile << result << endl;  //writing result into output file
            cLine.clear();
            cout << linecount++ << " - Done" << endl;  //clear input after done
        }
    } else
        cout << "Input file is not valid! Please try again" << endl;
    inFile.close();
    outFile.close();
}

void MainLoop::ProcessLine() {
    QInt Qsrc(cLine.parameter1, stoi(cLine.srcBase));
    if (cLine.Operator == "")  //Trường hợp convert base
    {
        if (cLine.destBase == "2")
            result = Qsrc.getBin();
        else if (cLine.destBase == "10")
            result = Qsrc.getDec();
        else if (cLine.destBase == "16")
            result = Qsrc.getHex();

    } else if (cLine.Operator == "rol" || cLine.Operator == "ror" || cLine.Operator == "~") {
        if (cLine.Operator == "rol")
            Qsrc = Qsrc.rol();
        else if (cLine.Operator == "ror")
            Qsrc = Qsrc.ror();
        else if (cLine.Operator == "~")
            Qsrc = Qsrc = ~Qsrc;

        if (cLine.srcBase == "2")
            result = Qsrc.getBin();
        else if (cLine.srcBase == "10")
            result = Qsrc.getDec();
        else if (cLine.srcBase == "16")
            result = Qsrc.getHex();
    } else {
        if (cLine.Operator == ">>" || cLine.Operator == "<<") {
            int a = atoi(cLine.parameter2.c_str());
            if (cLine.Operator == ">>")
                Qsrc = Qsrc >> a;
            else if (cLine.Operator == "<<")
                Qsrc = Qsrc << a;

        } else {
            QInt Q_to(cLine.parameter2, stoi(cLine.srcBase));
            if (cLine.Operator == "+")
                Qsrc = Qsrc + Q_to;
            else if (cLine.Operator == "-")
                Qsrc = Qsrc - Q_to;
            else if (cLine.Operator == "*")
                Qsrc = Qsrc * Q_to;
            else if (cLine.Operator == "/")
                Qsrc = Qsrc / Q_to;
            else if (cLine.Operator == "^")
                Qsrc = Qsrc ^ Q_to;
            else if (cLine.Operator == "|")
                Qsrc = Qsrc | Q_to;
        }

        if (cLine.srcBase == "2")
            result = Qsrc.getBin();
        else if (cLine.srcBase == "10")
            result = Qsrc.getDec();
        else if (cLine.srcBase == "16")
            result = Qsrc.getHex();
    }
}
