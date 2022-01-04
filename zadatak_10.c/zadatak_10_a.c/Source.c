#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "Functions.h"
#define MAX_LINE 1024


int main()
{
	char fileName[MAX_LINE] = { 0 };
	char fileNames[MAX_LINE] = { 0 };
	char countryName[MAX_LINE] = { 0 };
	char countryNames[MAX_LINE] = { 0 };

	int number = 0;
	int numBytes = 0;
	int numBytes2 = 0;

	char* buffer = &fileNames;
	char* countriesBuffer = &countryNames;
	CountryPosition foundCountry = CreateNewCountryElement(" ");

	CountryElement countryHead = { .cityHead = NULL, .name = { 0 }, .next = NULL };
	CountryPosition firstCountry = &countryHead;

	CityElement cityHead = { .left = NULL, .right = NULL, .name = { 0 }, .population = 0 };
	CityPosition firstCity = &cityHead;

	printf("Enter the file name: \n");
	scanf("%s", fileName);

	if(ReadFromFirstFile(firstCountry, fileName, &fileNames, &countryNames))
		return EXIT_FAILURE;

	while (1)
	{
		if(sscanf(buffer, "%s %n", fileName, &numBytes) != 1)break;
		if(sscanf(countriesBuffer, "%s %n", countryName, &numBytes2) != 1)break;

		ReadFromNewFile(firstCountry, countryName, fileName); 

		buffer += numBytes;
		countriesBuffer += numBytes2;
	}
	
	PrintLine();
	printf("All countries and their cities(with city population)");
	Print(firstCountry);
	printf("\n");
	PrintLine();


	printf("Enter the country name: \n");
	scanf("%s", countryName);

	foundCountry = Find(firstCountry, countryName);

	printf("Enter the minimum population: \n");
	scanf("%d", &number);

	FindBiggerCities(foundCountry->cityHead, number);

	return 0;
}




