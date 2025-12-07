#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
        wait(NULL);
    } else {
        // parent goes down this path (original process)
        printf("Goodbye, I am parent of %d (pid:%d)\n", rc, getpid());
    }
    return 0;
}
