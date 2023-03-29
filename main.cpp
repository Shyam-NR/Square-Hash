#include<bits/stdc++.h>

#include"mmh.h"
#include"sqh.h"

// #include<chrono>

// using std::chrono::nanoseconds;
// using std::chrono::duration_cast;
using namespace std;

// void convert_string_to_numbers(string &s, vector<unsigned long> &v, unsigned long &base)
// {
//     // every position in vector v will hold a word (4 bytes) - 4 characters worth information
//     unsigned long word = 0;
//     for(int i=0; i<s.length(); i+=4, word = 0)
//     {
//         for(int j=0, val; j<4; j++)
//         {
//             if(i+j >= s.length())
//                 val = 0;
//             else
//                 val = (int)s[i+j];
//             word = word * base + val;
//         }
//     }
// }

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string key_string, msg_string;
    cin >> key_string >> msg_string;
    
    vector<unsigned long> key(32), msg;
    unsigned long base = 1 << 8; // The size of an ASCII character

    // Pending completion


    // unsigned long long int h_MMH = mmh(key, msg);

    // auto t0 = clock::now();
    // auto t1 = clock::now();
    // nanoseconds ns = duration_cast<nanoseconds>(t1-t0);

    return 0;
}