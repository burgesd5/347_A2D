/*
# Name: Elijah Atienza, Dylan Burges
# Description: 
# Date: 4/13/2025
*/
#include <stdlib.h>
#include <unistd.h> // linux I/O header
#include <fcntl.h> // flag header header
#include <string.h>
#include "Functions.h"

//Default file access permissions for new files
#define ACCESS_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define FILE_LINE_BUFFER_SIZE (NAME_SIZE + RANK_SIZE + SERIAL_NUMBER_SIZE)

int writeRecord(char* filename, char* name, char* rank, char* serialNumber) 
{
    int status = 0;
	// open Data.bin for writing or create it if it doesn't exist
    int fd = open("Data.bin", O_WRONLY | O_CREAT, ACCESS_MODE);
    if (fd == -1) {
        write(1, "file open error\n", 16);
		return -1; // Don't want to continue here
    }

    // creating buffers for the given fields
    char nameBuf[NAME_SIZE];
    char rankBuf[RANK_SIZE];
    char serialNumBuf[SERIAL_NUMBER_SIZE];

	// clearing and getting the provided data into the buffers
	// while filling remaining space with null
	for (int i = 0; i < NAME_SIZE; i++) {
		nameBuf[i] = (i < strlen(name)) ? name[i] : '\0';
	}
	for (int i = 0; i < RANK_SIZE; i++) {
		rankBuf[i] = (i < strlen(rank)) ? rank[i] : '\0';
	}
	for (int i = 0; i < SERIAL_NUMBER_SIZE; i++) {
		serialNumBuf[i] = (i < strlen(serialNumber)) ? serialNumber[i] : '\0';
	}

    // we need serial as an int to calc offset
    int newSerial = atoi(serialNumber);

    // calc record size, then offset based on that
    int recSize = NAME_SIZE + RANK_SIZE + SERIAL_NUMBER_SIZE;
	int ofs = newSerial * recSize;

    // getting pointer at right offset, using SEEK_SET to jump to exact record
    if (lseek(fd, ofs, SEEK_SET) == -1) {
        write(1, "seek error\n", 11);
        close(fd);
        status = -1;
		return status;
    }

    // attempting to write all 3 fields in the correct order
    if (write(fd, nameBuf, NAME_SIZE) == -1 || write(fd, rankBuf, RANK_SIZE) == -1 ||
        write(fd, serialNumBuf, SERIAL_NUMBER_SIZE) == -1) 
	{
		write(1, "write error\n", 13);
        close(fd);
        status = -1;
		return status;
    }

    if (close(fd) == -1) {
        write(1, "close error\n", 12);
        status = -1;
		return status;
    }
	
	// Success if we got here
	return status;
}


int readRecord(char* filename, int serialNumber, char* nameBuffer, char* rankBuffer, char* serialNumberBuffer) 
{
    int status = 0;

    // open file for reading
    int fd;
	if ((fd = open(filename, O_RDONLY)) == -1) {
		write(1, "open error\n", 11);
		status = -1;
		return status;
	}

    // creating buffers for the given fields
    char nameBuf[NAME_SIZE];
    char rankBuf[RANK_SIZE];
    char serialNumBuf[SERIAL_NUMBER_SIZE];

	// calc record size, then offset based on that
    int recSize = NAME_SIZE + RANK_SIZE + SERIAL_NUMBER_SIZE;
	int ofs = serialNumber * recSize;

    if (lseek(fd, ofs, SEEK_SET) == -1) {
        write(1, "seek error\n", 11);
        close(fd);
        return -1;
    }

    // reading all fields from the file
    if (read(fd, nameBuf, NAME_SIZE) <= 0 || read(fd, rankBuf, RANK_SIZE) <= 0 ||
        read(fd, serialNumBuf, SERIAL_NUMBER_SIZE) <= 0) {
        write(1, "read error\n", 12);
        close(fd);
        return -1;
    }

    // clearing and copying data from previous buffers to output bufs
	// while filling remaining space with null terminators
	for (int i = 0; i < NAME_SIZE; i++) {
		nameBuffer[i] = (i < strlen(nameBuf)) ? nameBuf[i] : '\0';
	}
	for (int i = 0; i < RANK_SIZE; i++) {
		rankBuffer[i] = (i < strlen(rankBuf)) ? rankBuf[i] : '\0';
	}
	for (int i = 0; i < SERIAL_NUMBER_SIZE; i++) {
		serialNumberBuffer[i] = (i < strlen(serialNumBuf)) ? serialNumBuf[i] : '\0';
	}

    if (close(fd) == -1) {
        write(1, "close error\n", 12);
        return -1;
    }
	// success if we got here
    return status;
}

