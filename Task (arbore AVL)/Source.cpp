#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<iostream>
#include <stack>
using namespace std;
#define DIM_BUFFER 300

enum Stare {
	NOU,
	DESCHIS,
	IN_LUCRU,
	REZOLVAT,
	INCHIS
};

Stare convertToStare(const string& str)
{
	if (str == "NOU") return NOU;
	else if (str == "DESCHIS") return DESCHIS;
	else if (str == "IN_LUCRU") return IN_LUCRU;
	else if (str == "REZOLVAT") return REZOLVAT;
	else if (str == "INCHIS") return INCHIS;
}
struct Task {
	int cod;
	char* data;
	char* numeAngajat;
	int nivel;
	Stare s;
};

void afisareTask(Task t) {
	printf("Cod:%d\nData:%s\nNume:%s\nNivel de complexitate:%d\nStare:%d\n\n", t.cod, t.data, t.numeAngajat, t.nivel, t.s);
}

struct NodArb {
	Task info;
	NodArb* left;
	NodArb* right;
};

NodArb* newNode(Task t)
{
	NodArb* temp = (NodArb*)malloc(sizeof(NodArb));
	temp->info = t;
	temp->left = temp->right = NULL;
	return temp;
}

int inaltimeArbore(NodArb* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->left);
		int inaltimeDR = inaltimeArbore(rad->right);
		return 1 + (inaltimeST > inaltimeDR ? inaltimeST : inaltimeDR);
	}
	else {
		return 0;
	}
}

int calculareGradEchilibru(NodArb* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->left);
		int inaltimeDR = inaltimeArbore(rad->right);
		return inaltimeST - inaltimeDR;
	}
	else {
		return 0;
	}
}

NodArb* rotireLaStanga(NodArb* root) {
	if (root) {
		NodArb* aux = root->right;
		root->right = aux->left;
		aux->left = root;
		return aux;
	}
	else {
		return root;
	}
}
NodArb* rotireLaDreapta(NodArb* root) {
	if (root) {
		NodArb* aux = root->left;
		root->right = aux->right;
		aux->right = root;
		return aux;
	}
	else {
		return root;
	}
}

NodArb* inserare(NodArb* root, Task ta) {
	if (root) {
		if (ta.cod < root->info.cod) {
			root->left = inserare(root->left, ta);
		}
		else {
			root->right = inserare(root->right, ta);
		}
		/*if (calculareGradEchilibru(root) == 2) {
			if (calculareGradEchilibru(root->left) != 1) {
				root->left = rotireLaStanga(root->left);
			}
			root = rotireLaDreapta(root);
		}
		if (calculareGradEchilibru(root) == -2) {
			if (calculareGradEchilibru(root->right) != -1) {
				root->right = rotireLaDreapta(root->right);
			}
			root = rotireLaStanga(root);
		}*/
		return root;
	}
	else {
		root = newNode(ta);
	}
}

void displayTree(NodArb* root) {
	if (root) {
		afisareTask(root->info);
		displayTree(root->left);
		displayTree(root->right);
	}
}

void deleteTree(NodArb*root) {
	if (root == NULL)
		return;
	/* Delete Left sub-tree */
	deleteTree(root->left);
	/* Delete right sub-tree */
	deleteTree(root->right);
	free(root);
	return;
}

void displayTree1(NodArb* root) {
	if (root) {
		displayTree1(root->left);
		afisareTask(root->info);
		displayTree1(root->right);
	}
}



void setChild(NodArb* node, bool toLeft, NodArb* child) {
	// Assign child node to the indicated direction: left or right
	if (toLeft) {
		node->left = child;
	}
	else {
		node->right = child;
	}
}

NodArb* splitTree(NodArb* root, int k) {
	NodArb* root2 = NULL;
	NodArb* parent1 = NULL;
	NodArb* parent2 = NULL;
	// Determine at which side of the root we will travel
	bool toLeft = root != NULL && k < root->info.cod;

	while (root != NULL) {
		while (root != NULL && (k <root->info.cod) == toLeft) {
			parent1 = root;
			root = toLeft ? root->left : root->right;
		}
		setChild(parent1, toLeft, NULL); // Cut out the edge. root is now detached
		toLeft = !toLeft; // toggle direction
		if (root2 == NULL) {
			root2 = root; // This is the root of the other tree.
		}
		else if (parent2 != NULL) {
			setChild(parent2, toLeft, root); // re-attach the detached subtree
		}
		parent2 = parent1;
		parent1 = NULL;
	}
	return root2;
}

void storeBSTNodes(NodArb* root, vector<struct NodArb*> &nodes)
{
	// Base case 
	if (root == NULL)
		return;

	// Store nodes in Inorder (which is sorted 
	// order for BST) 
	storeBSTNodes(root->left, nodes);
	nodes.push_back(root);
	storeBSTNodes(root->right, nodes);
}

/* Recursive function to construct binary tree */
NodArb* buildTreeUtil(vector<NodArb*> &nodes, int start,
	int end)
{
	// base case 
	if (start > end)
		return NULL;

	/* Get the middle element and make it root */
	int mid = (start + end) / 2;
	NodArb*root = nodes[mid];

	/* Using index in Inorder traversal, construct
	   left and right subtress */
	root->left = buildTreeUtil(nodes, start, mid - 1);
	root->right = buildTreeUtil(nodes, mid + 1, end);

	return root;
}

