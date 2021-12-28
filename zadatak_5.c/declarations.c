#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Position CreateNewElement(double number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(stackElement));
	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;
	return newElement;
}     

int InsertAfter(Position first, Position new)      
{
	new->next = first->next;
	first->next = new;
	return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
	Position new = NULL;
	new = CreateNewElement(number);
	if (!new)
	{
		perror("Couldn't allocate memory!\n");
		return -1;
	}
	InsertAfter(head, new);
	return EXIT_SUCCESS;
}

//dodaje element na pocetak liste

int Pop(double* destination, Position head)
{
	Position first = head->next;
	if (!first)
	{
		perror("Postfix not valid! Please check the file!\n");
		return -1;
	}
	*destination = first->number;
	DeleteAfter(head);
	return EXIT_SUCCESS;
}

//izvlaci element s pocetka liste, sprema na destination i brise taj element iz liste

int DeleteAfter(Position first)
{
	Position temp = first->next;
	if (!temp)
	{
		return EXIT_SUCCESS;
	}
	first->next = temp->next;
	free(temp);
	return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
	while (head->next != NULL)
	{
		DeleteAfter(head);
	}

	return EXIT_SUCCESS;
}

int PerformOperation(char operation, Position head)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return -2;
	}
	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return -1;
	}
	switch (operation)
	{
	case '+':
	{
		result = operand1 + operand2;
		break;
	}
	case '*':
	{
		result = operand1 * operand2;
		break;
	}
	case '-':
	{
		result = operand1 - operand2;
		break;
	}
	case '/':
	{
		if (operand2 == 0)
		{
			perror("Can't divide with zero!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	}
	default:
	{
		printf("This operation is not available yet!\n");
		return -4;
	}
	}

	Push(head, result);
	return EXIT_SUCCESS;
}

//prima znak operacije i head element liste, pomocu Pop-a uzima prva dva elementa liste, vraca rezultat u listu pomocu Pusha

int CalculateFromFile(char* fileName, double* result)
{
	FILE* fp = NULL;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	char operation = 0;
	int fileLength = 0;
	int status = 0;
	double number = 0;
	int numBytes = 0;
	stackElement head = { .number = 0, .next = NULL };

	fp = fopen(fileName, "rb");  //otvara datoteku
	if (!fp)
	{
		perror("Couldn't open the file!\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);  //dolazi na kraj datoteke
	fileLength = ftell(fp);  // vraca udaljenost od pocetka datoteke

	buffer = (char*)calloc(fileLength + 1, sizeof(char)); //alociramo memoriju za buffer
	if (!buffer)
	{
		perror("Couldn't allocate memory!\n");
		return -2;
	}

	rewind(fp);   //vracamo se na pocetak
	fread(buffer, sizeof(char), fileLength, fp); //Podatke iz file-a, onoliko njih koliki je fileLength,  upisuje u buffer
	printf("|%s|\n", buffer);
	
	fclose(fp);  //zatvara file

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, "%lf %n", &number, &numBytes);
		if (status == 1)
		{
			status = Push(&head, number);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return -3;
			}
			currentBuffer += numBytes;
		}
		else
		{
			status = sscanf(currentBuffer, "%c %n", &operation, &numBytes);
			if (status == 1)
			{
				status = PerformOperation(operation, &head);
				if (status != EXIT_SUCCESS)  //ako nema s èime napraviti zadanu operaciju; ako je stog prazan
				{
					free(buffer);
					DeleteAll(&head);
					return -4;
				}
				currentBuffer += numBytes;
			}
			else
			{
				printf("Postfix not valid!\n");
				DeleteAll(&head);
				return -7;
			}
		}
	}
	free(buffer);

	status = Pop(result, &head);
	if (status != EXIT_SUCCESS)
	{
		DeleteAll(&head);
		return -5;
	}

	if (head.next)
	{
		printf("Postfix not valid! Please check your file!\n");
		DeleteAll(&head);
		return -6;
	}

	return EXIT_SUCCESS;
}

//cita file, na result sprema krajnji rezultat