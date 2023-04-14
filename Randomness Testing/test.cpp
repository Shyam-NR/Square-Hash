/*
* Here we are conducting randomness testing for the square hash function
*
* 
*/
#include<bits/stdc++.h>
#include "../mmh.h"
#include "../sqh.h"
#include "../helper.h"
#include "test_functions.h"

using namespace std;

int main()
{
    freopen("test_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    string key_string, msg_string;
    cin >> key_string;

    cin >> n;
    int k_words = 32;
    vector<unsigned long> key(k_words), msg(k_words);
    unsigned long base = 1 << 8;

    convert_string_to_numbers(key_string, key, base);

    vector<unsigned long> mmh_values(n), sqh_values(n);
    // unsigned long mmh_hash, sqh_hash;
    for(int i=0; i<n; i++)
    {
        cin >> msg_string;
        convert_string_to_numbers(msg_string, msg, base);

        mmh_values[i] = mmh(key, msg);
        sqh_values[i] = sqh(key, msg);
    }

    vector<pair<double, double> > freq_mono_out(n), freq_block(n), runs_out(n), avalanche_out(n);

    for(int i=0, M = 8; i<n; i++)
    {
        freq_mono_out[i] = {frequency_test_monobit(mmh_values[i]), frequency_test_monobit(sqh_values[i])};
        // freq_block[i] = {frequency_test_block(mmh_values[i], M), frequency_test_block(sqh_values[i], M)};
        runs_out[i] = {run_test(mmh_values[i]), run_test(sqh_values[i])};
        avalanche_out[i] = {avalanche_test(mmh_values[0], mmh_values[i]), avalanche_test(sqh_values[0], sqh_values[i])};

    }

    // printing
    for(int i=0; i<n; i++)
    {
        printf("%3d ", i);
        printf(" Frequency test ");
        printf("%3.6lf", mmh_values[i]);
        cout << "Pending Work" << endl;
    }


    return 0;
}