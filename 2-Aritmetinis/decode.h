#pragma once
#include "compress.h"

class Decode : public Compress
{
	unsigned long long int low, high;
	unsigned long long int value;

	int buffer;
	int	bits_in_buf;
	bool end_decoding;

	ifstream in;
	ofstream out;
public:
	Decode(void);
	Decode(int);
	~Decode(void);

	void load_first_value(void);
	void decode(const char *infile,const char *outfile);
	int decode_symbol(void);
	int get_bit(void);
};

