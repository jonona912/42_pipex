#include <stdio.h>
#include <unistd.h>

int main() {
    // Arguments for the `ls` command
    char *argv[] = { "ls", "-l", NULL };
    int 
    // Environment variables (can be NULL if not needed)
    char *envp[] = { NULL };

    // Execute the `ls` command
    if (execve("/bin/ls", argv, envp) == -1) {
        perror("execve failed");
        return 1;
    }

    // This code will not be reached if execve is successful
    printf("This will not be printed.\n");
    return 0;
}
