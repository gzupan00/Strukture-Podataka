#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024
#define MAX_SIZE 128
struct _polinom;
typedef struct _polinom* position;
typedef struct _polinom
{
	int coeff;
	int expo;
	position next;
}polinom;

int readFile(char* file, position head1, position head2);
int findPairs(char* buffer, position head);
position createNew(int expo, int koef, position head);
int sortedInput(position head, position new);
int insertAfter(position after, position new);
int add(position head1, position head2, position headSum);
int multiply(position head1, position head2, position headMultiply);
int merge(position after, position new);
int DeleteAfter(position element);
int freeMemory(position head);
int printPoly(position first);


int main()
{
	polinom head1 = { .coeff = 0,.expo = 0,.next = NULL };
	polinom head2 = { .coeff = 0,.expo = 0,.next = NULL };
	polinom headSum = { .coeff = 0,.expo = 0,.next = NULL };
	polinom headMultiply = { .coeff = 0,.expo = 0,.next = NULL };
	char datoteka[MAX_SIZE] = { 0 };

	printf("Unesite ime datoteke: ");
	scanf(" %s", datoteka);

	readFile(datoteka, &head1, &head2);
	add(&head1, &head2, &headSum);
	multiply(&head1, &head2, &headMultiply);

	printPoly(head1.next);
	printf("\n-----------\n");
	printPoly(head2.next);

	printf("\nKonacna suma:\n");
	printPoly(headSum.next);

	printf("\nKonacan umnozak:\n");
	printPoly(headMultiply.next);

	freeMemory(&head1);
	freeMemory(&head2);
	freeMemory(&headSum);
	freeMemory(&headMultiply);

	return 0;
}

int readFile(char* file, position head1, position head2)
{
	FILE* fp = fopen(file, "r");
	char buffer[MAX_LINE] = { 0 };
	int status = 0;

	if (!fp)
	{
		perror("Neuspijelo otvaranje datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, fp);
	status = findPairs(buffer, head1);
	if (status != 0)
	{
		printf("Krivi unos podataka u datoteci! \n");
		return -1;
	}

	fgets(buffer, MAX_LINE, fp);

	status = findPairs(buffer, head2);
	if (status)
	{
		return -1;
	}

	fclose(fp);
	return 0;
}
int findPairs(char* buffer, position head)
{
	int status = 0, expo = 0, koef = 0, n = 0;
	position new = NULL;
	char* currentBuffer = buffer;
	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %d %d %n", &koef, &expo, &n);
		if (status != 2)
		{
			return -1;
		}

		new = createNew(expo, koef, head);
		if (!new)
		{
			return -1;
		}

		currentBuffer += n;
	}
	return 0;
}
position createNew(int expo, int koef, position head)
{
	position newElement = NULL;
	newElement = (position)malloc(sizeof(polinom));

	if (!newElement)
	{
		perror("Alokacija memorije nije uspijela!\n");
		return NULL;
	}

	newElement->expo = expo;
	newElement->coeff = koef;

	sortedInput(head, newElement);
	return newElement;
}
int sortedInput(position head, position new)
{
	position temp = head;
	while (temp->next != NULL && (temp->next->expo) > (new->expo))
	{
		temp = temp->next;
	}

	merge(temp, new);

	return 0;
}
int insertAfter(position after, position new)
{
	new->next = after->next;
	after->next = new;

	return 0;
}
int add(position head1, position head2, position headSum)
{
	position first = head1->next;
	position second = head2->next;
	position result = headSum;
	position temp = NULL;
	position new = NULL;

	while (first != NULL && second != NULL)
	{
		if (first->expo == second->expo)
		{
			if (first->coeff + second->coeff != 0) {
				new = createNew(first->expo, first->coeff + second->coeff, result);
				if (!new)
				{
					return -1;
				}
			}
			first = first->next;
			second = second->next;
		}
		else if (first->expo > second->expo)
		{
			new = createNew(first->expo, first->coeff, result);
			if (!new) {
				return -1;
			}
			first = first->next;
		}
		else
		{
			new = createNew(second->expo, second->coeff, result);
			if (!new) {
				return -1;
			}
			second = second->next;
		}
	}

	if (first == NULL)
	{
		temp = second;
	}

	if (second == NULL)
	{
		temp = first;
	}

	while (temp != NULL)
	{
		new = createNew(temp->expo, temp->coeff, result);
		if (!new) {
			return -1;
		}
		temp = temp->next;
	}

	return 0;
}

int multiply(position head1, position head2, position headMultiply)
{
	position first = NULL;
	position second = NULL;
	position result = headMultiply;

	for (first = head1->next; first != NULL; first = first->next)
	{
		for (second = head2->next; second != NULL; second = second->next)
		{
			position new = createNew(first->expo + second->expo, first->coeff * second->coeff, result);
			if (!new)
			{
				return -1;
			}
		}
	}
	return 0;
}

int merge(position after, position new)
{
	if (after->next == NULL || after->next->expo != new->expo)
	{
		insertAfter(after, new);
	}
	else
	{
		int koef = after->next->coeff + new->coeff;
		if (koef == 0)
		{
			DeleteAfter(after);
		}
		else
		{
			after->next->coeff = koef;
		}
		free(new);
	}
	return 0;
}

int DeleteAfter(position element)
{
	position toDelete = element->next;
	element->next = toDelete->next;
	free(toDelete);

	return 0;
}
int freeMemory(position head)
{
	position temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 0;
}

int printPoly(position first)
{
	position temp = first;
	printf("f(x) = ");
	while (temp != NULL)
	{
		printf("%dx^(%d)", temp->coeff, temp->expo);
		if (temp->next != NULL && temp->next->coeff > 0) printf("+");

		temp = temp->next;
	}
	return 0;
}