#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128

typedef struct _Directory* Position;
typedef struct _Stack* StackPosition;
typedef struct _Directory {
	char name[MAX_SIZE];
	Position sibling;		
	Position child;			
}Directory;

typedef struct _Stack {
	Position directory;
	StackPosition next;
} Stack;

int CMD(Position DirPos, StackPosition  StackPos); 
Position delete(Position current); 
Position InsertSort(Position p, Position q); 
Position CD(Position current, StackPosition stackHead, char* DirectoryName); 
int Push(StackPosition head, StackPosition newStackElement); 
Position Pop(StackPosition stackHead, Position current); 
int DIR(Position current); 
Position CreateDirectory(char* name); 
void PreOrderPrint(Position root, int dubina); 

int main()
{
	Directory C = { .name = "C:",.child = NULL,.sibling = NULL, };
	Stack stackHead = { .next = NULL,.directory = NULL };
	CMD(&C, &stackHead);
	return EXIT_SUCCESS;
}

Position InsertSort(Position current, Position newElement) {
	if (current == NULL) { 
		return newElement;
	}
	if (strcmp(current->name, newElement->name) > 0) { 
		newElement->sibling = current; 
		return newElement;
	}
	else if (strcmp(current->name, newElement->name) < 0) { 
		current->sibling = InsertSort(current->sibling, newElement); 
	}
	return current; 
}

Position delete(Position current) {
	if (current == NULL) { 
		return NULL;
	}
	delete(current->sibling);
	delete(current->child);
	free(current);
	return NULL;
}

int CMD(Position DirPos, StackPosition StackPos) {
	Position current = DirPos;
	char choice = 0;
	char directoryName[MAX_SIZE] = { 0 };
	printf("1- md \n2- cd \n3- cd.. \n4- dir \n5- Ispisi sve foldere i subfoldere\n6- Izbrisi sve foldere\n0- exit\n");
	do {
		printf("Choose your next action: ");
		scanf(" %c", &choice);
		switch (choice) {
		case '1': {
			printf("Enter the name of your new directory: ");
			scanf(" %s", directoryName);
			Position newDirectory = CreateDirectory(directoryName); 
			current->child = InsertSort(current->child, newDirectory); 
			break;
		}
		case '2': {
			printf("Enter the name of the directory you wish to move to: ");
			scanf(" %s", directoryName);
			current = CD(current, StackPos, directoryName); 
			break;
		}
		case '3': {
			current = Pop(StackPos, current); 
			break;
		}
		case '4': {
			printf(" /%s: \n", current->name); 
			DIR(current); 
			break;
		}
		case '0': {
			printf("kraj programa!");
			break;
		}
		case '5': {
			PreOrderPrint(DirPos, 0); 
			break;
		}
		case '6': {
			current->child = delete(DirPos->child); 
			break;
		}
		default: {
			printf("Wrong input,please follow the menu. \n");
			break;
		}
		}
	} while (choice != '0');
	current = delete(DirPos->child);
	return EXIT_SUCCESS;
}

Position CreateDirectory(char* name) { 
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Directory));
	if (!newElement) {
		printf("Error allocating the memory! \n");
		return NULL;
	}
	strcpy(newElement->name, name);
	newElement->sibling = NULL;
	newElement->child = NULL;
	return newElement;
}

StackPosition CreateStackElement(Position currentDir) { 
	StackPosition newElement = NULL;
	newElement = (StackPosition)malloc(sizeof(Stack));
	if (!newElement) {
		printf("Error allocating the memory! \n");
		return NULL;
	}
	newElement->directory = currentDir;
	newElement->next = NULL;
	return newElement;
}

int Push(StackPosition head, StackPosition newStackElement) { 
	newStackElement->next = head->next;
	head->next = newStackElement;
	return EXIT_SUCCESS;
}

Position CD(Position current, StackPosition stackHead, char* DirectoryName) { 
	Position temp = current->child; 
	while (temp && strcmp(temp->name, DirectoryName)) { 
		temp = temp->sibling;
	}
	if (temp == NULL) { 
		printf("Wrong input, no such subdirectory found!\n ");
		return current;
	}
	else { 
		StackPosition newStackElement = CreateStackElement(current);
		Push(stackHead, newStackElement);
		return temp;
	}
}
Position Pop(StackPosition head, Position current) { 
	StackPosition first = NULL;
	first = head->next;
	Position temp = NULL;
	if (!first) {
		printf("This Directory does not have a parent!\n");
		return current;
	}
	temp = first->directory; 
	head->next = first->next; 
	free(first); 
	return temp; 
}
int DIR(Position current) { 
	Position temp = current->child; 
	while (temp) {  
		printf(" -%s \n", temp->name);
		temp = temp->sibling;
	}
	return EXIT_SUCCESS;
}

void PreOrderPrint(Position root, int dubina) {
	if (root == NULL) {
		return;
	}
	for (int i = 0; i < dubina; i++) {
		printf(" ");
	}
	dubina++;
	printf("-%s\n", root->name);
	PreOrderPrint(root->child, dubina);
	if (root->sibling == NULL)dubina = 1; 
	else if (root->sibling != NULL)dubina = dubina - 1; 
	PreOrderPrint(root->sibling, dubina);
}