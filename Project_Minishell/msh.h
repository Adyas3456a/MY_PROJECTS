#ifndef MSH_H
#define MSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>

#define FOREGROUND 'F'
#define BACKGROUND 'B'
#define SUSPENDED 'S'
#define WAITING_INPUT 'W'
#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

void shellPrompt();
void changeDirectory(char **args);
void handleBuiltin(char **args, char *line);
void launchJob(char **args, int bg, char *line);
void parseInput(char *line, char **args);
void handle_signal(int sig);

#endif
