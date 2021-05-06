#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


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
        printf("Tefa> ");
        line = read_line();
        args = split_line(line);
        status = execute(args);
        free(line);
        free(args);
    } while (status);
}
char * read_line(){
    char *line = NULL;
    ssize_t buffer_size = 0;

    if(getline(&line, &buffer_size, stdin) < 0){
        if(feof(stdin))
            exit(EXIT_SUCCESS);
        else{
            perror("Read Line Error");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}
