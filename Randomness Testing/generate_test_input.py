import string
import random

def format(s):
    s = s.split()
    for i in range(len(s)) :
        s[i] = s[i][0].upper() + s[i][1:]

    s = ''.join(s)
    return s

def test_series(m, k) :
    series = []
    for i in range(len(m)):
        if(i+k >= len(m)) : break
        # rand_string = ''.join(random.choices(string.ascii_letters 
        #                                      + string.digits 
        #                                      + string.punctuation.replace('\\', ''), 
        #                                     k=k))
        rand_string = ''.join(random.choices(string.ascii_letters 
                                             + string.digits, 
                                            k=k))
        series.append(m[:i] + rand_string
                    + m[i+k:])
    return series

def generate_test_series(m) :
    series = []
    for  i in range(1, 8) :
        series.extend(test_series(m, i))
    
    return series


f = open("test_input.txt", "w")

# key was taken from this text
k = "Statistical randomness tests are functions that \
take arbitrary length input and produce a real number \
between 0 and 1 called the p-value, which is produced by evaluating \
certain randomness properties of the given input. For example, Frequency \
Test produces p-values depending on the number of ones in a binary sequence, \
where Overlapping Template Test evaluates the number of occurrences of a specific \
sequence of bits"

# k = ''.join(random.choices(string.ascii_letters 
#                                      + string.digits 
#                                      + string.punctuation.replace('\\', ''), 
#                                     k=300))

k = format(k)
k1 = k[0:128]
k2 = k[128:256]

# primary message is taken from this text
m = "One of the most basic properties expected from block ciphers and \
hash functions is passing statistical randomness testing, as they are \
expected to behave like random mappings. Previously, testing of AES candidate \
block ciphers was done by concatenating the outputs of the algorithms obtained \
from various input types. In this work, a more convenient method, namely the \
cryptographic randomness testing is introduced. A package of statistical tests are \
designed based on certain cryptographic properties of block ciphers and hash functions \
to evaluate their randomness. The package is applied to the AES finalists, and produced \
more precise results than those obtained in similar applications."

# m = ''.join(random.choices(string.ascii_letters 
#                                      + string.digits 
#                                      + string.punctuation.replace('\\', ''), 
#                                     k=300))

m = format(m)
m1 = m[0:128]
m2 = m[128:256]

test_cases = 2
f.write(str(test_cases) + '\n')

f.write(k1 + '\n')
# print("Test message 1 ---")
ser1 = generate_test_series(m1)

f.write(str(len(ser1) + 1))
f.write('\n')
f.write(m1 + '\n')
for ser in ser1 :
    f.write(ser + '\n')

f.write('\n')
f.write(k2 + '\n')
# print("Test message 2 ---")
ser2 = generate_test_series(m2)

f.write(str(len(ser2) + 1))
f.write('\n')
f.write(m2 + '\n')
for ser in ser2 :
    f.write(ser + '\n')

# print(ser1)
# print("-------------")
# print(ser2)


f.close()