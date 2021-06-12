#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <stack>
using namespace std;
#define SIZE_BUFFER 100


struct Exam
{
	int key;
	int sem;
	char* materie;
	unsigned int nrCredite;
	int nrStudenti;
	int* note;
};


struct BSTNode
{
	Exam* data;
	BSTNode* left;
	BSTNode* right;
	//BSTNode* next;
};
struct BinaryTree
{
	BSTNode* root = NULL;
};
Exam* createExam(int key,int sem,char* materie, unsigned int nrCredite, int nrStudenti, int* note)
{
	Exam* retValue = NULL;
	retValue = (Exam*)malloc(sizeof(Exam));
	retValue->key = key;
	retValue->sem = sem;
	retValue->materie = (char*)malloc(strlen(materie) + 1);
	strcpy(retValue->materie, materie);
	retValue->key = key;
	retValue->nrCredite = nrCredite;
	retValue->nrStudenti = nrStudenti;
	retValue->note = (int*)malloc(sizeof(int)*retValue->nrStudenti);
	for (int i = 0; i < retValue->nrStudenti; i++) {
		retValue->note[i] = note[i];
	}
	return retValue;
}
BSTNode* createNode(Exam* e)
{
		BSTNode* temp = (BSTNode*)malloc(sizeof(BSTNode));
		temp->data = e;
		temp->left = NULL;
		temp->right = NULL;
		return temp;

}

BSTNode* createNode2(Exam* e,int credite)
{
	BSTNode* temp = (BSTNode*)malloc(sizeof(BSTNode));
	if (e->nrCredite == credite) {
		temp->data = e;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}
	else
		return temp;
}
BSTNode* insertNode1(BSTNode* root, Exam* e)
{
	if (root == NULL)
		root = createNode(e);
	else {
		if (e->key < root->data->key) {
			root->left = insertNode1(root->left, e);
		}
		else if (e->key > root->data->key) {
			root->right = insertNode1(root->right, e);
		}
		return root;
	}	
}
//BSTNode* insertNode2(BSTNode* root, Exam* e)
//{
//	if (root == NULL)
//		root = createNode(e);
//	else  {
//		if (e->key < root->data->key) {
//			root->left=insertNode2(root->left, e);
//		}
//		else if (e->key > root->data->key) {
//			root->right=insertNode2(root->right, e);
//		}
//		/*else
//			printf("No duplicates allowed!");*/
//		return root;
//	}
//}

//BSTNode* insertNode(BSTNode* root, Exam* e)
//{
//	if (root == NULL)
//		root = createNode(e);
//	else {
//		if (e->key < root->data->key) {
//			root->left = insertNode(root->left, e);
//		}
//		else if (e->key > root->data->key) {
//			root->right = insertNode(root->right, e);
//		}
//		else
//			/*printf("No duplicates allowed!");*/
//		return root;
//	}
//}
//LD -> R -> RD
void printInorder(BSTNode* root)
{
	if (root) {
		printInorder(root->left);
		printf("Cod examen:%d\nSemestru:%d\nMaterie:%s\nNr credite:%d\nNr studenti:%d\n",
			root->data->key,
			root->data->sem,
			root->data->materie,
			root->data->nrCredite,
			root->data->nrStudenti);
		for (int i = 0; i < root->data->nrStudenti; i++) {
			printf("%d ", root->data->note[i]);
		}
		printf("\n\n");
		printInorder(root->right);
	}
}

struct Node {
	Exam* data;
	Node* next;
};
//int k = -1;
//int l = -1;

Node* add(Node* head, Exam* data) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->data = data;
	nou->next = head;
	return nou;
}

void determineChildrens(BSTNode* root)
{
	if (root) {
		printf("Parent node:%d\n", root->data->key);
		if (root->left == NULL) {
			printf("Left child:NULL\n");
		}
		else {
			printf("Left child:%d\n", root->left->data->key);
		}
		if (root->left == NULL) {
			printf("Right child:NULL\n");
		}
		else {
			printf("Right child:%d\n", root->right->data->key);
		}
		/*printf("\n\n");*/
		determineChildrens(root->left);
		determineChildrens(root->right);
	}
}



Node* printChildrens(BSTNode* root,int* a,int* i) {
	stack<BSTNode*> stack;
	BSTNode* curr = root;
	Node* node = NULL;
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
				if (a[*i] == curr->data->key) {
					if (curr->left) {
						node = add(node, curr->left->data);
					}
					if (curr->right) {

						node = add(node, curr->right->data);
					}
					return node;
				}
                curr = curr->right;
			}
		}
}

