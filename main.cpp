#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
using namespace std;

struct element{
    int val;
    int count;
    string bits;
    element(int value): val(value), count(0), bits("") {}
    
    void inc(){
        count++;
    }
};

struct dictionary{
    int val;
    string new_val;
};

struct comp_bigger{
    inline bool operator() (const element& struct1, const element& struct2){
        return (struct1.count > struct2.count);
    }
};

void make_word(vector<element> &elements, int start, int end){
    if(start == end){
        return;
    }
    if(end - start == 1){
        elements[start].bits+='0';
        elements[end].bits+='1';
    }else if(end-start > 1){
        int mid = (end-start+1)/2 + start;
        
        for(int i = start; i< mid; i++){
            elements[i].bits+='0';
        }
        make_word(elements, start, mid-1);
        for(int i = mid; i <= end; i++){
            elements[i].bits+='1';
        }
        make_word(elements, mid, end);
    }
}
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
/*
TODO:
    input verification???
    Bytes to bit
    The Algorithm 
    
    😸
*/

int main(int argc, char* argv[]){
    int count = 0;
    vector<string> binaryVector;
    vector<element> freq;
    int wordSize;      // word size (2 - 16)
    string inputFile;  // input file directory
    string outputFile; // output file directory
    char mode;         // encode/decode modes

    //Reading arguments
    //encode/decode inputFile outputFile
    cout << "argc " << argc << endl;
    if(argc != 5){
        cout << "Error: bad arguments inputed" << endl;
        cout << "[e|d] wordSize inputFile outputFile" << endl;
        cout << "default arguments entered" << endl;    
        mode = 'e';
        wordSize = 16;
        inputFile = "input.txt";
        outputFile = "output.txt";
    }
    else {
        mode = *argv[1];
        wordSize = (int)*argv[2] - '0';
        inputFile = argv[3];
        outputFile = argv[4];
    }
    int curr_elements = pow(2, wordSize); //curr_elements saves the max byte size (if 8 then 256)

    for(int i = 0; i < curr_elements; i++){
        freq.push_back(element(i));
    }
    
    //Reading stuff
    ifstream input(inputFile, std::ios::binary);

    vector<unsigned char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();
    cout<<bytes.size()<<endl;

    // creating binary vector
    binaryVector = createBinaryVector(bytes, wordSize);

    //adding bytes to array
    for(signed int i = 0; i < bytes.size(); i++){
        freq[int(bytes[i])].inc();
    }

    sort(freq.begin(), freq.end(), comp_bigger());
    for(int i = 0; i < freq.size(); i++){
        if(freq[i].count == 0){
            freq.erase(freq.begin()+i, freq.end());
            break;
        }
    }

    make_word(freq,0, freq.size()-1);
    for(int i = 0; i < freq.size(); i++){
        if(freq[i].bits.length() < 8){
            while (freq[i].bits.length() != 8){
               freq[i].bits.insert(freq[i].bits.begin(), '0');
            }
        }
    }

    for(int i = 0; i < freq.size(); i++){
        //cout<< char(freq[i].val) << " " << freq[i].count << " " << freq[i].bits << endl;
        //cout<< char(freq[i].val) << " " << freq[i].count << " " << endl;
   
    }

    return 1;
}






