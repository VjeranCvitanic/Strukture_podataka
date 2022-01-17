#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

int main()
{
	CountryElement head[table_size] = { 0 };
	CountryPosition first[table_size] = { 0 };
	for (int i = 0; i < table_size; i++)
	{
		strcpy(head[i].name, " ");
		head[i].cityHead = NULL;
		head[i].next = NULL;
		first[i] = &head[i];
	}

	ReadFromFirstFile("drzave.txt", first);

	Print(first);

	return 0;
}