# Comparing MAC with MMH and SQH hash families

### File details
#### `input.txt`

Input file contains three lines 
first line : number of key-msg pairs
second line : key 
third line: message

NOTE: key and message are of a maximum size 32 words or 128 ASCII characters

#### `sqh.h`
Custom library that includes sqh function to generate SQH-MAC

#### `mmh.h`
Custom library that includes mmh function to generate MMH-MAC

#### `main.cpp`
Main file that includes main function

#### `output.txt`
Output generated is saved in this file by default


The Program is run on a Linux machine and an optimization flag `-O3` is used during compilation to achieve higher compiler optimizations to the program.

```
g++ -O3 -w main.cpp -o main.out
```
```
./main.out
```

## Randomness Analysis of The Square hash 