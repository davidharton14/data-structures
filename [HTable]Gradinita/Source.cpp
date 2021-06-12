#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 100
#define LINESIZE 300

struct Gradinita
{
	char *cod;
	char *denumire;
	int nrCopii;
	int nrGrupe;
	int *nrCopiiPeGrupa;
};

struct HashTable
{
	Gradinita *info;
	int size;
	HashTable *next;
};

void displayGradinita(Gradinita *g)
{
	printf("Cod:%s\nDenumire:%s\nNr copii:%d\nNr grupe:%d\n", g->cod, g->denumire, g->nrCopii, g->nrGrupe);
	printf("Grupele:");
	for (int i = 0; i < g->nrGrupe; i++)
	{
		printf("%d ", g->nrCopiiPeGrupa[i]);
	}
	printf("\n\n");
}

int pozitieHTable(Gradinita *g, int size)
{
	/*int s = 0;
	for (int i = 0; i < strlen(g->cod); i++) {
		s += g->cod[i];
	}*/
	/*return s % size;*/
	return strlen(g->cod) % size;
}

void init(HashTable **h, int size)
{
	for (int i = 0; i < size; i++)
		h[i] = NULL;
}

void inserareHTable(HashTable **h, Gradinita *g, int size)
{
	int k;
	k = pozitieHTable(g, size);
	HashTable *newNode = (HashTable *)malloc(sizeof(HashTable));
	newNode->info = g;
	newNode->next = NULL;
	if (h[k])
	{
		HashTable *temp = h[k];
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	else
	{
		h[k] = newNode;
	}
}

void displayLista(HashTable *cap)
{
	HashTable *temp = cap;
	while (temp)
	{
		displayGradinita(temp->info);
		temp = temp->next;
	}
}

void displayH(HashTable **h, int size)
{
	if (*h != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			if (h[i])
			{
				HashTable *temp = h[i];
				while (temp)
				{
					displayGradinita(temp->info);
					temp = temp->next;
				}
			}
		}
	}
	else
		printf("The Hash table structure is empty.");
}

void modifiareCheie(HashTable **h, const char *cheie, const char *cheiaM, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (h[i])
		{
			HashTable *temp = h[i];
			while (temp)
			{
				if (strcmp(temp->info->cod, cheie) == 0)
					strcpy(temp->info->cod, cheiaM);
				temp = temp->next;
			}
		}
	}
}

struct node
{
	node *next;
	node *prev;
	Gradinita *info;
};

struct ListaDublu
{
	ListaDublu *next;
	ListaDublu *prev;
	Gradinita *info;
};

struct ListaSimpla
{
	ListaSimpla *next;
	Gradinita *info;
};
ListaSimpla *addatbeg(ListaSimpla *start, Gradinita *g)
{
	ListaSimpla *tmp = (ListaSimpla *)malloc(sizeof(ListaSimpla));
	tmp->info = g;
	tmp->next = start;
	start = tmp;
	return start;
}
ListaSimpla *initNod(Gradinita *g, ListaSimpla *next)
{
	ListaSimpla *nou = (ListaSimpla *)malloc(sizeof(ListaSimpla));
	nou->info = g;
	nou->next = next;

	return nou;
}
void insertToListaSimpla(HashTable **h, ListaSimpla **head_ref, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (h[i])
		{
			HashTable *temp = h[i];
			while (temp)
			{
				ListaSimpla *new_node = (ListaSimpla *)malloc(sizeof(ListaSimpla));
				new_node->info = temp->info;
				new_node->next = (*head_ref);
				(*head_ref) = new_node;
				temp = temp->next;
			}
		}
	}
}

void printList(ListaSimpla *n)
{
	ListaSimpla *temp = n;
	while (temp != NULL)
	{
		displayGradinita(temp->info);
		temp = temp->next;
	}
}

void insertToListaDubla(HashTable **h, ListaDublu **head_ref, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (h[i])
		{
			HashTable *temp = h[i];
			while (temp)
			{
				ListaDublu *new_node = (ListaDublu *)malloc(sizeof(ListaDublu));
				new_node->info = temp->info;
				new_node->next = (*head_ref);
				new_node->prev = NULL;
				if ((*head_ref) != NULL)
					(*head_ref)->prev = new_node;
				(*head_ref) = new_node;
				temp = temp->next;
			}
		}
	}
}
void SplitListaS(ListaSimpla *start, int value, ListaSimpla **start1);
void SplitListaD(ListaSimpla *start, int value, ListaSimpla **start1);

