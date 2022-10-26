#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int AddToStart(Position head);
int AddToEnd(Position head);
int PrintList(Position first);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
Position FindPerson(Position first, char* surname);
Position FindBefore(Position first, Position target);
int DeleteAfter(Position head, char* surname);
int DeleteAll(Position head);
Position CreatePerson();

int main(int argc, char** argv)
{
	Person head = { .next = NULL,.name = { 0 },.surname = { 0 },.birthYear = 0 };
	Position p = &head;
	Position find = NULL;
	char unos;
	int temp = 1;
	char surname[MAX_SIZE] = { 0 };

	while (temp)
	{
		printf("1- Dodaj novi el. na pocetak:\n"
			"2- Ispisi listu \n3- Dodaj el na kraj liste \n"
			"4- Pronadi po prezimenu\n5- Brisi elem\n"
			"6- Izbrisi sve elemente iz liste\n"
			"0- Izlaz iz programa\n");
		scanf(" %c", &unos);
		switch (unos) {
		case '1':
			AddToStart(p);
			break;
		case '2':
			PrintList(p->next);
			break;
		case '3':
			AddToEnd(p);
			break;
		case '4':
			printf("Unesite prezime: ");
			scanf(" %s", surname);
			find = FindPerson(p->next, surname);
			if (find == 0) printf("Trazena osoba nije pronadena\n");
			else printf("Ime: %s \nPrezime %s \nGodina Rodenja: %d \n\n",
				find->name, find->surname, find->birthYear);
			break;
		case '5':
			printf("Prezime elem. koji zelite uklonit: ");
			scanf("%s", surname);
			DeleteAfter(p, surname);
			break;
		case '6':
			printf("Svi elementi su obrisani!\n");
			DeleteAll(p);
			break;
		case '0':
			printf("Kraj programa\n");
			temp = 0;
			break;
		default:
			printf("Krivi unos!\n");
			break;
		}
	}
	return EXIT_SUCCESS;
}

int AddToStart(Position head) {
	Position newPerson = NULL;
	newPerson = CreatePerson();
	if (!newPerson)
	{
		return -1;
	}
	InsertAfter(head, newPerson);
	return EXIT_SUCCESS;
}
Position CreatePerson() {
	Position newPerson = NULL;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear;

	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson)
	{
		perror("Can't allocate memory! \n");
		return NULL;
	}
	printf("Ime: ");
	scanf("%s", name);
	printf("Prezime: ");
	scanf("%s", surname);
	printf("Godina rodenja: ");
	scanf("%d", &birthYear);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}
int AddToEnd(Position head) {
	Position newPerson = NULL;
	Position last = NULL;
	newPerson = CreatePerson();
	if (!newPerson)
	{
		return -1;
	}
	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	if (first == NULL) {
		printf("Lista je prazna!\n");
	}
	while (first)
	{
		printf("Name: %s, surname= %s, birth year: %d\n", first->name, first->surname, first->birthYear);
		first = first->next;
	}
	return EXIT_SUCCESS;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;
	return EXIT_SUCCESS;
}

Position FindLast(Position p)
{
	while (p->next)
	{
		p = p->next;
	}
	return p;
}

Position FindPerson(Position first, char* surname)
{
	while (first)
	{
		if (strcmp(first->surname, surname) == 0)
		{
			return first;
		}
		first = first->next;
	}
	return NULL;
}

Position FindBefore(Position first, Position target)
{
	while (first->next != target) {
		first = first->next;
	}
	return first;
}
int DeleteAfter(Position head, char* surname)
{
	Position find = NULL;
	Position before = NULL;
	find = FindPerson(head->next, surname);
	if (find == NULL) {
		printf("Nema te osobe !\n");
		return 0;
	}
	before = FindBefore(head, find);
	before->next = find->next;

	free(find);

	return EXIT_SUCCESS;
}
int DeleteAll(Position head) {
	Position temp;
	while (head->next != NULL) {
		temp = head->next;
		head->next = head->next->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}