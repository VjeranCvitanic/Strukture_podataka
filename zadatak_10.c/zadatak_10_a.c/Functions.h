#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE 1024

struct _CityTree;
typedef struct _CityTree* CityPosition;
typedef struct _CityTree
{
	char name[MAX_LINE];
	int population;
	CityPosition left;
	CityPosition right;
}CityElement;


struct _CountryList;
typedef struct _CountryList* CountryPosition;
typedef struct _CountryList
{
	char name[MAX_LINE];
	CityPosition cityHead;
	CountryPosition next;
}CountryElement;


int ReadFromFirstFile(CountryPosition head, char fileName[MAX_LINE], char* destination, char* nameDestination);
int ReadFromNewFile(CountryPosition head, char countryName[MAX_LINE], char fileName[MAX_LINE]);
CountryPosition CreateNewCountryElement(char countryName[MAX_LINE]);
int InsertCountryElement(CountryPosition head, char countryName[MAX_LINE]);

CityPosition CreateNewCityElement(char cityName[MAX_LINE], int population);
int InsertCityElement(CountryPosition head, char cityName[MAX_LINE], int population);
CityPosition Insert(CityPosition head, CityPosition new);

int Print(CountryPosition head);
int PrintCities(CityPosition head);

CountryPosition Find(CountryPosition head, char countryName[MAX_LINE]);
int FindBiggerCities(CityPosition current, int number);

void PrintLine();
#endif 

