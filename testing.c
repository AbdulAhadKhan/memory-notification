#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_MEMORY_SIZE 1024 // Maximum memory allocation size
#define DURATION 60 // Duration in seconds

void signalHandler(int signal);
void setAlarm();

int main() {
    pid_t pid;
    int i;

    // Register signal handler for SIGINT (Ctrl+C) and SIGALRM (timer expiration)
    signal(SIGINT, signalHandler);
    signal(SIGALRM, signalHandler);

    setAlarm(); // Set the alarm after 60 seconds

    for (i = 0; i < 15; i++) {
        pid = fork();
        
        if (pid == 0) {
            // Child process
            srand(getpid());
            while (1) {
                // Randomly choose memory operation (increase or decrease)
                int operation = rand() % 2;
                
                if (operation == 0) {
                    // Increase memory allocation
                    int size = rand() % MAX_MEMORY_SIZE;
                    void* ptr = malloc(size);
                    printf("Child process %d allocated %d bytes\n", getpid(), size);
                    
			sleep(DURATION);
                } else {
                    // Decrease memory allocation
                    sleep(1);
                    printf("Child process %d freed memory\n", getpid());
                    break;
                }
            }
            
            return 0;
        } else if (pid < 0) {
            // Error occurred while forking
            printf("Error occurred while forking!\n");
            return 1;
        }
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0) {
        // Do nothing
    }

    return 0;
}

void signalHandler(int signal) {
    if (signal == SIGINT) {
        // Free allocated memory and terminate all processes
        printf("\nReceived Ctrl+C signal. Freeing memory and terminating all processes.\n");
        while (wait(NULL) > 0) {
            // Do nothing
        }
        exit(0);
    } else if (signal == SIGALRM) {
        // Set SIGINT after 60 seconds
        setAlarm();
        raise(SIGINT);
    }
}

void setAlarm() {
    alarm(DURATION);
}