void printPreorder(BSTNode* root)
{
	if (root) {
		printf("Cod examen:%d\nSemestru:%d\nMaterie:%s\nNr credite:%d\nNr studenti:%d\n",
			root->data->key,
			root->data->sem,
			root->data->materie,
			root->data->nrCredite,
			root->data->nrStudenti);
		for (int i = 0; i < root->data->nrStudenti; i++) {
			printf("%d ", root->data->note[i]);
		}
		printf("\n\n");
		printPreorder(root->left);
		printPreorder(root->right);
	}
}
int nr = 0;
int nrExamene(BSTNode* root)
{
	stack<BSTNode*> stack;
	BSTNode* curr = root;
	Node* node = NULL;
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
			nr++;
			curr = curr->right;
		}
	}
	return nr;
}

void searchBiTree(BSTNode* root, BSTNode* newroot, int element) 
{
	if (root == NULL)
		return;
	else
	{
		newroot->data = root->data;     
		if (root->left != NULL)
			newroot->left = (BSTNode*)malloc(sizeof(BSTNode));
		if (root->right != NULL)
			newroot->right = (BSTNode*)malloc(sizeof(BSTNode));

		searchBiTree(root->left, newroot->left, element);
		searchBiTree(root->right, newroot->right, element);

	}
}

BSTNode* minValueNode(BSTNode* node) {
	BSTNode* current = node;
	while (current && current->left != NULL)
		current = current->left;
	return current;
}

BSTNode* deleteNode(BSTNode* root, int key) {
	if (root == NULL) return root;
	if (key < root->data->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->data->key)
		root->right = deleteNode(root->right, key);
	else {
		if (root->left == NULL) {
			BSTNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			BSTNode* temp = root->left;
			free(root);
			return temp;
		}
		BSTNode* temp = minValueNode(root->right);
		root->data->key = temp->data->key;
		root->right = deleteNode(root->right, temp->data->key);
	}
	return root;
}

void deleteNodes(BSTNode** tree,int credite) {
	stack<BSTNode*> stack;
	for (int i = 0; i < 2; i++) {
		BSTNode* curr = tree[i];
		printf("\n\n\n");
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
				if (curr->data->nrCredite==credite) {
					curr = deleteNode(curr, curr->data->key);
				}
				else {
					printf("Cod examen:%d\nSemestru:%d\nMaterie:%s\nNr credite:%d\nNr studenti:%d\n",
						curr->data->key,
						curr->data->sem,
						curr->data->materie,
						curr->data->nrCredite,
						curr->data->nrStudenti);
					for (int i = 0; i < curr->data->nrStudenti; i++) {
						printf("%d ", curr->data->note[i]);
					}
					printf("\n\n");
				}
				if(curr!=NULL)
				curr = curr->right;
			}
		}
	}
}


void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		printf("Cod examen:%d\nSemestru:%d\nMaterie:%s\nNr credite:%d\nNr studenti:%d\n",
			temp->data->key,
			temp->data->sem,
			temp->data->materie,
			temp->data->nrCredite,
			temp->data->nrStudenti);
		for (int i = 0; i < temp->data->nrStudenti; i++) {
			printf("%d ", temp->data->note[i]);
		}
		printf("\n\n");
		temp = temp->next;
	}
}

void printTree(BSTNode** tree) {
		printInorder(tree[0]);
		printInorder(tree[1]);
}



BSTNode** addToTree(BSTNode* root1, BSTNode* root2, Node** s,int* arr1, int* arr2) // Copy binary tree
{
	stack<BSTNode*> stack;
	BSTNode*newroot1 = NULL;
	BSTNode*newroot2 = NULL;
	BSTNode*node = NULL;
	int* a = (int*)malloc(sizeof(int) * 10);
	int j = 0;
	BSTNode* curr = root1;
	int value=0;
	for (int i = 0; i < 10; i++) {
		if(i!=0)
		curr = node;
		if (arr1[i] != value) {
			while (!stack.empty() || curr != nullptr)
			{
				if (curr != nullptr)
				{
					stack.push(curr);
					curr = curr->left;
				}
				else {
					curr = stack.top();
					if (curr->data->nrCredite == arr1[i]) {
						newroot1 = insertNode1(newroot1, curr->data);
					    *s = add(*s, curr->data);
						value = arr1[i];
					}
					else
						node = insertNode1(node, curr->data);
					stack.pop();
					curr = curr->right;
				}
			}
		}
	}
	curr = root2;
	node = NULL;
	value = 0;
	for (int i = 0; i < 10; i++) {
		if (i != 0)
			curr = node;
		if (arr2[i] != value) {
			while (!stack.empty() || curr != nullptr)
			{
				if (curr != nullptr)
				{
					stack.push(curr);
					curr = curr->left;
				}
				else {
					curr = stack.top();
					if (curr->data->nrCredite == arr2[i]) {
						newroot2 = insertNode1(newroot2, curr->data);
						*s = add(*s, curr->data);
						value = arr2[i];
					}
					else
						node = insertNode1(node, curr->data);
					stack.pop();
					curr = curr->right;
				}
			}
		}
	}
	BSTNode**tree= (BSTNode**)malloc(sizeof(BSTNode*) * 2);
	tree[0] = newroot1;
	tree[1] = newroot2;

	return tree;		
}

