#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Result {
	int data;
};

struct Node
{
	Result* r;
	Node* pNext;
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
	return retValue;
}

void displayResult(Result * r) {
	printf("%d\n", r->data);
}

void initHashTable(HashTable* ht, int size)
{
	ht->slots = (Node * *)malloc(sizeof(Node*) * size);
	ht->size = size;
	memset(ht->slots, NULL, sizeof(Node*) * size);
}

int pozitieHTable(Result* r, int size,int a,int b,int c) {
	
	
	return ((c*(r->data ^ 2)) + (b*r->data) + a) % size;
}

void inserareHTable(HashTable* h, Result* r, int a, int b, int c) {
	int k;
	k = pozitieHTable(r, h->size,a,b,c);
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
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	Result* r = NULL;
	int m, a, b, c,data;
	printf("Dimensiunea tabelei de dispersie:");
	scanf("%d", &m);
	printf("a=");
	scanf("%d", &a);
	printf("b=");
	scanf("%d", &b);
	printf("c=");
	scanf("%d", &c);
	initHashTable(h, m);
	for (int i = 0; i < m; i++) {

		r = (Result*)malloc(sizeof(Result));
		printf("nod %d:",i);
		scanf("%d", &data);
		r->data = data;
		inserareHTable(h, r, a, b, c);
	}
	displayH(h);
	

}








