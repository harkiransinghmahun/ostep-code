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
        printf("I am child (pid:%d)\n", (int) getpid());
        int fd = open("ls_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("open failed");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl failed");
    } else {
        // parent goes down this path (original process)
        printf("I am parent of %d (pid:%d)\n", rc, (int) getpid());
    }
    return 0;
}
