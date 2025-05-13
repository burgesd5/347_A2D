#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utilities.h"
#include "Functions.h"

#define USER_INPUT_SIZE 50
#define FILE_NAME_SIZE 50

int main(void)
{
	printf("Program executing...\n\n");
	
	char userInput[USER_INPUT_SIZE] = {0};
	char enterRecordAnswer = 0;

	char* enterRecordPrompt = "Enter A to add a record, S to search for a record, Q to quit: ";
	char* enterNamePrompt = "Enter name: ";
	char* enterRankPrompt = "Enter rank: ";
	char* enterSerialNumberPrompt = "Enter serial number: ";

	char filename[FILE_NAME_SIZE] = {0};
	char name[NAME_SIZE] = {0};
	char rank[RANK_SIZE] = {0};
	char serialNumberBuffer[SERIAL_NUMBER_SIZE] = {0};

	strncpy(filename, "Data.bin", FILE_NAME_SIZE);

	enterRecordAnswer = ReadUserInputAsChar(enterRecordPrompt, userInput, USER_INPUT_SIZE);
	printf("\n");
	
	while (enterRecordAnswer != 'Q')
	{
		if (enterRecordAnswer == 'A')
		{
			ReadUserInput(enterNamePrompt, name, NAME_SIZE);
			ReadUserInput(enterRankPrompt, rank, RANK_SIZE);
			ReadUserInput(enterSerialNumberPrompt, serialNumberBuffer, SERIAL_NUMBER_SIZE);

			writeRecord(filename, name, rank, serialNumberBuffer);

			printf("\n");
		}

		if (enterRecordAnswer == 'S')
		{
			ReadUserInput(enterSerialNumberPrompt, serialNumberBuffer, SERIAL_NUMBER_SIZE);

			int serialNumber = atoi(serialNumberBuffer);
			
			readRecord(filename, serialNumber, name, rank, serialNumberBuffer);

			printf("Name: %s Rank: %s Serial Number: %s\n", name, rank, serialNumberBuffer);

			printf("\n");	
		}

		enterRecordAnswer = ReadUserInputAsChar(enterRecordPrompt, userInput, USER_INPUT_SIZE);
		printf("\n");
	}

	printf("Program complete...\n");

	return 0;
}
