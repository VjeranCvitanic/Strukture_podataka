#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 100

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_LINE];
	char surname[MAX_LINE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position p, Position p2, char* name, char* surname, int birthYear); //dodaje na kraj liste
Position CreatePerson(char* name, char* surname, int birthYear);					//kreira novu osobu
void PrintList(Position p);															//ispisuje listu
int AppendList(Position p, Position p2, char* name, char* surname, int birthYear);	//dodaje na pocetak liste
void insertAfter(Position one, Position toBeInserted);								//dodaje nakon
Position FindLast(Position p);														//pronalazi zadnjeg
Position FindBySurname(Position p, char* surname);									//pronalazi po prezimenu
Position FindBefore(Position p, Position target);									//pronalazi prije trazene osobe, po prezimenu
Position FindBefore2(Position p2, Position target);									//pronalazi prije trazene osobe, po prezimenu, u sortiranoj listi
int DeleteAfter(Position one);														//brise osobu nakon
int AlphabeticalOrder(Position p, Position newPerson);								//sortira unos liste						 
int Write(Position p, char* title);													//pise listu u datoteku
int Read(Position p, Position p2, char* title);										//cita listu iz datoteke
void DeleteList(Position p);														//brise listu iz memorije					
/*void transferP(Position p1, Position p2);	*/										//kopira listu 

int main()
{
	Person Head = { .name = " ", .surname = " ", .birthYear = 0, .next = NULL };
	Person Head2 = { .name = " ", .surname = " ", .birthYear = 0, .next = NULL };
	Person Head3 = { .name = " ", .surname = " ", .birthYear = 0, .next = NULL };
	Person Head4 = { .name = " ", .surname = " ", .birthYear = 0, .next = NULL };
	Position p = NULL;
	Position p2 = NULL;
	Position p3 = NULL;
	Position p4 = NULL;
	Position newPerson;
	Position wantedSurname;
	Position wantedSurname2;
	Position before;
	Position before2;
	p = &Head;
	p2 = &Head2;
	p3 = &Head3;
	p4 = &Head4;
	char name[MAX_LINE] = { 0 };
	char surname[MAX_LINE] = { 0 };
	int birthyear;
	char simbol[MAX_LINE] = { 0 };
	char title[MAX_LINE] = { 0 };
	int br = 0;
	int flag = 0;
	int flag2 = 0;

	while (flag == 0)
	{
		flag2 = 0;
		printf("Menu:\nInput 1 for adding a person at the start\nInput 2 for adding a person at the end of the list\nInput 3 for printing the list\nInput 4 for finding a person by his/her surname\nInput 5 for deleting a person\nInput 6 for inserting afer someone\nInput 7 for inserting before someone\nInput 8 for writing the list in a file\nInput 9 for reading the list from a file\nInput 10 for deleting a list\nInput 11 for exiting\n");
		scanf("%d", &br);
		switch (br)
		{
		case 1:
		{
			printf("Enter name, surname and birthyear:\n");
			scanf("%s %s %d", name, surname, &birthyear);
			PrependList(p, p2, name, surname, birthyear);
			break;
		}

		case 2:
		{
			printf("Enter name, surname and birthyear:\n");
			scanf("%s %s %d", name, surname, &birthyear);
			AppendList(p, p2, name, surname, birthyear);
			break;
		}

		case 3:
		{
			printf("Pick p1(main list) or p2(alphabetical order) or p3(read from file) or p4(alphabetically sorted from file)\n");
			scanf("%s", simbol);
			if (strcmp(simbol, "p1") == 0)
			{
				printf("\n");
				PrintList(p);
				printf("\n");
			}

			else if (strcmp(simbol, "p2") == 0)
			{
				printf("\n");
				PrintList(p2);
				printf("\n");
			}

			else if (strcmp(simbol, "p3") == 0)
			{
				printf("\n");
				PrintList(p3);
				printf("\n");
			}

			else if(strcmp(simbol,"p4") == 0)
			{
				printf("\n");
				PrintList(p4);
				printf("\n");
			}

			else printf("Wrong input!\n");
			break;
		}

		case 4:
		{
			printf("Enter the surname:\n");
			scanf("%s", surname);
			wantedSurname = FindBySurname(p, surname);
			if (!wantedSurname)break;
			printf("The person is %s %s, born in %d.\n", wantedSurname->name, wantedSurname->surname, wantedSurname->birthYear);
			break;
		}

		case 5:
		{
			printf("Enter the surname:\n");
			scanf("%s", surname);
			wantedSurname = FindBySurname(p, surname);
			wantedSurname2 = FindBySurname(p2, surname);
			if (!wantedSurname)printf("There is no person with that last name in the list.\n");
			else {
				before = FindBefore(p, wantedSurname);
				before2 = FindBefore2(p2, wantedSurname2);
				DeleteAfter(before);
				DeleteAfter(before2);
			}
			break;
		}

		case 6:
		{
			printf("Enter name, surname and birthyear:\n");
			scanf("%s %s %d", name, surname, &birthyear);
			newPerson = CreatePerson(name, surname, birthyear);
			printf("Enter the surname:\n");
			scanf("%s", surname);
			wantedSurname = FindBySurname(p, surname);
			if (wantedSurname == NULL)printf("There is no person with that last name in the list.\n");
			else
			{
				insertAfter(wantedSurname, newPerson);
				AlphabeticalOrder(p2, newPerson);
			}
			break;
		}

		case 7:
		{
			printf("Enter name, surname and birthyear:\n");
			scanf("%s %s %d", name, surname, &birthyear);
			newPerson = CreatePerson(name, surname, birthyear);
			printf("Enter the surname:\n");
			scanf("%s", surname);
			wantedSurname = FindBySurname(p, surname);
			if (!wantedSurname)
			{
				printf("There is no person with that last name in the list.\n");
			}
			else
			{
				before = FindBefore(p, wantedSurname);
				insertAfter(before, newPerson);
				AlphabeticalOrder(p2, newPerson);
			}
			break;
		}

		case 8:
		{
			int br2 = 0;
			printf("Enter the name of the file:\n");
			scanf("%s", title);
			printf("Choose which list to write in file:\n1->user input\n2->sorted list\n");
			scanf("%d", &br2);
			if (br2 == 1)Write(p, title);
			else if (br2 == 2)Write(p2, title);
			else printf("Wrong input!\n");
			break;
		}

		case 9:
		{
			printf("Enter the name of the file:\n");
			scanf("%s", title);
			Read(p3, p4, title);
			break;
		}

		case 10:
		{
			printf("Pick p1(main list) or p2(alphabetical order) or p3(read from file) or p4(alphabetically sorted from file)\n");
			scanf("%s", simbol);
			if (strcmp(simbol, "p1") == 0)
			{
				printf("\n");
				DeleteList(p);
				printf("\n");
			}

			else if (strcmp(simbol, "p2") == 0)
			{
				printf("\n");
				DeleteList(p2);
				printf("\n");
			}

			else if (strcmp(simbol, "p3") == 0)
			{
				printf("\n");
				DeleteList(p3);
				printf("\n");
			}

			else if (strcmp(simbol, "p4") == 0)
			{
				printf("\n");
				DeleteList(p4);
				printf("\n");
			}

			else printf("Wrong input!\n");
			break;
		}

		case 11:
		{
			flag = 1;
			break;
		}

		default:
		{
			printf("Wrong input!\n");
			break;
		}
		}
		printf("\n");
	}

	return 0;
}


Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		printf("Can't allocate memory!\n");
		return NULL;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;
	return newPerson;
}

