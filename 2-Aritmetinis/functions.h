#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>

std::vector<unsigned char> readFile(std::string fileName);
std::vector<std::string> str2bs(std::vector<unsigned char> bytes);
void printToFileStr(std::string str, std::string fileName);
#endif 