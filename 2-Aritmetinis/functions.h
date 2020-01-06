#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>

void check_debug(std::vector<unsigned char> original,std::vector<unsigned char> decoded);
std::vector<unsigned char> readFile(std::string fileName);
int check(std::vector<unsigned char> original,std::vector<unsigned char> decoded);

#endif 