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

void main() {
	Multime* m = NULL;
	Nod* lista = NULL;

	int numar=123,k=0;
	printf("Tastati elementele multimi 1:\n");
	for (int i = 0; numar!=0; i++) {
		m = (Multime*)malloc(sizeof(Multime));
		scanf("%d", &numar);
		m->data = numar;
		k++;
		push(&lista, m);
	}
	printf("\nAfisare elemente:\n\n");
	parcurgereLista(lista);
	printf("\nAfisare numar de elemente:%d",k);
}