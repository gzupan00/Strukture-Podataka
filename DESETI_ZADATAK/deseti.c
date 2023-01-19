#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (50)


typedef struct _country* positionCountry;
typedef struct _city* positionCity;

typedef struct _country
{
	char nameCountry[MAX_SIZE];
	char belongingFile[MAX_SIZE];
	
	positionCountry nextCountry;
	positionCity nextCity;

}country;


typedef struct _city
{
	char nameCity[MAX_SIZE];
	int people;

	positionCity right;
	positionCity left;

}city;

int menu();
int readFile(positionCountry headCountry);
int createNewElementCountry(char* countryName, char* newFile, positionCountry headCountry);
int deleteAllList(positionCountry headCountry);
int sortedInput(positionCountry headCountry, positionCountry newCountry);
int printList(positionCountry x);
int insertAfter(positionCountry headCountry, positionCountry newCountry);
int addTreesToLists(positionCountry headCountryNextCountry);
int insertToTree(positionCity root, positionCity newCity);
int createNewElementCity(positionCity root, positionCity newCity);
int INorderPrint(positionCity root);
int connectListWithTree(positionCountry headCountryNextCountry, positionCity root);
int deleteAllTree(positionCountry headCountryNextCountry, positionCity root);
int findCountry(positionCountry headCountry, char* country, int number);
int findCities(positionCity current, int number);


int main() {

	positionCountry headCountry;
	headCountry = (positionCountry)malloc(sizeof(country));
	headCountry->nextCountry = NULL;
	headCountry->nextCity = NULL;
	headCountry->nextCountry = NULL;
	
	positionCity headCity;
	headCity = (positionCity)malloc(sizeof(city));
	headCity->right = NULL;
	headCity->left = NULL;
	
	char input = '0';
	char name[MAX_SIZE];
	int number=0;
	
	while (input!='3')
	{
		menu();
		scanf(" %c", &input);

		switch (input) {
		case '1':
			
			readFile(headCountry);
			printList(headCountry->nextCountry);
			addTreesToLists(headCountry->nextCountry);
			
			break;
		case '2':
			
			printf("Unesite neku drzavu i broj stanovnika: \nDrzava: ");
			scanf(" %s", name);
			printf("Broj stanovnika: ");
			scanf("%d", &number);

			findCountry(headCountry, name, number);

			break;
		case '3':
			printf("kraj!");
			break;
		default:
			printf("Krivi unos!\n");
			break;
		}
	}

	deleteAllTree(headCountry, headCity);
	deleteAllList(headCountry);

	return 0;
}

int menu() {

	printf("\n1- sortirani unos drzava:\n"
		"2-pretraga \n3-kraj\n"
		);
		
	return EXIT_SUCCESS;
}

int readFile(positionCountry headCountry) {

	char countryName[MAX_SIZE];
	char newFile[MAX_SIZE];

	FILE* f;
	f = fopen("drzave.txt", "r");
	
	while (fscanf(f, " %s %s", countryName, newFile)!=EOF) {

		createNewElementCountry(countryName, newFile, headCountry);
	}

	fclose(f);
	
	return EXIT_SUCCESS;
}

int createNewElementCountry(char *countryName, char *newFile, positionCountry headCountry)
{
	positionCountry newCountry = NULL;
	newCountry = (positionCountry)malloc(sizeof(country));
	newCountry->nextCountry = NULL;
	newCountry->nextCity = NULL;

	if (!newCountry)
	{
		perror("Alokacija memorije nije uspijela!\n");

		return NULL;
	}

	strcpy(newCountry->nameCountry, countryName );
	strcpy(newCountry->belongingFile, newFile);

	sortedInput(headCountry, newCountry);

	return EXIT_SUCCESS;
}

int deleteAllList(positionCountry headCountry) {

	positionCountry temp = NULL;

	while (headCountry->nextCountry != NULL) {

		temp = headCountry->nextCountry;
		headCountry->nextCountry = headCountry->nextCountry->nextCountry;

		free(temp);
	}

	return EXIT_SUCCESS;
}

int sortedInput(positionCountry headCountry, positionCountry newCountry) {

	while (headCountry->nextCountry != NULL && strcmp(headCountry->nextCountry->nameCountry, newCountry->nameCountry) < 0) {

		headCountry = headCountry->nextCountry;
	}

	insertAfter(headCountry, newCountry);

	return EXIT_SUCCESS;
}

