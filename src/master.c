/**
 * ARP 2022-2023 - SECOND ASSIGNMENT
 * @brief This project develops an interactive simulator that tracks objects in two dimensions, simulates camera capture, and extracts features from them.

 * @author Parinaz (s5214640@studenti.unige.it), Danial (s5217544@studenti.unige.it)
 * @version 1.0
 * @date 1 June 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define FAILURE_EXIT_CODE 1
#define MAX_PROCESSES 2

/**
 * @brief Structure to encapsulate a process
 */
typedef struct {
    const char * program; /**< The name of the program to execute */
    char **arg_list; /**< The argument list for the program */
} Process;

/**
 * @brief Spawns a child process to execute a given program
 * 
 * @param proc Process to be executed
 * @return pid_t The PID of the child process
 */
pid_t spawn(Process proc) {

    pid_t child_pid = fork();

    // Fork failed, log error and exit
    if(child_pid < 0) {
        perror("Error while forking");
        exit(FAILURE_EXIT_CODE);
    }

    // Child process: attempt to execute the program
    if(child_pid == 0) {
        if(execvp(proc.program, proc.arg_list) < 0) {
            perror("Exec failed");
            exit(FAILURE_EXIT_CODE);
        }
    }

    // Parent process: return child PID
    return child_pid;
}

/**
 * @brief Waits for a process with a given PID to finish, and logs its exit status
 * 
 * @param pid The PID of the process to wait for
 */
void wait_for(pid_t pid) {
    int status;
    waitpid(pid, &status, 0);

    if(WIFEXITED(status)) {
        printf("Child process with pid %d exited with status %d\n", pid, WEXITSTATUS(status));
    } else {
        printf("Child process with pid %d terminated abnormally\n", pid);
    }
}

/**
 * @brief Main function
 * 
 * Spawns and waits for two child processes that execute /usr/bin/konsole with different arguments.
 * 
 * @return int Exit status. Returns 0 if execution was successful.
 */
int main() {

    // Define the processes to execute
    char * arg_list_A[] = { "/usr/bin/konsole", "-e", "./bin/processA", NULL };
    char * arg_list_B[] = { "/usr/bin/konsole", "-e", "./bin/processB", NULL };

    Process processes[MAX_PROCESSES] = {
        {"/usr/bin/konsole", arg_list_A},
        {"/usr/bin/konsole", arg_list_B}
    };

    pid_t pids[MAX_PROCESSES];

    // Spawn child processes
    for(int i = 0; i < MAX_PROCESSES; i++) {
        pids[i] = spawn(processes[i]);
    }

    // Wait for child processes to finish
    for(int i = 0; i < MAX_PROCESSES; i++) {
        wait_for(pids[i]);
    }

    printf("Main program exiting successfully\n");
    return 0;
}
