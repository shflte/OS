#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    printf("Main pid: %d\n", getpid());
    pid = fork(); // fork 0
    if (pid == 0) {
        printf("Fork 0; Current pid: %d; parent pid: %d. \n", getpid(), getppid());
        pid = fork(); // fork 1
        if (pid > 0) {
            wait(NULL);
        }
        else if (pid == 0) {
            printf("Fork 1; Current pid: %d; parent pid: %d. \n", getpid(), getppid());
            pid = fork(); // fork 2
            if (pid == 0) {
                printf("Fork 2; Current pid: %d; parent pid: %d. \n", getpid(), getppid());
            }
            else if (pid > 0) {
                wait(NULL);
            }
        }
    }
    else if (pid > 0) {
        wait(NULL);
        pid = fork(); // fork 3
        if (pid == 0) {
            printf("Fork 3; Current pid: %d; parent pid: %d. \n", getpid(), getppid());
        }
        if (pid > 0)
            wait(NULL);
    }
    else {
        printf("Error!\n");
    }
    pid = fork(); // fork 4
    if (pid == 0) {
        printf("Fork 4; Current pid: %d; parent pid: %d. \n", getpid(), getppid());
    }
    else if (pid > 0)
        wait(NULL);
    return 0;
}