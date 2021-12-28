#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024

int main(int argc, char* argv[])
{
	double result = 0;
	int status = 0;
	char fileName[MAX_LINE] = { 0 };
	printf("Unesi ime file-a:\n");
	scanf("%s", fileName);
	status = CalculateFromFile(fileName, &result);
	if (status == EXIT_SUCCESS)
	{
		printf("Krajnji rezultat postfixa je %lf", result);
	}
	return EXIT_SUCCESS;
}