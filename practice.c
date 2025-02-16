#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    write(1, "ex1\n", 4);
    printf("First: %s\nSecond: %s\n", argv[0], argv[1]);

    return (0);
}
