#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;
#define DIM_BUFFER 300
enum SursaPlasare {
	telefonic,
	online,
	showRoom
};

enum Stare {
	inLucru,
	confirmata,
	livrare,
	executata
};

SursaPlasare convertToSursaPlasare(const string& str)
{
	if (str == "telefonic") return telefonic;
	else if (str == "online") return online;
	else if (str == "showRoom") return showRoom;
}
Stare convertToStare(const string& str)
{
	if (str == "inLucru") return inLucru;
	else if (str == "confirmata") return confirmata;
	else if (str == "livrare") return livrare;
	else if (str == "executata") return executata;
}

struct Comanda {
	unsigned int idComanda;
	char* numeClient;
	int nrProduse;
	int valoareComanda;
	enum SursaPlasare sursaPlasare;
	enum Stare stare;
};

struct NodArb {
	Comanda c;
	NodArb* st;
	NodArb* dr;
};
struct nodLista {
	Comanda info;
	nodLista* next;
};
Comanda createComanda(unsigned int idComanda, char* numeClient, int nrProduse, int valoareComanda, SursaPlasare sursaPlasare, Stare stare) {
	Comanda c;
	c.idComanda = idComanda;
	c.numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(c.numeClient, numeClient);
	c.nrProduse = nrProduse;
	c.valoareComanda = valoareComanda;
	c.sursaPlasare = sursaPlasare;
	c.stare = stare;
	return c;
}

void displayComanda(Comanda c) {
	printf("Id comanda:%d\nNume client:%s\nNr produse:%d\nValoare comanda:%d\nSursa plasare:%d\nStare:%d\n\n", c.idComanda, c.numeClient, c.nrProduse, c.valoareComanda, c.sursaPlasare+1, c.stare+1);
}


NodArb* inserareArb(NodArb* rad, Comanda c, int&e) {
	if (rad) {
		if (c.idComanda < rad->c.idComanda) {
			rad->st = inserareArb(rad->st, c, e);
		}
		else {
			rad->dr = inserareArb(rad->dr, c, e);
		}
		return rad;
	}
	else /*if (rad->c.idComanda == c.idComanda) e = 1;*/
	{

		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->c = c;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}

}

void displayArb(NodArb* rad) {
	if (rad) {
		displayComanda(rad->c);
		displayArb(rad->st);
		displayArb(rad->dr);
	}
}

NodArb* minValueNode(struct NodArb* node) {
	NodArb* current = node;
	while (current && current->st != NULL)
		current = current->st;
	return current;
}
NodArb* getNodeWithMaxim(NodArb* root) {
	if (root) {
		while (root->dr)
			root = root->dr;
		return root;
	}
}
NodArb* deleteNode(NodArb* root, int key)
{
	if (root) {
		if (key > root->c.idComanda) {
			root->dr = deleteNode(root->dr, key);
		}
		else if (key < root->c.idComanda) {
			root->st = deleteNode(root->st, key);
		}
		else {
			if (root->st == NULL) {
				free(root->c.numeClient);
				NodArb* temp = root->dr;
				free(root);
				return temp;
			}
			if (root->dr == NULL) {
				free(root->c.numeClient);
				NodArb* temp = root->st;
				free(root);
				return temp;
			}
			NodArb* temp = getNodeWithMaxim(root->st);
			Comanda aux = temp->c;
			temp->c = root->c;
			root->c = aux;
			root->st = deleteNode(root->st, key);
			return root;
		}
	}
	return root;
}


NodArb* getNodeWithMaximum(NodArb* root) {
	if (root) {
		if (root->dr) {
			return getNodeWithMaximum(root->dr);
		}
		else {
			return root;
		}
	}
}
//NodArb* deleteNode(NodArb* root, const char* nume) {
//	if (root) {
//		if (strcmp(root->c.numeClient,nume)==0) {
//			if (root->st == NULL) {
//				NodArb* temp = root->dr;
//				free(root->c.numeClient);
//				free(root);
//				return temp;
//			}
//			if (root->dr == NULL) {
//				NodArb* temp = root->st;
//				free(root->c.numeClient);
//				free(root);
//				return temp;
//			}
//			NodArb* temp = getNodeWithMaximum(root->st);
//			Comanda aux = root->c;
//			root->c = temp->c;
//			temp->c = aux;
//			root->st= deleteNode(root->st, nume);
//			return root;
//
//		}
//		else if (strcmp(root->c.numeClient,nume)>0) {
//			root->st = deleteNode(root->st, nume);
//			return root;
//		}
//		else {
//			root->dr = deleteNode(root->dr, nume);
//			return root;
//		}
//	}
//}
Comanda extract(NodArb** root, int key) {
	if (*root) {
		if ((*root)->c.idComanda == key) {
			Comanda result = (*root)->c;
			if ((*root)->dr == NULL) {
				NodArb* temp = (*root)->st;
				free(*root);
				*root = temp;
			}
			else
				if ((*root)->st == NULL) {
					NodArb* temp = (*root)->dr;
					free(*root);
					*root = temp;
				}
				else {
					NodArb* temp = getNodeWithMaximum((*root)->st);
					Comanda aux = temp->c;
					temp->c = (*root)->c;
					(*root)->c = aux;
					extract(&(*root)->st, key);
				}
		return result;
	}else if ((*root)->c.idComanda > key) {
			return extract(&(*root)->st, key);
		}
	else {
			return extract(&(*root)->dr, key);
		}
	}
}

