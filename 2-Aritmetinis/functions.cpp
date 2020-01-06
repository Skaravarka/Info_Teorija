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

using namespace std;

void check_debug(vector<unsigned char> original, vector<unsigned char> decoded){

    cout<<"File size:"<<original.size()<<endl;
    cout<<"Out size:"<<decoded.size()<<endl;
    int dif = 0;
    cout<<"Inas:"<<endl;
    for(unsigned int i = 0; i < original.size();i++){
    printf("%d - %d  ",original[i],decoded[i]);
    cout<<original[i]<<"-"<<decoded[i];
    if(original[i] != decoded[i]){
        dif++;
        cout<<" Blogas";
    }
    cout<<endl;  
    }
    cout<<dif;
    cout<<"Done"<<endl;
}

int check(vector<unsigned char> original, vector<unsigned char> decoded){
    if(original.size()!=decoded.size()){
        cout<<"Files differ on size alone"<<endl;
        return -1;
    }
    for(unsigned int i = 0; i < original.size();i++){
    if(original[i] != decoded[i]){
        cout<<"Files differ"<<endl;
        return -1;
    }
    }
    cout <<"Files are identical"<<endl;
    return 1;
}

vector<unsigned char> readFile(string fileName){
    ifstream input(fileName, std::ios::binary);
    vector<unsigned char> bytes( 
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));
    input.close();

    return bytes;
}