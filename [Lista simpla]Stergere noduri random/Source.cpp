#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
// Linked List LinkNode
struct LinkNode
{
	int data;
	struct LinkNode *next;
};
// Singly linked list 
struct SingleLL
{
	struct LinkNode *head;
	struct LinkNode *tail;
};
// Returns the new linked list
struct SingleLL *newLinkedList()
{
	// Create memory of head and tail Nodes
	struct SingleLL *sll =
		(struct SingleLL *) malloc(sizeof(struct SingleLL));
	if (sll == NULL)
	{
		printf("Memory overflow\n");
	}
	else
	{
		sll->head = NULL;
	}
	return sll;
}
// Handles the request of adding new node in linked list
void addNode(struct SingleLL *sll, int data)
{
	// Create dynamic node
	struct LinkNode *node =
		(struct LinkNode *) malloc(sizeof(struct LinkNode));
	if (node == NULL)
	{
		printf("Memory overflow to Create LinkNode\n");
		return;
	}
	else
	{
		// Set initial node value
		node->data = data;
		node->next = NULL;
	}
	if (sll->head == NULL)
	{
		sll->head = node;
	}
	else
	{
		sll->tail->next = node;
	}
	sll->tail = node;
}
// Display linked list element
void display(struct LinkNode *node)
{
	if (node == NULL)
	{
		printf("Lista este goala");
		return;
	}
	struct LinkNode *temp = node;
	// iterating linked list elements
	while (temp != NULL)
	{
		printf(" %d ", temp->data);
		// Visit to next node
		temp = temp->next;
	}
	printf(" NULL\n");
}
void randomNode(struct LinkNode *node)
{
	struct LinkNode * temp = node;
	struct LinkNode * result = node;

	int n = 2;
	while (temp != NULL)
	{
		if (rand() % n == 0)
		{
			// Get new resultant node
			result = temp;
		}
		// visit to next node
		temp = temp->next;

		// increase the value of n by one
		n++;
	}

	if (result == NULL)
	{
		printf("\n None \n");

	}
	else
	{
		printf(" Result : %d \n", result->data);
	}
}
int deleteRandomNodes(struct LinkNode *node)
{
	struct LinkNode * temp = node;
	struct LinkNode * result = node;
	int n = 2;
	while (temp != NULL)
	{
		if (rand() % n == 0)
		{
			// Get new resultant node
			result = temp;
		}
		// visit to next node
		temp = temp->next;

		// increase the value of n by one
		n++;
	}
	if (result == NULL)
	{
		printf("\n None \n");

	}
	else
	{
		printf(" Result : %d \n", result->data);
		return result->data;
	}
}
LinkNode* removeElements(LinkNode* head, int val) {
	if (!head) {
		return NULL;
	}
	LinkNode* post = removeElements(head->next, val);
	if (head->data != val) {
		head->next = post;
		return head;
	}
	delete head;
	return post;
}
int main(int argc, char const *argv[])
{
	srand(time(NULL));

	struct SingleLL *sll1 = newLinkedList();
	struct SingleLL *sll2 = newLinkedList();
	// First linked list
	//  5 → 2 → -2 → 1 → 3 → 6 → NULL
	//int n, persoana;
	//printf("Introduceti numarul de persoane:");
	//scanf("%d", &n);
	//for (int i = 0; i < n; i++) {
	//	printf("Persoana %d:", i);
	//	scanf("%d", &persoana);
	//	addNode(sll1,persoana);
	//}
	addNode(sll1, 5);
	addNode(sll1, 2);
	addNode(sll1, -2);
	addNode(sll1, 1);
	addNode(sll1, 3);
	addNode(sll1, 6);
	// Second linked list
	//  -1 → 7 → 5 → 8 → 9 → -9 → 10 → NULL
	addNode(sll2, -1);
	addNode(sll2, 7);
	addNode(sll2, 5);
	addNode(sll2, 8);
	addNode(sll2, 9);
	addNode(sll2, -9);
	addNode(sll2, 10);
	// Test in first LL
	display(sll1->head);
	sll1->head= removeElements(sll1->head,10);
	//randomNode(sll1->head);
	//randomNode(sll1->head);
	//randomNode(sll1->head);
	// Test in second LL
	//display(sll2->head);
	//randomNode(sll2->head);
	//randomNode(sll2->head);
	randomNode(sll1->head);
	printf("Nodurile sterse random sunt:\n");
	int value;
	value = deleteRandomNodes(sll1->head);
	sll1->head=removeElements(sll1->head, value);

	value = deleteRandomNodes(sll1->head);
	sll1->head = removeElements(sll1->head, value);

	value = deleteRandomNodes(sll1->head);
	sll1->head = removeElements(sll1->head, value);

	value = deleteRandomNodes(sll1->head);
	sll1->head = removeElements(sll1->head, value);

	value = deleteRandomNodes(sll1->head);
	sll1->head = removeElements(sll1->head, value);

	value = deleteRandomNodes(sll1->head);
	sll1->head = removeElements(sll1->head, value);
	display(sll1->head);

	return 0;
}