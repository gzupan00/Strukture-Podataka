#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct _BinaryTree* Position;
typedef struct _BinaryTree {
	int number;
	Position left;
	Position right;
}BinaryTree;

typedef struct _Queue* QueuePosition;
typedef struct _Queue {
	Position ElementOfTree;
	QueuePosition next;
}Queue;

int Menu(Position root, QueuePosition head);
Position InsertToTree(Position current, Position q);
Position CreateNewElement(int number, Position root);
int INorderPrint(Position current);
int POSTorderPrint(Position current);
int PREorderPrint(Position current);
int AddToQueue(Position element, QueuePosition head);
int RemoveFromQueue(QueuePosition head);
QueuePosition CreateNewQueueElement(Position element);
QueuePosition FindLast(QueuePosition head);
int LEVELorderPrint(Position root, QueuePosition head);
Position DeleteElement(int number, Position root);
Position FindElement(int number, Position current);
Position FindMin(Position current);
int DeleteAll(Position current);

int main()
{
	Position root = NULL;
	Queue Head = { .ElementOfTree = 0,.next = NULL };

	Menu(root, &Head);
	return 0;
}
int Menu(Position root, QueuePosition head) {
	int choice = 0;
	int NumberOfElements = 0;
	int input = 0;
	do {
		printf("\n1-Add element to binary tree \n2-delete element\n"
			"3-find element\n4-INorder print \n5-POSTorder print\n6-PREorder print\n"
			"7-LEVELorder print\n0-exit program\n"
			"\nChoose your next action: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Input how many elements you would like to add to binary tree: ");
			scanf("%d", &NumberOfElements);
			for (int i = 0; i < NumberOfElements; i++)
			{
				printf("Element number %d: ", i + 1);
				scanf("%d", &input);
				root = CreateNewElement(input, root);
			}
			break;
		case 2:
			printf("Input the number you wish to delete: ");
			scanf("%d", &input);
			root = DeleteElement(input, root);
			break;
		case 3:
			printf("Input the number you want to search for: ");
			scanf("%d", &input);
			FindElement(input, root);
			break;
		case 4:
			INorderPrint(root);
			break;
		case 5:
			POSTorderPrint(root);
			break;
		case 6:
			PREorderPrint(root);
			break;
		case 7:
			LEVELorderPrint(root, head);
			break;
		case 0:
			DeleteAll(root);
			printf("All elements deleted!");
			break;
		default:
			printf("Wrong input please follow the menu");
			break;
		}
	} while (choice != 0);
	return EXIT_SUCCESS;
}
Position CreateNewElement(int number, Position root) {
	Position newNumber = NULL;
	newNumber = (Position)malloc(sizeof(BinaryTree));
	if (!newNumber) {
		printf("Error allocating memory!\n");
		return NULL;
	}

	newNumber->number = number;
	newNumber->left = NULL;
	newNumber->right = NULL;

	newNumber = InsertToTree(root, newNumber);
	return newNumber;
}
Position InsertToTree(Position current, Position q) {
	if (current == NULL)
		return q;

	else if (current->number < q->number)
		current->right = InsertToTree(current->right, q);

	else if (current->number > q->number)
		current->left = InsertToTree(current->left, q);

	else
		free(q);

	return current;
}

int INorderPrint(Position current) {
	if (current == NULL) {
		return 0;
	}

	INorderPrint(current->left);
	printf("%d ", current->number);
	INorderPrint(current->right);
	return EXIT_SUCCESS;
}

int POSTorderPrint(Position current) {
	if (current == NULL) {
		return 0;
	}

	POSTorderPrint(current->left);
	POSTorderPrint(current->right);
	printf("%d ", current->number);
	return EXIT_SUCCESS;
}

int PREorderPrint(Position current) {
	if (current == NULL) {
		return 0;
	}

	printf("%d ", current->number);
	PREorderPrint(current->left);
	PREorderPrint(current->right);
	return EXIT_SUCCESS;
}

int LEVELorderPrint(Position root, QueuePosition head) {
	if (NULL == root) {
		printf("Binary tree is empty!\n");
		return 0;
	}
	Position current = NULL;
	AddToQueue(root, head);

	while (head->next != NULL) {
		current = head->next->ElementOfTree;
		printf("%d ", current->number);
		if (current->left != NULL) {
			AddToQueue(current->left, head);
		}
		if (current->right != NULL) {
			AddToQueue(current->right, head);
		}
		RemoveFromQueue(head);
	}
	return EXIT_SUCCESS;
}
QueuePosition CreateNewQueueElement(Position element) {
	QueuePosition newQueueEl = NULL;
	newQueueEl = (QueuePosition)malloc(sizeof(Queue));
	if (!newQueueEl)
	{
		printf("Failed allocation!\n");
		return NULL;
	}
	newQueueEl->ElementOfTree = element;
	newQueueEl->next = NULL;

	return newQueueEl;
}
int AddToQueue(Position element, QueuePosition head) {
	QueuePosition last = NULL;
	last = FindLast(head);

	last->next = CreateNewQueueElement(element);
	if (!head->next) {
		printf("No elements added to queue");
		return -1;
	}

	last->next->next = NULL;
	return 0;
}
int RemoveFromQueue(QueuePosition head) {
	QueuePosition toDelete = head->next;
	if (!toDelete) {
		printf("No elements in queue!\n");
		return 0;
	}

	head->next = toDelete->next;
	free(toDelete);
	return 0;
}
QueuePosition FindLast(QueuePosition head) {
	QueuePosition temp = head;
	while (temp->next != NULL)
		temp = temp->next;

	return temp;
}
Position DeleteElement(int number, Position current) {
	if (NULL == current) {
		printf("There is no such element in binary tree!\n");
	}

	else if (number < current->number) {
		current->left = DeleteElement(number, current->left);
	}

	else if (number > current->number) {
		current->right = DeleteElement(number, current->right);
	}
	else {
		if (current->left != NULL && current->right != NULL) {
			Position temp = FindMin(current->right);
			current->number = temp->number;
			current->right = DeleteElement(current->number, current->right);
		}
		else {
			Position temp = current;

			if (NULL == current->left) {
				current = current->right;
			}
			else {
				current = current->left;
			}
			free(temp);
		}
	}
	return current;
}
Position FindElement(int number, Position current) {
	if (NULL == current)
	{
		printf("There is no such element in binary tree!\n");
		return NULL;
	}
	if (current->number == number)
	{
		printf("Element found! \n");
		return current;
	}
	else if (number > current->number)
		FindElement(number, current->right);

	else if (number < current->number)
		FindElement(number, current->left);
}
Position FindMin(Position current) {
	if (NULL == current) {
		return NULL;
	}
	else {
		if (NULL == current->left) {
			return current;
		}
		else {
			return FindMin(current->left);
		}
	}
}
int DeleteAll(Position current) {
	if (current == NULL) {
		return 0;
	}
	DeleteAll(current->left);
	DeleteAll(current->right);

	free(current);
	return EXIT_SUCCESS;
}