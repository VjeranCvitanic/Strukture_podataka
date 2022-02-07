#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

Position CreateNewBill(int day, int month, int year)
{
	Position q = NULL;
	q = (Position)malloc(sizeof(Bill));
	if (!q)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	q->date.day = day;
	q->date.month = month;
	q->date.year = year;
	q->headArticle = CreateNewArticle("", 0, 0);
	q->next = NULL;

	return q;
};

ArticlePosition CreateNewArticle(char name[MAX_NAME], int quantity, float price)
{
	ArticlePosition q = NULL;
	q = (ArticlePosition)malloc(sizeof(Article));
	if (!q)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	q->next = NULL;
	q->price = price;
	q->quantity = quantity;
	strcpy(q->name, name);

	return q;
}

int ReadFromFile(char fileName[MAX_NAME], Position first, char* destination)
{
	FILE* fp = fopen(fileName, "r");
	if (!fp)
	{
		perror("Couldn't open the file\n");
		return EXIT_FAILURE;
	}

	char buffer[MAX_LINE] = { 0 };
	char fileName2[MAX_NAME] = { 0 };

	//fread(buffer, sizeof(char[MAX_LINE]), 1, fp);

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);
		if (sscanf(buffer, "%s\n", fileName2) == 1);
		strncat(destination, " ");
		strncat(destination, fileName2);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int ReadFromSecondFile(char fileName2[MAX_NAME], Position first)
{
	FILE* fp = fopen(fileName2, "r");
	if (!fp)
	{
		perror("Couldn't open the file!\n");
		return EXIT_FAILURE;
	}

	char buffer[MAX_LINE] = { 0 };
	int year = 0, month = 0, day = 0;
	int quantity = 0;
	char name[MAX_NAME] = { 0 };
	float price = 0.0;
	Position q = NULL;

	fgets(buffer, MAX_LINE, fp);

	if (sscanf(buffer, "%d-%d-%d\n", &year, &month, &day) == 3)
	{
		q = CreateNewBill(day, month, year);

		while (!feof(fp))
		{
			fgets(buffer, MAX_LINE, fp);
			if (sscanf(buffer, "%s %d %f\n", name, &quantity, &price) == 3)
			{
				ArticlePosition newArticle = CreateNewArticle(name, quantity, price);
				InsertArticle(q, newArticle);
			}
		}
		InsertBill(first, q);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int InsertBill(Position first, Position q)
{
	Position temp = first;

	while (temp->next != NULL && IsOlder(temp->next->date, q->date) == 1)
		temp = temp->next;

	q->next = temp->next;
	temp->next = q;

	return EXIT_SUCCESS;
}

int IsOlder(Date date1, Date date2)
{
	if (date1.year * 10000 + date1.month * 100 + date1.day > date2.year * 10000 + date2.month * 100 + date2.day)
		return -1;
	else if (date1.year * 10000 + date1.month * 100 + date1.day < date2.year * 10000 + date2.month * 100 + date2.day)
	{
		return 1;
	}

	else return 0;
}

int InsertArticle(Position bill, ArticlePosition q)
{
	ArticlePosition temp = bill->headArticle;
	while (temp->next && strcmp(temp->next->name, q->name) > 0)
		temp = temp->next;

	q->next = temp->next;
	temp->next = q;

	return EXIT_SUCCESS;
}

int Cost(Position first, char articleName[MAX_NAME], Date d1, Date d2, int* quantity, float* price)
{
	Position temp = first->next;
	while (temp)
	{
		if (IsOlder(d1, temp->date) != -1 && IsOlder(d2, temp->date) == -1)
		{
			ArticlePosition articleTemp = temp->headArticle->next;
			while (articleTemp)
			{
				if (strcmp(articleTemp, articleName) == 0)
				{
					*price += articleTemp->price;
					*quantity += articleTemp->quantity;
				}

				articleTemp = articleTemp->next;
			}
		}

		temp = temp->next;
	}

	return EXIT_SUCCESS;
}