#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define DIM_BUFFER 300

struct Angajat {
	unsigned int cod_departament;
	char* nume_angajat;
	char* nume_departament;
	int id_angajat;
	float salariu;
	int numar_ani_vechime;
};

struct nodListaPrincipala;
struct nodListaSecundara {
	nodListaSecundara* next;
	nodListaPrincipala* info;
	int distanta;
};

struct nodListaPrincipala {
	nodListaSecundara*vecini;
	Angajat* info;
	nodListaPrincipala*next;
};

nodListaPrincipala*inserareListaPrincipala(nodListaPrincipala* cap, Angajat* a) {
	nodListaPrincipala* nou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
	nou->info = a;
	nou->vecini = NULL;
	nou->next = NULL;
	if (cap) {
		nodListaPrincipala* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}


nodListaSecundara* inserareListaSecundara(nodListaSecundara*cap, nodListaPrincipala* info, int distanta) {
	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->info = info;
	nou->distanta = distanta;
	nou->next = NULL;
	if (cap) {
		nodListaSecundara*p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

nodListaPrincipala* cautareDupaID(nodListaPrincipala* cap, int id) {
	while (cap && cap->info->id_angajat != id) {
		cap = cap->next;
	}
	return cap;
}
void inserareArcInGraf(nodListaPrincipala* graf, int idStart, int idStop, int distanta) {
	if (graf) {
		nodListaPrincipala*nodStart = cautareDupaID(graf, idStart);
		nodListaPrincipala*nodStop = cautareDupaID(graf, idStop);
		if (nodStart && nodStop) {
			nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop, distanta);
			/*nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);*/
		}
	}
}

void afisareListaSecundara(nodListaSecundara* cap) {
	while (cap) {
		printf("Cod departament:%d\nNume angajat:%s\nNume departament:%s\nId angajat:%d\nSalariu:%.2f\nNumar ani vechime:%d\n\n",
			cap->info->info->cod_departament, cap->info->info->nume_angajat, 
			cap->info->info->nume_departament, cap->info->info->id_angajat, 
			cap->info->info->salariu,cap->info->info->numar_ani_vechime);
		printf("Distanta:%d\n", cap->distanta);
		cap = cap->next;
	}
}

void afisareListaPrincipala(nodListaPrincipala*cap) {
	while (cap) {
		if (cap->vecini) {
			printf("NODUL:\n\nsCod departament:%d\nNume angajat:%s\nNume departament:%s\nId angajat:%d\nSalariu:%.2f\nNumar ani vechime:%d\n\n",
				cap->info->cod_departament, cap->info->nume_angajat,
				cap->info->nume_departament, cap->info->id_angajat,
				cap->info->salariu, cap->info->numar_ani_vechime);
			printf("AU URMATORII VECINI:\n");
			afisareListaSecundara(cap->vecini);
		}
		cap = cap->next;
	}
}

int nrAngajatiPeUnCriteriu(nodListaPrincipala*cap, int value) {
	nodListaPrincipala*temp = cap;
	int nr = 0;
	while (temp) {
		if (temp->info->salariu>value) {
			nr++;
		}
		temp = temp->next;
	}
	return nr;
}
Angajat** determinareAngajatiPeUnCriteriu(nodListaPrincipala*cap, int value) {
	Angajat** vector = (Angajat**)malloc(sizeof(Angajat*)*nrAngajatiPeUnCriteriu(cap, value));
	int j = 0;
	nodListaPrincipala*temp = cap;
	while (temp) {
		if (temp->info->salariu > value) {
			vector[j] = temp->info;
			j++;
		}
		temp = temp->next;
	}
	return vector;
}

struct NodeQ
{
	Angajat* a;
	NodeQ* pNext;
	NodeQ* pPrev;
};
struct Queue
{
	NodeQ* head = NULL;
	NodeQ* tail = NULL;
};

NodeQ* newNode(Angajat* a)
{
	NodeQ* temp = (NodeQ*)malloc(sizeof(NodeQ));
	temp->a = a;
	temp->pNext = NULL;

	return temp;
}

Queue push(Queue& q, Angajat* a, int p)
{
	NodeQ*tmp, *qu;

	tmp = (NodeQ *)malloc(sizeof(NodeQ));
	tmp = newNode(a);
	if (q.head == NULL || p < q.head->a->cod_departament)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else
	{
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->a->cod_departament <= p)
			qu = qu->pNext;
		tmp->pNext = qu->pNext;
		qu->pNext = tmp;
	}
	return q;
}

Queue addToQ(Queue& q,nodListaPrincipala*cap,const char* dep) {
	Queue qu;
	while (cap) {
		if (strcmp(cap->info->nume_departament, dep) == 0) {
			qu = push(q, cap->info, cap->info->id_angajat);
		}
		cap = cap->next;
	}
	return qu;
}

void displayQ(Queue& q)
{
	if (q.head == NULL)
		printf("\nStack is Empty!!!\n");
	else {
		NodeQ *temp = q.head;
		while (temp->pNext != NULL) {
			printf("Cod departament:%d\nNume angajat:%s\nNume departament:%s\nId angajat:%d\nSalariu:%.2f\nNumar ani vechime:%d\n\n",
				temp->a->cod_departament, temp->a->nume_angajat,
				temp->a->nume_departament, temp->a->id_angajat,
				temp->a->salariu, temp->a->numar_ani_vechime);
			temp = temp->pNext;
		}
		printf("Cod departament:%d\nNume angajat:%s\nNume departament:%s\nId angajat:%d\nSalariu:%.2f\nNumar ani vechime:%d\n\n",
			temp->a->cod_departament, temp->a->nume_angajat,
			temp->a->nume_departament, temp->a->id_angajat,
			temp->a->salariu, temp->a->numar_ani_vechime);
	}
}

struct Heap
{
	Angajat**elements;
	int heapSize;
	int index;
};

void initHeap(Heap &heap, int size)
{
	heap.elements = (Angajat**)malloc(sizeof(Angajat*) * size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(Angajat*) * size);
}

Angajat* creareAngajat(Angajat* a) {
	Angajat*nou = (Angajat*)malloc(sizeof(Angajat));
	nou->cod_departament = a->cod_departament;
	nou->nume_angajat = (char*)malloc(strlen(a->nume_angajat) + 1);
	strcpy(nou->nume_angajat, a->nume_angajat);
	nou->nume_departament = (char*)malloc(strlen(a->nume_departament) + 1);
	strcpy(nou->nume_departament, a->nume_departament);
	nou->id_angajat = a->id_angajat;
	nou->salariu = a->salariu;
	nou->numar_ani_vechime = a->numar_ani_vechime;
	return nou;

}

int nrAngajati(nodListaPrincipala*cap,int cod) {
	int nr = 0;
	while (cap) {
		if(cap->info->cod_departament==cod)
		nr++;
		cap = cap->next;
	}
	return nr;
}

void reheapUp(Heap heap, int first, int last)
{
	int parinte;
	Angajat*temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->id_angajat <
			heap.elements[last]->id_angajat)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			reheapUp(heap, first, parinte);
		}
	}
}

