#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define SIZE_BUFFER 300


struct Result {
	char examCode[5];
	char* studentName;
	int noOfCorrectResponses;
	int noOfIncorrectResponses;
	int minNoOfPoints;
};

struct Node
{
	Result* r;
	Node* pNext;
	Node* pPrev;
};
struct HashTable
{
	Node** slots;
	int size;
};

Node* createNode(Result * r)
{
	Node* retValue = NULL;
	retValue = (Node*)malloc(sizeof(Node));
	retValue->r = r;
	retValue->pNext = NULL;
	retValue->pPrev = NULL;
	return retValue;
}

void displayResult(Result * r) {
	printf("Exam code:%s\nStudent name:%s\nNo of correct responses:%d\nNo of incorrect responses:%d\nMin no of points:%d\n\n", r->examCode, r->studentName, r->noOfCorrectResponses, r->noOfIncorrectResponses, r->minNoOfPoints);
}

void initHashTable(HashTable* ht, int size)
{
	ht->slots = (Node * *)malloc(sizeof(Node*) * size);
	ht->size = size;
	/*for (int i = 0; i < size; i++)
		ht->slots[i] = NULL;*/
	memset(ht->slots, NULL, sizeof(Node*) * size);
}

int pozitieHTable(Result* r, int size) {
	int s = 0;
	for (int i = 0; i < strlen(r->examCode); i++) {
		s += r->examCode[i];
	}
	return s % size;
	/*return strlen(r->examCode) % size;*/
}

void inserareHTable(HashTable* h, Result* r) {
	int k;
	k = pozitieHTable(r, h->size);
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->r = r;
	newNode->pNext = NULL;
	if (h->slots[k]) {
		Node*temp = h->slots[k];
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = newNode;
	}
	else {
		h->slots[k] = newNode;
	}
}

void displayH(HashTable* h) {
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					displayResult(temp->r);
					temp = temp->pNext;
				}
			}
		}
	}
	/*printf("The Hash table structure is empty.");*/
}

int numarStudentiPromovati(HashTable* h) {
	
	int nr = 0;
	for (int i = 0; i < h->size; i++)
	{
		if (h->slots[i]) {
			Node*temp = h->slots[i];
			while (temp)
			{
				if (temp->r->noOfCorrectResponses > temp->r->minNoOfPoints) {
					displayResult(temp->r);
					nr++;
				}
				temp = temp->pNext;
			}
		}
	}
	return nr;
}

void removeStudents(HashTable* h,const char* name) {
	int sw = 0;
	for (int i = 0; i < h->size; i++)
	{
		int sw = 0;
		if (h->slots[i]) {
			Node*temp = h->slots[i];
			while (temp)
			{
				if (strcmp(temp->r->studentName,name)==0) {
					h->slots[i] = NULL;
				}
				temp = temp->pNext;
			}
		}
	}
}

void removeStudents2(HashTable* h, const char*code) {
	int sw = 0;
	for (int i = 0; i < h->size; i++)
	{
		int sw = 0;
		if (h->slots[i]) {
			Node*temp = h->slots[i];
			while (temp)
			{
				if (strcmp(temp->r->examCode,code)==0) {
					h->slots[i] = NULL;
				}
				temp = temp->pNext;
			}
		}
	}
}




Node* add(Node* head, Result* data) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->r = data;
	nou->pNext = head;
	return nou;
}

Node* storesStudents(HashTable* h, const char* code ) {
	Node* arr = NULL;
	for (int i = 0; i < h->size; i++)
	{
		if (h->slots[i]) {
			Node*temp = h->slots[i];
			while (temp)
			{
				if (strcmp(temp->r->examCode,code)==0) {
					arr = add(arr, temp->r);
					h->slots[i] = NULL;
				}
				temp = temp->pNext;
			}
		}
	}
	return arr;
}

void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		displayResult(temp->r);
		temp = temp->pNext;
	}
}

int nrPoints(HashTable* h, const char* name) {
	int nr = 0;
	for (int i = 0; i < h->size; i++)
	{
		if (h->slots[i]) {
			Node*temp = h->slots[i];
			while (temp)
			{
				if (strcmp(temp->r->studentName, name) == 0) {
					nr = temp->r->noOfCorrectResponses;
				}
				temp = temp->pNext;
			}
		}
	}
	return nr;
}

void deleteHT(HashTable** h) {
	Node* tmp;
	
	for (int i = 0; i < (*h)->size; i++)
	{
		if ((*h)->slots[i]) {
			Node*temp = (*h)->slots[i];
			while (temp)
			{
				tmp = temp;
				temp = temp->pNext;
				free(tmp->r);
				free(tmp);
			}
		}
	}
	*h = NULL;
}

void main() {
	FILE* pFile = fopen("results.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	Result* r = NULL;
	initHashTable(h, DIM);
	if (pFile)
	{
		char* token, separators[] = ",\n";
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			r = (Result*)malloc(sizeof(Result));
			token = strtok(buffer, separators);
			strcpy(r->examCode, token);
			token = strtok(NULL, separators);
			r->studentName = (char*)malloc(strlen(token) + 1);
			strcpy(r->studentName, token);
			token = strtok(NULL, separators);
			r->noOfCorrectResponses = atoi(token);
			token = strtok(NULL, separators);
			r->noOfIncorrectResponses = atoi(token);
			token = strtok(NULL, separators);
			r->minNoOfPoints = atoi(token);
			inserareHTable(h, r);
		}
		displayH(h);
	}
	printf("\n\n\n");
	//printf("Numarul de studenti promovati este:%d", numarStudentiPromovati(h));

	//ex4
	//removeStudents(h, "Lumperdean Radu");
	//displayH(h);

	//ex5
	/*Node* list = NULL;
	list = storesStudents(h, "ABC12");
	printList(list);*/

	//ex6
	/*printf("%d", nrPoints(h,"Harton Maria"));*/

	//ex7
	/*removeStudents2(h, "ABC12");
	displayH(h);*/

	//deleteHT(&h);
	//displayH(h);
    




}








