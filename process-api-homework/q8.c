#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


// Aim is child 1 writes and child 2 reads
int
main(int argc, char *argv[])
{
    printf("Creating a pipe\n");
    int pipefd[2];
    pipe(pipefd); // index 0 is read and index 1 is write


    int rc1 = fork();
    int rc2 = fork();
    if (rc1 < 0 || rc2 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // child process 1 writes
        close(pipefd[0]); // Close read end of pipe
        write(pipefd[1], "Hello World", 12); // Write to write end of pipe
    }  else if (rc2 == 0) {
        // child process 2 reads
        close(pipefd[1]); // Close write end of pipe
        char buff[10];
        read(pipefd[0], buff , sizeof(buff)); // Write to write end of pipe
        printf("Child 2 read: %s\n", buff);
    }
    else {
        // parent goes down this path (original process)
        waitpid(rc1, NULL, 0);
        waitpid(rc2, NULL, 0);
        printf("Parent done\n");
    }
    return 0;
}
