#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
#include "functions.h"
#include "struct.h"

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
void make_word(vector<element> &elements, int start, int end){
    if(start == end){
        return;
    }
    if(end - start == 1){
        elements[start].cypherBits+='0';
        elements[end].cypherBits+='1';
    }else if(end-start > 1){
        int mid = (end-start+1)/2 + start;
        
        for(int i = start; i< mid; i++){
            elements[i].cypherBits+='0';
        }
        make_word(elements, start, mid-1);
        for(int i = mid; i <= end; i++){
            elements[i].cypherBits+='1';
        }
        make_word(elements, mid, end);
    }
}
*/
/*
TODO:
    input verification???
    Bytes to bit
    The Algorithm 
    
    😸
*/

int main(int argc, char* argv[]){
    // Defining stuff
    int count = 0;
    vector<string> binaryVector;
    vector<element> freq; //Frequency vector with element Struct

    // reading inputs
    inputVerification(argc, argv);

    // Reading input file
    ifstream input(inputFile, std::ios::binary);
    vector<unsigned char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));
    input.close();
    //cout<< bytes.size() << " LINE" << __LINE__ << endl;

    // creating binary vector
    binaryVector = createBinaryVector(bytes, wordSize);
    
    // creating frequency vector
    freq = createFrequencyVector(wordSize, binaryVector);

    // making cyphers
    codeSFTree(freq, 0, freq.size(), sumCounts(freq, 0, freq.size()));

    /*
    make_word(freq,0, freq.size()-1);
    for(int i = 0; i < freq.size(); i++){
        if(freq[i].bits.length() < 8){
            while (freq[i].bits.length() != 8){
               freq[i].bits.insert(freq[i].bits.begin(), '0');
            }
        }
    }
    */

    for(int i = 0; i < freq.size(); i++){
        cout<< char(freq[i].val) << " " << freq[i].count << " " << freq[i].bits << " " << freq[i].cypherBits << endl;
        //cout<< char(freq[i].val) << " " << freq[i].count << " " << endl;
    }
    encode(freq, outputFile.c_str()); //Writes to file!?

    return 1;
}
