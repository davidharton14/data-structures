#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
#define DIM 100
#define LINESIZE 300
struct Produs {
	char* nume;
	/*unsigned char numar_magazine;*/
	int numar_magazine;
	float* stocuri_magazine;
	float pret;
	int cantitate;
	int dim;
};

struct hashtable_item
{
	Produs*data;
};
void init_array(hashtable_item* arr)
{
	for (int i = 0; i < DIM; i++)
	{
		arr[i].data = NULL;
	}
}
void displayProdus(Produs* p) {
	printf("Nume:%s\nNumar magazine:%d\nStocurile magazinelor sunt:\n",p->nume,p->numar_magazine,p->stocuri_magazine);
	for (int i = 0; i < p->numar_magazine; i++) {
		printf("%.2f ", p->stocuri_magazine[i]);
	}
	printf("\n");
	printf("Pret:%.2f\nCantitate:%d\n\n", p->pret, p->cantitate);
}

int CalculateHash(int key)
{
	return key % DIM;
}

void Insert(hashtable_item* &arr,Produs* p)
{
	int probe = CalculateHash(p->numar_magazine);
	int sw = 0;
	while (arr[probe].data != NULL)
	{
		sw = 1;
		probe = (probe + 1) % DIM;
	}
	arr[probe].data = p;
}
int Search(hashtable_item* arr,Produs* p)
{
	int probe = CalculateHash(p->numar_magazine);
	while (arr[probe].data != 0)
	{
		if (arr[probe].data == p)
			return probe;
		probe = (probe + 1) % DIM;
	}
	printf("\nElement %d not found.\n", p);
	return -1;
}

void Delete(hashtable_item* arr,Produs* p)
{
	int loc = Search(arr,p);
	if (loc != NULL)
	{
		arr[loc].data = NULL;
	}
}

void PrintList(hashtable_item* arr)
{
	for (int i = 0; i < DIM; i++) {
		if (arr[i].data) {
			displayProdus(arr[i].data);
		}
	}		
}

struct Node
{
	Produs* p;
	Node* pNext;
};
Node* add(Node* head, Produs* data) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->p = data;
	nou->pNext = head;
	return nou;
}


Node* insertToListaSimpla(hashtable_item* arr,int nr)
{
	Node* n = NULL;
	for (int i = 0; i < DIM; i++) {
		if (arr[i].data) {
			if (arr[i].data->numar_magazine > nr) {
				n = add(n, arr[i].data);
			}
		}
	}
	return n;
}

void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		displayProdus(temp->p);
		temp = temp->pNext;
	}
}

int cautareString(int* sir, int j, int nr) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (sir[i]==nr) {
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


int nrVectorDeNr(hashtable_item* arr) {
	int* vector = (int*)malloc(sizeof(int)*DIM);
	int j = 0;
	for (int i = 0; i < DIM; i++) {
			if (arr[i].data) {
				if (cautareString(vector, j, arr[i].data->numar_magazine)==0) {
					vector[j] = arr[i].data->numar_magazine;
					j++;
				}
			}
		}
	return j;
}

Produs* createProdus(int numar_magazine,int dim) {
	Produs* nou = (Produs*)malloc(sizeof(Produs));
	nou->numar_magazine = numar_magazine;
	nou->dim = dim;
	return nou;
}
int Nr(hashtable_item* arr) {
	int* vector = (int*)malloc(sizeof(int)*nrVectorDeNr(arr));
	Produs** vec = (Produs**)malloc(sizeof(Produs*)*nrVectorDeNr(arr));
	int k = 0;
	int j = 0;
	for (int i = 0; i < DIM; i++) {
		if (arr[i].data) {
			if (cautareString(vector, j, arr[i].data->numar_magazine) == 0) {
				vector[j] = arr[i].data->numar_magazine;
				/*printf("%d\n", vector[j]);*/
				j++;
			}
		}
	}
	for (int j = 0; j < nrVectorDeNr(arr); j++) {
		Produs* p = NULL;
		int nr = 0;
		FILE*f = fopen("produse.txt", "r");
		if (f) {
			char* token, buffer[LINESIZE], sep[] = ",";
			while (fgets(buffer, sizeof(buffer), f)) {
				p = (Produs*)malloc(sizeof(Produs));
				token = strtok(buffer, sep);
				p->nume = (char*)malloc(strlen(token) + 1);
				strcpy(p->nume, token);
				token = strtok(NULL, sep);
				p->numar_magazine = atoi(token);
				p->stocuri_magazine = (float*)malloc(sizeof(float)*p->numar_magazine);
				for (int i = 0; i < p->numar_magazine; i++) {
					token = strtok(NULL, sep);
					p->stocuri_magazine[i] = atof(token);
				}
				token = strtok(NULL, sep);
				p->pret = atof(token);
				token = strtok(NULL, sep);
				p->cantitate = atoi(token);
				int probe = CalculateHash(p->numar_magazine);
				int sw = 0;
				while (arr[probe].data != NULL)
				{
					sw = 1;
					probe = (probe + 1) % DIM;
				}
				arr[probe].data = p;
					if (arr[probe].data->numar_magazine == vector[j]) {
						if (sw == 1) {
							nr++;
						}
					}
				
			}
			fclose(f);
		}
		/*printf("%d\n", vector[j]);*/
		if (nr>1) {
			
				k++;
			
		}
	}
	return k;
}



Produs**vectorDeNr(hashtable_item* arr) {
	int* vector = (int*)malloc(sizeof(int)*nrVectorDeNr(arr));
	Produs** vec = (Produs**)malloc(sizeof(Produs*)*Nr(arr));
	int k = 0;
	int j = 0;
	for (int i = 0; i < DIM; i++) {
		if (arr[i].data) {
			if (cautareString(vector, j, arr[i].data->numar_magazine) == 0) {
				vector[j] = arr[i].data->numar_magazine;
				j++;
			}
		}
	}
	for (int j = 0; j < nrVectorDeNr(arr); j++) {
		Produs* p = NULL;
		int nr = 0;
		FILE*f = fopen("produse.txt", "r");
		if (f) {
			char* token, buffer[LINESIZE], sep[] = ",";
			while (fgets(buffer, sizeof(buffer), f)) {
				p = (Produs*)malloc(sizeof(Produs));
				token = strtok(buffer, sep);
				p->nume = (char*)malloc(strlen(token) + 1);
				strcpy(p->nume, token);
				token = strtok(NULL, sep);
				p->numar_magazine = atoi(token);
				p->stocuri_magazine = (float*)malloc(sizeof(float)*p->numar_magazine);
				for (int i = 0; i < p->numar_magazine; i++) {
					token = strtok(NULL, sep);
					p->stocuri_magazine[i] = atof(token);
				}
				token = strtok(NULL, sep);
				p->pret = atof(token);
				token = strtok(NULL, sep);
				p->cantitate = atoi(token);
				int probe = CalculateHash(p->numar_magazine);
				int sw = 0;
				while (arr[probe].data != NULL)
				{
					sw = 1;
					probe = (probe + 1) % DIM;
				}
				arr[probe].data = p;
				if (arr[probe].data->numar_magazine == vector[j]) {
					if (sw == 1) {
						nr++;
					}
				}
			}
			fclose(f);
		} 
		if (nr>1) {
				vec[k] = createProdus(vector[j], nr - 1);
				k++;
			
	    }
	} 
	return vec;
}

void swap(Node*a, Node*b)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->p = a->p;
	a->p = b->p;
	b->p = temp->p;

	free(temp);
}
void bubbleSort(struct Node *start)
{
	int swapped, i;
	struct Node *ptr1;
	struct Node *lptr = NULL;

	if (start == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->pNext != lptr)
		{
			if (ptr1->p->numar_magazine >= ptr1->pNext->p->numar_magazine)
			{
				swap(ptr1, ptr1->pNext);
				swapped = 1;
			}
			ptr1 = ptr1->pNext;
		}
		lptr = ptr1;
	} while (swapped);
}

