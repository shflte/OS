#include<iostream>
#include<unistd.h>
#include<sys/types.h>

using namespace std;

int main()
{
    pid_t pid[10];

    cout << "Main Process ID : " << getpid() << "\n";

    pid[1] = fork(); // fork 1

    if (pid[1] == 0) {
        cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
        pid[2] = fork(); // fork 2
        if (pid[2] == 0) {
            cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
            pid[3] = fork(); // fork 3
            if (pid[3] == 0) {
                cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
                exit(0);
            }
            else if (pid[3] > 0) {
                wait(NULL);
                exit(0);
            }
        }
        else if (pid[2] > 0) {
            wait(NULL);
            exit(0);
        }
        exit(0);
    }
    else if (pid[1] > 0) {
        wait(NULL);
        pid[4] = fork(); // fork 4
        if (pid[4] == 0) {
            cout << "Fork 4. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
        }
        else if (pid[4] > 0) {
            wait(NULL);
            pid[6] = fork(); // fork 6
            if (pid[6] == 0) {
                cout << "Fork 6. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
            }
            else if (pid[6] > 0) {
                wait(NULL);
            }
        }
    }
    pid[5] = fork(); // fork 5
    if (pid[5] == 0) { 
        cout << "Fork 5. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
    }
    else if (pid[5] > 0) {
        wait(NULL);
    }
    
    return 0;
}