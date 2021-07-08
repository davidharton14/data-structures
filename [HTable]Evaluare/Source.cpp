#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define SIZE_BUFFER 300

struct Evaluare {
	char* denumireExamen;
	char* numeStudent;
	int semestru;
	float notaFinala;
	int codStudent;
	int nrCredite;
};

struct Node
{
	Evaluare* info;
	Node* pNext;
	Node* pPrev;
};
struct TabelaDeDispersie
{
	Node** slots;
	int size;
};

void afisareEvaluare(Evaluare* e) {
	printf("Denumire examen:%s\nNume student:%s\nSemestru:%d\nNota finala:%.2f\nCod student:%d\nNr credite:%d\n\n",
		e->denumireExamen, e->numeStudent, e->semestru, e->notaFinala, e->codStudent, e->nrCredite);
}


void initHashTable(TabelaDeDispersie* ht, int size)
{
	ht->slots = (Node**)malloc(sizeof(Node*) * size);
	ht->size = size;
	memset(ht->slots, NULL, sizeof(Node*) * size);
}

int pozitieHTable(Evaluare* e, int size) {

	return strlen(e->denumireExamen) % size;
}

void inserareHTable(TabelaDeDispersie* h, Evaluare* e) {
	int k;
	k = pozitieHTable(e, h->size);
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->info = e;
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

void displayH(TabelaDeDispersie* h) {
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					afisareEvaluare(temp->info);
					temp = temp->pNext;
				}
			}
		}
	}
}

int nrEvaluari(TabelaDeDispersie* h, int nrCredite) {
	int nr = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (temp->info->nrCredite==nrCredite) {
						nr++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
}

Evaluare* createEvaluare(Evaluare* c) {
	Evaluare* nou = (Evaluare*)malloc(sizeof(Evaluare));
	nou->denumireExamen = (char*)malloc(strlen(c->denumireExamen) + 1);
	strcpy(nou->denumireExamen, c->denumireExamen);
	nou->numeStudent = (char*)malloc(strlen(c->numeStudent) + 1);
	strcpy(nou->numeStudent, c->numeStudent);
	nou->semestru = c->semestru;
	nou->notaFinala = c->notaFinala;
	nou->codStudent = c->codStudent;
	nou->nrCredite = c->nrCredite;
	return nou;
}

Evaluare** determinareEvaluari(TabelaDeDispersie* h, int nrCredite) {
	Evaluare** vector = (Evaluare**)malloc(sizeof(Evaluare)*nrEvaluari(h, nrCredite));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (temp->info->nrCredite == nrCredite){
						vector[j] = createEvaluare(temp->info);
						j++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return vector;
}

int nrEvaluari1(TabelaDeDispersie* h) {
	int nr = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (temp->info->semestru == 1) {
						nr++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
}

int nrEvaluari2(TabelaDeDispersie* h) {
	int nr = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (temp->info->semestru == 2) {
						nr++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
}

Evaluare** grupareEvaluariPeSem1(TabelaDeDispersie* h) {
	Evaluare** vector = (Evaluare**)malloc(sizeof(Evaluare*)*nrEvaluari1(h));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (temp->info->semestru == 1) {
						vector[j] = createEvaluare(temp->info);
						j++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return vector;
}


Evaluare** grupareEvaluariPeSem2(TabelaDeDispersie* h) {
	Evaluare** vector = (Evaluare**)malloc(sizeof(Evaluare*)*nrEvaluari2(h));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (temp->info->semestru == 2) {
						vector[j] = createEvaluare(temp->info);
						j++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return vector;
}

void stergereTabelaDeDispersie(TabelaDeDispersie** h) {
	Node* tmp;
	for (int i = 0; i < (*h)->size; i++)
	{
		if ((*h)->slots[i]) {
			Node*temp = (*h)->slots[i];
			while (temp)
			{
				tmp = temp;
				temp = temp->pNext;
				free(tmp->info);
				free(tmp);
			}
		}
	}
	*h = NULL;
	printf("Tabela de dispersie a fost stearsa.\n");
}


void main() {
	FILE* pFile = fopen("fisier.txt", "r");
	TabelaDeDispersie* h = (TabelaDeDispersie*)malloc(sizeof(TabelaDeDispersie));
	Evaluare* e = NULL;
	initHashTable(h, DIM);
	char* buffer = (char*)malloc(SIZE_BUFFER);
	if (pFile)
	{
		char* token, separators[] = ",\n";
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			e = (Evaluare*)malloc(sizeof(Evaluare));
			token = strtok(buffer, separators);
			e->denumireExamen = (char*)malloc(strlen(token) + 1);
			strcpy(e->denumireExamen, token);
			token = strtok(NULL, separators);
			e->numeStudent = (char*)malloc(strlen(token) + 1);
			strcpy(e->numeStudent, token);
			token = strtok(NULL, separators);
			e->semestru = atoi(token);
			token = strtok(NULL, separators);
			e->notaFinala = atof(token);
			token = strtok(NULL, separators);
			e->codStudent = atoi(token);
			token = strtok(NULL, separators);
			e->nrCredite= atoi(token);
			inserareHTable(h, e);
		}
	}
	//subiectul 1
	printf("\n");
	displayH(h);
	//subiectul 2
	printf("\n");
	Evaluare** vector = (Evaluare**)malloc(sizeof(Evaluare)*nrEvaluari(h, 4));
	vector = determinareEvaluari(h, 4);
	for (int i = 0; i < nrEvaluari(h, 4); i++) {
		afisareEvaluare(vector[i]);
	}
	//subiectul 4
	Evaluare** vectorPeSem1 = (Evaluare**)malloc(sizeof(Evaluare*)*nrEvaluari1(h));
	vectorPeSem1 = grupareEvaluariPeSem1(h);
	printf("Evaluarile de pe semestrul 1 sunt:\n");
	for (int i = 0; i < nrEvaluari1(h); i++) {
		afisareEvaluare(vectorPeSem1[i]);
	}
	printf("Evaluarile de pe semestrul 2 sunt:\n");
	Evaluare** vectorPeSem2 = (Evaluare**)malloc(sizeof(Evaluare*)*nrEvaluari2(h));
	vectorPeSem2 = grupareEvaluariPeSem2(h);
	for (int i = 0; i < nrEvaluari2(h); i++) {
		afisareEvaluare(vectorPeSem2[i]);
	}
	//subiectul 5
	stergereTabelaDeDispersie(&h);
	free(vector);
	printf("Primul vector a fost sters.\n");
	free(vectorPeSem1);
	printf("Al doilea vector a fost sters.\n");
	free(vectorPeSem2);
	printf("Al treilea vector a fost sters.\n");
}