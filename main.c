#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE_TOK 64
#define DELIM_TOK "\t\r\n\a"

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
            perror("Read Line Error\n");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}
char ** split_line(char * line){
    int buffer_size = BUFFER_SIZE_TOK;
    int position = 0;
    char **tokens = malloc(buffer_size * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "Allocation Error!!\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIM_TOK);
    while (token != NULL){
        tokens[position++] = token;
        if(position >= buffer_size){
            buffer_size += BUFFER_SIZE_TOK;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
            if(!tokens){
                fprintf(stderr, "Allocation Error!!\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, DELIM_TOK);
    }
    tokens[position] = NULL;
    return tokens;

}
