#include<math.h>
#include<bits/stdc++.h>
// #include "./lib/cephes/mconf.h"
// #include "./lib/cephes/double/igam.c"

using namespace std;

/*
* input to each of the functions is the 32 bit hash value generated
* Output is the p-value
* p-value > 0.01 => output is random
*/

int n = 32;

double frequency_test_monobit(unsigned long hash)
{
    int S = __builtin_popcount(hash);
    S -= (32 - S); 
    // S = +1 (for 1) -1 (for 0)

    double s_obs = abs(S)/sqrt((double)n);

    double p_value = erfcf32x(s_obs/sqrt(2));

    return p_value;

}

// double frequency_test_block(unsigned long hash, int M)
// {
//     int g = n/M;
//     unsigned long mask = (1 << n%M);
//     vector<double> pi(g);
//     for(int i=0; i<g; i++)
//     {
//         double pi_i = 0;
//         for(int j=0; j<M; j++, mask <<= 1)
//         {
//             pi_i += ((hash & mask) ? 1 : -1 );
//         }
//         pi[i] = pi_i / M ;
//     }

//     // compute X^2_(obs)
//     double XX_obs = 0;
//     for(int i=0; i<g; i++)
//     {
//         XX_obs += (pi[i] - 0.5) * (pi[i] - 0.5) ;
//     } 
//     XX_obs *= 4 * M;

//     double p_value = 0.2; // SHOULD CHANGE ASAP - learn to include cephes library

//     return p_value;

// }

double run_test(unsigned long hash)
{
    
    double pi = (double) __builtin_popcount(hash) / n;
    double tow = (double) 2 / sqrt(n);
    if(abs(pi - 0.5) >= tow)
        return 0; // run test would not pass since frequency test did not pass
    double V_obs = 0;
    unsigned long temp = hash;

    int prev = hash % 2;
    hash /= 2;
    while(hash)
    {
        if(hash%2 != prev)
            V_obs++;
        prev = hash%2;
        hash /= 2;
    }

    V_obs += 1;

    double p_value = erfcf32x(abs(V_obs - 2 * n * pi * (1 - pi))/(2 * sqrt(2*n) * pi * (1 - pi)));

    return p_value;


}

double avalanche_test(unsigned long hash, unsigned long hash_)
{
    // in here we find out the percentage hamming distance between hash and hash_
    unsigned long mask = 1;
    int dif = 0;
    for(int i=0; i<n; ++i, mask <<= 1)
    {
        dif += ((hash & mask) != (hash_ & mask));
    }

    return (double)dif*100 / n;

}