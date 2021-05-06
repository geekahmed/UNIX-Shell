#include <stdlib.h>
#include "shell-headers.h"
int main(int argc, char **argv) {
    // Load config files.
    // Main command loop interpreter.
    main_loop_interpreter();
    // Pre-termination cleanup.
    return EXIT_SUCCESS;
}
