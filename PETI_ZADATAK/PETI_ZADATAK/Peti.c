#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define MAXSIZE 128
#define MAX_LINE 1024
typedef struct _Element* Position;
typedef struct _Element {
	double number;
	Position next;
} Element;

int ReadFile(Position head);
int Operation(char operator, Position head);
Position CreateElement(double number);
int DeleteFirst(Position head);
int Push(Position head, double tempNum);
double Pop(Position head);
int PrintPostfixResult(Position head);
int DeleteAll(Position head);

int main() {

	Element head = { .number = 0,.next = NULL };
	int status = 0;

	status = ReadFile(&head);

	if (status == EXIT_SUCCESS) {
		printf("\nPostfix izraz uspjesno izracunat!\n");
		DeleteAll(&head);
	}

	return EXIT_SUCCESS;
}

int ReadFile(Position head) {

	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char* currentBuffer = buffer;
	char fileName[MAXSIZE] = { 0 };
	char operator = '0';
	int n = 0, status = 0;
	double number = 0;

	printf("Unesite ime datoteke: ");
	scanf(" %s", fileName);

	fp = fopen(fileName, "r");

	if (!fp) {
		perror("Datoteka se ne moze otvoriti! Pokusajte ponovno!\n");
		return ERROR;
	}

	fgets(buffer, MAX_LINE, fp);
	while (strlen(currentBuffer) > 0) {
		if (sscanf(currentBuffer, " %lf %n", &number, &n) == 1) {
			status = Push(head, number);
			if (status != EXIT_SUCCESS) {
				return ERROR;
			}
		}

		else if (sscanf(currentBuffer, " %c %n", &operator, &n) == 1) {
			status = Operation(operator, head);
			if (status != EXIT_SUCCESS) {
				DeleteAll(head);
				return ERROR;
			}
		}

		currentBuffer += n;
	}
	fclose(fp);
	status = PrintPostfixResult(head); 
	if (status!=EXIT_SUCCESS) {
		DeleteAll(head);
		return ERROR;
	}
	printf(" \npostfix: %s\n", buffer);
	return EXIT_SUCCESS;
}

int Operation(char operator, Position head) {
	double num1 = 0;
	double num2 = 0;

	if (!head->next || !head->next->next) { 
		printf("Postfix izraz netocno napisan\n");
		return ERROR;
	}

	num1 = Pop(head);
	num2 = Pop(head);
	
	switch (operator) {
	case '+':
		Push(head, num2 + num1);
		break;
	case '-':
		Push(head, num2 - num1);
		break;
	case '*':
		Push(head, num2*num1);
		break;
	case '/':
		if (num1 == 0) {
			printf("Pokusaj dijeljenja s nulom! \n");
			return ERROR;
		}
		Push(head, num2 / num1);
		break;
	default: 
		printf("Ne podrzana matematicka operacija, provjeri zapis u datoteci!\n");
		return ERROR;
	}

	return EXIT_SUCCESS;
}

Position CreateElement(double number) { 
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Element));

	if (!newElement) {
		printf("Alokacija memorije neuspjesna!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int Push(Position head, double number) { 

	Position newElement = NULL;
	newElement = CreateElement(number);

	if (!newElement) {
		printf("Greska u izradi novog elementa!\n");
		return ERROR;
	}

	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}

int DeleteFirst(Position head) { 
	Position temp = NULL;

	temp = head->next;

	if (!temp) {
		printf("Lista je prazna!\n");
		return EXIT_SUCCESS;
	}

	head->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
	while (head->next != NULL) {
		DeleteFirst(head);
	}
	printf("\nCijeli stog je izbrisan!\n");
	return EXIT_SUCCESS;
}

double Pop(Position head) { 
	double toPop = 0;
	toPop = head->next->number;
	DeleteFirst(head);

	return toPop;
}

int PrintPostfixResult(Position head) { 

	if (!head->next || head->next->next) { 
		printf("Postfix izraz netocno napisan (ne balansirani broj brojeva i operatora)!!!\n");
		return ERROR;
	}
	printf("Rezultat postfixa je: %.2lf\n", head->next->number);

	return EXIT_SUCCESS;
}