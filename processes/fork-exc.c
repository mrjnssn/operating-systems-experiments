// attempt to explore how shared variables behave in parent 
// and child processes

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int x = 100;
    printf("variable: %d\n", x);

    int return_code = fork();

    if (return_code < 0) {
        fprintf(stderr, "fork failed"); // fork() returns -1
    } else if (return_code == 0) {
        // child process starts
        printf("Return code child process: %d\n", return_code);
        printf("original variable x in child process: %d\n", x);
        x = 99;
        printf("changed variable x in child process: %d\n", x);
    } else {
        // parent process follows this path
        printf("Return code parent process: %d\n", return_code);
        x = 101;
        printf("changed variable x in parent process: %d\n", x);
    }
    return 0;
}