struct ListaS {
	Produs* p;
	ListaS* pNext;
};
ListaS* add(ListaS* head, Produs* data) {
	ListaS* nou = (ListaS*)malloc(sizeof(ListaS));
	nou->p = data;
	nou->pNext = head;
	return nou;
}

ListaS* determinareProduseCeleMaiMici(Node* n) {
	ListaS* nou = NULL;
	int k = 0;
	bubbleSort(n);
	Node* temp = n;
	while (temp != NULL) {
		if (k < 3) {
			nou = add(nou, temp->p);
		}
		k++;
		temp = temp->pNext;
	}
	return nou;
}

void printListS(ListaS* n)
{
	ListaS* temp = n;
	while (temp != NULL) {
		displayProdus(temp->p);
		temp = temp->pNext;
	}
}
void deleteHT(hashtable_item* arr) {

	for (int i = 0; i < DIM; i++)
	{
		if (arr[i].data) {
			free(arr[i].data);
		}
	}
	free(arr);
}
void deleteLS(ListaS **head_ref)
{

	ListaS *current = *head_ref;
	ListaS *next = NULL;

	while (current != NULL)
	{
		next = current->pNext;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}
void deleteLS1(Node**head_ref)
{

	Node *current = *head_ref;
	Node *next = NULL;

	while (current != NULL)
	{
		next = current->pNext;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}
void main() {
	Produs* p = NULL;
	FILE*f = fopen("produse.txt", "r");
	hashtable_item* array = (hashtable_item*)malloc(DIM * sizeof(hashtable_item));
	init_array(array);
	if (f) {
		char* token, buffer[LINESIZE], sep[] = ",";
		while (fgets(buffer, sizeof(buffer), f)) {
			p = (Produs*)malloc(sizeof(Produs));
			token = strtok(buffer, sep);
			p->nume = (char*)malloc(strlen(token) + 1);
			strcpy(p->nume, token);
			token = strtok(NULL, sep);
			p->numar_magazine = atoi(token);
			p->stocuri_magazine = (float*)malloc(sizeof(float)*p->numar_magazine);
			for (int i = 0; i < p->numar_magazine; i++) {
				token = strtok(NULL, sep);
				p->stocuri_magazine[i] = atof(token);
			}
			token = strtok(NULL, sep);
			p->pret = atof(token);
			token = strtok(NULL, sep);
			p->cantitate = atoi(token);
			Insert(array, p);
		}
		fclose(f);
	}
	//ex1
	PrintList(array);
	//ex2
	Node* n = NULL;
	n=insertToListaSimpla(array, 2);
	printf("\n\n");
	printList(n);
	//ex3
	Produs** vec = (Produs**)malloc(sizeof(Produs*)*Nr(array));
	vec = vectorDeNr(array);
	for (int i = 0; i < Nr(array); i++) {
		printf("Numarul de magazine:%d\nDimensiune cluster:%d\n\n", vec[i]->numar_magazine, vec[i]->dim);
	}
	//ex4
	ListaS* nou = NULL;
	nou = determinareProduseCeleMaiMici(n);
	printListS(nou);
	//ex5
	deleteHT(array);
	deleteLS(&nou);
	deleteLS1(&n);
	free(vec);
}