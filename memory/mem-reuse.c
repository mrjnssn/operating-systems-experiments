/*
 * EXPERIMENT: REUSING MEMORY
 * 
 * system: macOS
 * total allocations: 10,000
 * freed blocks: 5,000 (every second block)
 * reallocations: 5,000
 * 
 * RESULTS:
 * -----------------------------
 *   SIZE      REUSED ADDRESSES 
 * ------------------------------
 * 32 bytes    =    32 / 5000 
 * 64 bytes    =    16 / 5000 
 * 256 bytes   =     4 / 5000 
 * 512 bytes   =  4976 / 5000 
 * 1024 bytes  =  4992 / 5000 
 *
 * Additional measurements:
 * 256 bytes   =     4 / 5000 (second try, same result)
 * 312 bytes   =  4992 / 5000
 * 257 to 304  =     0 / 5000
 * 305 bytes   =  4992 / 5000
 * 512 bytes   =  4976 / 5000 (second try, same result) 
 *
 * OBSERVATIONS:
 * 1. small allocations show little address reuse
 *
 * 2. at 1024 bytes, almost all freed addresses are reused, which
 *    leads me to conclude that the allocator changes behaviour
 *    depending on size of allocations
 *
 * 3. between exactly 257 and 304 (including) bytes, no addresses
 *    are reused at all
 *
 * 4. from 305 bytes and higher, address reuse increases sharply.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 10000
#define SIZE 260

int main(void) {
    void *blocks[N];

    for (int i = 0; i < N; i++) {
        blocks[i] = malloc(SIZE);

        if (blocks[i] == NULL) {
            return 1;
        }

        // OLD: printf("address %d: %p\n", i, blocks[i]);
    }
    
    void *freed_addresses[N / 2];

    for (int i = 0; i < N / 2; i++) {
        freed_addresses[i] = blocks[i];
        free(blocks[i]);
        blocks[i] = NULL;
    }
    
    void *new_blocks[N / 2];
    for (int i = 0; i < N / 2; i++) {
        new_blocks[i] = malloc(SIZE);

        if (new_blocks[i] == NULL) {
            return 1;
        }
    }

    int reused = 0;

    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N / 2; j++) {
            if ((uintptr_t)new_blocks[i] ==
                (uintptr_t)freed_addresses[j]) {
                    reused ++;
                    break;
                }
        }
    }

    printf("Reused addresses: %d out of %d\n", reused, N / 2);


    for (int i = 0; i < N; i++) {
        free(blocks[i]);
    }

    for (int i = 0; i < N / 2; i++) {
        free(new_blocks[i]);
    }
}