#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void main()
{

    char buffer1[] = "Executing file manipulations system calls\n";
    char buffer2[100];
    int fd = open("filecalls.txt", O_RDWR | O_CREAT);
    if (fd == -1)
    {
        printf("Failure to open file\n");
        exit(0);
    }
    printf("File opened\n");
    printf("Writing from buffer into file\n");
    write(fd, buffer1, strlen(buffer1));
    close(fd);
    fd = open("filecalls.txt",O_RDONLY);
    if (fd == -1)
    {
        printf("Failure to open file\n");
        exit(0);
    }
    printf("Reading from file into buffer\n");
    read(fd, buffer2, strlen(buffer1));
    buffer2[strlen(buffer1)]='\0';
    printf("Buffer = %s", buffer2);
    if (close(fd) == -1)
    {
        printf("Error in closing the file\n");
        exit(0);
    }
    printf("File closed\n");
}
