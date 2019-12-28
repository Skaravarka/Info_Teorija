#include "functions.h"
#include "struct.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
#include <sstream>

using namespace std;
// creates binary vector from input file
vector<string> createBinaryVector(vector<unsigned char> bytes, int wordSize){ //fun
    vector<string> tempVector;
     
    string tempString1;
    string tempString2 = "";

    for(int i = 0; i < bytes.size(); i++){
        bitset<8> temp(bytes[i]);
        tempString1 = tempString2 + temp.to_string();
    
        while(tempString1.size() >= wordSize){
            tempVector.push_back(tempString1.substr(0, wordSize));
            tempString1.erase(0, wordSize);
        }
        tempString2 = tempString1;
    }
    
    if(tempString2.size() != 0){
        while (tempString2.size() != wordSize){
            tempString2 = "0" + tempString2;
        }
        tempVector.push_back(tempString2);
    }
    /*
    for(int i = 0; i < tempVector.size(); i++){
        cout << binaryStringToInt(tempVector[i]) << endl;
    }
    */
    return tempVector;
}
int binaryStringToInt(string bin){
    return stoi(bin, 0, 2);
}
string decToBinary(int n, int size) {
    string temp = ""; 
    // Size of an integer is assumed to be 32 bits 
    for (int i = size - 1; i >= 0; i--) { 
        int k = n >> i; 
        if (k & 1) 
            temp += "1"; 
        else
            temp += "0"; 
    }
    return temp; 
} 
// creates frequency of repeating symbols in the input file
vector<element> createFrequencyVector(int wordSize, vector<string> binaryVector){
    int curr_elements = pow(2, wordSize); //curr_elements saves the max byte size (if 8 then 256)
    vector<element> freq;
    
    for(int i = 0; i < curr_elements; i++){
        freq.push_back(element(i, wordSize));
    }
    for(signed int i = 0; i < binaryVector.size(); i++){
        freq[int(binaryStringToInt(binaryVector[i]))].inc();
    };

    sort(freq.begin(), freq.end(), comp_bigger());
    for(int i = 0; i < freq.size(); i++){
        if(freq[i].count == 0){
            freq.erase(freq.begin()+i, freq.end());
            break;
        }
    }
    return freq;
}
// sums freq counts
int sumCounts(vector<element> freq, int start, int end){
    int sum = 0;
    for(int i = start; i < end; i++){
        sum += freq[i].count;
    }
    return sum;
}
// create cypher code by using The Shannon–Fano tree
void codeSFTree(vector<element> &freq, int start, int end, int sum){
    //cout << sumCounts(freq, start, end) << endl;
    //cout << "start" << start << " end" << end << endl;
    if(start == end - 1){
        return;
    }
    int tempSum1 = 0;
    int tempSum2 = 0;
    int mid; 

    for(int i = start; i < end; i++){
        tempSum1 += freq[i].count;
        mid = i;
        if(abs(sum - (tempSum2 * 2)) < abs(sum - (tempSum1 * 2))){
            tempSum1 = tempSum2;
            break;
        }
        else tempSum2 = tempSum1;
    }
    for(int i = start; i < mid; i++){
        freq[i].cypherBits += "0";
    }
    codeSFTree(freq, start, mid, tempSum1);

    for(int i = mid; i < end; i++){
        freq[i].cypherBits += "1";
    }
    codeSFTree(freq, mid, end, sum - tempSum1);
}

string codeFileHeader(vector<element> codeMap, int wordSize){
    string header = "";
    int temp = codeMap.size();
    header += decToBinary(temp, wordSize);
    cout << header << endl;
    for(int i = 0; i < temp; i++){
        header += decToBinary(codeMap[i].cypherBits.size(), wordSize);
        header += codeMap[i].bits;
        header += codeMap[i].cypherBits;
    }
    while(header.size() % wordSize != 0){
        header += "0";
    }

    return header;
}
string codeBody(vector<string> text, vector<element> codeMap, int wordSize){
    string body = "";
    for(int i = 0; i < text.size(); i++){
        for(int j = 0; j < codeMap.size(); j++){
            if(text[i].compare(codeMap[j].bits) == 0){
                body += codeMap[j].cypherBits;
                break;
            }
        }
    }
    return body;
}
void printToFile(string str, string fileName){
    ofstream out(fileName);

    istringstream in(str);
    bitset<8> bs;
    while(in >> bs){
        out << char(bs.to_ulong());
    }
    cout << endl;
    out.close();
}
vector<unsigned char> readFile(string fileName){
    ifstream input(fileName, std::ios::binary);
    vector<unsigned char> bytes( 
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));
    input.close();

    return bytes;
}