#include<vector>
using namespace std;

#define D(i) sum += key[i] * (unsigned long long) msg[i];

int K = 32; // inputs to the function will be two K-word integers

unsigned long mmh(vector<unsigned long> &key, vector<unsigned long> &msg)
{
    signed long long stmp;
    unsigned long long utmp;


    unsigned long long sum = 0LL;
    unsigned long ret; // return value

    /* Using Loop */
    for(int i=0; i<K; i++)
    {
        sum += key[i] * (unsigned long long) msg[i];
    }

    /********** return (sum % Ox1OOOOOOOfLL); **********/

    stmp = (sum & 0xffffffffLL) - ((sum >> 32) * 15);
    utmp = (stmp & 0xffffffffLL) - ((stmp >> 32) * 15);

    ret = utmp & 0xffffffff;

    if(utmp > 0x10000000fLL)
        ret -= 15;
    return ret;

}