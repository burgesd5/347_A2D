/*
# Name: Elijah Atienza, Dylan Burges
# Description: 
# Date: 4/13/2025
*/
#include "Utilities.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void ReadUserInput(char* prompt, char* read_buffer, int read_buffer_size) 
{
    printf("%s", prompt); // prompting the user

    // read input, limit read_buffer_size for null terminator
    if (!fgets(read_buffer, read_buffer_size, stdin)) {
        // clear on fail
        memset(read_buffer, 0, read_buffer_size);
        return;
    }
    // get rid of trailing newline
    int len = strlen(read_buffer);
    if (len && read_buffer[len - 1] == '\n') {
        read_buffer[len - 1] = '\0';
    }
}

char ReadUserInputAsChar(char* prompt, char* read_buffer, int read_buffer_size) 
{
    ReadUserInput(prompt, read_buffer, read_buffer_size);
    // cast to char, and first character as uppercase
    return (char)toupper(read_buffer[0]);
}


