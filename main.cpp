#include<bits/stdc++.h>
#include<chrono>

#include"mmh.h"
#include"sqh.h"


using namespace std;
using namespace std::chrono;

void convert_string_to_numbers(string &s, vector<unsigned long> &v, unsigned long &base)
{
    // every position in vector v will hold a word (4 bytes) - 4 characters worth information
    unsigned long word = 0;
    for(int i=0; i<s.length(); i+=4, word = 0)
    {
        for(int j=0, val; j<4; j++)
        {
            if(i+j >= s.length())
                val = 0;
            else
                val = (int)s[i+j];
            word = word * base + val;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string key_string, msg_string;
    cin >> key_string >> msg_string;


    vector<unsigned long> key(32), msg(32);
    unsigned long base = 1 << 8; // The size of an ASCII character

    convert_string_to_numbers(key_string, key, base);
    convert_string_to_numbers(msg_string, msg, base);

    // MAC computation using MMH
    auto start_mmh = high_resolution_clock::now();

    unsigned long mmh_mac = mmh(key, msg);
    
    auto stop_mmh = high_resolution_clock::now();
    auto mmh_duration = duration_cast<nanoseconds>(stop_mmh - start_mmh);

    // MAC computation using SQH
    auto start_sqh = high_resolution_clock::now();

    unsigned long sqh_mac = sqh(key, msg);

    auto stop_sqh = high_resolution_clock::now();
    auto sqh_duration = duration_cast<nanoseconds>(stop_sqh - start_sqh);

    // Printing outputs and results
    cout << "---------------MMH-MAC---------------\n";
    cout << "MAC: " << mmh_mac << "\n";
    cout << "Execution Time: " << mmh_duration.count() << " nanoseconds\n";

    cout << "\n";
    cout << "---------------SQH-MAC---------------\n";
    cout << "MAC: " << sqh_mac << "\n";
    cout << "Execution Time: " << sqh_duration.count() << " nanoseconds\n";

    

    return 0;
}