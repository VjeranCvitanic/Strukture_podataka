#ifndef TREE_H
#define TREE_H
#define MAX_LINE 1024
struct _Node;
typedef struct _Node* Position;
typedef struct _Node
{
	int number;
	Position left;
	Position right;
}Node;

struct _StackElement;
typedef struct _StackElement* StackP;
typedef struct _StackElement
{
	Position element;
	StackP next;
}StackElement;


Position CreateNewElement(int number);
Position Insert(Position current, Position new);
int Print(Position first);
int Replace(Position first); 

StackP CreateNewStackElement(Position new);
int Push(StackP head, Position new);
int Pop(StackP head, Position* q);
int AddToStack(StackP head, Position first);

int* ArrayInput(int* A, int numa);
int InsertArray(Position first, int* A, int numa);
int* RandomArray(int* A, int num);

int WriteInFile(Position first, char fileName[MAX_LINE], StackP head);



#endif 