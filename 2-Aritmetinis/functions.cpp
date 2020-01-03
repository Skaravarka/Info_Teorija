#include "functions.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include <string.h>

using namespace std;

vector<unsigned char> readFile(string fileName){
    ifstream input(fileName, std::ios::binary);
    vector<unsigned char> bytes( 
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));
    input.close();

    return bytes;
}

vector<string> str2bs(vector<unsigned char> bytes) {
    char buffer[9] = "";
    vector <string> ret;
    for(int i = 0; i < bytes.size(); i++) {
        sprintf(buffer, 
            "%c%c%c%c%c%c%c%c", 
            (bytes[i] & 0x80) ? '1':'0', 
            (bytes[i] & 0x40) ? '1':'0', 
            (bytes[i] & 0x20) ? '1':'0', 
            (bytes[i] & 0x10) ? '1':'0', 
            (bytes[i] & 0x08) ? '1':'0', 
            (bytes[i] & 0x04) ? '1':'0', 
            (bytes[i] & 0x02) ? '1':'0', 
            (bytes[i] & 0x01) ? '1':'0');
        ret.push_back(buffer);
        buffer[0] = '\0';
    }
    return ret;
}
void printToFileStr(string str, string fileName){ 
    if(str.length()==0){
        cout<<"ERROR Writing, string of length 0"<<endl;
        return;
    }
    ofstream out(fileName);
    ofstream fout;
    string l;
    fout.open(fileName, ios::binary | ios::out);
    for(int i = 0; i <str.length();i++){
        l =str[i];
        const char *c = l.c_str();
        fout.write(c,1);
    }
    fout.close();
}

