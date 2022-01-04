#include "Functions.h"
#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE 1024
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	char countries[MAX_LINE] = { 0 }, files[MAX_LINE] = { 0 };
	char buffer[MAX_LINE] = { 0 };

	CountryPosition head = CreateNewCountryElement(buffer);
	if(ReadFromFirstFile(head, "Countries.txt", &countries, &files)) return EXIT_FAILURE;

	ReadFromNewFiles(head, files);

	Print(head);

	return EXIT_SUCCESS;
}