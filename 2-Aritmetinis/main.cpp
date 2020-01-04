#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>
#include "functions.h"
#include <map>

using namespace std;

bool DEBUG = true;

struct frequency // this struct creates a frequency table with symbol probabilities
{
    char symbol;
    unsigned long long int low;
    unsigned long long int high;


     frequency(char temp_symbol, unsigned long long int temp_low, unsigned long long int temp_high)
     {
         symbol = temp_symbol;
         low = temp_low;
         high = temp_high;
     }


};

unsigned long long int algorithm (string text, vector<frequency> table ) // TODO change this function so that it could save first letter's frequency and after that
                                                                         // it goes down recurcively down in the interval
{
    unsigned long long int result;
    unsigned long long int low;
    unsigned long long int high;
    for(char & symbol : text)
    {
        for(frequency correct_symbol_frequency : table)
        if(symbol == correct_symbol_frequency.symbol)
        {
        }
    }

}

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
    string test = "This is a test for arithmetic coding.........";
    string_view viewTest = test;
    map <char,int> mapping;
    int whole_value;
    int length= viewTest.length();

    for(int i = 0;i<length;i++)
    {
        mapping[viewTest[i]]++;
    }

    for(auto& [key,value]: mapping)
    {
        std::cout << key << " has value " << value << std::endl;
        whole_value+=value;    
    }
    std::cout << whole_value<< std::endl;

    unsigned long long int high=0xFFFFFFFFU *1.0; // multiplying by a double we can change the length of our interval to a bigger number 0xFFFFFFFF is a 1 if in we are
                                                  // talking about the length of the interval
    unsigned long long int low = 0xFFFFFFFFU *0.0;  // TODO change *1.0 and *0.0 to the interval numbers user provides
    unsigned long long int middle = (high+low)/2;
    std::cout <<std::hex<<  high<< " middle" << std::hex << middle<< std::endl;
    vector<frequency> frequency_table; // shows which symbol what part of the interval takes
    unsigned long long int temp_low = low;
    unsigned long long int one_value = (high-low)/whole_value; // show how much space one letter would fit in an interval


    for(auto& [key,value]: mapping)
    {
        frequency_table.emplace_back(frequency(key,temp_low,temp_low+one_value*value)); // inserts the symbol and how much space it takes in the interval
        temp_low =temp_low+ one_value* value;
        //std::cout << key << " " << high/whole_value*value << endl;

    }

    for(auto & [symbol, low, high]: frequency_table)
    {
        std::cout << symbol << " " <<std::hex << low << " " << std::hex << high << endl;
    }


    //Turns char vector to byte vectors
    vector<string> a = str2bs(bytes);
    
    //prints string to file
    printToFileStr(a[0], outputFile);

    return 1;
}
