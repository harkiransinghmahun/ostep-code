#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
    int closefd = close(STDOUT_FILENO); // Close stdout and open a new file
    printf("Close FD: %d\n", closefd);

    int openfd = open("./q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    printf("Open FD: %d\n", openfd);

    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        for (int i = 1; i <= 10000; i++) {
            printf("Child is counting: %d\n", i);
        }

    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());

        for (int i = 1; i <= 10000; i++) {
            printf("Parent is counting: %d\n", i);
        }
    }
    return 0;
}