void displayArbb(NodArb* rad) {
	stack<NodArb*> stack;
	NodArb* curr= rad;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			displayComanda(curr->c);
			curr = curr->dr;
		}
		
	}
}
void modificareNrComenzi(NodArb* root, const char* s, const char* nume) {
	Stare st = convertToStare(s);
	/*if (root) {
		if (st == root->c.stare) {
			if (strcmp(root->c.numeClient, nume) == 0) {
				Comanda c;
				c = extract(&root, root->c.idComanda);
				FILE *fptr;
				fptr = fopen("asd.txt", "w");
				char sep[] = ", ";
				char sep2[] = "\n";
				if (fptr == NULL)
				{
					printf("Error!");
					exit(1);
				}
				else {
					fprintf(fptr, "%d", c.idComanda);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%s", c.numeClient);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", c.nrProduse);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", c.valoareComanda);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", c.sursaPlasare);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", c.stare);
					fprintf(fptr, "%s", sep2);
				}
				fclose(fptr);
			}
		}  if (root) {
			displayComanda(root->c);
			modificareNrComenzi(root->st, s, nume);
			modificareNrComenzi(root->dr, s, nume);
		}
	}*/
	FILE *fptr;
	FILE *f;
	Comanda c;
	fptr = fopen("comenzi_finalizate.txt", "w");
	f = fopen("comenzi_nefinalizate.txt", "w");
	stack<NodArb*> stack;
	NodArb* curr = root;

	char sep[] = ", ";
	char sep2[] = "\n";
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}else{
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (st == curr->c.stare) {
				if (strcmp(curr->c.numeClient, nume) == 0) {
					c = extract(&curr, curr->c.idComanda);
						fprintf(fptr, "%d", c.idComanda);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%s", c.numeClient);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%d", c.nrProduse);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%d", c.valoareComanda);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%d", c.sursaPlasare);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%d", c.stare);
						fprintf(fptr, "%s", sep2);
					}
				}
			}
			if (curr) {
				fprintf(f, "%d", curr->c.idComanda);
				fprintf(f, "%s", sep);
				fprintf(f, "%s", curr->c.numeClient);
				fprintf(f, "%s", sep);
				fprintf(f, "%d", curr->c.nrProduse);
				fprintf(f, "%s", sep);
				fprintf(f, "%d", curr->c.valoareComanda);
				fprintf(f, "%s", sep);
				fprintf(f, "%d", curr->c.sursaPlasare);
				fprintf(f, "%s", sep);
				fprintf(f, "%d", curr->c.stare);
				fprintf(f, "%s", sep2);
				displayComanda(curr->c);
				curr = curr->dr;
			}
		}
	}
	fclose(fptr);
	fclose(f);
}

nodLista* inserareInceputLista(nodLista* cap, Comanda c) {
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info = c;
	nou->next = cap;
	return nou;
}

int getLevel(NodArb* root, int data){
	queue<NodArb*> q;
	int level = 1;
	q.push(root);
	q.push(NULL);
	while (!q.empty()) {
		NodArb* temp = q.front();
		q.pop();
		if (temp == NULL) {
			if (q.front() != NULL) {
				q.push(NULL);
			}
			level += 1;
		}
		else {
			if (temp->c.idComanda == data) {
				return level;
			}
			if (temp->st) {
				q.push(temp->st);
			}
			if (temp->dr) {
				q.push(temp->dr);
			}
		}
	}
	return 0;
}

nodLista* copiereComenzi(NodArb* root, nodLista* cap,int level) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->st;
	}
		else {
			curr = stack.top();
			stack.pop();
			if (level == getLevel(root, curr->c.idComanda)) {
				cap = inserareInceputLista(cap, curr->c);
			}
			curr = curr->dr;
			
		}
	}
	return cap;
}


void main() {
	Comanda c;
	NodArb* rad = NULL;
	FILE* f = fopen("comenzi.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			c.idComanda = atoi(token);
			token = strtok(NULL, sep);
			c.numeClient = (char*)malloc(strlen(token) + 1);
			strcpy(c.numeClient, token);
			token = strtok(NULL, sep);
			c.nrProduse = atoi(token);
			token = strtok(NULL, sep);
			c.valoareComanda = atoi(token);
			token = strtok(NULL, sep);
			c.sursaPlasare = convertToSursaPlasare(token);
			token = strtok(NULL, sep);
			c.stare = convertToStare(token);
			int e = 0;
			rad = inserareArb(rad, c, e);
			if (e) {
				free(c.numeClient);
			}
		}
		fclose(f);
	}
	/*displayArb(rad);*/
	modificareNrComenzi(rad, "executata", "Harton Maria");
	/*displayArb(rad);*/
	/*displayArbb(rad);*/
	
	//displayComanda(extract(&rad,1));
	//displayComanda(extract(&rad, 2));
	//displayComanda(extract(&rad, 3));
	//printf("--------\n");
	/*displayArb(rad);*/
	/*afisareDePeNivel(rad, 7);*/
	/*nodLista* cap = NULL;
	cap = copiereComenzi(rad,cap,7);
	printf("Lista:\n\n\n");
	while (cap) {
		displayComanda(cap->info);
		cap = cap->next;
	}*/
}