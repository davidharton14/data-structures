#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stack>
using namespace std;
#define DIM_BUFFER 300

struct Echipament {
	int cod_produs;
	int pret;
	char* categorie;
	char* denumire;
	int cantitate;
	char* data;
};

struct NodArb {
	Echipament* e;
	NodArb* st;
	NodArb* dr;
};

void displayEchipament(Echipament* e) {
	printf("Cod produs:%d\nPret:%d\nCategorie:%s\nDenumire:%s\nCantitate:%d\nData:%s\n\n",
		e->cod_produs, e->pret, e->categorie, e->denumire, e->cantitate, e->data);
}


NodArb* inserareArb(NodArb* rad, Echipament* e) {
	if (rad) {
		if (e->cod_produs < rad->e->cod_produs) {
			rad->st = inserareArb(rad->st, e);
		}
		else {
			rad->dr = inserareArb(rad->dr, e);
		}
		return rad;
	}
	else
	{
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->e = e;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}

}

void displayArb(NodArb* rad) {
	if (rad) {
		displayEchipament(rad->e);
		displayArb(rad->st);
		displayArb(rad->dr);
	}
}

int cautare(int k, char** sir, const char*string) {
	int sw = 0;
	for (int i = 0; i < k; i++) {
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



int determinareCodEchipament(NodArb* root, const char* categorie) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int max = 0;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (strcmp(categorie, curr->e->categorie) == 0) {
				if (curr->e->pret > max)
					max = curr->e->pret;
			}
			curr = curr->dr;
		}
	}	
	return max;
}

int codPretMaxim(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int max = 0;
	int id;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (curr->e->pret > max){
				max = curr->e->pret;
				id = curr->e->cod_produs;
			}
			curr = curr->dr;
		}
	}
	return id;
}

NodArb* getNodeWithMaximum(NodArb* root) {
	if (root) {
		if (root->dr) {
			return getNodeWithMaximum(root->dr);
		}
		else {
			return root;
		}
	}
}
Echipament* extract(NodArb** root) {
	if (*root) {
		if ((*root)->e->cod_produs == codPretMaxim(*root)){
			Echipament* result = (*root)->e;
			if ((*root)->dr == NULL) {
				NodArb* temp = (*root)->st;
				free(*root);
				*root = temp;
			}
			else
				if ((*root)->st == NULL) {
					NodArb* temp = (*root)->dr;
					free(*root);
					*root = temp;
				}
				else {
					NodArb* temp = getNodeWithMaximum((*root)->st);
					Echipament* aux = temp->e;
					temp->e = (*root)->e;
					(*root)->e = aux;
					extract(&(*root)->st);
				}
			return result;
		}
		else if ((*root)->e->cod_produs > codPretMaxim(*root)) {
			return extract(&(*root)->st);
		}
		else {
			return extract(&(*root)->dr);
		}
	}
}

int nrEc(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int nr = 0;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			nr++;
			curr = curr->dr;
		}
	}
	return nr;
}

int nrEchipamente(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	char** sir = (char**)malloc(sizeof(char*)*nrEc(root));
	int j = 0;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (cautare(j, sir, curr->e->categorie) == 0) {
				sir[j] = curr->e->categorie;
				j++;
			}
			curr = curr->dr;
		}
	}
	return j;
}

int* nrEchipamenteVector(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	char** sir = (char**)malloc(sizeof(char*)*nrEchipamente(root));
	int j = 0;
	int* vector=(int*)malloc(sizeof(int)*nrEchipamente(root));
	int k = 0;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (cautare(j, sir, curr->e->categorie) == 0) {
				sir[j] = curr->e->categorie;
				j++;
			}
			curr = curr->dr;
		}
	}
	int nr;
	for (int i = 0; i < j; i++) {
		NodArb* t = root;
		nr = 0;
		while (!stack.empty() || t != NULL)
		{
			if (t != NULL)
			{
				stack.push(t);
				t = t->st;
			}
			else {
				t = stack.top();
				stack.pop();
				if (strcmp(sir[i], t->e->categorie) == 0)
					nr++;
					t = t->dr;
			}
		}
		vector[k] = nr;
		k++;
	}
	return vector;
}

struct ListaDublu
{
	ListaDublu *next;
	ListaDublu *prev;
	Echipament* info;
};

void insertToListaDubla(NodArb* root, ListaDublu **head_ref,const char* data)
{
	stack<NodArb*> stack;
	NodArb* curr = root;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (strcmp(curr->e->data, data) == 0) {
				ListaDublu *new_node = (ListaDublu *)malloc(sizeof(ListaDublu));
				new_node->info = curr->e;
				new_node->next = (*head_ref);
				new_node->prev = NULL;
				if ((*head_ref) != NULL)
					(*head_ref)->prev = new_node;
				(*head_ref) = new_node;
			}		
			curr = curr->dr;
		}
	}
}

void printLD(ListaDublu *node)
{
	ListaDublu *last;
	if (node == NULL)
	{
		printf("\nList is empty\n");
		return;
	}
	while (node != NULL)
	{
		displayEchipament(node->info);
		last = node;
		node = node->next;
	}
}


void _deleteTree(NodArb* node)
{
	if (node->st)
	{
		_deleteTree(node->st);
		free(node->st);
	}
	if (node->dr)
	{
		_deleteTree(node->dr);
		free(node->dr);
	}
}

void deleteTree(NodArb** node_ref)
{
	if (*node_ref)
	{
		_deleteTree(*node_ref);
		free(*node_ref);
	}
}

void deleteAllNodes(ListaDublu* head) {
	ListaDublu* temp = (ListaDublu*)malloc(sizeof(ListaDublu));
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}



void main() {
	Echipament* e=NULL;
	NodArb* rad = NULL;
	FILE* f = fopen("file.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			e = (Echipament*)malloc(sizeof(Echipament));
			token = strtok(buffer, sep);
			e->cod_produs = atoi(token);
			token = strtok(NULL, sep);
			e->pret = atoi(token);
			token = strtok(NULL, sep);
			e->categorie = (char*)malloc(strlen(token) + 1);
			strcpy(e->categorie, token);
			token = strtok(NULL, sep);
			e->denumire = (char*)malloc(strlen(token) + 1);
			strcpy(e->denumire, token);
			token = strtok(NULL, sep);
			e->cantitate = atoi(token);
			token = strtok(NULL, sep);
			e->data = (char*)malloc(strlen(token) + 1);
			strcpy(e->data, token);
			rad = inserareArb(rad, e);
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu a fost deschis");
	}
	//ex1
	displayArb(rad);
	//ex2
	int pret = determinareCodEchipament(rad, "alergare");
	printf("%d\n", pret);
	//ex3
	Echipament* ec=extract(&rad);
	printf("Nodurile dupa extragere sunt:\n");
	displayArb(rad);
	printf("Nodul extras este:\n");
	displayEchipament(ec);
	//ex4
	int* vector = (int*)malloc(sizeof(int)*nrEchipamente(rad));
	vector = nrEchipamenteVector(rad);
	for (int i = 0; i < nrEchipamente(rad); i++) {
		printf("%d ", vector[i]);
	}
	//ex5
	printf("\n");
	ListaDublu*listaD = NULL;
	insertToListaDubla(rad, &listaD, "12/05/2021");
	printLD(listaD);
	//ex5
	deleteTree(&rad);
	deleteAllNodes(listaD);
	free(vector);
}