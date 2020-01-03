#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
#include "functions.h"

using namespace std;

bool DEBUG = true;

string inputFile;  // input file directory
string outputFile; // output file directory
char mode;         // encode/decode modes

void inputVerification(int argc, char* argv[]){
    if(argc != 4){
        cout << "Error: bad arguments entered" << endl;
        cout << "Should be: [e|d] inputFile outputFile" << endl;
        cout << "Entering default mode: [e input.txt output.txt]"<< endl;
        mode = 'e';
        inputFile = "input.txt";
        outputFile = "output.txt";
    }
    else {
        mode = *argv[1];
        inputFile = argv[2];
        outputFile = argv[3];
    }
}

/*
    Put request in here:

*/
/*
    Is failo skaito/raso string i faila
*/

int main(int argc, char* argv[]){
    inputVerification(argc, argv);
    //Reads input file into single chars
    vector<unsigned char> bytes = readFile(inputFile);
    //Turns char vector to byte vectors
    vector<string> a = str2bs(bytes);
    
    //prints string to file
    printToFileStr(a[0], outputFile);

    return 1;
}
