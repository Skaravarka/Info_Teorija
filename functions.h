#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include "struct.h"

std::vector<std::string> createBinaryVector(std::vector<unsigned char> bytes, int wordSize);
int binaryStringToInt(std::string bin);
std::vector<element> createFrequencyVector(int wordSize, std::vector<std::string> binaryVector);
void codeSFTree(std::vector<element> &freq, int start, int end, int sum);
int sumCounts(std::vector<element> freq, int start, int end);
std::string codeFileHeader(std::vector<element> codeMap, int wordSize);
std::string codeBody(std::vector<std::string> text, std::vector<element> codeMap, int wordSize);
void printToFile(std::string str, std::string fileName);
std::vector<unsigned char> readFile(std::string fileName);

#endif 