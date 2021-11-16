#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <stdio.h>
#include <stdlib.h>

struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement
{
	int number;
	Position next;
}stackElement;

Position CreateNewElement(double number);
int Push(Position head, double number);
int InsertAfter(Position first, Position new);
int Pop(Position head);
int DeleteAfter(Position first);
int DeleteAll(Position head);
int PerformOperation(char operation, Position head);
int CalculateFromFile(char* fileName, double* result);

#endif // !