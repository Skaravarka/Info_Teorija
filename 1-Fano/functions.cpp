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
#include <chrono>

using namespace std;
// creates binary vector from input file
vector<string> createBinaryVector(vector<unsigned char> bytes, int wordSize, bool mode, int &del){ //fun
    vector<string> tempVector;
    del = 0;
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
    
    if(mode){
        if(tempString2.size() != 0){
            while (tempString2.size() != wordSize){
                tempString2 = "0" + tempString2;
                del++;
            }
            tempVector.push_back(tempString2);
        }
    }
    else tempVector.push_back(tempString2);


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

string codeFileHeader(vector<element> codeMap, int wordSize, int zeroNum, int del){
    string header = "";
    int temp = codeMap.size();
    //cout << "temp" << temp << endl;
    if(wordSize != 2){
        header += decToBinary(del, wordSize);
        header += decToBinary(temp, wordSize);
        header += decToBinary(zeroNum, wordSize);
        //cout << header << endl;
    }
    else {
        header += decToBinary(del, wordSize * 2);
        header += decToBinary(temp, wordSize);
        header += decToBinary(zeroNum, wordSize * 2);
    }
    for(int i = 0; i < temp; i++){
        header += decToBinary(codeMap[i].cypherBits.size(), wordSize);
        header += codeMap[i].bits;
        header += codeMap[i].cypherBits;
        //cout << decToBinary(codeMap[i].cypherBits.size(), wordSize) << " " << codeMap[i].bits << " " << codeMap[i].cypherBits << endl;
    }
    while(header.size() % 8 != 0){
        header += "0";
    }

    return header;
}
string codeBody(vector<string> text, vector<element> codeMap, int wordSize, int del){
    string body = "";
    for(int i = 0; i < text.size(); i++){
        for(int j = 0; j < codeMap.size(); j++){
            if(text[i].compare(codeMap[j].bits) == 0){
                body += codeMap[j].cypherBits;
                //cout << body << endl;
                break;
            }
        }
    }
    int zeroNum = 0;
    while(body.size() % 8 != 0){
        body += "0";
        zeroNum ++;
    }
    
    // creating code header (code table)
    string header = codeFileHeader(codeMap, wordSize, zeroNum, del);
    //cout << "header: " << header << endl;
    
    //cout << "body size" << header.size() << " " << body.size() << endl;
    //cout << header + " " + body << endl;

    return header + body;
}
void printToFileBin(string str, string fileName){

    std::cout << str.size() << endl;
    ofstream out(fileName);
    
    

    /*
    istringstream in(str);
    bitset<8> bs;
    while(in >> bs){
        out << char(bs.to_ulong());
    }
    */
    ofstream fout;
    int temp;
    fout.open(fileName, ios::binary | ios::out);
    for(int i = 0; i < str.size(); i += 8){
        temp = binaryStringToInt(str.substr(i, 8));
        fout.write((char*) &temp, 1);
    }
    

    fout.close();

    out.close();
}
string remove_CR(string str){
    for(int i = 0; i < str.length();i++)
        if(str[i] == 13 && str[i+1]==10){
            str.erase(i,1);
        }
              
    return str;
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
vector<unsigned char> readFile(string fileName){
    ifstream input(fileName, std::ios::binary);
    vector<unsigned char> bytes( 
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));
    input.close();

    return bytes;
}
int findShortestCypher(vector<element> vec){
    int temp = vec[0].cypherBits.size();
    for(int i = 1; i < vec.size(); i++){
        if(temp > vec[i].cypherBits.size()){
            temp = vec[i].cypherBits.size();
        }
    }
    return temp;
}

string decode(vector<string> text, int wordSize, int del){
    std::cout << "start Decode" << endl;
    vector<element> codeMap; // code table
    string str = "";
    string textString = ""; // string of coded text
    int size = 0;
    int beginFrom;
    int zeroNum;
    if(wordSize != 2){
        beginFrom = 3;
        del = binaryStringToInt(text[0]);
        size = binaryStringToInt(text[1]);
        if(size == 0){
            size = pow(2, wordSize);
        }
        zeroNum = binaryStringToInt(text[2]);

        //cout << size << " miau " << zeroNum << endl;
    }
    else{
        beginFrom = 5;
        del = binaryStringToInt(text[0] + text[1]);
        size = binaryStringToInt(text[2]);
        if(size == 0){
            size = pow(2, wordSize);
        }
        zeroNum = binaryStringToInt(text[3] + text[4]);
    }

   // cout << "zeroNum: " << zeroNum << endl;
    
    for(int i = beginFrom; i < text.size(); i++){
        textString += text[i];
    }
    
    //cout << textString << endl;
    int j = 0;
    std::cout << "creating decode table" << endl;
    //  creating code table
    for(int i = 0; i < size; i++){
        int temp = binaryStringToInt(textString.substr(j,  wordSize));
        string tempBit = textString.substr(j + wordSize, wordSize);
        string cypherBit = textString.substr(j + (2*wordSize), temp);

        //cout << temp << " " << tempBit << " " << cypherBit << endl;

        codeMap.push_back(element(binaryStringToInt(tempBit), wordSize, cypherBit));
        j = j + (temp + wordSize * 2);
        
    }

    for(int i = 0; i < codeMap.size(); i++){
        //cout << codeMap[i].cypherBits << endl;
        //cout<< char(codeMap[i].val) << " " << codeMap[i].count << " " << codeMap[i].bits << " " << codeMap[i].cypherBits << endl;
        //cout<< char(freq[i].val) << " " << freq[i].count << " " << endl;
    }
    // exiting header
    int tempAdd = ((wordSize * beginFrom) % 8);
    cout << "tempAdd " << tempAdd << endl;
    j = j + tempAdd;
    while(j % (8) != 0){
        j++;
    }
    j = j - tempAdd;
    

    //decoding
    std::cout << "Decoding" << endl;
    std::cout << "bit count: " << textString.size() << endl;
    std::cout << "code table count: " << codeMap.size() << endl;
    //string tempString = "";
    textString = textString.substr(0, textString.size() - zeroNum);
    //cout << "textString" << textString.substr(j) << endl;
    string_view tempString = textString;
    int smallestCypher = findShortestCypher(codeMap);
    int len = smallestCypher;
    int saveI = 0;
    bool find1 = false, find2 = false;
    string buffStr = "";
    while(j < textString.size()){
    
         

        
        
        //tempString = textString.substr(j, len);
        //cout << textString.substr(j) << endl;
        //std::cout << tempString << endl;
        for(int i = 0; i < codeMap.size(); i++){
            if(codeMap[i].cypherBits.compare(tempString.substr(j, len)) == 0){
                find1 = true;
                saveI = i;
                break;
            }
            else find1 = false;
        }

        if((!find1 && find2)){
            find2 = false;
            find1 = false;
            j += len - 1;
            len = smallestCypher - 1;
            buffStr += codeMap[saveI].bits;
            while(buffStr.size() >=8){
                //cout << binaryStringToInt(buffStr.substr(0, 8)) << endl;
                str += char(binaryStringToInt(buffStr.substr(0, 8)));

                buffStr = buffStr.substr(8);
            } 
            //str += char(binaryStringToInt(codeMap[saveI].bits));
            //cout << j << endl;
            
        }


        if(tempString.substr(j).compare(tempString.substr(j, len)) == 0){
            for(int i = 0; i < codeMap.size(); i++){
                if(codeMap[i].cypherBits.compare(tempString.substr(j)) == 0){
                    //str += char(binaryStringToInt(codeMap[i].bits));
                    string tempSt = codeMap[i].bits;
                    //cout << buffStr << " " << tempSt << endl;
                    int tempDe = (buffStr.size() + tempSt.size()) % 8;
                    tempSt = tempSt.substr(del);

                    while(buffStr.size() + tempSt.size() >= 8){
                        int tempIn = buffStr.size();
                        buffStr += tempSt.substr(0, 8 - tempIn);

                        //cout << buffStr << " " << tempSt << endl;
                        str += char(binaryStringToInt(buffStr.substr(0, 8)));
                        buffStr = buffStr.substr(8);
                        tempSt = tempSt.substr(8 - tempIn);
                    }
                    break;
                }
            }
            break;
        } 

        find2 = find1;
        len++;

    }

    //cout << "end string" << str << " " << str.size() << endl;
    return str;
}

void check_debug(vector<unsigned char> original, vector<unsigned char> decoded){

    cout<<"File size:"<<original.size()<<endl;
    cout<<"Out size:"<<decoded.size()<<endl;
    int dif = 0;
    cout<<"Inas:"<<endl;
    for(int i = 0; i < original.size();i++){
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
    for(int i = 0; i < original.size();i++){
    if(original[i] != decoded[i]){
        cout<<"Files differ"<<endl;
        return -1;
    }
    }
    cout <<"Files are identical"<<endl;
    return 1;
}
