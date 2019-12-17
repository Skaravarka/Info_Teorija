#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct element{
    int val;
    int count;
    string bits;
    element(int value): val(value), count(0), bits("") {}
    
    void inc(){
        count++;
    }
};

struct dictionary{
    int val;
    string new_val;
};

struct comp_bigger{
    inline bool operator() (const element& struct1, const element& struct2){
        return (struct1.count > struct2.count);
    }
};

void make_word(vector<element> &elements, int start, int end){
    if(start == end){
        return;
    }
    if(end - start == 1){
        elements[start].bits+='0';
        elements[end].bits+='1';
    }else if(end-start > 1){
        int mid = (end-start+1)/2 + start;
        
        for(int i = start; i< mid; i++){
            elements[i].bits+='0';
        }
        make_word(elements, start, mid-1);
        for(int i = mid; i <= end; i++){
            elements[i].bits+='1';
        }
        make_word(elements, mid, end);
    }
}

int main(){
    int count = 0;
    vector<element> freq;
    int curr_elements = 256;
    for(int i = 0; i < 255; i++){
        freq.push_back(element(i));
    }
    
    ifstream input("test.txt", std::ios::binary);

    vector<unsigned char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();
    cout<<bytes.size()<<endl;
    for(signed int i = 0; i < bytes.size(); i++){
        freq[int(bytes[i])].inc();
    }
    sort(freq.begin(), freq.end(), comp_bigger());
    for(int i = 0; i < freq.size(); i++){
        if(freq[i].count == 0){
            freq.erase(freq.begin()+i, freq.end());
            break;
        }
    }
    make_word(freq,0, freq.size()-1);
    for(int i = 0; i < freq.size(); i++){
        if(freq[i].bits.length() < 8){
            while (freq[i].bits.length() != 8){
               freq[i].bits.insert(freq[i].bits.begin(), '0');
            }
        }
    }

    for(int i = 0; i < freq.size(); i++){
        cout<<char(freq[i].val)<<" "<<freq[i].count<<" "<<freq[i].bits<<endl;
    }
    return 0;
}
