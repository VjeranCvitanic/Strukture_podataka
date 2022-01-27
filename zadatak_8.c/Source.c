#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 1024

struct _Node;
typedef struct _Node* Position;
typedef struct _Node
{
	int number;
	Position left;
	Position right;
}Node;


struct _QueueElement;
typedef struct _QueueElement* QP;
typedef struct _QueueElement
{
	Position node;
	QP next;
}Q;

int InsertNewElement(Position head, int number);
Position CreateNewElement(int number);
Position Insert(Position head, Position new);
Position DeleteElement(Position head, int number);		
int FindElement(Position head, int number, Position* mem);
int FindLargest(Position head,Position* mem);
int PrintInOrder(Position current);
int PrintPreOrder(Position current);
int PrintPostOrder(Position current);
int PrintLevelOrder(Position current, QP head);


QP CreateNewQueueElement(Position element);
int Push(QP head, Position element);
QP FindLast(QP head);
int Pop(QP head, Position* destination);

int main()
{
	int num = 0;
	int flag = 0;
	int br = 0;
	Node head = { .number = 0, .left = NULL, .right = NULL };
	Position first = &head;
	Q qHead = { .node = NULL, .next = NULL };
	QP qpHead = &qHead;
	qpHead->next = CreateNewQueueElement(first);
	printf("Enter the value of the first element\n");
	scanf("%d", &num);
	head.number = num;
	Position temp = CreateNewElement(0);

	while (flag == 0)
	{
		printf("Enter:\n1 -> Insert new element\n2 -> Delete a element\n3 -> Find an element\n4 -> Print in order\n5 -> Print pre order\n6 -> Print post order\n7 -> Print level order\n8 -> Exit menu\n");
		scanf("%d", &br);
		switch (br)
		{
		case 1:
		{
			printf("Enter the value of a new element:\n");
			scanf("%d", &num);
			if (first == NULL)
				first = CreateNewElement(num);
			else InsertNewElement(first, num);
			break;
		}

		case 2:
		{
			printf("Enter the value you want to delete:\n");
			scanf("%d", &num);
			first = DeleteElement(first, num, &temp);
			break;
		}

		case 3:
		{
			printf("Enter the value you want to find:\n");
			scanf("%d", &num);
			if (FindElement(first, num, &temp) == EXIT_SUCCESS) printf("There is an element with number %d\n", num);
			else printf("There is no element with number %d\n", num);
			break;
		}

		case 4:
		{
			printf("\n");
			PrintInOrder(first);
			printf("\n");
			break;
		}

		case 5:
		{
			printf("\n");
			PrintPreOrder(first);
			printf("\n");
			break;
		}

		case 6:
		{
			printf("\n");
			PrintPostOrder(first);
			printf("\n");
			break;
		}

		case 7:
		{
			printf("\n");
			PrintLevelOrder(first, qpHead);
			printf("\n");
			qpHead->next = CreateNewQueueElement(first);
			break;
		}

		case 8:
		{
			flag = 1;
			break;
		}
		default:
		{
			printf("Wrong input, please try again!\n");
			break;
		}
		}
	}

	printf("You successfully exited the menu!\n");
	return 0;
}


Position CreateNewElement(int number)
{
	Position q = (Position)malloc(sizeof(Node));
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

int InsertNewElement(Position head, int number)
{
	Position new = NULL;
	new = CreateNewElement(number);
	if (!new)
	{
		return EXIT_FAILURE;
	}
	head = Insert(head, new);

	return EXIT_SUCCESS;
}

Position Insert(Position head, Position new)
{
	if (head)
	{
		if (head->number < new->number)
		{
			head->right = Insert(head->right, new);
		}
		else if (head->number > new->number)
		{
			head->left = Insert(head->left, new);
		}
		else if (head->number == new->number)
		{
			free(new);
			printf("An element with this number already exists!\n");
		}
		return head;
	}
	else return new;
}

int FindElement(Position head, int number, Position* mem)
{
	if (head)
	{
		if (head->number == number)*mem = head;
		else if (head->number > number)FindElement(head->left, number, mem);
		else FindElement(head->right, number, mem);
	}
	else
	{
		*mem = NULL;
		//printf("There is no element with the given number!\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

Position DeleteElement(Position head, int number)
{
	Position temp = CreateNewElement(0);

	if (head == NULL)
		return head;
	else if (head->number > number)
		head->left = DeleteElement(head->left, number);
	else if (head->number < number)
		head->right = DeleteElement(head->right, number);
	else if (head->number == number)
	{
		if (head->left != NULL && head->right != NULL)
		{
			FindLargest(head->left, &temp);
			head->number = temp->number;
			head->left = DeleteElement(head->left, temp->number);
		}

		else if (head->left == NULL)
		{
			return head->right;
		}

		else return head->left;
	}

	return head;
}

int FindLargest(Position head, Position* mem)
{
	if (head)
	{
		if (head->right == NULL)*mem = head;
		else FindLargest(head->right, mem);
	}

	else
	{
		*mem = NULL;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int PrintInOrder(Position current)
{
	if (current)
	{
		PrintInOrder(current->left);
		printf("%d ", current->number);
		PrintInOrder(current->right);

		return 0;
	}
		
	return 1;
}

int PrintPreOrder(Position current)
{
	if (current)
	{
		printf("%d ", current->number);
		PrintPreOrder(current->left);
		PrintPreOrder(current->right);

		return 0;
	}

	return 1;
}

int PrintPostOrder(Position current)
{
	if (current)
	{
		PrintPostOrder(current->left);
		PrintPostOrder(current->right);
		printf("%d ", current->number);

		return 0;
	}

	return 1;
}


int PrintLevelOrder(Position current, QP head)
{
	QP r = head;
	Position temp = CreateNewElement(0);
	while (r->next)
	{
		Pop(r, &temp);
		printf("%d", temp->number);
		Push(r, temp->left);
		Push(r, temp->right);
	}

	return 0;
}



QP CreateNewQueueElement(Position element)
{
	QP q = NULL;
	q = (QP)malloc(sizeof(Q));
	if (!q)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	q->node = element;
	q->next = NULL;

	return q;
}

int Push(QP head, Position element)
{
	QP last = NULL;
	if (element == NULL) return EXIT_FAILURE;
	QP q = CreateNewQueueElement(element);
	if (!q) return EXIT_FAILURE;
	last = FindLast(head);
	last->next = q;
	q->next = NULL;

	return EXIT_SUCCESS;
}

QP FindLast(QP head)
{
	if (!head)
		return NULL;

	QP temp = head->next;
	QP prev = head;
	while (temp)
	{
		temp = temp->next;
		prev = prev->next;
	}

	return prev;
}

int Pop(QP head, Position* destination)
{
	if (head->next)
	{
		*destination = head->next->node;
		head->next = head->next->next;
		return EXIT_SUCCESS;
	}
	else
	{
		printf("Queue is empty!\n");
		return 1;
	}
}


