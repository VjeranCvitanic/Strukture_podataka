#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1024
#include "Tree.h"

int main()
{
	Node head = { .number = 0, .left = NULL, .right = NULL };
	Position first = &head;
	StackElement sHead = { .element = first, .next = NULL };
	StackP s = &sHead;
	int f = 1, br = 0, num = 0, t = 0, numa = 0;
	int* A = (int*)malloc(sizeof(int));
	Position q = NULL;
	char fileName[1024] = { 0 };

	printf("Welcome to the main menu!\n");
	while (f)
	{
		printf("Please, enter the number which represents the action you want to do:\n");
		printf("1 -> Insert new element\n2 -> Insert multiple new elements\n3 -> Insert elements of an array\n4 -> Insert elements of a random array\n5 -> Print out the list\n6 -> Replace the list (with the sums of children's numbers)\n7 -> Write in file\n8 -> exit\n");
		scanf("%d", &br);
		switch (br)
		{
		case 1:
		{
			if (t == 0)
			{
				printf("Enter the number of the first element in the list:\n");
				scanf("%d", &num);
				head.number = num;
				t = 1;
			}
			else
			{
				printf("Enter the number of the new element:\n");
				scanf("%d", &num);
				q = CreateNewElement(num);
				first = Insert(first, q);
			}
			break;
		}

		case 2:
		{
			printf("Press '-1' for halting input.\n");
			while (1)
			{
				if (t == 0)
				{
					printf("Enter the number of the first element in the list:\n");
					scanf("%d", &num);
					head.number = num;
					t = 1;
				}
				else
				{
					printf("Enter the number of the new element:\n");
					scanf("%d", &num);
					if (num == -1)break;
					q = CreateNewElement(num);
					first = Insert(first, q);
				}
			}

			break;
		}

		case 3:
		{
			printf("Enter the number of elements of the array:\n");
			scanf("%d", &numa);

			A = (int*)realloc(A, numa * sizeof(int));
			printf("Enter the elements of the array:\n");
			A = ArrayInput(A, numa);
			if (t == 0)
			{
				first->number = A[0];
				InsertArray(first, &A[1], numa - 1);
				t = 1;
			}

			else InsertArray(first, A, numa);

			break;
		}

		case 4:
		{
			printf("Enter the number of elements of the array:\n");
			scanf("%d", &numa);
			A = (int*)realloc(A, numa * sizeof(int));
			A = RandomArray(A, numa);

			if (t == 0)
			{
				first->number = A[0];
				InsertArray(first, &A[1], numa - 1);
				t = 1;
			}

			else InsertArray(first, A, numa);

			break;
		}

		case 5:
		{
			Print(first);
			break;
		}

		case 6:
		{
			Replace(first);
			break;
		}

		case 7:
		{
			WriteInFile(first, "Text.txt", s);
			break;
		}
		case 8:
		{
			f = 0;
			break;
		}

		default:
		{
			printf("Wrong input, please try again!\n");
			break;
		}
		}
	}

	printf("You successfully exited the main menu!\n");


	return 0;
}

