#include "Qint.h"

struct CalculatedLine {
    string srcBase;
    string destBase;
    string Operator;
    string parameter1;
    string parameter2;
    int elementCount;

    CalculatedLine();
};

class MainLoop {
   private:
    CalculatedLine cLine;
    string result;

   public:
    bool isOperator(string Opr_check);
    void ParseInput(string line);  //Parse input into CalculatedLine
    void MainProcess(string pathFileInput, string pathFileOutput);
    void ProcessLine();
};
