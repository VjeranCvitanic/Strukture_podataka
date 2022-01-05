#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE 1024

struct _CityElement;
typedef struct _CityElement* CityPosition;

struct _CountryElement;
typedef struct _CountryElement* CountryPosition;
typedef struct _CountryElement
{
	char name[MAX_LINE];
	CityPosition cityHead;
	CountryPosition left;
	CountryPosition right;

}CountryElement;



typedef struct _CityElement
{
	char name[MAX_LINE];
	int population;
	CityPosition next;
}CityElement;


CountryPosition CreateNewCountryElement(char name[]);

CityPosition CreateNewCityElement(char name[], int population);

int ReadFromFirstFile(CountryPosition head, char fileName[MAX_LINE], char* countrieNamesDestination, char* fileNamesDestination);

int ReadFromNewFiles(CountryPosition head, char countryName[MAX_LINE], char fileName[MAX_LINE]);

int InsertCountry(CountryPosition head, CountryPosition new);

CountryPosition Insert(CountryPosition head, CountryPosition new);

int InsertCity(CityPosition first, CityPosition new);

int Print(CountryPosition head);

int PrintCities(CityPosition head);

int FindBigger(CountryPosition current, int number);

CountryPosition Find(CountryPosition head, char countryName[MAX_LINE]);
#endif 

