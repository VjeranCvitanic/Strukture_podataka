#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"
#define MAX_LINE 1024


Position CreateNewElement(int number)
{
	Position q = NULL;
	q = (Position)malloc(sizeof(Node));
	if (!q)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	q->number = number;
	q->left = NULL;
	q->right = NULL;

	return q;
}

Position Insert(Position current, Position new)
{
	if (!current)
	{
		return new;
	}

	else if (current->number > new->number)
	{
		current->right = Insert(current->right, new);
	}

	else
	{
		current->left = Insert(current->left, new);
	}

	return current;
}

int Print(Position first)
{
	if (!first)
	{
		return 0;
	}
	
	Print(first->right);
	printf("%d ", first->number);
	Print(first->left);

	return EXIT_SUCCESS;
}

int Replace(Position first)
{
	int temp = 0;
	if (first->left == NULL && first->right == NULL)
	{
		temp = first->number;
		first->number = 0;
		return temp;
	}
	
	else if (first->left == NULL)
	{
		temp = first->number;
		first->number = Replace(first->right);
		return first->number + temp;
	}

	else if (first->right == NULL)
	{
		temp = first->number;
		first->number = Replace(first->left);
		return first->number + temp;
	}

	else
	{
		temp = first->number;
		first->number = Replace(first->left) + Replace(first->right);
		return first->number + temp;
	}
}



StackP CreateNewStackElement(Position new)
{
	StackP q = NULL;
	q = (StackP)malloc(sizeof(StackElement));
	if (!q)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	q->element = new;
	q->next = NULL;

	return q;
}

int Push(StackP head, Position new)
{
	StackP q = CreateNewStackElement(new);
	if (!q)
	{
		return EXIT_FAILURE;
	}

	q->next = head->next;
	head->next = q;

	return EXIT_SUCCESS;
}



int* ArrayInput(int* A, int numa)
{
	int i = 0;
	int br = 0;
	for (i = 0;i < numa; i++)
	{
		scanf("%d", &br);
		A[i] = br;
	}

	return A;
}

int InsertArray(Position first, int* A, int numa)
{
	int i = 0;
	for (i = 0; i < numa; i++)
	{
		Position new = CreateNewElement(A[i]);
		Insert(first, new);
	}

	return EXIT_SUCCESS;
}

int* RandomArray(int* A, int num)
{
	time_t t;
	srand((unsigned) time(&t));
	int i = 0;
	for (i = 0; i < num; i++)
	{
		A[i] = 11 + rand() % 79;
	}

	return A;
}

int WriteInFile(Position first, char fileName[MAX_LINE], StackP head)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "w");
	Position q = CreateNewElement(0);

	AddToStack(head, first);

	fprintf(fp, "Initial tree:\n");

	while (head->next)
	{
		if (!Pop(head, &q))
		{
			fprintf(fp, "%d ", q->number);
		}
	}

	fprintf(fp, "\nAfter Replace function:\n");

	Replace(first);
	AddToStack(head, first);

	while (head->next)
	{
		if (!Pop(head, &q))
		{
			fprintf(fp, "%d ", q->number);
		}
	}

	return 0;
}

int AddToStack(StackP head, Position first)
{
	if (!first)
		return -1;

	AddToStack(head, first->right);
	AddToStack(head, first->left);
	Push(head, first);

	return 0;
}

int Pop(StackP head, Position* q)
{
	StackP temp = NULL;
	if (head->next)
	{
		*q = head->next->element;
		temp = head->next;
		head->next = head->next->next;
		free(temp);

		return EXIT_SUCCESS;
	}

	else
	{
		printf("Stack is empty!\n");
		return EXIT_FAILURE;
	}
}
