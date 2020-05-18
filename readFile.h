#include <iostream>
#include <fstream>
using namespace std;

void readAndWriteFile(string inFileName, string outFileName){
    ifstream inFile(inFileName);
    ofstream outFile(outFileName);
    if(inFile.is_open() && outFile.is_open()){
        string line;
        while(getline(inFile,line)){
            outFile << line << endl;
        }
        inFile.close();
        outFile.close();
    }
}

