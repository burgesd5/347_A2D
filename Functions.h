#pragma once

#define NAME_SIZE 16
#define RANK_SIZE 16
#define SERIAL_NUMBER_SIZE 16
#define FILE_LINE_BUFFER_SIZE (NAME_SIZE + RANK_SIZE + SERIAL_NUMBER_SIZE)

int writeRecord(char* filename, char* name, char* rank, char* serialNumber);
int readRecord(char* filename, int serialNumber, char* nameBuffer, char* rankBuffer, char* serialNumberBuffer);
