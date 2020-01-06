#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::ios;



const int NO_OF_CHARS = 256;
const int EOF_SYMBOL = (NO_OF_CHARS + 1);
const int NO_OF_SYMBOLS = (NO_OF_CHARS + 1);

class Compress
{
public:
	int CODE_VALUE = 16;
	unsigned long long int MAX_VALUE = ((1ULL << CODE_VALUE) - 1);
	unsigned long long int MAX_FREQ = (MAX_VALUE + 1) / 4 - 1;

	unsigned long long int FIRST_QTR = (MAX_VALUE / 4 + 1);
	unsigned long long int HALF = (2 * FIRST_QTR);
	unsigned long long int THIRD_QTR = (3 * FIRST_QTR);
	
	unsigned char index_to_char [NO_OF_SYMBOLS];
	int char_to_index [NO_OF_CHARS];

	unsigned long long int cum_freq [NO_OF_SYMBOLS + 1];
	int freq [NO_OF_SYMBOLS + 1];

	Compress(void);
	~Compress(void);
	void change(int);
	void update_tables(int sym_index);

};

