#include "encode.h"
#include "decode.h"
#include "functions.h"
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>

//compile su Makefile aka. mingW32-make
//use: e <input file> <codeWord>

std::string out = "out.txt";
std::string dec = "dec.txt";

int main ( int argc, char **argv){
	int parametras =16;
	if (argc < 3){
		cout<< "Error: invalid arguments \n Usage: [e|d] inputFile outputFile" <<endl;
		return -1;
	}
	else{
		parametras = std::stoi(argv[3]);
		cout <<"Parameter:"<<parametras<<endl;
	}

	Encode obj(parametras);
	obj.encode(argv[2], out.c_str());

	Decode objc(parametras);
	objc.decode(out.c_str(), dec.c_str());
	//Checkas mazesniem failmas nes bus isspausdinti visi bitai
	//check_debug(readFile(argv[2]),readFile("dec.txt"));
	//Checkas tik paziuret ar failai vienodi ar ne
	check(readFile(argv[2]),readFile("dec.txt"));
	//cout <<"code:"<<CODE_VALUE<<endl;
	return 0;
}
