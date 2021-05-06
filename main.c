#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE_TOK 64
#define DELIM_TOK "\t\r\n\a"

void main_loop_interpreter(void);
char * read_line();
char ** split_line(char *);
int execute(char **);
int launch(char **);
int tefa_cd(char **);
int tefa_exit(char **);
int tefa_help(char **);
int builtin_numbers();
char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[]) (char **) = {&tefa_cd,&tefa_help,&tefa_exit};
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
int launch(char **args){
    pid_t pid, wait_paid;
    int status;

    pid = fork();

    if(pid == 0){
        if(execvp(args[0], args) < 0){
            perror("Error in Executing the program (Tefa Unix Shell)");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0){
        perror("Error in forking  (Tefa Unix Shell)");
    } else {
        do {
            wait_paid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
int builtin_numbers(){
    return sizeof(builtin_str) / sizeof(char *);
}
int tefa_cd(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "Tefa: expected argument to \"cd\"\n");
    } else{
        if (chdir(args[1]) != 0) {
            perror("Tefa");
        }
    }
    return 1;
}
int tefa_exit(char **args){
    return 0;
}
int tefa_help(char **args){
    printf("Tefa UNIX Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    for (int i = 0; i < builtin_numbers(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    printf("Use the man command for information on other programs.\n");
    return 1;
}
int execute(char ** args) {
    if (args[0] == NULL) return 1;

    for (int i = 0; i < builtin_numbers(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return launch(args);
}