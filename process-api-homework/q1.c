#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int x = 10; // Variable in the parent process
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        x = 15;
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("Value of x in child is %d\n", x);
    } else {
        // parent goes down this path (original process)
        x = 20;
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
        printf("Value of x in parent is %d\n", x);
    }
    return 0;
}
