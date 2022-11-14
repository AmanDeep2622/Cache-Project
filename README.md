

Shortforms
```
- `-s <s>`: Number of set index bits (*S = 2^s* is the number of sets)

- `-E <E>`: Associativity (number of lines per set)

- `-b <b>`: Number of block bits (*B = 2^b* is the block size)

- `-t <tracefile>`: Name of the trace file.


b=log Blocksize
s=log setsize
ways 

Case 1
Blocksize 32kb
b=5
s=6
e=8
```
Case 2
Blocksize 32kb
b=5
s=6
e=1

Case 3
Blocksize 16kb
b=4
s=6
e=16


LU Decompostion
./csim -v -s 6 -E 8 -b 5 -t traces/lu.trace   hits:41810 misses:22

./csim -v -s 6 -E 1 -b 5 -t traces/lu.trace   hits:41809 misses:23

./csim -v -s 6 -E 16 -b 4 -t traces/lu.trace  hits:41793 misses:39


Queue
./csim -v -s 6 -E 8 -b 5 -t traces/qu.trace     hits:506 misses:18

./csim -v -s 6 -E 1 -b 5 -t traces/qu.trace     hits:506 misses:18

./csim -v -s 6 -E 16 -b 4 -t traces/qu.trace    hits:498 misses:26

Matrix Multiply:

./csim -v -s 6 -E 8 -b 5 -t traces/mat.trace    hits:9052 misses:23


./csim -v -s 6 -E 1 -b 5 -t traces/mat.trace    hits:8806 misses:269

./csim -v -s 6 -E 16 -b 4 -t traces/mat.trace   hits:9035 misses:40

