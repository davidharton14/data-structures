#include<stdio.h>
#include<stdlib.h>
#include<string>
#define DIM_BUFFER 300
struct Car {
	int id;
	char* matricolNr;
	char* brand;
	char* customerName;
	float price;
	char* status;
};

struct NodeTree {
	Car info;
	NodeTree* left;
	NodeTree* right;
};

void displayCar(Car c) {
	printf("Id:%d\nMatricol number:%s\nBrand:%s\nCustomer name:%s\nPrice:%.2f EURO\nStatus:%s\n\n", c.id,c.matricolNr, c.brand, c.customerName, c.price, c.status);
}

NodeTree* insertTree(NodeTree* root,Car c)
{
	if (root) {
		if (c.id < root->info.id) {
			root->left = insertTree(root->left, c);
		}
		else {
			root->right = insertTree(root->right, c);
		}
		return root;
	}
	else {
		NodeTree* newNode = (NodeTree*)malloc(sizeof(NodeTree));
		newNode->info = c;
		newNode->left = NULL;
		newNode->right = NULL;
		root = newNode;
	}
}

int inaltimeArbore(NodeTree* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->left);
		int inaltimeDR = inaltimeArbore(rad->right);
		return 1 + (inaltimeST > inaltimeDR ? inaltimeST : inaltimeDR);
	}
	else {
		return 0;
	}
}

int calculareGradEchilibru(NodeTree* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->left);
		int inaltimeDR = inaltimeArbore(rad->right);
		return inaltimeST - inaltimeDR;
	}
	else {
		return 0;
	}
}

NodeTree* rotireLaStanga(NodeTree* root) {
	if (root) {
		NodeTree* aux = root->right;
		root->right = aux->left;
		aux->left = root;
		return aux;
	}
	else {
		return root;
	}
}
NodeTree* rotireLaDreapta(NodeTree* root) {
	if (root) {
		NodeTree* aux = root->left;
		root->right = aux->right;
		aux->right = root;
		return aux;
	}
	else {
		return root;
	}
}

NodeTree* insertAVLTree(NodeTree* root, Car c)
{
	if (root) {
		if (c.id < root->info.id) {
			root->left = insertAVLTree(root->left, c);
		}
		else {
			root->right = insertAVLTree(root->right, c);
		}
		if (calculareGradEchilibru(root) == 2) {
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
		}
		return root;
	}
	else {
		NodeTree* newNode = (NodeTree*)malloc(sizeof(NodeTree));
		newNode->info = c;
		newNode->left = NULL;
		newNode->right = NULL;
		root = newNode;
	}
}
void displayTree(NodeTree* root) {
	if (root) {
		displayCar(root->info);
		displayTree(root->left);
		displayTree(root->right);
	}
}
int sw = 0;
bool isSold(NodeTree* root,const char* nr) {
	if (root) {
		if (strcmp(root->info.matricolNr, nr) == 0) {
			if (strcmp(root->info.status, "sold") == 0) {
				sw = 1;
			}
		}
		isSold(root->left,nr);
		isSold(root->right,nr);
	}
	if (sw == 1)
		return true;
	else return false;
}
void selectCars(NodeTree* root, int installmentsNr) {
	if (root) {
		float value=0;
		if (strcmp(root->info.status, "unsold") == 0) {
			displayCar(root->info);
			printf("\n");
			for (int i = 0; i < 60; i++) {
				if (i == installmentsNr) {
					value = root->info.price / installmentsNr;
					for (int j = 0; j < installmentsNr; j++) {
						printf("The montly rate %d is %.2f EURO\n", j+1, value);
					}
				}
			}
		}
		selectCars(root->left, installmentsNr);
		selectCars(root->right, installmentsNr);
	}
}

int nr=0;
void countCars(NodeTree* root,const char* brand) {
	if (root) {
		if (strcmp(root->info.brand, brand) == 0) {
			nr++;
		}
		countCars(root->left, brand);
		countCars(root->right, brand);
	}
}

void main() {

	Car c;
	NodeTree* root = NULL;
	FILE* f = fopen("cars.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token,sep[]=",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			c.id = atoi(token);
			token = strtok(NULL, sep);
			c.matricolNr = (char*)malloc(strlen(token) + 1);
			strcpy(c.matricolNr, token);
			token = strtok(NULL, sep);
			c.brand = (char*)malloc(strlen(token) + 1);
			strcpy(c.brand, token);
			token = strtok(NULL, sep);
			c.customerName = (char*)malloc(strlen(token) + 1);
			strcpy(c.customerName, token);
			token = strtok(NULL, sep);
			c.price = atof(token);
			token = strtok(NULL, sep);
			c.status = (char*)malloc(strlen(token) + 1);
			strcpy(c.status, token);
			/*root = insertTree(root, c);*/
			root = insertAVLTree(root,c);

		}
		fclose(f);
	}
	
	//if (isSold(root,"SB 78 GIU")) { //ex3
	//	printf("The car is sold");
	//}
	//else {
	//	printf("The car is unsold");
	//}
	selectCars(root, 12); //ex4
	//countCars(root, "Dacia"); //ex5
	//printf("Numarul de masini cu brandul Dacia este:%d", nr);
	/*displayTree(root);*/

	/*for (int i = 0; i < 13; i++)
		printf("%d ",ids[i]);*/
}