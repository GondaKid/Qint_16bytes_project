#include "Qint.h"

struct CalculatedLine {
    string srcBase;
    string destBase;
    string Operator;
    string parameter1;
    string parameter2;
    int elementCount;

    CalculatedLine();
    void getLine();
};

class MainLoop {
   private:
    CalculatedLine cLine;
    string result;

   public:
    bool isOperator(string Opr_check);
    void ParseInput(string line);  //Parse input into CalculatedLine
    void MainProcess(const string& pathFileInput, const string& pathFileOutput);
    void ProcessLine();
};
