#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>

#include <stdio.h>
#include <time.h>

#define NUMBITS 128  // number of address bits

typedef struct cache_line {
    long long tag;
    int accessTime;
    bool valid;
} cache_line;


static int S, E;


static int s, b;  // s index bits, b bits block offset 
static bool bflag = 0; 


static int hits, misses;  //Hit ,Miss countes



void printSummary(int hits, int misses) {
    printf("hits:%d misses:%d \n", hits, misses);
}

cache_line *initCache() {
    cache_line *val = (cache_line *) malloc(S * E * sizeof(cache_line));

    for (int i = 0; i < S; i++) {
        for (int j = 0; j < E; j++) {
            cache_line line;
            line.valid = 0;
            val[i * E + j] = line;
        }
    }
    return val;
}

void CacheAccess(cache_line *val, long long address, int *time) {
   
    int index = (address >> b) & ((1 << s) - 1);  // Extract index bits
    int setIndex = index * E;
    
    
    long long tag = address >> (b + s);  // Extract tag bits;

    int loadTime = *time;
    int lru = loadTime;

    int emptySlot = -1; 
    int lruPos = -1;

     // Hit Condition
    for (int i = 0; i < E; i++) {
        if (val[setIndex + i].valid && val[setIndex + i].tag == tag) {
            val[setIndex + i].accessTime = loadTime;
            hits++;
            if (bflag);
            return;
        } else if (!val[setIndex + i].valid) {
            emptySlot = i;
        } else if (val[setIndex + i].accessTime < lru) {
            lru = val[setIndex + i].accessTime;
            lruPos = i;
        }
    }
    
    // Cold miss
    if (emptySlot != -1) {
        val[setIndex + emptySlot].valid = 1;
        val[setIndex + emptySlot].tag = tag;
        val[setIndex + emptySlot].accessTime = loadTime;
        misses++;
        if (bflag);
        return;
    } else {
        // Miss 
        val[setIndex + lruPos].tag = tag;
        val[setIndex + lruPos].accessTime = loadTime;
        misses++;
        if (bflag)
        return;
    }
}

void printUsageInfo(char *arg[]) {
  
}
int main(int argument, char *arg[]) {

    int opt;
    char *traceFile;
    while ((opt = getopt(argument, arg, "hvs:E:b:t:")) != -1) {             // Getting input then opening file for more info check Readme file 
        switch (opt) {
            case 'v':
                bflag = 1;
                break;
            case 's':
                s = atoi(optarg);
                S = 1 << s;
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                traceFile = optarg;
                break;
            default:
                printUsageInfo(arg);
                exit(1);
        }
    }

    hits = misses = 0;
    cache_line *val = initCache();

    FILE *filePtr;
    filePtr = fopen(traceFile, "r");                   // Opening Tracefile

    char identifier;
    long long address;
    int size, time;
    time = 0;

    while (fscanf(filePtr, "%llx", &address) > 0) {         //Differenting between Read and Write by Splitting the string 

        if (identifier == 'I') continue;
         CacheAccess(val, address, &time);
        
        time++;
    }

    free(val);
    fclose(filePtr);

    printSummary(hits, misses);                        // Giving Output 
    return 0;
}