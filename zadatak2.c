#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
} Person;

Position CreatePerson(char* name, char* surname, int birthYear);
int PreppendList(Position Head, char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
int PrintList(Position first);
Position FindLast(Position Head);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position first, Position target);
int DeleteAfter(Position beforeTarget);
int AppendList(Position first, char* name, char* surname, int birthYear);
int unosInta();

int main()
{
	Person Head = { .next = NULL,.name = {0},.surname = {0},.birthYear = 0 };
	Position p = &Head;
	char name, surname;
	char* ime = &name;
	char* prezime = &surname;
	int broj = 0;
	int godRodenja = 0;
	int flag = 1;
	char b;
	char* pb = NULL;
	pb = &b;
	while (flag)
	{
		printf("Izbornik:\n1->PreppendList\n2->AppendList\n3->PrintList\n4->FindBySurname\n5->Delete\n6->exit\n");
		broj = unosInta();
		switch (broj)
		{
		case 1:
		{
			printf("Unesi ime prezime i godinu rodjenja:\n");
			printf("Ime: ");
			scanf("%s",ime);
			printf("Prezime: ");
			scanf("%s", prezime);
			printf("Godina rodenja: ");
			godRodenja = unosInta();
			PreppendList(p, ime, prezime, godRodenja);
			break;
		}

		case 2:
		{
			printf("Unesi ime prezime i godinu rodjenja:\n");
			printf("Ime: ");
			scanf("%s", ime);
			printf("Prezime: ");
			scanf("%s", prezime);
			printf("Godina rodenja: ");
			godRodenja = unosInta();
			AppendList(p, ime, prezime, godRodenja);
			break;
		}
		case 3:
		{
			PrintList(p);
			break;
		}
		case 4:
		{
			printf("Unesi prezime koje zelis pronaci:\n");
			scanf("%s", pb);
			FindBySurname(p,pb);
			break;
		}
		case 5:
		{
			printf("Unesi prezime koje zelis izbrisati:\n");
			scanf("%s", pb);
			Position u = FindBySurname(p, pb);
		}
		case 6:
		{
			flag = 0;
			break;
		}
		default:
		{
			printf("Krivi unos, pokusaj ponovo!\n");
			break;
		}
		}
	}

	return 0;
}


Position
CreatePerson(char* name, char* surname, int birthYear)	//stvori novu osobu
{
	Position NewPerson = NULL;
	NewPerson = (Position)malloc(sizeof(Person));

	if (!NewPerson)
	{
		printf("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(NewPerson->name, name);
	strcpy(NewPerson->surname, surname);
	NewPerson->birthYear = birthYear;
	NewPerson->next = NULL;

	return NewPerson;
}

int
PreppendList(Position Head, char* name, char* surname, int birthYear)	//dodaje na pocetak
{
	Position NewPerson = NULL;
	NewPerson = CreatePerson(name, surname, birthYear);
	if (!NewPerson)
	{
		printf("Couldn't create a new person.\n");
		return 1;
	}

	InsertAfter(Head, NewPerson);
	return 0;
}

int
InsertAfter(Position position, Position newPerson)	//dodaj poslije
{
	newPerson->next = position->next;
	position->next = newPerson;
	return 0;
}

int
PrintList(Position first)	//ispisuje listu
{
	Position temp = first->next;
	printf("\n");
	while (temp)
	{
		printf("%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	printf("\n");
	return 0;
}

Position FindLast(Position Head)	//pronalazi zadnjeg
{
	Position temp = Head;
	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}

Position FindBySurname(Position first, char* surname)	//pronadi prezime
{
	Position temp;
	Position z = NULL;
	temp = first;
	int flag = 0;
	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			z = temp;
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	if (flag == 0)
	{
		printf("Krivi unos!\n");return NULL;
	}
	printf("Pronadena je osoba %s %s, %d\n", temp->name, temp->surname, temp->birthYear);
	//FindBefore(first, temp);
	return z;
}

Position FindBefore(Position first, Position target)	//pronadi prije
{
	Position temp = first;
	while (temp->next != target)
	{
		temp = temp->next;
	}
	/*printf("Zelis li brisati ovu osobu? Odgovori: da/ne\n");
	char a;
	char b = "da";
	scanf("%s", &a);
	if (strcmp(a, b) == 0)*/
	DeleteAfter(temp);
	return temp;
}

int
DeleteAfter(Position beforeTarget)	//brisi poslije
{
	Position a = beforeTarget->next;
	beforeTarget->next = a->next;
	free(a);

	return 0;
}

int
AppendList(Position first, char* name, char* surname, int birthYear)	//dodaj na kraj
{
	Position newPerson = NULL;
	Position last = NULL;
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
		return -1;
	last = FindLast(first);
	InsertAfter(last, newPerson);
	return 0;
}

int unosInta()
{
	char Unos[MAX_SIZE] = { 0 };
	int unos;
	int i = 0;
	int oznaka = 0;
	do
	{
		scanf("%s", Unos);
		for (i = 0; i < strlen(Unos); i++)
		{
			oznaka = 0;
			if (isdigit(Unos[i]) == 0) {
				oznaka = 1;
				printf("Krivi unos, unesi broj!\n");
				break;
			}
			i++;
		}
		
	} while (oznaka == 1);
	unos = atoi(Unos);
	return unos;
}