int PrependList(Position p, Position p2, char* name, char* surname, int birthYear)
{
	Position NewPerson = CreatePerson(name, surname, birthYear);
	if (!NewPerson)
	{
		printf("Couldn't create a new person!\n");
		return EXIT_FAILURE;
	}
	insertAfter(p, NewPerson);
	AlphabeticalOrder(p2, NewPerson);
	return EXIT_SUCCESS;
}

void PrintList(Position p)
{
	Position temp = p->next;
	while (temp)
	{
		printf("%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
}

int AppendList(Position p, Position p2, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position temp = p;
	newPerson = (Position)malloc(sizeof(Position));
	if (!newPerson)
	{
		printf("Couldn't create a new person!\n");
		return EXIT_FAILURE;
	}
	newPerson = CreatePerson(name, surname, birthYear);
	while (temp->next)
	{
		temp = temp->next;
	}
	Position last = FindLast(temp);
	insertAfter(last, newPerson);
	AlphabeticalOrder(p2, newPerson);
	return EXIT_SUCCESS;
}

void insertAfter(Position one, Position toBeInserted)
{
	if (!one);
	else
	{
		toBeInserted->next = one->next;
		one->next = toBeInserted;
	}
}

Position FindLast(Position p)
{
	Position last = NULL;
	while (p->next)
	{
		p = p->next;
	}
	last = p;
	return last;
}

Position FindBySurname(Position p, char* surname)
{
	Position temp = p->next;
	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	printf("There is no person with that last name in the list.\n");
	return NULL;
}

Position FindBefore(Position p, Position target)
{
	Position temp = p;
	while ((temp->next) != target)
	{
		temp = temp->next;
	}
	return temp;
}

Position FindBefore2(Position p2, Position target)
{
	Position temp = p2;
	while ((temp->next) != target)
	{
		temp = temp->next;
	}
	return temp;
}
int DeleteAfter(Position one)
{
	if (!one)return -1;
	Position a = one->next;
	one->next = one->next->next;
	free(a);
	return EXIT_SUCCESS;
}

int AlphabeticalOrder(Position p2, Position newPerson)
{
	Position newPerson2 = CreatePerson(newPerson->name, newPerson->surname, newPerson->birthYear);
	Position temp = p2;
	if (temp->next == NULL)
	{
		insertAfter(p2, newPerson2);
	}
	else
	{
		while (temp->next != NULL)
		{
			if (strcmp(temp->next->surname, newPerson2->surname) > 0)
			{
				insertAfter(temp, newPerson2);
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		if (temp->next == NULL)
		{
			insertAfter(temp, newPerson2);
		}
	}
	return 0;
}

int Write(Position p, char* title)
{
	Position temp = p->next;
	FILE* fp;
	fp = fopen(title, "w");
	while (temp)
	{
		fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int Read(Position p, Position p2, char* title)
{
	char name[MAX_LINE];
	char surname[MAX_LINE];
	int dob;
	Position last = NULL;
	Position temp = p;
	Position newPerson = NULL;
	FILE* fp;
	fp = fopen(title, "r");
	if (fp == NULL)return -1;
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d\n", name, surname, &dob);
		newPerson = CreatePerson(name, surname, dob);
		last = FindLast(p);
		insertAfter(last, newPerson);
		AlphabeticalOrder(p2, newPerson);
	}
	PrintList(p);
	fclose(fp);
	return EXIT_SUCCESS;
}

void DeleteList(Position p)
{
	Position temp;
	temp = p->next;
	p->next = p->next->next;
	free(temp);
}

/*void transferP(Position p1, Position p2)
{
	Position temp = p2;
	p2 = p1;
	DeleteList(temp);

}*/
