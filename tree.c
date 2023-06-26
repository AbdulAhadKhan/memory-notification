#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void signalHandler(int signum) {
    // Terminate the process
    exit(0);
}

void createChildProcesses(int level, int numProcesses) {
    if (level >= numProcesses) {
        // Leaf process
        printf("Leaf process (PID: %d) created.\n", getpid());

        // Set the signal handler to terminate after 30 seconds
        signal(SIGALRM, signalHandler);
        alarm(30);

        // Keep the process alive for 30 seconds
        while (1) {
            // Process will be terminated by the signal handler
        }
    }

    printf("Internal process (PID: %d) created two child processes:\n", getpid());

    for (int i = 0; i < numProcesses - level; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            createChildProcesses(level + 1, numProcesses);
            break;
        } else if (pid < 0) {
            fprintf(stderr, "Fork failed. Exiting.\n");
            exit(1);
        }
    }
}

int main() {
    int numProcesses = 5;

    printf("Parent process (PID: %d) created a binary tree with 2^%d = %d processes.\n", getpid(), numProcesses, 1 << numProcesses);

    createChildProcesses(0, numProcesses);

    // Wait for all child processes to terminate
    for (int i = 0; i < numProcesses; i++) {
        wait(NULL);
    }

    printf("All child processes terminated.\n");

    return 0;
}
