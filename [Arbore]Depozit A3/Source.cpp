#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;
#define DIM_BUFFER 300


struct Depozit {
	int cod;
	char* id;
	int capacitate;
	float coordonateGPS;
	int nrMateriale;
	char** categoriiMateriale;
	int procentVolum;
};

struct NodArb {
	Depozit info;
	NodArb* left;
	NodArb* right;
};

void afisareDepozit(Depozit d) {
	printf("Cod depozit:%d\nId:%s\nCapacitate:%d\nCoordonate GPS%.2f\nNr materiale:%d\n", d.cod, d.id, d.capacitate, d.coordonateGPS, d.nrMateriale);
	printf("\n");
	for (int i = 0; i < d.nrMateriale; i++) {
		printf("%s\n", d.categoriiMateriale[i]);
	}
	/*printf("Procent volum:%.2f\n", d.procentVolum);*/
	printf("\n\n");
}

NodArb* inserareArb(NodArb* rad, Depozit d) {
	if (rad) {
		if (d.cod < rad->info.cod) {
			rad->left = inserareArb(rad->left, d);
		}
		else
			rad->right = inserareArb(rad->right, d);
		return rad;
	}
	else {
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->info = d;
		nou->left = NULL;
		nou->right = NULL;
	}
}
void afisareArb(NodArb* rad) {
	if (rad) {
		afisareDepozit(rad->info);
		afisareArb(rad->left);
		afisareArb(rad->right);
	}
}

bool printAscensors(NodArb*root, int* A, int* i,int target)
{
	if (root == NULL)
		return false;

	if (root->info.cod == target)
		return true;
	if (printAscensors(root->left, A,i,target) ||
		printAscensors(root->right,A,i,target))
	{
		A[*i] = root->info.cod;
		*i = *i + 1;
		return true;
	}
	return false;
}

int height(NodArb* root) {
	if (root == NULL) {
		return -1;
	}
	else {
		if (root->left == NULL && root->right == NULL) {
			return 0;
		}
		return max(height(root->left), height(root->right)) + 1;
	}
}
int* createAscensorsArray(NodArb* root, int target) {
	if (root != NULL) {
		int *A = (int*)malloc(sizeof(int)*height(root));
		int i = 0;
		printAscensors(root, A, &i, target);
		return A;
	}
}

int numNodesLevel(NodArb* root, int level) {
	if (root == NULL) {
		return 0;
	}
	else {
		if (level == 0) {
			return 1;
		}
		return numNodesLevel(root->left, level - 1) + numNodesLevel(root->right, level - 1);
	}
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int maxNodesLevel(NodArb* root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int max = 0;
		int h = height(root);
		int i = 0;
		for (i = 0; i <= h; i++) {
			if (numNodesLevel(root, i) > max) {
				max = numNodesLevel(root, i);
			}
		}
		return max;
	}
}

void fill(NodArb* root, int* A, int level, int* i) {
	if (root != NULL) {
		if (level == 0) {
			A[*i] = root->info.cod;
			*i = *i + 1;
		}
		fill(root->left, A, level - 1, i);
		fill(root->right, A, level - 1, i);
	}
}

int* createArray(NodArb* root, int level) {
	if (root != NULL) {
		int *A = (int*)malloc(sizeof(int)*maxNodesLevel(root));
		int i = 0;
		fill(root, A, level, &i);
		return A;
	}
}
int maxNodeLevel(NodArb*root)
{
	if (root == NULL)
		return -1;

	queue<NodArb*> q;
	q.push(root);
	int level = 0;

	int max = INT_MIN;
	int level_no = 0;

	while (1)
	{
		int NodeCount = q.size();

		if (NodeCount == 0)
			break;
		if (NodeCount > max)
		{
			max = NodeCount;
			level_no = level;
		}
		while (NodeCount > 0)
		{
			NodArb*Node = q.front();
			q.pop();
			if (Node->left != NULL)
				q.push(Node->left);
			if (Node->right != NULL)
				q.push(Node->right);
			NodeCount--;
		}
		level++;
	}
	return level_no;
}

NodArb* leafDelete(NodArb* root)
{
	if (root == NULL)
		return NULL;
	if (root->left == NULL && root->right == NULL) {
		free(root);
		return NULL;
	}
	root->left = leafDelete(root->left);
	root->right = leafDelete(root->right);
	return root;
}


void deleteTree(NodArb* node)
{
	if (node == NULL) return;

	/* first delete both subtrees */
	deleteTree(node->left);
	deleteTree(node->right);

	/* then delete the node */
	cout << "\n Deleting node: " << node->info.cod;
	delete node;
}



void main() {
	NodArb* rad = NULL;
	Depozit d;
	FILE* f = fopen("depozite.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			d.cod = atoi(token);
			token = strtok(NULL, sep);
			d.id = (char*)malloc(strlen(token) + 1);
			strcpy(d.id, token);
			token = strtok(NULL, sep);
			d.capacitate = atoi(token);
			token = strtok(NULL, sep);
			d.coordonateGPS = atof(token);
			token = strtok(NULL, sep);
			d.procentVolum = atoi(token);
			token = strtok(NULL, sep);
			d.nrMateriale = atoi(token);
			d.categoriiMateriale = (char**)malloc(sizeof(token)*d.nrMateriale);
			for (int i = 0; i < d.nrMateriale; i++) {
				token = strtok(NULL, sep);
				d.categoriiMateriale[i] = token;
			}
			rad = inserareArb(rad, d);
		}
		fclose(f);
	}	
	/*afisareArb(rad);
	printf("\n\n");*/

	//ex2
	/*int*arr1 = createArray(rad, 1);
	for (int i = 0; i < numNodesLevel(rad, 1); i++) {   
		printf("%d ", arr1[i]);
	}*/

	//ex3
	/*int*arr2 = createAscensorsArray(rad, 7);
	for (int i = 0; i < height(rad); i++) {
		printf("%d ", arr2[i]);
	}*/

	//ex4
	/*printf("Level having maximum number of Nodes : %d",maxNodeLevel(rad));*/

	//ex5
	/*rad=leafDelete(rad);
	afisareArb(rad);*/

	//ex6
	/*deleteTree(rad); */

}

