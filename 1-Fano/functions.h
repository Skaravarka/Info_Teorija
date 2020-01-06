#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include "struct.h"

std::vector<std::string> createBinaryVector(std::vector<unsigned char> bytes, int wordSize, bool mode, int &del);
int binaryStringToInt(std::string bin);
std::vector<element> createFrequencyVector(int wordSize, std::vector<std::string> binaryVector);
void codeSFTree(std::vector<element> &freq, int start, int end, int sum);
int sumCounts(std::vector<element> freq, int start, int end);
std::string codeFileHeader(std::vector<element> codeMap, int wordSize, int zeroNum, int del);
std::string codeBody(std::vector<std::string> text, std::vector<element> codeMap, int wordSize, int del);
void printToFileBin(std::string str, std::string fileName);
void printToFileStr(std::string str, std::string fileName);
std::string remove_CR(std::string str);
std::vector<unsigned char> readFile(std::string fileName);
void encode(std::vector<element> freq, const   char* filename);
std::string decode(std::vector<std::string> text, int wordSize, int del);
void check_debug(std::vector<unsigned char> original,std::vector<unsigned char> decoded);
int check(std::vector<unsigned char> original,std::vector<unsigned char> decoded);

#endif 