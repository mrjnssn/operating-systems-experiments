/* 
 * EXPERIMENT: MEMORY ALLOCATION BEHAVIOUR
 *
 * experiment to discover how malloc() allocates memory
 *
 * Is memory allocated in contigious blocks?
 *
 * tested with size 24, 25 and 33
 * 
 * OBSERVATIONS:
 * discovered randomized memory locations and fixed-sized
 * classes of 16 bytes or multiples thereof, leading to
 * potential internal fragmentation (i.e. SIZE 25 gets a 
 * 32-byte class size in memory allocated to it)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 10
#define SIZE 16

int main(void) {
    void *blocks[N];

    for (int i = 0; i < N; i++) {
        blocks[i] = malloc(SIZE);

        if (blocks[i] == NULL) {
            return 1;
        }

        printf("address %d: %p\n", i, blocks[i]);
    }

    for (int i = 0; i < N; i++) {
        free(blocks[i]);
    }

}