void enqueue(Heap &heap, Angajat* c)
{
	if (heap.index < heap.heapSize)
	{
		Angajat*nou = creareAngajat(c);
		heap.elements[heap.index] = nou;
		reheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void displayHeap(Heap &heap)
{
	for (int i = 0; i < heap.heapSize; i++)
	{
		printf("Index:%d\n", i);
		printf("Cod departament:%d\nNume angajat:%s\nNume departament:%s\nId angajat:%d\nSalariu:%.2f\nNumar ani vechime:%d\n\n",
			heap.elements[i]->cod_departament, heap.elements[i]->nume_angajat,
			heap.elements[i]->nume_departament, heap.elements[i]->id_angajat,
			heap.elements[i]->salariu, heap.elements[i]->numar_ani_vechime);
	}
}

Heap copiere(nodListaPrincipala*cap,int cod) {
	Heap heap;
	initHeap(heap, nrAngajati(cap,cod));
	while (cap) {
		if (cap->info->cod_departament == cod)
			enqueue(heap, cap->info);
		cap = cap->next;
	}
	return heap;
}

Queue pushInDescendingOrder(Queue& q, Angajat* a, int p)
{
	NodeQ*tmp, *qu;
	tmp = (NodeQ *)malloc(sizeof(NodeQ));
	tmp = newNode(a);
	if (q.head == NULL || p <= q.head->a->salariu)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else {
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->a->salariu <= p)
			qu = qu->pNext;
		tmp->pNext = qu->pNext;
		qu->pNext = tmp;
	}
	return q;
}

Angajat** determinareAngajatiCuSalariuMic(Queue& q, nodListaPrincipala*cap) {
	nodListaPrincipala* tmp = cap;
	Queue qu;
	Angajat** vector = (Angajat**)malloc(sizeof(Angajat*) * 3);
	int j = 0;
	int k = 0;
	while (tmp) {
		qu = pushInDescendingOrder(q, tmp->info, tmp->info->salariu);
		tmp = tmp->next;
	}
	NodeQ *temp = q.head;
	while (temp->pNext != NULL) {
		if (k < 3) {
			vector[j] = temp->a;
			j++;
		}
		k++;
		temp = temp->pNext;
	}
	return vector;
}

void deleteQ(Queue& q) {

	NodeQ*ptr;
	NodeQ*temp;
	int sw = 0;
	ptr = q.head;
	if (q.head == NULL)
		printf("Queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			ptr = ptr->pNext;
			NodeQ *temp = q.head;
			q.head = q.head->pNext;
			free(temp);
		}
	}
	printf("Coada implementata cu lista simpla inlantuita a fost stearsa.\n");
}

