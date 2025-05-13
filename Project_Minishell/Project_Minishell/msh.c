/*############################################################################################### 
 *
 *           Author         : Emertxe-style Shell Implementation
 *           Date           : 2025-05-13
 *           File           : msh.c
 *           Description    : minishell program capable of executing commands and job control
 *           Objective      : To create a basic shell mimicking BASH
 *           Usage          : ./msh
 *           Output         : Matches Emertxe sample output
 *
 ###############################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "msh.h"

#ifdef __linux__
#include <unistd.h>  // For readlink on Linux
#elif __APPLE__
#include <mach-o/dyld.h>  // For _NSGetExecutablePath on macOS
#include <stdlib.h>  // For getenv()
#elif _WIN32
#include <windows.h>  // For GetModuleFileName on Windows
#include <stdlib.h>  // For getenv()
#endif

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

char* prompt = "msh> ";
int last_exit_status = 0;
pid_t shell_pid;
char shell_path[1024];

typedef struct job {
    pid_t pid;
    char command[MAX_CMD_LEN];
    struct job *next;
} job;

job *job_list = NULL;

void add_job(pid_t pid, const char *cmd) {
    job *new_job = malloc(sizeof(job));
    new_job->pid = pid;
    strncpy(new_job->command, cmd, MAX_CMD_LEN);
    new_job->next = job_list;
    job_list = new_job;
}

void get_shell_path() {
    #ifdef __APPLE__
    uint32_t size = sizeof(shell_path);
    if (_NSGetExecutablePath(shell_path, &size) != 0) {
        perror("Failed to get shell path on macOS");
    }
    #elif _WIN32
    if (GetModuleFileName(NULL, shell_path, sizeof(shell_path)) == 0) {
        perror("Failed to get shell path on Windows");
    }
    #else
    if (readlink("/proc/self/exe", shell_path, sizeof(shell_path)) == -1) {
        perror("Failed to get shell path on Linux");
    }
    #endif
}

void remove_job(pid_t pid) {
    job *curr = job_list, *prev = NULL;
    while (curr) {
        if (curr->pid == pid) {
            if (prev) prev->next = curr->next;
            else job_list = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void print_jobs() {
    job *curr = job_list;
    while (curr) {
        printf("[%d] %s\n", curr->pid, curr->command);
        curr = curr->next;
    }
}

void bring_fg(pid_t pid) {
    int status;
    tcsetpgrp(STDIN_FILENO, pid);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    if (WIFSTOPPED(status)) {
        printf("[%d]+ Stopped\n", pid);
    } else {
        remove_job(pid);
    }
}

void signal_handler(int sig) {
    printf("\n");
    shellPrompt();
    fflush(stdout);
}

void shellPrompt() {
    char *ps1 = getenv("PS1");
    if (ps1) {
        printf("%s", ps1);
    } else {
        printf("%s", prompt);
    }
    fflush(stdout);
}

void changeDirectory(char **args) {
    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        chdir(getenv("HOME"));
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

int is_background(char **args) {
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], "&") == 0) {
            args[i] = NULL;
            return 1;
        }
    }
    return 0;
}

int has_pipe(char *line) {
    return strchr(line, '|') != NULL;
}

void exec_pipe(char *line) {
    char *cmds[10];
    int i = 0;
    cmds[i++] = strtok(line, "|");
    while ((cmds[i++] = strtok(NULL, "|")) != NULL);

    int pipefd[2], in_fd = 0;
    pid_t pid;

    for (int j = 0; cmds[j]; j++) {
        pipe(pipefd);
        pid = fork();
        if (pid == 0) {
            dup2(in_fd, 0);
            if (cmds[j + 1]) dup2(pipefd[1], 1);
            close(pipefd[0]);
            char *args[MAX_ARGS];
            parseInput(cmds[j], args);
            execvp(args[0], args);
            perror("pipe exec");
            exit(1);
        } else {
            wait(NULL);
            close(pipefd[1]);
            in_fd = pipefd[0];
        }
    }
}

void handle_redirection(char **args) {
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        } else if (strcmp(args[i], ">>") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        } else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i+1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
}

void handleBuiltin(char **args, char *line) {
    pid_t pid;
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        changeDirectory(args);
    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    } else if (strcmp(args[0], "echo") == 0) {
        pid = fork();
        if (pid == 0) {
            // In the child process, apply redirection and execute echo
            handle_redirection(args);
            if (args[1]) {
                if (strcmp(args[1], "$?") == 0) {
                    printf("%d\n", last_exit_status);
                } else if (strcmp(args[1], "$") == 0) {
                    printf("%d\n", shell_pid);
                } else if (strcmp(args[1], "$SHELL") == 0) {
                    printf("%s\n", shell_path);
                } else {
                    for (int i = 1; args[i]; i++) printf("%s ", args[i]);
                    printf("\n");
                }
            } else {
                printf("\n");
            }
            exit(0);  // Exit after execution
        } else {
            // Parent process waits for child to finish
            wait(NULL);
        }
    } else if (strcmp(args[0], "jobs") == 0) {
        print_jobs();
    } else if (strcmp(args[0], "fg") == 0) {
        if (args[1]) bring_fg(atoi(args[1]));
        else if (job_list) bring_fg(job_list->pid);
    } else if (strcmp(args[0], "bg") == 0) {
        kill(job_list->pid, SIGCONT);
    } else {
        launchJob(args, is_background(args), line);
    }
}


void launchJob(char **args, int bg, char *line) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        last_exit_status = 1;
        return;
    }
    if (pid == 0) {
        // In the child process, apply redirection and execute the command
        handle_redirection(args);
        if (execvp(args[0], args) == -1) {
            perror("msh");
            exit(EXIT_FAILURE);
        }
    } else {
        if (bg) {
            add_job(pid, line);
            printf("[%d] %d\n", pid, pid);
        } else {
            int status;
            waitpid(pid, &status, WUNTRACED);
            if (WIFSTOPPED(status)) {
                add_job(pid, line);
                printf("[%d]+ Stopped\n", pid);
            }
            last_exit_status = WEXITSTATUS(status);
        }
    }
}


void parseInput(char *line, char **args) {
    int pos = 0;
    char *token = strtok(line, " \t\n");
    while (token != NULL && pos < MAX_ARGS - 1) {
        args[pos++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[pos] = NULL;
}

int main() {
    char line[MAX_CMD_LEN];
    char *args[MAX_ARGS];

    shell_pid = getpid();
    get_shell_path(); 

    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);

    while (1) {
        shellPrompt();
        if (!fgets(line, MAX_CMD_LEN, stdin)) {
            printf("\n");
            break;
        }
        if (strlen(line) <= 1) continue;

        if (strstr(line, "PS1 ") || strstr(line, "PS1 =")) {
            // Invalid PS1 format
            launchJob((char*[]){"echo", line, NULL}, 0, line);
            continue;
        }

        if (strncmp(line, "PS1=", 4) == 0) {
            line[strcspn(line, "\n")] = 0;
            setenv("PS1", line + 4, 1);
            continue;
        }

        if (has_pipe(line)) {
            exec_pipe(line);
            continue;
        }

        char temp_line[MAX_CMD_LEN];
        strcpy(temp_line, line);
        parseInput(temp_line, args);
        if (args[0] == NULL) continue;
        handleBuiltin(args, line);
    }

    return 0;
}