int printList(positionCountry x)
{
	if (x == NULL) {

		printf("Lista je prazna!\n");
	}
	while (x != NULL)
	{
		printf(" Name: %s\nbelonging file: %s\n ", x->nameCountry, x->belongingFile);

		x = x->nextCountry;
	}
	return EXIT_SUCCESS;
}

int insertAfter(positionCountry headCountry, positionCountry newCountry )
{
	newCountry->nextCountry = headCountry->nextCountry;
	headCountry->nextCountry = newCountry;

	return EXIT_SUCCESS;
}

int addTreesToLists(positionCountry headCountryNextCountry) {

	char cityName[MAX_SIZE];
	int peopleNumber=0;

	while (headCountryNextCountry != NULL) {

		positionCity root;
		root = (positionCity)malloc(sizeof(city));
		root->right = NULL;
		root->left = NULL;

		if (!root)
		{
			perror("Alokacija memorije nije uspijela!\n");

			return NULL;
		}

		FILE* f2;
		f2 = fopen(headCountryNextCountry->belongingFile, "r");

		fscanf(f2, " %s %d", cityName, &peopleNumber);

		root->people = peopleNumber;
		strcpy(root->nameCity, cityName);

		connectListWithTree(headCountryNextCountry, root);

		while (fscanf(f2, " %s %d", cityName, &peopleNumber) != EOF) {

			createNewElementCity(cityName, peopleNumber, root);
		}

		printf(" %s:", headCountryNextCountry->nameCountry);

		INorderPrint(root);

		printf("\n");

		headCountryNextCountry = headCountryNextCountry->nextCountry;

		fclose(f2);
	}

	return EXIT_SUCCESS;
}

int insertToTree(positionCity root, positionCity newCity) {

	if (root == NULL)
		return newCity;

	else if (root->people < newCity->people)
		root->right = insertToTree(root->right, newCity);

	else if (root->people > newCity->people)
		root->left = insertToTree(root->left, newCity);

	else
	{
		if (strcmp(root->nameCity, newCity->nameCity) > 0)
		{
			root->left = insertToTree(root->left, newCity);
		}

		else if (strcmp(root->nameCity, newCity->nameCity) < 0)
		{
			root->right = insertToTree(root->right, newCity);
		}
	
	}

	return root;
}

int createNewElementCity(char* cityName, int peopleNumber, positionCity root)
{
	positionCity newCity = NULL;
	newCity = (positionCity)malloc(sizeof(city));
	newCity->right = NULL;
	newCity->left = NULL;

	if (!newCity)
	{
		perror("Alokacija memorije nije uspijela!\n");

		return NULL;
	}

	strcpy(newCity->nameCity, cityName);
	newCity->people = peopleNumber;

	insertToTree(root, newCity);

	return EXIT_SUCCESS;
}

int INorderPrint(positionCity root) {

	if (root == NULL) {
		return 0;
	}

	INorderPrint(root->left);
	printf(" %s", root->nameCity);
	printf(" %d", root->people);
	INorderPrint(root->right);

	return EXIT_SUCCESS;
}

int connectListWithTree(positionCountry headCountryNextCountry, positionCity root) {

	headCountryNextCountry->nextCity = root;

	return EXIT_SUCCESS;
}

int deleteAllTree(positionCountry headCountryNextCountry, positionCity root) {

		if (root == NULL) {

			return 0;
		}

		deleteAllTree(headCountryNextCountry->nextCountry, root->left);
		deleteAllTree(headCountryNextCountry->nextCountry, root->right);

		free(root);

	return EXIT_SUCCESS;
}

int findCountry(positionCountry headCountry, char* country, int number)
{
	positionCountry temp = headCountry->nextCountry;

	while (temp != NULL && strcmp(country, temp->nameCountry) != 0)
		temp = temp->nextCountry;

	if (temp)
	{
		printf("Cities in %s that have population larger than %d: \n", country, number);
		temp->nextCity = findCities(temp->nextCity, number);
	}

	else
		printf("There is no such country in the file!\n");

	return 0;

}

int findCities(positionCity current, int number)
{
	if (current == NULL)
	{
		return NULL;
	}

	else if (current->people < number)
	{
		current->right = findCities(current->right, number);
	}
	else if (current->people >= number)
	{
		current->left = findCities(current->left, number);
		printf("Name:%s  Population: %d\n", current->nameCity, current->people);
		current->right = findCities(current->right, number);
	}

	return current;
}