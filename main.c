#include <stdio.h>
#include <malloc.h>

#define EXIT_SUCCESS 0

void main_loop_interpreter(void);
char * read_line();
char ** split_line(char *);
int execute(char **);

int main(int argc, char **argv) {
    // Load config files.

    // Main command loop interpreter.
    main_loop_interpreter();
    // Pre-termination cleanup.
    return EXIT_SUCCESS;
}
void main_loop_interpreter(void){
    char *line;
    char **args;
    int status;

    do {
        line = read_line();
        args = split_line(line);
        status = execute(args);
        free(line);
        free(args);
    } while (status);
}

