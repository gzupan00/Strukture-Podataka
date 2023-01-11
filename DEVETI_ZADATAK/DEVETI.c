#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct _binaryTree* position;
typedef struct _binaryTree {

	int number;
	position left;
	position right;

}binaryTree;

int insert(position root, position newNumber);
int createNewElement(int a[], int n, position root);
int INorderPrint(position root, FILE* f);
int deleteAll(position root);
int randomArray(int a[], int n);
int replace(position root);


int main() {

	FILE* f = NULL;
	f = fopen("INorderPrint.txt", "w");

	if (!f) {

		perror("Error opening file!");

		return EXIT_FAILURE;
	}
	
	int a[10] = { 0 };
	int n = sizeof(a) / 4;

	randomArray(a, n);

	position root;
	root = (position)malloc(sizeof(binaryTree));
	root->number = a[0];
	root->left = NULL;
	root->right = NULL;

	if (!root) {

		perror("Error allocating memory!");

		return EXIT_FAILURE;
	}

	createNewElement(a, n, root);

	INorderPrint(root, f);

	replace(root);

	INorderPrint(root,f);

	deleteAll(root);

	fclose(f);

	return 0;
}

int insert(position root, position newNumber) {

	if (root == NULL) {

		return newNumber;
	}

	else if (root->number <= newNumber->number)
		root->left = insert(root->left, newNumber);

	else if (root->number > newNumber->number) 
		root->right = insert(root->right, newNumber);

	return root;
}

int createNewElement(int a[], int n, position root) {
	
	for (int i = 1; i < n; i++) {

		position newNumber = NULL;
		newNumber = (position)malloc(sizeof(binaryTree));
		
		newNumber->number = a[i];
		newNumber->left = NULL;
		newNumber->right = NULL;

		if (!newNumber) {

			perror("Error allocating memory!");

			return EXIT_FAILURE;
		}
		
		insert(root, newNumber);
	}

	return EXIT_SUCCESS;
}

int INorderPrint(position root, FILE* f) {

	if (root == NULL) {

		return 0;
	}

	INorderPrint(root->right,f);
	fprintf(f, " %d\n", root->number);
	INorderPrint(root->left,f);

	return EXIT_SUCCESS;
}

int deleteAll(position root) {

	if (root == NULL) {

		return 0;
	}

	deleteAll(root->left);
	deleteAll(root->right);

	free(root);

	return EXIT_SUCCESS;
}

int randomArray(int a[], int n) {

	for (int j = 0; j < n; j++) {

		a[j] = (rand() % 80 + 10);
	}

	return EXIT_SUCCESS;
}

int replace(position root){

	int sum = 0;
	int temp = 0;

	if (root != NULL){
	
		sum = replace(root->left);
		sum += replace(root->right);

		temp = root->number;
		root->number = sum;
		sum += temp;
	}

	return sum;
}