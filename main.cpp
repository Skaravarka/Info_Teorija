#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
#include "functions.h"
#include "struct.h"
#include <chrono>

using namespace std;

int wordSize;      // word size (2 - 16)
string inputFile;  // input file directory
string outputFile; // output file directory
char mode;         // encode/decode modes

void inputVerification(int argc, char* argv[]){
    //Reading arguments
    //encode/decode inputFile outputFile
    cout << "argc " << argc << endl;
    if(argc != 5){
        cout << "Error: bad arguments inputed" << endl;
        cout << "[e|d] wordSize inputFile outputFile" << endl;
        cout << "default arguments entered" << endl;    
        mode = 'e';
        wordSize = 8;
        inputFile = "input.txt";
        outputFile = "output.txt";
    }
    else {
        mode = *argv[1];
        wordSize = (int)*argv[2] - '0';
        inputFile = argv[3];
        outputFile = argv[4];
    }
}
/*
TODO:
    input verification???
    Bytes to bit
    The Algorithm 
    
    😸
*/

int main(int argc, char* argv[]){
    // Defining stuff
    chrono::steady_clock::time_point begin = chrono::steady_clock::now(); // clock begin
    int count = 0;
    vector<string> binaryVector;
    vector<element> freq; //Frequency vector with element Struct

    // reading inputs
    inputVerification(argc, argv);

    // Reading input file
    vector<unsigned char> bytes = readFile(inputFile);
    //cout<< bytes.size() << " LINE" << __LINE__ << endl;

    // creating binary vector
    binaryVector = createBinaryVector(bytes, wordSize);

    // creating frequency vector
    freq = createFrequencyVector(wordSize, binaryVector);

    // making cyphers
    codeSFTree(freq, 0, freq.size(), sumCounts(freq, 0, freq.size()));
    
    // creating code body (coding text itself)
    string body = codeBody(binaryVector, freq, wordSize);
    //cout << "afterBody: " << body << endl;

    // printing binary string to output file
    printToFileBin(body, outputFile);

    //
    //
    // DECODE
    //
    //
    


    // reading file
    bytes = readFile(outputFile);
    //cout<< bytes.size() << " LINE" << __LINE__ << endl;
    
    // creating binary vector for decoding
    binaryVector = createBinaryVector(bytes, wordSize);
    // decoding
    string decodeString = decode(binaryVector, wordSize);

    cout <<"Writing back"<<endl;
    printToFileStr(decodeString, "decoded.txt");

    check(readFile(inputFile),readFile(inputFile));

    /*for(int i = 0; i < freq.size(); i++){
        cout<< char(freq[i].val) << " " << freq[i].count << " " << freq[i].bits << " " << freq[i].cypherBits << endl;
       // cout<< char(freq[i].val) << " " << freq[i].count << " " << endl;

    }*/

    // clock end
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[µs]" << std::endl;

    return 1;
}
