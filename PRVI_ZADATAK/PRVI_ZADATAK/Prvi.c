#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_SIZE (128)
#define MAX_LINE (1024)

struct _studenti;
typedef struct _studenti {
	char ime[20];
	char prezime[20];
	int bodovi;
}student;

int prebrojiStudente(char* imeDatoteke);
student* ZauzmiMemorijuIUpisiStudente(int brojStudenata, char* filename);
int maxBodovi(student* studenti, int brojStudenata);

int main()
{
	char nazivDatoteke[50];
	double relBod = 0;
	char c = ' ';
	student* studenti;
	int brojStudenata, maxBod;
	do {
		printf("Unesi naziv datoteke: ");
		scanf(" %s", nazivDatoteke);
		brojStudenata = prebrojiStudente(nazivDatoteke);
	} while (brojStudenata == FILE_DIDNT_OPEN_ERROR);
	printf("Broj studenata u datoteci je: %d\n", brojStudenata);
	studenti = ZauzmiMemorijuIUpisiStudente(brojStudenata, nazivDatoteke);
	maxBod = maxBodovi(studenti, brojStudenata);
	printf("Ime%-18cPrezime%-14cAPSOLUTNI BODOVI%-5cRELATIVNI BODOVI \n", c, c, c, c);
	for (int i = 0; i < brojStudenata; i++)
	{
		relBod = 100 * studenti[i].bodovi / (double)maxBod;
		printf("%-20s %-20s %-20d %.0lf \n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relBod);

	}
	free(studenti);
	system("pause");
	return EXIT_SUCCESS;

}
int prebrojiStudente(char* imeDatoteke) {
	FILE* fp = NULL;
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };
	fp = fopen(imeDatoteke, "r");
	if (NULL == fp) {
		printf("Greska u otvaranju datoteke!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		if (strcmp(buffer, "\n\0") != 0) {
			brojac++;
		}
	}
	fclose(fp);
	return brojac;
}
student* ZauzmiMemorijuIUpisiStudente(int brojStudenata, char* filename) {
	FILE* fp = NULL;
	int brojac = 0;
	student* studenti = NULL;
	studenti = (student*)malloc(brojStudenata * sizeof(student));
	if (!studenti) {
		printf("Neuspjesna alokacija memorije!!\n");
		return NULL;
	}
	fp = fopen(filename, "r");
	if (!fp) {
		printf("Greska u otvaranju datoteke!\n");
		return NULL;
	}
	while (!feof(fp)) {
		fscanf(fp, " %s %s %d", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	fclose(fp);
	return studenti;
}
int maxBodovi(student* studenti, int brojStudenata) {

	int max = 0;

	for (int i = 0; i < brojStudenata; i++) {
		if (max < studenti[i].bodovi) {
			max = studenti[i].bodovi;
		}
	}
	return max;
}