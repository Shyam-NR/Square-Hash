#include<vector>
using namespace std;

int k = 32; // inputs to the function will be two K-word integers
/*
* parameters based on word size (l), prime (p = 2^l + b), b 
int l = 32;
int b = 15;
unsigned long long mod_factor = (1 << 32) - 1;
unsigned long long int p = (1 << 32) + 15;

*/


unsigned long sqh(vector<unsigned long> &key, vector<unsigned long> &msg)
{
    signed long long stmp;
    unsigned long long utmp;
    
    unsigned long long sum = 0LL;
    unsigned long ret; // return value

    for(int i=0; i<k; i++)
    {
        sum += ((((key[i] + (unsigned long long) msg[i]) & 0xffffffffLL) 
                * ((key[i] + (unsigned long long) msg[i]) & 0xffffffffLL )) 
                    & 0xffffffffLL) ;
        sum &= 0xffffffffLL;
    }

    stmp = (sum & 0xffffffffLL) - ((sum >> 32) * 15);
    utmp = (stmp & 0xffffffffLL) - ((stmp >> 32) * 15);

    ret = utmp & 0xffffffffLL;
    if(utmp > 0x10000000fLL)
        ret -= 15;

    return ret;

}