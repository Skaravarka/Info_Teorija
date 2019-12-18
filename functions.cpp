#include "functions.h"
#include <vector>
#include <string>
#include <bitset>

using namespace std;

vector<string> createBinaryVector(vector<unsigned char> bytes, int wordSize){
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
        cout << tempVector[i] << endl;
    }
    */
    return tempVector;
}