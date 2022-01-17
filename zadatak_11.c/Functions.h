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



int HashFunction(char countryName[MAX_LINE]);                                            //Raèuna hash kljuè

CountryPosition CreateNewCountryElement(char name[MAX_LINE]);                            

CityPosition CreateNewCityElement(char name[MAX_LINE], int population);

int InsertCountryElement(CountryPosition first[table_size], char name[MAX_LINE]);        //Poziva funkciju Insert za odgovarajuci head element u nizu

int Insert(CountryPosition current, CountryPosition new);                                //Inserta zemlju

int InsertCityElement(CountryPosition head, char name[MAX_LINE], int population);        //Poziva funkciju InsertCity

CityPosition InsertCity(CityPosition current, CityPosition new);                         //Rekurzivno dodaje grad 

int ReadFromFirstFile(char fileName[MAX_LINE], CountryPosition first[table_size]);       //Èita iz prvog filea

int ReadFromNewFile(CountryPosition first[table_size], char countryName[MAX_LINE], char newFileName[MAX_LINE]);  //Èita drugi file

CountryPosition FindCountry(CountryPosition first[table_size], char name[MAX_LINE]);    

int Print(CountryPosition first[table_size]);                                            //Printa sve drzave i poziva PrintCities

int PrintCities(CityPosition head);                                                      //Rekurzivno ispisuje gradove (u preorderu) 

#endif