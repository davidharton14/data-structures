#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define SIZE_BUFFER 300

struct Articol {
	int id;
	char* titlu;
	char* categorie;
	int nrPagini;
	int nrAutori;
};

struct Node
{
	Articol* a;
	Node* pNext;
	Node* pPrev;
};
struct HashTable
{
	Node** slots;
	int size;
};

Node* createNode(Articol* a)
{
	Node* retValue = NULL;
	retValue = (Node*)malloc(sizeof(Node));
	retValue->a = a;
	retValue->pNext = NULL;
	retValue->pPrev = NULL;
	return retValue;
}

void displayArticol(Articol* a) {
	printf("Id:%d\nTitlu:%s\nCategorie:%s\nNr pagini:%d\nNr autori:%d\n\n", a->id, a->titlu, a->categorie, a->nrPagini, a->nrAutori);
}

void initHashTable(HashTable* ht, int size)
{
	ht->slots = (Node * *)malloc(sizeof(Node*) * size);
	ht->size = size;
	/*for (int i = 0; i < size; i++)
		ht->slots[i] = NULL;*/
	memset(ht->slots, NULL, sizeof(Node*) * size);
}

int pozitieHTable(Articol* a, int size) {
	/*int s = 0;
	for (int i = 0; i < strlen(a->id); i++) {
		s += r->examCode[i];
	}
	return s % size;*/
	return strlen(a->categorie) % size;
}

void inserareHTable(HashTable* h, Articol* a) {
	int k;
	k = pozitieHTable(a, h->size);
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->a = a;
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
					displayArticol(temp->a);
					temp = temp->pNext;
				}
			}
		}
	}
	/*printf("The Hash table structure is empty.");*/
}

int nrTotalAutori(HashTable* h) {
	int nr = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					nr += temp->a->nrAutori;
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
}

Node* add(Node* head, Articol* data) {
	Node* nou = (Node *)malloc(sizeof(Node));
	nou->a = data;
	nou->pNext = head;
	return nou;
}

Node* determinareArticole(HashTable* h,const char* categorie) {
	Node* list = NULL;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (strcmp(temp->a->categorie, categorie) == 0)
					list = add(list, temp->a);
					temp = temp->pNext;
				}
			}
		}
	}
	return list;
}

void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		displayArticol(temp->a);
		temp = temp->pNext;
	}
}

void stergereArticol(HashTable* h,int id,const char* categorie) {
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (temp->a->id == id && strcmp(temp->a->categorie, categorie) == 0)
						h->slots[i] = NULL;
					temp = temp->pNext;
				}
			}
		}
	}
}

void marireNumarPagini(HashTable* h) {
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					temp->a->nrPagini += 1;
					temp = temp->pNext;
				}
			}
		}
	}
}
int cautareString(char** sir, int j, const char* string) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (strcmp(sir[i], string) == 0) {
			sw = 1;
			break;
		}
	}
	if (sw == 1) {
		return sw;
	}
	else
		return sw;
}

int nrArticole(HashTable* h) {
	int nr = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					nr++;
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
}

int nrCategorii(HashTable* h) {
	int nr = 0;
	char** sir = (char**)malloc(sizeof(char*)*nrArticole(h));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (cautareString(sir, j, temp->a->categorie) == 0) {
						sir[j] = temp->a->categorie;
						nr++;
						j++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
}
int* vectorCuNrDePagini(HashTable* h) {
	int j = 0;
	int nr = 0;
	char** sir = (char**)malloc(sizeof(char*)*nrArticole(h));
	int* vector = (int*)malloc(sizeof(int)*nrArticole(h));
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (cautareString(sir, j, temp->a->categorie) == 0) {
						sir[j] = temp->a->categorie;
						j++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	int k = 0;
	for (int j = 0; j < nrCategorii(h); j++) {
		int numar = 0;
		if (h) {
			for (int i = 0; i < h->size; i++)
			{
				if (h->slots[i]) {
					Node*temp = h->slots[i];
					while (temp)
					{
						if (strcmp(sir[j], temp->a->categorie) == 0) {
							numar+=temp->a->nrPagini;
						}
						temp = temp->pNext;
					}
				}
			}
		}
		vector[k] = numar;
		k++;
	}
	free(sir);
	return vector;
	free(vector);
}


void main() {
	FILE* pFile = fopen("articole.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	Articol* a = NULL;
	initHashTable(h, DIM);
	if (pFile)
	{
		char* token, separators[] = ",\n";
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			a = (Articol*)malloc(sizeof(Articol));
			token = strtok(buffer, separators);
			a->id = atoi(token);
			token = strtok(NULL, separators);
			a->titlu = (char*)malloc(strlen(token) + 1);
			strcpy(a->titlu, token);
			token = strtok(NULL, separators);
			a->categorie = (char*)malloc(strlen(token) + 1);
			strcpy(a->categorie, token);
			token = strtok(NULL, separators);
			a->nrPagini = atoi(token);
			token = strtok(NULL, separators);
			a->nrAutori = atoi(token);
			inserareHTable(h, a);
		}
		displayH(h);
	}
	printf("\n\n\n");

	//ex3
	/*printf("Nr total de autori este:%d", nrTotalAutori(h));*/
	
	//ex4
	/*Node* list = NULL;
	list = determinareArticole(h,"Sport");
	printList(list);*/

	//ex5
	/*stergereArticol(h, 15, "Sport");
	displayH(h);*/

	//ex6
	/*marireNumarPagini(h);
	displayH(h);*/

	//ex7
	/*int* vector = (int*)malloc(sizeof(int)*nrCategorii(h));
	vector = vectorCuNrDePagini(h);
	printf("Sirul cu numarul de pagini este:");
	for (int i = 0; i < nrCategorii(h); i++) {
		printf("%d ", vector[i]);
	}*/
}


