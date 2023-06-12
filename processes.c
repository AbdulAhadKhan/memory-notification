#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // Added sys/types.h for pid_t
#include <unistd.h>

#define KEEP_ALIVE 30 // Number of seconds to keep the process alive

const int UPPER_LIMIT = (int)5e+8; // Upper limit for memory allocation
const int LOWER_LIMIT = (int)1e+7; // Lower limit for memory allocation
int running = 1;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        running = 0;
    }
}

int main() {
    signal(SIGINT, signalHandler); // Register the signal handler for Ctrl + C

    int numProcesses = 15; // Number of child processes to spawn

    for (int i = 0; i < numProcesses; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            srand(getpid());
            int memorySize = rand() % UPPER_LIMIT + LOWER_LIMIT;
            int *memory = (int *)malloc(memorySize * sizeof(int));
            printf("Child process (PID: %d) allocated %ld bytes of memory at "
                   "address: "
                   "%p\n",
                   getpid(), memorySize * sizeof(int), memory);

            while (running) {
                sleep(KEEP_ALIVE);
            }

            free(memory);
            printf("Child process (PID: %d) terminated.\n", getpid());
            exit(0);
        } else if (pid < 0) {
            // Fork failed
            fprintf(stderr, "Fork failed. Exiting.\n");
            return 1;
        }
    }

    // Parent process
    printf("Parent process spawned %d child processes.\n", numProcesses);
    printf("Press Ctrl + C to quit.\n");

    sleep(KEEP_ALIVE * 2);

    // Terminate all child processes
    for (int i = 0; i < numProcesses; i++) {
        kill(0, SIGTERM);
    }

    printf("Parent process terminated.\n");

    return 0;
}
