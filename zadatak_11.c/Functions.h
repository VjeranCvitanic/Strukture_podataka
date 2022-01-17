#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define table_size 11

struct _CityElement;
typedef struct _CityElement* CityPosition;
struct _CountryElement;
typedef struct _CountryElement* CountryPosition;
typedef struct _CountryElement
{
	char name[MAX_LINE];
	CountryPosition next;
	CityPosition cityHead;
}CountryElement;

typedef struct _CityElement
{
	char name[MAX_LINE];
	int population;
	CityPosition right;
	CityPosition left;
}CityElement;



int HashFunction(char countryName[MAX_LINE]);

CountryPosition CreateNewCountryElement(char name[MAX_LINE]);

CityPosition CreateNewCityElement(char name[MAX_LINE], int population);

int InsertCountryElement(CountryPosition first[table_size], char name[MAX_LINE]);

int Insert(CountryPosition current, CountryPosition new);

int InsertCityElement(CountryPosition head, char name[MAX_LINE], int population);

CityPosition InsertCity(CityPosition current, CityPosition new);

int ReadFromFirstFile(char fileName[MAX_LINE], CountryPosition first[table_size]);

int ReadFromNewFile(CountryPosition first[table_size], char countryName[MAX_LINE], char newFileName[MAX_LINE]);

CountryPosition FindCountry(CountryPosition first[table_size], char name[MAX_LINE]);

int Print(CountryPosition first[table_size]);

int PrintCities(CityPosition head);

#endif