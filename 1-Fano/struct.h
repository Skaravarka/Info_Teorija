#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <vector>
#include <string>
#include <bitset>

// elements which we code
struct element{
    int val;
    int count;
    std::string cypherBits; //bits to which to code to
    std::string bits; //value in binary
    element(int value, int wSize): val(value), count(0), cypherBits("") {
        bits = std::bitset<16>(value).to_string();
        bits = bits.substr(16 - wSize, 16);
    }
    element(int value, int wSize, std::string stva): val(value), count(0), cypherBits(stva) {
        bits = std::bitset<16>(value).to_string();
        bits = bits.substr(16 - wSize, 16);
    }
    void inc(){
        count++;
    }
};
struct comp_bigger{
    inline bool operator() (const element& struct1, const element& struct2){
        return (struct1.count > struct2.count);
    }
};
struct dictionary{
    int val;
    std::string new_val;
};

#endif