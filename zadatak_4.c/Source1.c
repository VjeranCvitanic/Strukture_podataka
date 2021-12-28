#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1024

struct _Polinom;
typedef struct _Polinom* Position;
typedef struct _Polinom
{
	int koef;
	int pot;
	Position next;
}Polinom;

Position CreateNewElement(int koef, int pot);
int ReadFromFile(char datoteka[MAX], Position p1, Position p2);
void SortList(Position p, Position new);
int InsertAfter(Position p, Position new);
void PrintList(Position p);
Position FindBefore(Position p, Position temp);
Position SumF(Position p1, Position p2, Position p3);
int Delete(Position p, Position temp);
Position ProductF(Position p1, Position p2, Position p3);

int main()
{
	Polinom Head1 = { .koef = 0, .pot = 0, .next = NULL };
	Polinom Head2 = { .koef = 0, .pot = 0, .next = NULL };
	Polinom HeadSum = { .koef = 0, .pot = 0, .next = NULL };
	Polinom HeadProduct = { .koef = 0, .pot = 0, .next = NULL };
	Position p1 = &Head1;
	Position p2 = &Head2;
	Position Sum = &HeadSum;
	Position Product = &HeadProduct;
	ReadFromFile("Polinom.txt", p1, p2);
	printf("Prvi polinom:\n");
	PrintList(p1);
	printf("Drugi polinom:\n");
	PrintList(p2);
	Sum = SumF(p1, p2, Sum);
	printf("Suma polinoma je:\n");
	PrintList(Sum);
	ProductF(p1, p2, Product);
	printf("Produkt polinoma je:\n");
	PrintList(Product);
	

	return 0;
}


Position CreateNewElement(int koef, int pot)
{
	Position new = (Position)malloc(sizeof(Polinom));
	if (new == NULL)
	{
		printf("couldn't create a new element");
		return NULL;
	}
	new->koef = koef;
	new->pot = pot;
	//new->next = (Position)malloc(sizeof(Polinom));
	return new;
}

int ReadFromFile(char datoteka[MAX], Position p1, Position p2)
{
	FILE* fp = NULL;
	//fp = (FILE*)malloc(sizeof(FILE));
	fp = fopen("Polinom.txt", "r");
	if (!fp)
	{
		printf("Error in opening the file\n");
		return -1;
	}

	char buffer[MAX] = { 0 };
	int pot = 0;
	int koef = 0;
	int pomakPointera = 0;
	char* p = NULL;

	p = buffer;
	fgets(p, MAX, fp);
	if (strlen(p) == 0)p1->next = CreateNewElement(0, 0);
		//p1->next = NULL;
	else
	{
		do
		{
			if (sscanf(p, "%d %d %n", &koef, &pot, &pomakPointera) != 2)
			{
				printf("Wrong input in file!\n");
				return EXIT_FAILURE;
			}
			if (koef == 0)continue;
			Position new = CreateNewElement(koef, pot);
			SortList(p1, new);

			p = p + pomakPointera;
		} while (strlen(p) > 0);
	}

	pomakPointera = 0;
	fgets(p, MAX, fp);
	if (strlen(p) == 0)p2->next = CreateNewElement(0, 0); //p2->next = NULL;
	else
	{
		do
		{
			if (sscanf(p, "%d %d %n", &koef, &pot, &pomakPointera) != 2)
			{
				printf("Wrong input in file!\n");
				return EXIT_FAILURE;
			}
			if (koef == 0)continue;
			Position new = CreateNewElement(koef, pot);
			SortList(p2, new);

			p = p + pomakPointera;
		} while (strlen(p) > 0);
	}

	fclose(fp);

	return 1;
}

void SortList(Position p, Position new)
{
	Position temp = p->next;
	if (temp == NULL)
	{
		InsertAfter(p, new);
	}

	else
	{
		while (temp->next != NULL && temp->pot > new->pot)
		{
			temp = temp->next;
		}
		if (temp->pot <= new->pot)
		{
			if (temp->pot == new->pot)
			{ 
				temp->koef = temp->koef + new->koef;
				if (temp->koef == 0)Delete(p, temp);
			}
	
			else
			{
				Position before = FindBefore(p, temp);
				InsertAfter(before, new);
			}
		}
		else
		{
			InsertAfter(temp, new);
		}
	}
}

int InsertAfter(Position p, Position new)
{
	new->next = p->next;
	p->next = new;
	return EXIT_SUCCESS;
}

void PrintList(Position p)
{
	Position temp = p->next;
	while (temp != NULL)
	{
		printf("%d %d ", temp->koef, temp->pot);
		temp = temp->next;
	}
	printf("\n");
}

Position FindBefore(Position p, Position temp)
{
	Position p1 = p;
	while (p1->next != temp && p1->next != NULL)
	{
		p1 = p1->next;
	}
	if (p1->next == NULL)
	{
		printf("Error, element not found in the list\n");
		return NULL;
	}
	else return p1;
}

Position SumF(Position p1, Position p2, Position p3)
{
	Position temp1 = p1->next;
	Position temp2 = p2->next;
	Position temp3 = p3;
	Position new = NULL;

	while (temp1 != NULL && temp2 != NULL)
	{
		if (temp1->pot == temp2->pot)
		{
			if (temp1->koef + temp2->koef == 0)
			{
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else 
			{
				new = CreateNewElement(temp1->koef + temp2->koef, temp1->pot);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		else if (temp1->pot > temp2->pot)
		{
			new = CreateNewElement(temp1->koef, temp1->pot);
			temp1 = temp1->next;
		}
		else if (temp1->pot < temp2->pot)
		{
			new = CreateNewElement(temp2->koef, temp2->pot);
			temp2 = temp2->next;
		}
		InsertAfter(temp3, new);
		temp3 = temp3->next;
	}

	if (temp1 == NULL)
	{
		while (temp2 != NULL)
		{
			new = CreateNewElement(temp2->koef, temp2->pot);
			InsertAfter(temp3, new);
			temp3 = temp3->next;
			temp2 = temp2->next;
		}
	}

	if (temp2 == NULL)
	{
		while (temp1 != NULL)
		{
			new = CreateNewElement(temp1->koef, temp1->pot);
			InsertAfter(temp3, new);
			temp3 = temp3->next;
			temp1 = temp1->next;
		}
	}
	return p3;
}

int Delete(Position p, Position temp)
{
	Position before = FindBefore(p, temp);
	before->next = before->next->next;
	free(temp);
	return 0;
}

Position ProductF(Position p1, Position p2, Position p3)
{
	Position temp1 = p1->next;
	Position temp2 = p2->next;
	Position temp3 = p3;
	Position new = NULL;

	while (temp1 != NULL)
	{
		temp2 = p2->next;
		while (temp2 != NULL)
		{
			new = CreateNewElement(temp1->koef * temp2->koef, temp1->pot + temp2->pot);
			SortList(p3, new);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
	return p3;
}