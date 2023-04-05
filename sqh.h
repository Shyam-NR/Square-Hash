#include<vector>
using namespace std;

#define DO(i) sum = (sum + ((((key[i] + (unsigned long long) msg[i]) & 0xffffffffLL) * ((key[i] + (unsigned long long) msg[i]) & 0xffffffffLL )) & 0xffffffffLL)) & 0xffffffffLL
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

    // without loop
    DO(0); DO(1); DO(2); DO(3); 
    DO(4); DO(5); DO(6); DO(7); 
    DO(8); DO(9); DO(10); DO(11); 
    DO(12); DO(13); DO(14); DO(15); 
    DO(16); DO(17); DO(18); DO(19); 
    DO(20); DO(21); DO(22); DO(23); 
    DO(24); DO(25); DO(26); DO(27);
    DO(28); DO(29); DO(30); DO(31);
    // for(int i=0; i<k; i++)
    // {
        // sum += ((((key[i] + (unsigned long long) msg[i]) & 0xffffffffLL) * ((key[i] + (unsigned long long) msg[i]) & 0xffffffffLL );
        // sum &= 0xffffffffLL;
    // }

    stmp = (sum & 0xffffffffLL) - ((sum >> 32) * 15);
    utmp = (stmp & 0xffffffffLL) - ((stmp >> 32) * 15);

    ret = utmp & 0xffffffffLL;
    if(utmp > 0x10000000fLL)
        ret -= 15;

    return ret;

}