void delete_queue(Heap& heap)
{
	for (int i = 0; i < heap.heapSize; i++) {
		free(heap.elements[i]);
		heap.heapSize--;
	}
	printf("Coada de tipul HEAP a fost stearsa.\n");
}

void dezalocareLs(nodListaSecundara *cap) {
	nodListaSecundara *temp = cap;
	while (temp) {
		nodListaSecundara *temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLp(nodListaPrincipala* cap) {
	nodListaPrincipala *temp = cap;
	while (temp) {
		nodListaPrincipala *temp2 = temp->next;
		if (temp->vecini != NULL)
			dezalocareLs(temp->vecini);
		free(temp);
		temp = temp2;
	}
	printf("Graful a fost sters.\n");
}

void main()
{
	nodListaPrincipala* graf = NULL;
	Angajat* a = NULL;
	FILE* file = fopen("file.txt", "r");
	if (file) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		int nr = 0;
		int nrArce;
		while (fgets(buffer, DIM_BUFFER, file)) {
			if (nr == 0) {
				token = strtok(buffer, sep);
				nrArce = atoi(token);
				for (int i = 0; i < nrArce; i++) {
					token = strtok(NULL, sep);
					token = strtok(NULL, sep);
					token = strtok(NULL, sep);
				}
			}
			else {
				a = (Angajat*)malloc(sizeof(Angajat));
				token = strtok(buffer, sep);
				a->cod_departament= atoi(token);
				token = strtok(NULL, sep);
				a->nume_angajat = (char*)malloc(strlen(token) + 1);
				strcpy(a->nume_angajat, token);
				token = strtok(NULL, sep);
				a->nume_departament = (char*)malloc(strlen(token) + 1);
				strcpy(a->nume_departament, token);
				token = strtok(NULL, sep);
				a->id_angajat = atoi(token);
				token = strtok(NULL, sep);
				a->salariu = atof(token);
				token = strtok(NULL, sep);
				a->numar_ani_vechime = atoi(token);
				graf = inserareListaPrincipala(graf, a);
			}
			nr++;
		}
		fclose(file);
	}
	int nrArce;
	FILE*f = fopen("file.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		int nr = 0;
		while (fgets(buffer, DIM_BUFFER, f)) {
			if (nr == 0) {
				token = strtok(buffer, sep);
				nrArce = atoi(token);
				for (int i = 0; i < nrArce; i++) {
					token = strtok(NULL, sep);
					int idStart = atoi(token);
					token = strtok(NULL, sep);
					int idStop = atoi(token);
					token = strtok(NULL, sep);
					int distanta = atoi(token);
					inserareArcInGraf(graf, idStart, idStop, distanta);
				}
			}
			nr++;
		}
		fclose(f);
	}
	//ex1
	afisareListaPrincipala(graf);
	//ex2
	printf("-------------\n");
	Angajat** vector = (Angajat**)malloc(sizeof(Angajat*)*nrAngajatiPeUnCriteriu(graf, 4000));
	vector = determinareAngajatiPeUnCriteriu(graf, 4000);
	for (int i = 0; i < nrAngajatiPeUnCriteriu(graf, 4000); i++) {
		printf("Cod departament:%d\nNume angajat:%s\nNume departament:%s\nId angajat:%d\nSalariu:%.2f\nNumar ani vechime:%d\n\n",
			vector[i]->cod_departament, vector[i]->nume_angajat,
			vector[i]->nume_departament, vector[i]->id_angajat,
			vector[i]->salariu, vector[i]->numar_ani_vechime);
	}
	//ex3
	printf("----------\n");
	Queue q;
	addToQ(q, graf, "PR");
	displayQ(q);
	printf("----------\n");
	Heap h;
	h = copiere(graf, 34);
	displayHeap(h);
	//ex4
	printf("----------\n");
	Queue qu;
	Angajat** vec = (Angajat**)malloc(sizeof(Angajat*) * 3);
	vec = determinareAngajatiCuSalariuMic(qu, graf);
	for (int i = 0; i < 3; i++) {
		printf("Cod departament:%d\nNume angajat:%s\nNume departament:%s\nId angajat:%d\nSalariu:%.2f\nNumar ani vechime:%d\n\n",
			vec[i]->cod_departament, vec[i]->nume_angajat,
			vec[i]->nume_departament, vec[i]->id_angajat,
			vec[i]->salariu, vec[i]->numar_ani_vechime);
	}
	//ex5
	for (int i = 0; i < nrAngajatiPeUnCriteriu(graf, 4000); i++) {
		free(vector[i]->nume_angajat);
		free(vector[i]->nume_departament);
	}
	free(vector);
	vector = NULL;
	printf("Primul vector implementat a fost sters.\n");
	for (int i = 0; i < 3; i++) {
		free(vec[i]->nume_angajat);
		free(vec[i]->nume_departament);
	}
	free(vec);
	vec = NULL;
	printf("Al doilea vector implementat a fost sters.\n");
	deleteQ(qu);
	delete_queue(h);
	dezalocareLp(graf);
}


