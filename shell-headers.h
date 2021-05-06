#ifndef UNIX_SHELL_SHELL_HEADERS_H
#define UNIX_SHELL_SHELL_HEADERS_H
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
#endif //UNIX_SHELL_SHELL_HEADERS_H
