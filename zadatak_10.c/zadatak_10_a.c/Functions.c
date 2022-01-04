#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "Functions.h"
#define MAX_LINE 1024

int ReadFromFirstFile(CountryPosition head, char fileName[MAX_LINE], char* destination, char* nameDestination)
{
	char* buffer = NULL;
	char countryName[MAX_LINE] = { 0 };
	char newFileName[MAX_LINE] = { 0 };
	int numBytes = 0;
	int i = 0;
	int flag = 1;

	buffer = (char*)malloc(MAX_LINE * sizeof(char));
	FILE* fp = fopen(fileName, "r");

	if (!fp)
	{
		printf("Couldn't open the file!\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);

		if (sscanf(buffer, "%s %s%n", countryName, newFileName, &numBytes) == 2)
		{
			InsertCountryElement(head, countryName);
			strncat(destination, newFileName);
			strncat(destination, " ");

			strncat(nameDestination, countryName);
			strncat(nameDestination, " ");

			buffer += numBytes;
		}

		else
		{
			printf("Incorrect file!");
			return EXIT_FAILURE;
		}
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int ReadFromNewFile(CountryPosition head, char countryName[MAX_LINE], char fileName[MAX_LINE])
{
	char cityName[MAX_LINE] = { 0 };
	int population = 0;

	FILE* fp = fopen(fileName, "r");

	char* buffer = NULL;
	buffer = (char*)malloc(MAX_LINE * sizeof(char));

	CountryPosition temp = head->next;
	CountryPosition q = NULL;

	CityPosition new = NULL;

	while (temp != NULL && strcmp(temp->name, countryName) < 0)
	{
		temp = temp->next;
	}

	if (!temp)
	{
		printf("Incorrect file!\n");
		return EXIT_FAILURE;
	}


	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);

		if (sscanf(buffer, "%s %d", cityName, &population) == 2)
		{
			InsertCityElement(temp, cityName, population);
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

CountryPosition CreateNewCountryElement(char countryName[MAX_LINE])
{
	CountryPosition new = NULL;
	new = (CountryPosition)malloc(sizeof(CountryElement));

	if (!new)
	{
		printf("Couldn't allocate memory!\n");
		return NULL;
	}

	strcpy(new->name, countryName);
	new->cityHead = NULL;
	new->next = NULL;

	return new;
}

int InsertCountryElement(CountryPosition head, char countryName[MAX_LINE])
{
	CountryPosition new = CreateNewCountryElement(countryName);
	CountryPosition temp = head->next;
	CountryPosition prev = head;
	if (new)
	{
		while(temp!= NULL && strcmp(countryName, temp->name) >= 0)
		{
			prev = temp;
			temp = temp->next;
		}

		new->next = temp;
		prev->next = new;

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

CityPosition CreateNewCityElement(char cityName[MAX_LINE], int population)
{
	CityPosition new = NULL;
	new = (CityPosition)malloc(sizeof(CityElement));

	if (!new)
	{
		perror("Couldn't allocate memory!\n");
		return  NULL;
	}

	strcpy(new->name, cityName);
	new->population = population;
	new->left = NULL;
	new->right = NULL;

	return new;
}

int InsertCityElement(CountryPosition head, char cityName[MAX_LINE], int population)
{
	CityPosition new = CreateNewCityElement(cityName, population);
	CityPosition temp = head->cityHead;

	if (!new)
	{
		return EXIT_FAILURE;
	}

	head->cityHead = Insert(temp, new);

	return EXIT_SUCCESS;
}

CityPosition Insert(CityPosition head, CityPosition new)
{
	if (!head)
	{
		return new;
	}

	if (new->population > head->population)
	{
		head->right = Insert(head->right, new);
	}

	else if (new->population < head->population)
	{
		head->left = Insert(head->left, new);
	}

	else
	{
		if (strcmp(head->name, new->name) > 0)
		{
			new->left = head->left;
			head->left = new;
			new->right = NULL;
			return head;
		}

		else
		{
			new->right = head->right;
			head->right = new;
			new->left = NULL;
			return head;
		}
	}

	return head;
}

int Print(CountryPosition head)
{
	CountryPosition temp = head->next;

	while (temp)
	{
		printf("\n\n%s:\n", temp->name);
		PrintCities(temp->cityHead);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int PrintCities(CityPosition head)
{
	CityPosition temp = head;

	if (temp)
	{
		printf("%s(%d) ", temp->name, temp->population);
		PrintCities(temp->left);
		PrintCities(temp->right);
	}

	return EXIT_SUCCESS;
}

CountryPosition Find(CountryPosition head, char countryName[MAX_LINE])
{
	CountryPosition temp = head->next;
	while ((temp != NULL) && (strcmp(temp->name, countryName) != 0))
	{
		temp = temp->next;
	}

	if (!temp)
	{
		perror("Wrong input, there is no country named %s.\nPlease try again.\n", countryName);
		return NULL;
	}

	return temp;
}

int FindBiggerCities(CityPosition current, int number)
{
	if (current)
	{
		FindBiggerCities(current->left, number);
		if (current->population > number)
		{
			printf("%s ", current->name);
		}
		FindBiggerCities(current->right, number);
	}

	return EXIT_SUCCESS;
}

void PrintLine()
{
	printf("\n------------------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------\n");
}