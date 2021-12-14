#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024

struct _Directory;
typedef struct _Directory* Position;
typedef struct _Directory
{
	char name[MAX_LINE];
	Position sibling;
	Position child;
}Directory;


struct _StackElement;
typedef struct _StackElement* StackP;
typedef struct _StackElement
{
	Position dir;
	StackP next;
}StackElement;


Position CreateNewElement(char name[]); //md
Position Insert(Position current, Position newElement);
int List(Position parent); //dir
Position EnterDirectory(Position parent, char name[], StackP head); //cd dir
Position GoToParent(StackP head); //cd..
int DeleteDirAfter(Position del);
int DeleteDirAll(Position first);
int InsertAfter(Position first, Position new);



StackP CreateNewStackElement(Position dir);
int Push(StackP head, StackP newS);
int Pop(StackP head, Position* mem);
int DeleteStack(StackP head);



int SwitchCase(Position c, StackP head);

int main()
{
	Directory cHead = { .name = "C", .sibling = NULL, .child = NULL };

	Position c = &cHead;


	StackElement sHead = { .dir = c, .next = NULL };

	StackP s = &sHead;

	SwitchCase(c, s);

	printf("You successfully exited the menu!\n");
	return 0;
}




int SwitchCase(Position c, StackP head)
{
	Position currentDir = c;
	int flag = 0;
	int br = 0;
	char name[MAX_LINE] = { 0 };

	while (flag == 0)
	{
		printf("Enter the number which represents the action you want to do:\n1 -> make directory (md)\n2 -> print the contents of the directory (dir)\n3 -> enter the directory (cd dir)\n4 -> go to parent directory (cd..)\n5 -> exit\n\n");
		scanf("%d", &br);
		printf("\n");

		switch (br)
		{
		case 1:
		{
			printf("Enter name of the new directory:\n\n");
			//scanf_s("%s", name, MAX_LINE);
			printf("\n");
			scanf("%s", name);
			Position new = CreateNewElement(name);
			currentDir->child = Insert(currentDir->child, new);
			/*if (temp == new)
			{
				currentDir->child = new;
			}
			else
			{
				InsertAfter(temp, new);
			}*/
			break;
		}

		case 2:
		{

			printf("%s:", currentDir->name);
			List(currentDir);
			break;
		}

		case 3:
		{
			printf("Enter name of the directory that you want to enter:\n\n");
			printf("%s:", currentDir->name);
			scanf_s("%s", name, MAX_LINE);
			Position prev = currentDir;
			currentDir = EnterDirectory(currentDir, name, head);
			if (!currentDir)
			{
				currentDir = prev;
			}
			break;
		}

		case 4:
		{
			if (currentDir == c)
			{
				break;
			}
			currentDir = GoToParent(head);
			break;
		}

		case 5:
		{
			if (c->child)
			{
				DeleteDirAll(c->child);
			}
			DeleteStack(head);
			flag = 1;
			break;
		}

		default:
		{
			printf("Wrong input, please try again!\n\n");
			break;
		}
		}
	}

	return EXIT_SUCCESS;
}






int Push(StackP head, StackP newS)
{
	newS->next = head->next;
	head->next = newS;
	return 0;
}
int Pop(StackP head, Position* mem)
{
	if (head->next == NULL)
	{
		printf("Stack is empty!\n");
		return 1;
	}

	StackP temp = head->next;
	head->next = head->next->next;
	*mem = temp->dir;
	free(temp);
	return 0;
}
StackP CreateNewStackElement(Position dir)
{
	StackP q = (StackP)malloc(sizeof(StackElement));
	if (!q)
	{
		perror("Couldn't allocate memory\n");
		return NULL;
	}
	q->next = NULL;
	q->dir = dir;
	return q;
}
int DeleteStack(StackP head)
{
	Position mem = CreateNewElement("");
	while (head->next)
	{
		Pop(head, &mem);
	}

	return EXIT_SUCCESS;
}



Position CreateNewElement(char name[])
{
	Position q = (Position)malloc(sizeof(Directory));
	if (!q)
	{
		perror("Couldn't allocate memory\n");
		return NULL;
	}

	strcpy(q->name, name);
	q->sibling = NULL;
	q->child = NULL;
	return q;
}

Position Insert(Position current, Position newElement)
{
	if (!current)
	{
		return newElement;
	}
	else if (strcmp(current->name, newElement->name) < 0)
	{
		current->sibling = Insert(current->sibling, newElement);
	}
	else if (strcmp(current->name, newElement->name) == 0)
	{
		free(newElement);
		return current;
	}
	else
	{
		newElement->sibling = current;
		return newElement;
	}

	return current;
}

int List(Position parent)
{
	Position temp = parent->child;
	while (temp)
	{
		printf("%s\n", temp->name);
		temp = temp->sibling;
	}

	printf("\n");

	return 0;
}

Position EnterDirectory(Position parent, char name[], StackP head)
{
	Position temp = parent->child;
	StackP q = NULL;
	while (temp != NULL && strcmp(temp->name, name) != 0)
	{
		temp = temp->sibling;
	}

	if (temp == NULL)
	{
		printf("Directory not found!\n");
		return NULL;
	}
	q = CreateNewStackElement(parent);
	Push(head, q);

	return temp;
}

int DeleteDirAfter(Position del)
{
	Position temp = del->sibling;
	del->sibling = del->sibling->sibling;
	free(temp);
	return EXIT_SUCCESS;
}

int DeleteDirAll(Position first)
{
	if (!first)
		return 0;
	else if (first->sibling)
	{
		DeleteDirAll(first->sibling);
	}
	else if (first->child)
	{
		DeleteDirAll(first->child);
	}
	free(first);

	return 0;
}

int InsertAfter(Position first, Position new)
{
	new->sibling = first->sibling;
	first->sibling = new;
	return EXIT_SUCCESS;
}

Position GoToParent(StackP head)
{
	Position mem = CreateNewElement("");
	if (Pop(head, &mem))
		return head->dir;

	return mem;
}

