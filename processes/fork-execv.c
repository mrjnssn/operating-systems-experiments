// implementation of fork() in combination with execv()
// to explore the difference between the two 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int return_code = fork();
    
    if (return_code < 0) {
        // fail
        perror("fork failed");
        exit(1);
    } else if (return_code > 0) {
        // parent
        int return_code_wait = wait(NULL);
        printf("\ngoodbye from the parent (id: %d)\n", (int) getpid());
    } else {
        // child
        printf("hello from the child (id: %d)", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("cat");
        myargs[1] = strdup("hello-world.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        printf("this should never print\n");
    }
    return 0;
}