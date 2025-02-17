#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file "infile"
    int fd = open("infile", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    printf("fd: %d\n", fd);
    // Replace stdin (file descriptor 0) with the file descriptor of "infile"
    if (dup2(fd, 0) == -1) {
        perror("dup2");
        exit(1);
    }
    printf("fd: %d\n", fd);
    printf("fd: %d\n", STDIN_FILENO);
    // Close the original file descriptor (it's no longer needed)
    close(fd);

    // Execute "grep a1"
    execlp("grep", "grep", "a1", NULL);

    // If execlp fails
    perror("execlp");
    exit(1);
}