void SplitListaS(ListaSimpla *start, int value, ListaSimpla **start1)
{
	ListaSimpla *p = start;

	while (p != NULL)
	{
		if (p->info->nrCopii == value)
			break;
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\nValue does not exist\n");
		return;
	}
	*start1 = p->next;
	p->next = NULL;
}

void SplitListaD(ListaDublu *start, int value, ListaDublu **start1)
{
	ListaDublu *p = start;

	while (p != NULL)
	{
		if (p->info->nrCopii == value)
			break;
		p = p->next;
	}
	if (p == NULL)
	{
		printf("\nValue does not exist\n");
		return;
	}
	*start1 = p->next;
	p->next = NULL;
}

void displayLS(ListaSimpla *start)
{
	ListaSimpla *p;
	if (start == NULL)
	{
		printf("\nList is empty\n");
		return;
	}
	p = start;
	while (p != NULL)
	{
		displayGradinita(p->info);
		p = p->next;
	}
}

void printLD(ListaDublu *node)
{
	ListaDublu *last;
	/*printf("\nTraversal in forward direction \n");*/
	if (node == NULL)
	{
		printf("\nList is empty\n");
		return;
	}
	while (node != NULL)
	{
		displayGradinita(node->info);
		last = node;
		node = node->next;
	}
	/*printf("\nTraversal in reverse direction \n");
	while (last != NULL) {
		displayGradinita(last->info);
		last = last->prev;
	}*/
}

void deleteHT(HashTable **h, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (h[i])
		{
			free(h[i]->info->cod);
			free(h[i]->info->denumire);
			free(h[i]->info->nrCopiiPeGrupa);
			free(h[i]->info);
			free(h[i]);
		}
	}
	*h = NULL;
}

void deleteLS(ListaSimpla **head_ref)
{

	ListaSimpla *current = *head_ref;
	ListaSimpla *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	*head_ref = NULL;
}

void deleteLD(ListaDublu **head_ref)
{

	ListaDublu *current = *head_ref;
	ListaDublu *node = *head_ref;
	ListaDublu *next = NULL;
	ListaDublu *prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	while (node != NULL)
	{
		prev = node->prev;
		free(node);
		node = prev;
	}
	*head_ref = NULL;
}
void main()
{
	Gradinita *g = NULL;
	FILE *f = fopen("gradinite.txt", "r");
	HashTable **h = (HashTable **)malloc(sizeof(HashTable *) * 10);
	init(h, 10);
	if (f)
	{
		char *token, buffer[LINESIZE], sep[] = ",";
		while (fgets(buffer, sizeof(buffer), f))
		{
			g = (Gradinita *)malloc(sizeof(Gradinita));
			token = strtok(buffer, sep);
			g->cod = (char *)malloc(strlen(token) + 1);
			strcpy(g->cod, token);
			token = strtok(NULL, sep);
			g->denumire = (char *)malloc(strlen(token) + 1);
			strcpy(g->denumire, token);
			token = strtok(NULL, sep);
			g->nrCopii = atoi(token);
			token = strtok(NULL, sep);
			g->nrGrupe = atoi(token);
			token = strtok(NULL, sep);
			g->nrCopiiPeGrupa = (int *)malloc(sizeof(int) * g->nrGrupe);
			for (int i = 0; i < g->nrGrupe; i++)
			{
				token = strtok(NULL, sep);
				g->nrCopiiPeGrupa[i] = atoi(token);
			}
			inserareHTable(h, g, 10);
		}
		fclose(f);
	}
	/*displayH(h,DIM);*/
	/*modifiareCheie(h, "23", "100", DIM);
	printf("-------\n");
	displayH(h, DIM);*/
	ListaSimpla *listaS = NULL;
	insertToListaSimpla(h, &listaS, 10);
	ListaSimpla *startS = NULL;
	/*SplitListaS(listaS, 150, &startS);
	printf("\n\n\n");
	displayLS(listaS);
	printf("--------\n\n\n");
	displayLS(startS);*/
	ListaDublu *startD = NULL;
	ListaDublu *listaD = NULL;
	insertToListaDubla(h, &listaD, 10);
	/*SplitListaD(listaD, 150, &startD);
	printLD(listaD);
	printf("------\n");
	printLD(startD);*/
	/*deleteHT(h, DIM);
	displayH(h, DIM);*/
	/*deleteLS(&listaS);*/
	/*displayLS(listaS);*/
	deleteLD(&listaD);
	printLD(listaD);
}