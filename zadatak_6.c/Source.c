#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

int main()
{
	Bill head = { .date = { 0 }, .headArticle = NULL, .next = NULL };

	Position first = &head;

	char fileNames[MAX_LINE] = { 0 };
	char* buffer = (char*)malloc(MAX_LINE * sizeof(char));
	char fileName2[MAX_NAME] = { 0 };

	int numBytes = 0;

	if (ReadFromFile("racuni.txt", first, &fileNames) == EXIT_SUCCESS)
	{
		buffer = &fileNames;
		for(int i = 0; i < 5; i++)
		{
			if(sscanf(buffer, "%s%n", fileName2, &numBytes) == 1)
				ReadFromSecondFile(fileName2, first);

			sscanf(buffer, " ");
			buffer += numBytes + 1;
		}
	}

	Date d1 = { .year = 2021, .month = 8, .day = 1 };
	Date d2 = { .year = 2021, .month = 9, .day = 23 };
	int quan = 0;
	float pr = 0;

	Cost(first, "kivi", d1, d2, &quan, &pr);

	printf("kivi: %d - %f", quan, pr);

	return 0;
}