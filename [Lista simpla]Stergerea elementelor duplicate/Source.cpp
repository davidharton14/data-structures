#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300
struct Sir {
	int data;
};

struct Nod {
	Sir* info;
	Nod* next;
};

void afisareSir(Sir* m) {
	printf("%d\n", m->data);
}

void push(Nod** head_ref, Sir* info)
{
	Nod* new_node = (Nod*)malloc(sizeof(Nod));
	new_node->info = info;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;

}

void parcurgereLista(Nod* cap) {
	Nod* temp = cap;
	while (temp) {
		afisareSir(temp->info);
		temp = temp->next;
	}
}
void deleteNode(struct Nod **head, int key)
{
	//temp is used to freeing the memory
	struct Nod *temp;


	//key found on the head node.
	//move to head node to the next and free the head.
	if ((*head)->info->data == key)
	{
		temp = *head;    //backup the head to free its memory
		*head = (*head)->next;
		free(temp);
	}


}
void deleteLista(Nod**head_ref,int* arr,int n)
{
	Nod*current = *head_ref;
	Nod*temp;
	Nod*next = NULL;
	for (int i = 0; i < n; i++) {
		
		
		
		
	}
	
	//*head_ref = NULL;
}
int cautareElement(int* sir, int j, int numar) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (sir[i]==numar) {
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

int numarElemente(Nod* cap) {
	Nod* temp = cap;
	int* arr = NULL;
	int k = 0;
	while (temp) {
		k++;
		temp = temp->next;
	}
	arr = (int*)malloc(sizeof(int)*k);
	int j = 0;
	temp = cap;
	while (temp) {
		if (cautareElement(arr, j, temp->info->data) == 0) {
			arr[j] = temp->info->data;
			j++;
		}
		temp = temp->next;
	}
	return j;
}
void removeDuplicates(struct Nod* start)
{
	struct Nod *ptr1, *ptr2, *dup;
	ptr1 = start;

	/* Pick elements one by one */
	while (ptr1 != NULL && ptr1->next != NULL) {
		ptr2 = ptr1;

		/* Compare the picked element with rest
		   of the elements */
		while (ptr2->next != NULL) {
			/* If duplicate then delete it */
			if (ptr1->info->data == ptr2->next->info->data) {
				/* sequence of steps is important here */
				dup = ptr2->next;
				ptr2->next = ptr2->next->next;
				delete (dup);
			}
			else /* This is tricky */
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

void main() {
	Sir* s = NULL;
	Nod* lista = NULL;
	int numar,n;
	printf("n=");
	scanf("%d", &n);
	printf("Tastati elementele:\n");
	for (int i = 0; i<n; i++) {
		s = (Sir*)malloc(sizeof(Sir));
		scanf("%d", &numar);
		s->data = numar;
		push(&lista, s);
	}
	printf("\nAfisare elemente:\n\n");
	parcurgereLista(lista);
	printf("\nAfisare elemente dupa stergerea duplicatelor\n\n");
	removeDuplicates(lista);
	parcurgereLista(lista);
	printf("----------------\n");
	printf("%d", numarElemente(lista));
}