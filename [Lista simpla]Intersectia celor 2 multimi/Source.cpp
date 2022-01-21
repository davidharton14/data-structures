#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300
struct Multime {
	int data;
};

struct Nod {
	Multime* info;
	Nod* next;
};

void afisareMultime(Multime* m) {
	printf("%d\n", m->data);
}

void push(Nod** head_ref, Multime* info)
{
	Nod* new_node = (Nod*)malloc(sizeof(Nod));
	new_node->info = info;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;

}

void parcurgereLista(Nod* cap) {
	Nod* temp = cap;
	while (temp) {
		afisareMultime(temp->info);
		temp = temp->next;
	}
}
Nod* parcurgere(Nod*lista1,Nod*lista2) {
	Nod* temp = lista1;
	Nod* t = lista2;
	Multime* info = NULL;
	Nod* lista3=NULL;
	while (temp) {
		Nod* t = lista2;
		while (t) {
			if (temp->info->data == t->info->data) {
				info = (Multime*)malloc(sizeof(Multime));
				info->data = temp->info->data;
				push(&lista3, info);
			}
			t = t->next;
		}
		temp = temp->next;
	}
	return lista3;
}
void main() {
	Multime* mu=NULL;
	Nod* lista1 = NULL;
	Nod* lista2 = NULL;
	Nod* lista3 = NULL;
	int n,m,numar;
	printf("n=");
	scanf("%d", &n);
	printf("m=");
	scanf("%d", &m);
	printf("Tastati elementele multimi 1:\n");
	for (int i = 0; i < n; i++) {
		mu = (Multime*)malloc(sizeof(Multime));
		scanf("%d", &numar);
		mu->data = numar;
		push(&lista1, mu);
	}
	printf("Tastati elementele multimi 2:\n");
	for (int i = 0; i < m; i++) {
		mu = (Multime*)malloc(sizeof(Multime));
		scanf("%d", &numar);
		mu->data = numar;
		push(&lista2, mu);
	}
	printf("\nAfisare prima multime:\n\n");
    parcurgereLista(lista1);
	printf("\nAfisare a doua multime:\n\n");
	parcurgereLista(lista2);
	printf("\nAfisare a treia multime:\n\n");
	lista3 = parcurgere(lista1, lista2);
	parcurgereLista(lista3);
}