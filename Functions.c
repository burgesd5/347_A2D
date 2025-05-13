#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "Functions.h"

//Default file access permissions for new files
#define ACCESS_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define FILE_LINE_BUFFER_SIZE (NAME_SIZE + RANK_SIZE + SERIAL_NUMBER_SIZE)

int writeRecord(char* filename, char* name, char* rank, char* serialNumber)
{
	
	return status;
}

int readRecord(char* filename, int serialNumber, char* nameBuffer, char* rankBuffer, char* serialNumberBuffer)
{
	int status = 0;
	

	return status;
}