// This functions converts an unbalanced BST to 
// a balanced BST 
NodArb* buildTree(NodArb* root)
{
	// Store nodes of given BST in sorted order 
	vector<NodArb*> nodes;
	storeBSTNodes(root, nodes);

	// Constucts BST from nodes[] 
	int n = nodes.size();
	return buildTreeUtil(nodes, 0, n - 1);
}

NodArb* displayLeafNodes(NodArb* radacina) {
	if (radacina == NULL)
		return NULL;
	if (radacina->right == NULL && radacina->left == NULL) {
		displayTree(radacina);
		free(radacina);
		return NULL;
	}
	radacina->left = displayLeafNodes(radacina->left);
	radacina->right = displayLeafNodes(radacina->right);
	return radacina;
}

struct ListaDublu {
	ListaDublu*next;
	ListaDublu*prev;
	Task info;
};


void insertToListaDubla(NodArb* rad, ListaDublu** head_ref,int status)
{
	if (rad) {
		if (rad->info.s == status) {
			ListaDublu*new_node = (ListaDublu*)malloc(sizeof(ListaDublu));
			new_node->info = rad->info;
			new_node->next = (*head_ref);
			new_node->prev = NULL;
			if ((*head_ref) != NULL)
				(*head_ref)->prev = new_node;
			(*head_ref) = new_node;
		}
		insertToListaDubla(rad->left, head_ref, status);
		insertToListaDubla(rad->right,head_ref, status);
	}



	/*stack<NodArb*> stack;
	NodArb* curr = rad;
	ListaDublu* new_node = NULL;
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
			if (curr->info.s == status) {
				new_node = (ListaDublu*)malloc(sizeof(ListaDublu));
				new_node->info = curr->info;
				new_node->next = (*head_ref);
				new_node->prev = NULL;
				if ((*head_ref) != NULL)
					(*head_ref)->prev = new_node;
				(*head_ref) = new_node;
			}
			curr = curr->right;
		}
	}*/
}

void printLD(ListaDublu* node)
{
	ListaDublu* last;
	/*printf("\nTraversal in forward direction \n");*/
	
	if (node == NULL)
	{
		printf("\nList is empty\n");
		return;
	}
	while (node != NULL) {
		afisareTask(node->info);
		last = node;
		node = node->next;
	}
	/*printf("\nTraversal in reverse direction \n");
	while (last != NULL) {
		displayGradinita(last->info);
		last = last->prev;
	}*/
}


int nrElements(ListaDublu* node, int nivel) {
	ListaDublu* last;
	int nr = 0;
	while (node != NULL) {
		if (node->info.nivel == nivel) {
			nr++;
		}
		last = node;
		node = node->next;
	}
	return nr;
}

int* insertToVector(ListaDublu* node, int nivel) {
	ListaDublu* last;
	int* vector = (int*)malloc(sizeof(int)*nrElements(node, nivel));
	int i = 0;
	while (node != NULL) {
		if (node->info.nivel == nivel) {
			vector[i] = node->info.cod;
			i++;
		}
		last = node;
		node = node->next;
	}
	return vector;
}

void deleteLD(ListaDublu** head_ref) {

	ListaDublu* current = *head_ref;
	ListaDublu* node = *head_ref;
	ListaDublu* next = NULL;
	ListaDublu* prev = NULL;
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




void main() {
	Task t;
	NodArb* rad = NULL;
	FILE* f = fopen("tasks.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			t.cod = atoi(token);
			token = strtok(NULL, sep);
			t.data = (char*)malloc(strlen(token) + 1);
			strcpy(t.data, token);
			token = strtok(NULL, sep);
			t.numeAngajat = (char*)malloc(strlen(token) + 1);
			strcpy(t.numeAngajat, token);
			token = strtok(NULL, sep);
			t.nivel = atoi(token);
			token = strtok(NULL, sep);
			t.s = convertToStare(token);
			/*int e = 0;*/
			rad = inserare(rad, t);
		/*	if (e) {
				free(t.data);
				free(t.numeAngajat);
			}*/
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu a fost deschis");
	}
	rad = buildTree(rad);
	/*displayTree(rad);
	printf("\n\n\n");
	NodArb* node = NULL;
	node=splitTree(rad,7);
	displayTree1(rad)*/;
	/*printf("Inaltimea arborelui este %d\n", inaltimeArbore(rad));
	rad = displayLeafNodes(rad);*/
	/*printf("-----------\n");*/
	/*displayTree1(node);*/
	/*printf("Inaltimea arborelui este %d\n", inaltimeArbore(node));
	node = displayLeafNodes(node);*/
	ListaDublu* lista = NULL;
	insertToListaDubla(rad, &lista,1);
	/*deleteLD(&lista);*/
	/*printLD(lista);*/
	//int* vec = (int*)malloc(sizeof(int)*nrElements(lista, 3));
	///*printf("%d", nrElements(lista, 3));*/
	/*vec = insertToVector(lista, 3);*/
	/*free(vec);*/
	/*for (int i = 0; i < nrElements(lista, 3); i++) {
		printf("%d ", vec[i]);
	}*/
	/*deleteTree(rad);*/
}


