#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	struct node * preptr;
	struct node * nextptr;
}*stnode, *ennode;


void DlListcreation(int n)
{
	int i, num;
	struct node *fnNode;

	if (n >= 1)
	{
		stnode = (struct node *)malloc(sizeof(struct node));

		if (stnode != NULL)
		{
			printf("Input data for node 1 : "); // assigning data in the first node
			scanf("%d", &num);

			stnode->num = num;
			stnode->preptr = NULL;
			stnode->nextptr = NULL;
			ennode = stnode;
			for (i = 2; i <= n; i++)
			{
				fnNode = (struct node *)malloc(sizeof(struct node));
				if (fnNode != NULL)
				{
					printf("Input data for node %d : ", i);
					scanf("%d", &num);
					fnNode->num = num;
					fnNode->preptr = ennode;    // new node is linking with the previous node
					fnNode->nextptr = NULL;     // set next address of fnnode is NULL
					ennode->nextptr = fnNode;   // previous node is linking with the new node
					ennode = fnNode;            // assign new node as last node
				}
				else
				{
					printf("Memory can not be allocated.");
					break;
				}
			}
		}
		else
		{
			printf("Memory can not be allocated.");
		}
	}
}
void DlLinsertNodeAtBeginning(int num)
{
	struct node * newnode;
	if (stnode == NULL)
	{
		printf("No data found in the list!\n\n");
	}
	else
	{
		newnode = (struct node *)malloc(sizeof(struct node));
		newnode->num = num;
		newnode->nextptr = stnode;  // next address of new node is linking with starting node
		newnode->preptr = NULL;     // set previous address field of new node is NULL
		stnode->preptr = newnode;   // previous address of starting node is linking with new node
		stnode = newnode;           // set the new node as starting node
	}
}
void DlLinsertNodeAtEnd(int num)
{
	struct node * newnode;

	if (ennode == NULL)
	{
		printf("No data found in the list!\n\n");
	}
	else
	{
		newnode = (struct node *)malloc(sizeof(struct node));
		newnode->num = num;
		newnode->nextptr = NULL;        // set next address field of new node  is NULL
		newnode->preptr = ennode;       // previous address of new node is linking with ending node
		ennode->nextptr = newnode;      // next address of ending node is linking with new node
		ennode = newnode;               // set the new node as ending node  
	}
}
void DlLinsertNodeAtAny(int num, int pos)
{
	int i;
	struct node * newnode, *tmp;
	if (ennode == NULL)
	{
		printf("No data found in the list!\n\n");
	}
	else
	{
		tmp = stnode;
		i = 1;
		while (i < pos - 1 && tmp != NULL)
		{
			tmp = tmp->nextptr;
			i++;
		}
		if (pos == 1)
		{
			DlLinsertNodeAtBeginning(num);
		}
		else if (tmp == ennode)
		{
			DlLinsertNodeAtEnd(num);
		}
		else if (tmp != NULL)
		{
			newnode = (struct node *)malloc(sizeof(struct node));
			newnode->num = num;
			//next address of new node is linking with the next address of temp node            
			newnode->nextptr = tmp->nextptr;
			// previous address of new node is linking with the tmp node            
			newnode->preptr = tmp;
			if (tmp->nextptr != NULL)
			{
				tmp->nextptr->preptr = newnode; // n+1th node is linking with new node
			}
			tmp->nextptr = newnode; // n-1th node is linking with new node 
		}
		else
		{
			printf("The position you entered, is invalid.\n\n");
		}
	}
}
void displayDlList(int m)
{
	struct node * tmp;
	int n = 1;
	if (stnode == NULL)
	{
		printf("No data found in the List yet.\n\n");
	}
	else
	{
		tmp = stnode;
		if (m == 1)
		{
			printf("\nData entered in the list are :\n\n");
		}
		else
		{
			printf("\nAfter deletion the new list are :\n\n");
		}
		while (tmp != NULL)
		{
			printf("node %d : %d\n", n, tmp->num);
			n++;
			tmp = tmp->nextptr; // current pointer moves to the next node
		}
	}
}
void DlListDeleteFirstNode()
{
	struct node * NodeToDel;
	if (stnode == NULL)
	{
		printf("Delete is not possible. No data in the list.\n\n");
	}
	else
	{
		NodeToDel = stnode;
		stnode = stnode->nextptr;   // move the next address of starting node to 2 node
		stnode->preptr = NULL;      // set previous address of staring node is NULL
		free(NodeToDel);            // delete the first node from memory
	}
}
void DlListDeleteLastNode()
{
	struct node * NodeToDel;

	if (ennode == NULL)
	{
		printf("Delete is not possible. No data in the list.\n\n");
	}
	else
	{
		NodeToDel = ennode;
		ennode = ennode->preptr;    // move the previous address of the last node to 2nd last node
		ennode->nextptr = NULL;     // set the next address of last node to NULL
		free(NodeToDel);            // delete the last node
	}
}
void deleteAllNodes() {
	node* temp = new node();
	while (stnode != NULL) {
		temp = stnode;
		stnode = stnode->nextptr;
		free(temp);
	}
	printf("All nodes are deleted successfully.\n\n");
}
void deleteNodes() {
	node* temp = new node();
	while (stnode != NULL) {
		temp = stnode;
		stnode = stnode->nextptr;
		free(temp);
	}
}
void verifyDoublyList() {
	if (stnode == NULL)
	{
		printf("No data found in the list!\n\n");
	}
	else {
		printf("There are data in the list!\n\n");
	}
}
void DlListDeleteAnyNode(int pos)
{
	struct node *curNode;
	int i;

	curNode = stnode;
	for (i = 1; i < pos && curNode != NULL; i++)
	{
		curNode = curNode->nextptr;
	}

	if (pos == 1)
	{
		deleteNodes();
	}
	else if (curNode == ennode)
	{
		DlListDeleteLastNode();
	}
	else if (curNode != NULL)
	{
		curNode->preptr->nextptr = curNode->nextptr;
		curNode->nextptr->preptr = curNode->preptr;

		free(curNode); //Delete the n node
	}
	else
	{
		printf("The given position is invalid!\n\n");
	}
}
void main() {
	int n, num1, a, insPlc;
	stnode = NULL;
	ennode = NULL;
	printf("\n\n Doubly Linked List : Insert new node at any position in a doubly linked list :\n");
	printf("-----------------------------------------------------------------------------------\n");
	int choice;
	do
	{
		printf("1. Inserare elemente\n\n2. Inserare element la o pozitie data\n\n3. Stergere element cu o cheie data\n\n4. Verificare daca lista este goala\n\n5. Display\n\n6. Sterge toate nodurile\n\n7. Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Input the number of nodes : ");
			scanf("%d", &n);
			DlListcreation(n);
			break;
		case 2:
			printf("Input the position ( 1 to %d ) to insert a new node : ", n + 1);
			scanf("%d", &insPlc);
			printf("Input data for the position %d : ", insPlc);
			scanf("%d", &num1);
			DlLinsertNodeAtAny(num1, insPlc);
			break;
		case 3:
			printf("Input the position ( 1 to %d ) to delete a node : ", n);
			scanf("%d", &insPlc);
			if (insPlc<1 || insPlc>n)
			{
				printf("\nInvalid position. Try again.\n ");
			}
			if (insPlc >= 1 && insPlc <= n)
			{
				DlListDeleteAnyNode(insPlc);
				break;
			}
		case 4:
			verifyDoublyList();
			break;
		case 5:
			a = 1;
			displayDlList(a);
			break;
		case 6:
			deleteAllNodes();
			break;
		case 7:
			exit(0);
			break;
		default:
			printf("Sorry, invalid choice!\n");
			break;
			}
		} while (choice != 7);
	}

