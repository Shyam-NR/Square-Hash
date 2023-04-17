#include<bits/stdc++.h>
#include<chrono>

#include"mmh.h"
#include"sqh.h"
#include"helper.h"


using namespace std;
using namespace std::chrono;


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int T;
    cin >> T;
    double mmh_avg(0), sqh_avg(0);

    cout << " +----+------------+----------+------------+----------+ \n";
    cout << " | SL |  MMH--MAC  | Time(ns) |  SQH--MAC  | Time(ns) | \n";
    cout << " +----+------------+----------+------------+----------+ \n";

    int k_words = 32;

    for(int t=1; t<=T; ++t)
    {

        string key_string, msg_string;
        cin >> key_string >> msg_string;


        vector<unsigned long> key(k_words), msg(k_words);
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
        // for terminal
        cout << " | " << setw(2) << t ;
        cout << " | " << setw(10) << hex << mmh_mac << dec ;
        cout << " | " << setw(8) << mmh_duration.count() ;

        cout << " | " << setw(10) << hex << sqh_mac << dec ;
        cout << " | " << setw(8) << sqh_duration.count() ;
        cout << " | " << endl;

        // printing to include in latex table
        // cout << t << " & " << hex << mmh_mac << dec << " & " << mmh_duration.count() << " & " << hex << sqh_mac << dec << " & " << sqh_duration.count() << " \\\\ " << endl << "\\hline" << endl;

        mmh_avg += mmh_duration.count();
        sqh_avg += sqh_duration.count();

        cout << " +----+------------+----------+------------+----------+ \n";
    }

    mmh_avg /= T;
    sqh_avg /= T;

    cout << "\n\n";

    cout << "Average MMH execution time: " << mmh_avg << " nanoseconds" << endl;
    cout << "Average SQH execution time: " << sqh_avg << " nanoseconds" << endl;

    return 0;
}