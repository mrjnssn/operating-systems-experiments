// studying the workings of fork() and indeterministic 
// order of process scheduling in the CPU

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("hello (pid: %d)\n", (int) getpid());
    int return_code = fork();
    printf("Return code: %d\n", return_code);
    
    if (return_code < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (return_code == 0) {
        printf("child (pid: %d)\n", (int) getpid());
        printf("Return code: %d\n", return_code);
    } else {
        // parent goes down this path
        printf("parent of %d (pid %d)\n", return_code, (int) getpid());
        printf("Return code: %d\n", return_code);
    }

    return 0;
}