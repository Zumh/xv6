#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAXLENGTH 512

void execute_line(char *args[], int skip);

void parse_input(char *line, char *args[], int skip); 

int main(int argc, char *argv[])
{
    char *args[MAXARG] = { 0 };
    char buf[MAXLENGTH], *b;
    b = buf;
    // copy all all the arguments from 1  to argc from command line
    for (int i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
    }

    // we read a byte at a time from stdin
    // we then null terminate when it hits new line
    // we parse the string and execute the command result from first command
    // all the result was tokenize and append to args variable
    // command1 | xargs command2
    while (read(0, b, 1) > 0) {
        if (*b == '\n') {
            *b = '\0';
	    parse_input(buf, args, argc - 1);
            execute_line(args, argc - 1);
        }

        b++;
    }
    exit(0);
}

void parse_input(char *line, char *args[], int skip) {
    /*
     * This improved version uses a more concise approach by moving the pointers directly and efficiently through the input string while handling the parsing logic. It skips leading spaces, identifies the start of a new argument, and moves to the end of each argument, populating the argument array accordingly
     * */
    int arg_index = skip;
    char *current_char = line;

    while (*current_char != '\0') {
        while (*current_char == ' ') {
            *current_char++ = '\0'; // Set current_char to NULL terminator and move to the next character
        }

        if (*current_char != '\0') {
            args[arg_index++] = current_char; // Start of a new argument
        }

        while (*current_char != '\0' && *current_char != ' ') {
            current_char++; // Move to the end of the current argument
        }
    }

    args[arg_index] = '\0'; // Null-terminate the argument list
    printf("%s", args[arg_index - 1]);
}

void execute_line(char *args[], int skip) {
    int fork_result = fork();
    if (fork_result < 0) {
        fprintf(2, "xargs: fork failed\n");
        exit(1);
    } else if (fork_result == 0) { // Child process
        exec(args[0], args);
    } else { // Parent process
        wait(0);
    }
}

