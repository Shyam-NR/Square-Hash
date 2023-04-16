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


#define F first
#define S second

int main()
{
    freopen("test_input.txt", "r", stdin);
    freopen("test_output.txt", "w", stdout);

    int T;
    cin >> T;
    for(int tc = 1; tc<=T; tc++)
    {
        
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
        
        // in all these following variables, first one stores mmh values and the second one stores the sqh value
        vector<pair<double, double> > freq_mono_out(n), runs_out(n), avalanche_out(n);
        // vector<pair<double, double>> freq_block(n);
        pair<double, double> avg_freq_mono({0, 0}), avg_runs({0, 0}), avg_avalanche({0, 0});
        // int M = 8;
        for(int i=0; i<n; i++)
        {
            freq_mono_out[i] = {frequency_test_monobit(mmh_values[i]), frequency_test_monobit(sqh_values[i])};
            // freq_block[i] = {frequency_test_block(mmh_values[i], M), frequency_test_block(sqh_values[i], M)};
            runs_out[i] = {run_test(mmh_values[i]), run_test(sqh_values[i])};
            avalanche_out[i] = {avalanche_test(mmh_values[0], mmh_values[i]), avalanche_test(sqh_values[0], sqh_values[i])};
            
            avg_freq_mono.F += freq_mono_out[i].F;
            avg_freq_mono.S += freq_mono_out[i].S;

            avg_runs.F += runs_out[i].F;
            avg_runs.S += runs_out[i].S;

            avg_avalanche.F += avalanche_out[i].F;
            avg_avalanche.S += avalanche_out[i].S;
        }
        avg_freq_mono.F /= n;
        avg_freq_mono.S /= n;

        avg_runs.F /= n;
        avg_runs.S /= n;

        avg_avalanche.F /= n;
        avg_avalanche.S /= n;


        // printing
        // for(int i=0; i<n; i++)
        // {
        //     printf("%3d ", i);
        //     printf(" Frequency test ");
        //     printf("%3.6lf", mmh_values[i]);
        //     cout << "Pending Work" << endl;
        // }
        cout << setprecision(12) ;
        cout << "TEST CASE #" << tc << ":\n";
        cout << "Frequency Test results: -- " << endl;
        cout << "\tMMH - " << avg_freq_mono.F << endl;
        cout << "\tSQH - " << avg_freq_mono.S << endl;

        cout << "Runs Test results: -- " << endl;
        cout << "\tMMH - " << avg_runs.F << endl;
        cout << "\tSQH - " << avg_runs.S << endl;

        cout << "Avalanche Test results: -- " << endl;
        cout << "\tMMH - " << avg_avalanche.F << endl;
        cout << "\tSQH - " << avg_avalanche.S << endl;
        cout << endl;
    }


    return 0;
}