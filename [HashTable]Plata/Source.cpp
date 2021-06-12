#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define SIZE_BUFFER 300

enum Canal {
	ELECTRONIC,
	HARTIE
};

Canal convertToCanal(char* str)
{
	if (strcmp(str,"ELECTRONIC")==0) return ELECTRONIC;
	else if (strcmp(str,"HARTIE")==0) return HARTIE;
}

const char* convertToString(Canal c)
{

	if (c == 0) return "ELECTRONIC";
	else if (c == 1) return "HARTIE";
}
struct Plata {
	char* IBANBeneficiar;
	char* nume;
	Canal c;
    float plata;
};

struct Node
{
	Plata* p;
	Node* pNext;
	Node* pPrev;
};
struct HashTable
{
	Node** slots;
	int size;
};


Node* createNode(Plata* p)
{
	Node* retValue = NULL;
	retValue = (Node*)malloc(sizeof(Node));
	retValue->p = p;
	retValue->pNext = NULL;
	retValue->pPrev = NULL;
	return retValue;
}

void displayPlata(Plata* p) {
	printf("IBAN beneficiar:%s\nNume:%s\nCanal:%s\nPlata:%.2f\n\n", p->IBANBeneficiar, p->nume, convertToString(p->c),p->plata);
}

void initHashTable(HashTable* ht, int size)
{
	ht->slots = (Node * *)malloc(sizeof(Node*) * size);
	ht->size = size;
	/*for (int i = 0; i < size; i++)
		ht->slots[i] = NULL;*/
	memset(ht->slots, NULL, sizeof(Node*) * size);
}

//char* codBanca(char* code) {
//	
//	char* cod = (char*)malloc(strlen(code)+1);
//	int j = 0;
//	for (int i = 0; i <strlen(code); i++) {
//		cod[j]=code[i];
//		printf("%s\n", cod[j]);
//		j++;
//	}
//	return cod;
//}

int pozitieHTable(Plata* p, int size) {
	int s = 0;
	for (int i = 4; i <= 7; i++) {
		s += p->IBANBeneficiar[i];
	}
	return s % size;
	/*return strlen(codBanca(p->IBANBeneficiar)) % size;*/
}


void inserareHTable(HashTable* h, Plata* p) {
	int k;
	k = pozitieHTable(p, h->size);
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->p = p;
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
					displayPlata(temp->p);
					temp = temp->pNext;
				}
			}
		}
	}else
	printf("The Hash table structure is empty.");
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
				free(tmp->p);
				free(tmp);
			}
		}
	}
	*h = NULL;
}

int volumMemorie(HashTable* h) {
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
	/*printf("%d", nr);*/
	return sizeof(h)*nr;
}

Node* add(Node* head, Plata* p) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->p = p;
	nou->pNext = head;
	return nou;
}

Node* determinarePlati(HashTable* h,float value) {
	Node* node=NULL;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if(temp->p->plata>value)
					node = add(node, temp->p);
					temp = temp->pNext;
				}
			}
		}
	}
	return node;
}

void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		displayPlata(temp->p);
		temp = temp->pNext;
	}
}

int cautareNod(HashTable* h,Node*list, int cod) {
	int sw = 0;
	while (list != NULL) {
		if (pozitieHTable(list->p,h->size)== cod) {
			sw = 1;
			break;
		}
		list = list->pNext;
	}
	if (sw == 1) {
		return sw;
	}
	else
		return sw;
}

Node* raport(HashTable* h) {
	Node* n = NULL;
	Node* lista = NULL;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					/*printf("%d\n", pozitieHTable(temp->p,h->size));*/
					if (cautareNod(h,n, pozitieHTable(temp->p, h->size)) == 0) {
						n = add(n, temp->p);
					}
					temp = temp->pNext;
				}
			}
		}
	}
	Node* tmp = n;
	Node* list = NULL;
	while (tmp != NULL) {
		if (h) {
			for (int i = 0; i < h->size; i++)
			{
				if (h->slots[i]) {
					Node*temp = h->slots[i];
					while (temp)
					{
						/*printf("%d\n", pozitieHTable(temp->p,h->size));*/
						if(pozitieHTable(temp->p,h->size)== pozitieHTable(n->p, h->size))
						list = add(list, temp->p);
						temp = temp->pNext;
					}
				}
			}
		}
		tmp = tmp->pNext;
	}
	while (n != NULL) {
		if (h) {
			for (int i = 0; i < h->size; i++)
			{
				if (h->slots[i]) {
					Node*temp = h->slots[i];
						while (temp)
						{
							/*printf("%d\n", pozitieHTable(temp->p,h->size));*/
							if (pozitieHTable(temp->p, h->size) == pozitieHTable(n->p, h->size))
								list = add(list, temp->p);
							temp = temp->pNext;
						}
				}
			}
		}
		n = n->pNext;
	}

	return list;

}

void removePlati(HashTable* h, const char*IBAN) {
	for (int i = 0; i < h->size; i++)
	{
		if (h->slots[i]) {
			Node*temp = h->slots[i];
			while (temp)
			{
				if (strcmp(temp->p->IBANBeneficiar, IBAN) == 0) {
					h->slots[i] = NULL;
				}
				temp = temp->pNext;
			}
		}
	}
}

void main() {
	FILE* pFile = fopen("plati.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	Plata* p = NULL;
	initHashTable(h, DIM);
	if (pFile)
	{
		char* token, separators[] = ",\n";
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			p = (Plata*)malloc(sizeof(Plata));
			token = strtok(buffer, separators);
			p->IBANBeneficiar = (char*)malloc(strlen(token) + 1);
			strcpy(p->IBANBeneficiar, token);
			token = strtok(NULL, separators);
			p->nume = (char*)malloc(strlen(token) + 1);
			strcpy(p->nume, token);
			token = strtok(NULL, separators);
			p->c = convertToCanal(token);
			token = strtok(NULL, separators);
			p->plata = atof(token);
			inserareHTable(h, p);
		}
		displayH(h);
	}

	//ex3
	/*printf("\n\n\n");*/
	/*deleteHT(&h);*/
	//displayH(h);

	//ex4
	//printf("%d",volumMemorie(h));

	//ex5
	/*Node* list = NULL;*/
	/*list = determinarePlati(h, 50000);
	printList(list);*/

	//ex6
	/*list = raport(h);
	printList(list);*/

	//ex7
	/*printf("\n\n\n");
	removePlati(h, "GB29 NWBK 60161331926819");
	displayH(h);*/
}