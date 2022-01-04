#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"
#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE 1024

CountryPosition CreateNewCountryElement(char name[])
{
	CountryPosition new = NULL;
	new = (CountryPosition)malloc(sizeof(CountryElement));

	if (!new)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	new->cityHead = NULL;
	new->left = NULL;
	new->right = NULL;
	strcpy(new->name, name);

	return new;
}

CityPosition CreateNewCityElement(char name[], int population)
{
	CityPosition new = NULL;
	new = (CityPosition)malloc(sizeof(CityElement));

	if (!new)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	strcpy(new->name, name);
	new->next = NULL;
	new->population = population;

	return new;
}

int ReadFromFirstFile(CountryPosition head, char fileName[MAX_LINE], char* countrieNamesDestination, char* fileNamesDestination)
{
	char* buffer = (char*)malloc(MAX_LINE * sizeof(char));

	char countryName[MAX_LINE] = { 0 }, fileNameNew[MAX_LINE] = { 0 };

	FILE* fp = fopen(fileName, "r");

	if (!fp)return EXIT_FAILURE;

	fgets(buffer, MAX_LINE, fp);

	sscanf(buffer, "%s %s", countryName, fileNameNew);

	strncat(countrieNamesDestination, countryName);
	strncat(countrieNamesDestination, " ");

	strncat(fileNamesDestination, fileNameNew);
	strncat(fileNamesDestination, " ");

	head = CreateNewCountryElement(countryName);

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);

		if (sscanf(buffer, "%s %s", countryName, fileNameNew) != 2)break;

		strncat(countrieNamesDestination, countryName);
		strncat(countrieNamesDestination, " ");

		strncat(fileNamesDestination, fileNameNew);
		strncat(fileNamesDestination, " ");

		CountryPosition new = CreateNewCountryElement(countryName);
		if (new)
		{
			InsertCountry(head, new);
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int InsertCountry(CountryPosition head, CountryPosition new)
{
	if (head)
	{
		if (strcmp(head->name, new->name) < 0)
		{
			head->right = Insert(head->right, new);
		}

		else head->left = Insert(head->left, new);
	}

	return EXIT_SUCCESS;
}

CountryPosition Insert(CountryPosition head, CountryPosition new)
{
	if (!head)
		return new;

	else
	{
		if (strcmp(head->name, new->name) > 0)head->left = Insert(head->left, new);

		else head->right = Insert(head->right, new);

		return head;
	}
}

int ReadFromNewFiles(CountryPosition head, char fileName[MAX_LINE])
{
	FILE* fp = fopen(fileName, "r");
	char* buffer = (char*)malloc(sizeof(char) * MAX_LINE);

	int cityPopulation = 0;
	char cityName[MAX_LINE];

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);

		if (sscanf(buffer, "%s %d", cityName, cityPopulation) != 2)break;

		CityPosition new = CreateNewCityElement(cityName, cityPopulation);

		InsertCity(head->cityHead, new);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int InsertCity(CityPosition first, CityPosition new)
{
	CityPosition temp = first->next;
	CityPosition prev = first;
	while (temp != NULL && new->population < temp->population)
	{
		prev = temp;
		temp = temp->next;
	}

	if (new->population == temp->population)
	{
		if (strcmp(new->name, temp->name) > 0)
		{
			new->next = temp->next;
			temp->next = new;
		}
	}
	new->next = temp;
	prev->next = new;

	return EXIT_SUCCESS;
}

int Print(CountryPosition head)
{
	if (head)
	{
		printf("%s", head->name);
		PrintCities(head->cityHead);
		Print(head->left);
		Print(head->right);
	}

	return EXIT_SUCCESS;
}

int PrintCities(CityPosition head)
{
	CityPosition temp = head->next;
	while (temp)
	{
		printf("%s ", temp->name);
		temp = temp->next;
	}

	printf("\n");

	return EXIT_SUCCESS;
}

int FindBigger(CountryPosition current, int number)
{
	CityPosition temp = current->cityHead;

	while (temp != NULL && temp->population > number)
	{
		printf("%s ", temp->name);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}