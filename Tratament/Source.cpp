#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>
#include <stack>
using namespace std;
#define DIM_BUFFER 300

struct Tratament {
	int idClient;
	char* numeClient;
	int bugetClient;
	int durataProceduri;
	int costProceduri;
};

struct NodArb {
	Tratament info;
	NodArb* left;
	NodArb* right;
};


void displayTratament(Tratament t) {
	printf("Id client:%d\nNume client:%s\nBuget client:%d\nDurata proceduri:%d\nCost proceduri:%d\n\n", 
		t.idClient,t.numeClient,t.bugetClient,t.durataProceduri,t.costProceduri);
}

NodArb* newNode(Tratament t)
{
	NodArb* temp = (NodArb*)malloc(sizeof(NodArb));
	temp->info = t;
	temp->left = temp->right = NULL;
	return temp;
}

NodArb* inserare(NodArb* root, Tratament t) {
	if (root) {
		if (t.idClient < root->info.idClient) {
			root->left = inserare(root->left, t);
		}
		else {
			root->right = inserare(root->right, t);
		}
		return root;
	}
	else {
		root = newNode(t);
	}
}

void displayTree(NodArb* root) {
	if (root) {
		displayTratament(root->info);
		displayTree(root->left);
		displayTree(root->right);
	}
}

int nrTratamente(NodArb* rad) {
	int nr = 0;
	stack<NodArb*> stack;
	NodArb* curr = rad;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->left;
		}
		else {
			curr = stack.top();
			nr++;
			stack.pop();
			curr = curr->right;
		}
	}
	return nr;
}

int* calculeazaSuma(NodArb* rad) {
	stack<NodArb*> stack;
	NodArb* curr = rad;
	int* suma = (int*)malloc(sizeof(int)*nrTratamente(rad));
	int j = 0;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->left;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (curr->info.bugetClient > curr->info.costProceduri) {
				suma[j] = (curr->info.bugetClient - curr->info.costProceduri);
				j++;
			}
			else {
					suma[j] = (curr->info.costProceduri - curr->info.bugetClient);
					j++;
			}
			curr = curr->right;
		}
	}
	return suma;
}

void storeBSTNodes(NodArb* root, vector<struct NodArb*> &nodes)
{
	if (root == NULL)
		return;

	storeBSTNodes(root->left, nodes);
	nodes.push_back(root);
	storeBSTNodes(root->right, nodes);
}

NodArb* buildTreeUtil(vector<NodArb*> &nodes, int start,
	int end)
{
	// base case 
	if (start > end)
		return NULL;
	int mid = (start + end) / 2;
	NodArb*root = nodes[mid];

	root->left = buildTreeUtil(nodes, start, mid - 1);
	root->right = buildTreeUtil(nodes, mid + 1, end);

	return root;
}

NodArb* buildTree(NodArb* root)
{

	vector<NodArb*> nodes;
	storeBSTNodes(root, nodes);
	int n = nodes.size();
	return buildTreeUtil(nodes, 0, n - 1);
}

struct ListaSimpla {
	Tratament info;
	ListaSimpla* next;
};


void insertLeafNodesToListaSimpla(NodArb* rad, ListaSimpla** head_ref) {
	if (rad) {
		if (rad->right == NULL && rad->left == NULL) {
			ListaSimpla* new_node = (ListaSimpla*)malloc(sizeof(ListaSimpla));
			new_node->info = rad->info;
			new_node->next = (*head_ref);
			(*head_ref) = new_node;
		}
		insertLeafNodesToListaSimpla(rad->left, head_ref);
		insertLeafNodesToListaSimpla(rad->right, head_ref);
	}
}

void printList(ListaSimpla* n)
{
	ListaSimpla* temp = n;
	while (temp != NULL) {
		displayTratament(temp->info);
		temp = temp->next;
	}
}

int nrClientiCuDatorie(NodArb* rad) {
	stack<NodArb*> stack;
	NodArb* curr = rad;
	int nr = 0;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->left;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (curr->info.bugetClient < curr->info.costProceduri) {
				nr++;
				/*printf("%s\n", curr->info.numeClient);*/
			}
			curr = curr->right;
		}
	}
	return nr;
}


void main() {
	Tratament t;
	NodArb* rad = NULL;
	FILE* f = fopen("tratamente.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			t.idClient = atoi(token);
			token = strtok(NULL, sep);
			t.numeClient = (char*)malloc(strlen(token) + 1);
			strcpy(t.numeClient, token);
			token = strtok(NULL, sep);
			t.bugetClient = atoi(token);
			token = strtok(NULL, sep);
			t.durataProceduri = atoi(token);
			token = strtok(NULL, sep);
			t.costProceduri = atoi(token);
			/*int e = 0;*/
			rad = inserare(rad, t);//ex2
			/*if (e) {
				free(im.numeStrada);
				free(im.numarLocatari);
			}*/
		}
	}
	rad = buildTree(rad);
	displayTree(rad);
	printf("\n\n\n");
	//ex4
	/*int* suma = (int*)malloc(sizeof(int)*nrTratamente(rad));
	suma = calculeazaSuma(rad);
	for (int i = 0; i < nrTratamente(rad); i++) {
		printf("%d ", suma[i]);
	}*/

	//ex5
	/*ListaSimpla* ls = NULL;
	insertLeafNodesToListaSimpla(rad, &ls);
	printList(ls);*/

	//ex6
	/*printf("Numarul clientilor care au datorie catre centru este:%d", nrClientiCuDatorie(rad));*/
}




