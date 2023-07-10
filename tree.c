#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int UPPER_LIMIT = (int)5e+8;
const int LOWER_LIMIT = (int)1e+7;

void signalHandler(int signum) {
    // Terminate the process
    exit(0);
}

void consumeMemory() {
    while (1) {
        int memorySize = rand() % UPPER_LIMIT + LOWER_LIMIT;
        int *memory = (int *)malloc(memorySize * sizeof(int));

        sleep(1);
        free(memory);
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
