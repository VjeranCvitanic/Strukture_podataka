#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"
#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE 1024


int main()
{
	char countries[MAX_LINE] = { 0 }, files[MAX_LINE] = { 0 };
	char* buffer = malloc(MAX_LINE * sizeof(char));
	char* buffer2 = malloc(MAX_LINE * sizeof(char));

	char countryName[MAX_LINE] = { 0 };
	char file[MAX_LINE] = { 0 };
	int numBytes = 0;
	int numBytes2 = 0;

	//CityElement cityHead = { .name = { 0 }, .next = NULL, .population = 0 };

	CountryElement head = { .cityHead = CreateNewCityElement(" ", 0), .left = NULL, .right = NULL, .name = {0}};
	CountryPosition countryHead = &head;
	if(ReadFromFirstFile(countryHead, "Countries.txt", &countries, &files)) return EXIT_FAILURE;
	buffer = countries;

	if (sscanf(buffer, "%s %n", countryName, &numBytes) == 1)
	{
		strcpy(countryHead->name, countryName);
		buffer += numBytes;
	}

	while (buffer)
	{
		if (sscanf(buffer, "%s %n", countryName, &numBytes) == 1)
		{
			CountryPosition new = CreateNewCountryElement(countryName);
			InsertCountry(countryHead, new);
			buffer += numBytes;
		}

		else break;
	}

	buffer = files;
	buffer2 = countries;

	while (sscanf(buffer, "%s %n", file, &numBytes) == 1)
	{
		if (sscanf(buffer2, "%s %n", countryName, &numBytes2) != 1)break;
		ReadFromNewFiles(countryHead, countryName, file);
		buffer += numBytes;
		buffer2 += numBytes2;
	}

	Print(countryHead);

	//FindBigger(countryHead, 75000);

	return EXIT_SUCCESS;
}