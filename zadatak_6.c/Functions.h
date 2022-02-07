#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_NAME 100

typedef struct _Date
{
	int day;
	int month;
	int year;
}Date;

struct _Article;
typedef struct _Article* ArticlePosition;
typedef struct _Article
{
	char name[MAX_NAME];
	int quantity;
	float price;
	ArticlePosition next;

}Article;

struct _Bill;
typedef struct _Bill* Position;
typedef struct _Bill
{
	Date date;
	ArticlePosition headArticle;
	Position next;

}Bill;


Position CreateNewBill(int day, int month, int year);

ArticlePosition CreateNewArticle(char name[MAX_NAME], int quantity, float price);

int ReadFromFile(char fileName[MAX_NAME], Position first, char* destination);

int ReadFromSecondFile(char fileName2[MAX_NAME], Position first);

int InsertBill(Position first, Position q);

int IsOlder(Date date1, Date date2);

int InsertArticle(Position bill, ArticlePosition q);

int Cost(Position first, char articleName[MAX_NAME], Date d1, Date d2, int* quantity, float* price);
#endif