void convert(BSTNode* root)
{
	if (root == NULL) {
		return;
	}
	convert(root->left);
	convert(root->right);
	if (root->left == NULL)
	{
		root->left = root->right;
		root->right = NULL;
	}
	else {
		root->left->right = root->right;
		root->right = NULL;
	}
}

void _deleteTree(BSTNode* node)
{
	if (node->left)
	{
		_deleteTree(node->left);
		free(node->left);
	}
	if (node->right)
	{
		_deleteTree(node->right);
		free(node->right);
	}
}

void deleteTree(BSTNode** node_ref)
{
	if (*node_ref)
	{
		_deleteTree(*node_ref);
		free(*node_ref);
	}
}



void main()
{
	BSTNode* tree1 = NULL;
	BSTNode* tree2 = NULL;
	BSTNode* tree3 = NULL;
	BSTNode* a = (BSTNode*)malloc(sizeof(BSTNode));
	BSTNode** tree = (BSTNode**)malloc(sizeof(BSTNode*) * 2);
	int* arr = (int*)malloc(sizeof(int) * 10);
	int* arr1 = (int*)malloc(sizeof(int) * 4);
	int* arr2 = (int*)malloc(sizeof(int) * 6);
	FILE* pFile = fopen("Data.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	Exam* e = NULL;
	int i = 0,j = 0,k = 0;
	if (pFile)
	{
		char* token, sep[] = ",\n", name[30];
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			e = (Exam*)malloc(sizeof(Exam));
			token = strtok(buffer, sep);
			e->key = atoi(token);
			token = strtok(NULL, sep);
			e->sem = atoi(token);
			token = strtok(NULL, sep);
			e->materie = (char*)malloc(strlen(token) + 1);
			strcpy(e->materie, token);
			token = strtok(NULL, sep);
			e->nrCredite = atoi(token);
			token = strtok(NULL, sep);
			e->nrStudenti = atoi(token);
			e->note = (int*)malloc(sizeof(int)*e->nrStudenti);
			for (int i = 0; i < e->nrStudenti; i++) {
				token = strtok(NULL, sep);
				e->note[i] = atoi(token);
			}
			if (e->sem == 1) {
				tree1 = insertNode1(tree1, e);
				arr1[i] = e->nrCredite;
				i++;
			}
			else {
				tree2 = insertNode1(tree2, e);
				arr2[j] = e->nrCredite;
				j++;
			}
			tree3 = insertNode1(tree3, e);
			arr[k]=e->key;
			k++;
		}
		fclose(pFile);
	}
	tree[0] = tree1;
	tree[1] = tree2;

	for (int i = 0; i < 10; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (arr1[i] < arr1[j]) {
				int temp = arr1[i];
				arr1[i] = arr1[j];
				arr1[j] = temp;
			}
			if (arr2[i] < arr2[j]) {
				int temp = arr2[i];
				arr2[i] = arr2[j];
				arr2[j] = temp;
			}
		}
	}
		//ex1
		/*printTree(tree);*/

		//ex2
		//Node* listaS = NULL;
		//tree=addToTree(tree1, tree2,&listaS,arr1,arr2);
		//printList(listaS);

		//ex3
		/*deleteNodes(tree, 6);*/

		//ex4
		/*convert(tree3);
		for (int i = 0; i < 10; i++) {
			Node* n=NULL;
			printf("Nodul:%d\n", arr[i]);
			n = printChildrens(tree3, arr, &i);
			if (n) {
				printf("\nLista de descendenti:\n\n");
				printList(n);
				printf("\n\n");
			}
			else {
				printf("NULL\n\n");
			}
		}*/

		//ex5
		//deleteTree(tree);
	    //printTree(tree);
}