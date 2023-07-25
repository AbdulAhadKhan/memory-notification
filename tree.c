#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const long int MEMORY_CHOICE[] = {
    (long int)2e+8,
    (long int)8e+9,
    (long int)2e+9,
};

void signalHandler(int signum) {
    // Terminate the process
    exit(0);
}

void consumeMemory() {
    while (1) {
        long int memory = MEMORY_CHOICE[rand() % 3];
        int *arr = (int *)malloc(memory);

        printf("Process (PID: %d) allocated %ld bytes of memory.\n", getpid(),
               memory);
        sleep(1);
        free(arr);
    }
}

void createChildProcesses(int level, int numProcesses) {
    signal(SIGALRM, signalHandler);
    alarm(30);

    // Leaf process
    if (level >= numProcesses) {
        printf("Leaf process (PID: %d) created.\n", getpid());
        consumeMemory();
    }

    printf("Internal process (PID: %d) created two child processes:\n",
           getpid());

    for (int i = 0; i < numProcesses - level; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            srand(getpid());
            createChildProcesses(level + 1, numProcesses);
            consumeMemory();
            break;
        } else if (pid < 0) {
            fprintf(stderr, "Fork failed. Exiting.\n");
            exit(1);
        }
    }
}

int main() {
    int numProcesses = 3;

    printf("Parent process (PID: %d) created a binary tree with 2^%d = %d "
           "processes.\n",
           getpid(), numProcesses, 1 << numProcesses);

    createChildProcesses(0, numProcesses);

    // Wait for all child processes to terminate
    for (int i = 0; i < numProcesses; i++) {
        wait(NULL);
    }

    printf("All child processes terminated.\n");

    return 0;
}
