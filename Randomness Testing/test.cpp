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
        // cout << key_string << endl << endl;
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
        avalanche_out[0] = {0, 0}; // first one
        for(int i=0; i<n; i++)
        {
            freq_mono_out[i] = {frequency_test_monobit(mmh_values[i]), frequency_test_monobit(sqh_values[i])};
            // freq_block[i] = {frequency_test_block(mmh_values[i], M), frequency_test_block(sqh_values[i], M)};
            runs_out[i] = {run_test(mmh_values[i]), run_test(sqh_values[i])};
            
            avg_freq_mono.F += freq_mono_out[i].F;
            avg_freq_mono.S += freq_mono_out[i].S;

            avg_runs.F += runs_out[i].F;
            avg_runs.S += runs_out[i].S;
            if(i == 0) continue;
            avalanche_out[i] = {avalanche_test(mmh_values[i-1], mmh_values[i]), avalanche_test(sqh_values[i-1], sqh_values[i])};

            avg_avalanche.F += avalanche_out[i].F;
            avg_avalanche.S += avalanche_out[i].S;
        }
        avg_freq_mono.F /= n;
        avg_freq_mono.S /= n;

        avg_runs.F /= n;
        avg_runs.S /= n;

        avg_avalanche.F /= (n-1);
        avg_avalanche.S /= (n-1);


        // printing results
        cout << setprecision(12) ;
        // cout << "Key: " << key_string << endl;

        cout << "Frequency Test Mono bit : \n";

        cout << " +-----+------------+------------+------------+------------+ \n";
        cout << " |  SL |  MMH--MAC  |   p_value  |  SQH--MAC  |   p_value  | \n";
        cout << " +-----+------------+------------+------------+------------+ \n";
        for(int i=0; i<n; i++)
        {

            cout << " | " << setw(3) << i+1 ;
            cout << " | " << setw(10) << hex << mmh_values[i] << dec ;
            cout << " | " << setw(10) ;
            cout << fixed << setprecision(8) << runs_out[i].F ;

            cout << " | " << setw(10) << hex << sqh_values[i] << dec ;
            cout << " | " << setw(10) ;
            cout << fixed << setprecision(8) << runs_out[i].F ;
            cout << " | " << endl;

        cout << " +-----+------------+------------+------------+------------+ \n";
        }
        cout << "\n-------------------------------------------------------- \n";
        cout << "-------------------------------------------------------- \n\n";

        cout << "Runs Test : \n";

        cout << " +-----+------------+------------+------------+------------+ \n";
        cout << " |  SL |  MMH--MAC  |   p_value  |  SQH--MAC  |   p_value  | \n";
        cout << " +-----+------------+------------+------------+------------+ \n";
        for(int i=0; i<n; i++)
        {

            cout << " | " << setw(3) << i+1 ;
            cout << " | " << setw(10) << hex << mmh_values[i] << dec ;
            cout << " | " << setw(10) ;
            cout << fixed << setprecision(8) << runs_out[i].F ;

            cout << " | " << setw(10) << hex << sqh_values[i] << dec ;
            cout << " | " << setw(10) ;
            cout << fixed << setprecision(8) << runs_out[i].S ;
            cout << " | " << endl;

        cout << " +-----+------------+------------+------------+------------+ \n";
        }
        cout << "\n-------------------------------------------------------- \n";
        cout << "-------------------------------------------------------- \n\n";

        cout << "Avalanche Test : \n";
        int inv = 0, v = 0;
        cout << " +-----+------------+--------------+------------+--------------+ \n";
        cout << " |  SL |  MMH--MAC  | avalanche(%) |  SQH--MAC  | avalanche(%) | \n";
        cout << " +-----+------------+--------------+------------+--------------+ \n";
        cout << " | " << setw(3) << 0 ;
        cout << " | " << setw(10) << hex << mmh_values[0] << dec ;
        cout << " | " << setw(12) << '-' ;

        cout << " | " << setw(10) << hex << sqh_values[0] << dec ;
        cout << " | " << setw(12) << '-' ;
        cout << " | " << endl;
        for(int i=1; i<n; i++)
        {

            cout << " | " << setw(3) << i+1 ;
            cout << " | " << setw(10) << hex << mmh_values[i] << dec ;
            cout << " | " << setw(12) ;
            cout << fixed << setprecision(2) << avalanche_out[i].F ;

            cout << " | " << setw(10) << hex << sqh_values[i] << dec ;
            cout << " | " << setw(12) ;
            cout << fixed << setprecision(2) << avalanche_out[i].S ;
            cout << " | " << endl;

            cout << " +-----+------------+--------------+------------+--------------+ \n";
        }

        cout << "\n-------------------------------------------------------- \n";
        cout << "-------------------------------------------------------- \n\n";


        // final average printing
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