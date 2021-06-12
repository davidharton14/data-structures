#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LINESIZE 300


struct Angajat {
	unsigned int cod_departament;
	char* nume;
	int experienta;
	char* departament;
	char* firma;
	float salariu;
};

void afisareAngajat(Angajat* a) {
	printf("Cod department:%d\nNume:%s\nExperienta:%d\nDepartament:%s\nFirma:%s\nSalariu:%.2f\n\n", 
		a->cod_departament, a->nume, a->experienta, a->departament, a->firma, a->salariu);
}

struct Nod {
	Angajat* info;
	Nod* next;
};

struct Lista {
	Angajat* info;
	Lista* next;
};

struct ListaDeListe {
	Lista* lista;
	ListaDeListe* next;
};



void push(Nod** head_ref,Angajat* info)
{
	Nod* new_node = (Nod*) malloc(sizeof(Nod));
	new_node->info=info;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
	
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

int nrAngajati(Nod* cap) {
	Nod* temp = cap;
	int nr=0;
	while (temp) {
		nr++;
		temp = temp->next;
	}
	return nr;
}

int nrDepartamente(Nod* cap) {
	Nod* temp = cap;
	char** charsArr = (char**)malloc(sizeof(char*)*nrAngajati(cap));
	int j = 0,nr=0;
	while (temp) {
		if (cautareString(charsArr, j, temp->info->departament) == 0) {
			charsArr[j] = temp->info->departament;
			j++;
			nr++;
		}
		temp = temp->next;
	}
	return nr;
}

void pushListaDeListe(Nod* cap,ListaDeListe** head_ref,Lista** l) {
	Nod* temp = cap;
	char** charsArr = (char**)malloc(sizeof(char*)*nrDepartamente(cap));
	int j = 0;
	while (temp) {
		if (cautareString(charsArr, j, temp->info->departament) == 0) {
			charsArr[j] = temp->info->departament;
			j++;
		}
		temp = temp->next;
	}
	int nr = j;
	for (int i = 0; i < nr; i++) {
		ListaDeListe* new_node = (ListaDeListe*)malloc(sizeof(ListaDeListe));
		temp = cap;
		while (temp) {
			if (strcmp(charsArr[i], temp->info->departament) == 0) {
				Lista* new_node = (Lista*)malloc(sizeof(Lista));
				new_node->info =temp->info;
				new_node->next = (*l);
				(*l) = new_node;
			}
			temp = temp->next;
		}
		new_node->lista=(*l);
		new_node->next = (*head_ref);
		(*head_ref) = new_node;
		*l = NULL;
	}	
}

void parcurgereLista(Lista* cap) {

	Lista* temp = cap;
	while (temp) {
		afisareAngajat(temp->info);
		temp = temp->next;
	}
}

void parcurgereListaDeListe(ListaDeListe* cap) {

	ListaDeListe* temp = cap;
	int i = 0;
	while (temp) {
		printf("Lista %d:\n\n",i);
		parcurgereLista(temp->lista);
		i++;
		temp = temp->next;
	}
}


//Angajat** prelucrareLista(Nod* head,Lista* cap,float salariu) {
//	Lista* temp = cap;
//	Angajat** vector = (Angajat**)malloc(sizeof(Angajat*)*nrAngajati(head));
//	int j = 0;
//	while (temp) {
//		if (temp->info->salariu > salariu) {
//			vector[j] = temp->info;
//			j++;
//		}
//		temp = temp->next;
//	}
//	return 
//}

int nr(Nod* head,ListaDeListe* cap, float salariu) {

	Nod* temp = head;
	int nr = 0;
	while (temp) {
		if (temp->info->salariu > salariu) {
			nr++;
		}
		temp = temp->next;
	}
	return nr;
}

Angajat** determinareAngajati(Nod* cap,ListaDeListe** head_ref,Lista** l,float salariu) {
	Nod* temp = cap;
	Angajat** vector = (Angajat**)malloc(sizeof(Angajat*)*nr(cap, *head_ref, salariu));
    int la = 0;
	char** charsArr = (char**)malloc(sizeof(char*)*nrDepartamente(cap));
	int j = 0;
	while (temp) {
		if (cautareString(charsArr, j, temp->info->departament) == 0) {
			charsArr[j] = temp->info->departament;
			j++;
		}
		temp = temp->next;
	}
	int nr = j;
	for (int i = 0; i < nr; i++) {
		ListaDeListe* new_node = (ListaDeListe*)malloc(sizeof(ListaDeListe));
		temp = cap;
		while (temp) {
			if (strcmp(charsArr[i], temp->info->departament) == 0) {
				Lista* new_node = (Lista*)malloc(sizeof(Lista));
				new_node->info = temp->info;
				if (temp->info->salariu > salariu) {
					vector[la] = temp->info;
					la++;
					}
				new_node->next = (*l);
				(*l) = new_node;

			}
			temp = temp->next;
		}
		new_node->lista = (*l);
		new_node->next = (*head_ref);
		(*head_ref) = new_node;
		*l = NULL;
	}
	return vector;
	free(vector);
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

Queue addToQ(Queue& q, Nod* cap, ListaDeListe** head_ref, Lista** l,const char* dep) {
	Nod* temp = cap;
	Queue qu;
	int la = 0;
	char** charsArr = (char**)malloc(sizeof(char*)*nrDepartamente(cap));
	int j = 0;
	while (temp) {
		if (cautareString(charsArr, j, temp->info->departament) == 0) {
			charsArr[j] = temp->info->departament;
			j++;
		}
		temp = temp->next;
	}
	int nr = j;
	for (int i = 0; i < nr; i++) {
		ListaDeListe* new_node = (ListaDeListe*)malloc(sizeof(ListaDeListe));
		temp = cap;
		while (temp) {
			if (strcmp(charsArr[i], temp->info->departament) == 0) {
				Lista* new_node = (Lista*)malloc(sizeof(Lista));
				new_node->info = temp->info;
				if (strcmp(temp->info->departament, dep) == 0) {
					qu = push(q, temp->info, temp->info->cod_departament);
				}
				new_node->next = (*l);
				(*l) = new_node;

			}
			temp = temp->next;
		}
		new_node->lista = (*l);
		new_node->next = (*head_ref);
		(*head_ref) = new_node;
		*l = NULL;
	}
	return qu;
}


void display(Queue& q)
{
	if (q.head == NULL)
		printf("\nStack is Empty!!!\n");
	else {
		NodeQ *temp = q.head;
		while (temp->pNext != NULL) {
			afisareAngajat(temp->a);
			temp = temp->pNext;
		}
		afisareAngajat(temp->a);
	}
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
	else{
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->a->salariu <= p)
			qu = qu->pNext;
		tmp->pNext = qu->pNext;
		qu->pNext = tmp;
	}
	return q;
}


Angajat** determinareAngajatiCuSalariuMic(Queue& q, Nod* head) {
	Nod* tmp = head;
	Queue qu;
	Angajat** vector = (Angajat**)malloc(sizeof(Angajat*)*3);
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
	free(vector);
}

void deleteLS(Nod**head_ref)
{
	Nod*current = *head_ref;
	Nod*next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void deleteListaDeListe(ListaDeListe**head_ref)
{
	ListaDeListe*current = *head_ref;
	ListaDeListe*next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void deleteLista(Lista**head_ref)
{
	Lista*current = *head_ref;
	Lista*next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
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
			NodeQ*temp = q.head;
			q.head = q.head->pNext;
			free(temp);
		}
	}
}

void main() {
	Angajat* a=NULL;
	Nod* cap = NULL;
	ListaDeListe* lista = NULL;
	Lista* l = NULL;
	FILE* f = fopen("angajati.txt", "r");
	if (f) {
		char buffer[LINESIZE];
		char* token, sep[] = ",";
		while (fgets(buffer, LINESIZE, f)) {
			a = (Angajat*)malloc(sizeof(Angajat));
			token = strtok(buffer, sep);
			a->cod_departament = atoi(token);
			token = strtok(NULL, sep);
			a->nume = (char*)malloc(strlen(token) + 1);
			strcpy(a->nume, token);
			token = strtok(NULL, sep);
			a->experienta = atoi(token);
			token = strtok(NULL, sep);
			a->departament = (char*)malloc(strlen(token) + 1);
			strcpy(a->departament, token);
			token = strtok(NULL, sep);
			a->firma = (char*)malloc(strlen(token) + 1);
			strcpy(a->firma, token);
			token = strtok(NULL, sep);
			a->salariu = atof(token);
			push(&cap, a);
		}
		fclose(f);
	}
	//ex1
	printf("EX 1\n");
	pushListaDeListe(cap,&lista,&l);
	parcurgereListaDeListe(lista);
	//ex2
	printf("\n\n");
	printf("EX 2\n");
	Angajat** vector = (Angajat**)malloc(sizeof(Angajat*)*nr(cap,lista,5000));
	vector = determinareAngajati(cap,&lista,&l,5000);
	for (int i = 0; i < nr(cap,lista, 5000); i++) {
		afisareAngajat(vector[i]);
	}
	//ex3
	printf("\n\n");
	printf("EX 3\n");
	Queue q;
	addToQ(q, cap, &lista, &l, "PR");
	display(q);
	//ex4
	printf("\n\n");
	printf("EX 4\n");
	Angajat** vec = (Angajat**)malloc(sizeof(Angajat*)*3);
	vec = determinareAngajatiCuSalariuMic(q, cap);
	for (int i = 0; i < 3; i++) {
		afisareAngajat(vec[i]);
	}
	//ex5
	printf("\n\n");
	printf("EX 5\n");
	deleteLS(&cap);
	deleteLista(&l);
	deleteListaDeListe(&lista);
	deleteQ(q);
	free(vector);
	free(vec);

}

