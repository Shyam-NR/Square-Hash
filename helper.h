#include<bits/stdc++.h>
using namespace std;

void convert_string_to_numbers(string &s, vector<unsigned long> &v, unsigned long &base)
{
    // every position in vector v will hold a word (4 bytes) - 4 characters worth information
    unsigned long word = 0;
    for(int i=0, ind = 0; i<s.length(); i+=4, word = 0, ++ind)
    {
        for(int j=0, val; j<4; j++)
        {
            if(i+j >= s.length())
                val = 0;
            else
                val = (int)s[i+j];
            // cout << val << " ";
            word = word * base + val;
            // cout << word << " ";
        }
        // cout << endl;
        v[ind] = word;
    }
}
