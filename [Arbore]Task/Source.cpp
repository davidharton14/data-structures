#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300
int value = 1;
struct Task {
	int id;
	char* data;
	char* nume;
	int nivelComplexitate;
	char* stare;
};

void afisareTask(Task t) {
	printf("Id task:%d\nData:%s\nNume:%s\nNivel de complexitate:%d\nStare:%s\n\n", t.id, t.data, t.nume, t.nivelComplexitate, t.stare);
}

Task createTask(int id, char* data, char* nume, int nivelComplexitate, char* stare) {
	Task t;
	t.id = id;
	t.data = (char*)malloc(strlen(data) + 1);
	strcpy(t.data, data);
	t.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(t.nume, nume);
	t.nivelComplexitate = nivelComplexitate;
	t.stare = (char*)malloc(strlen(stare) + 1);
	strcpy(t.stare, stare);
	return t;
}

struct NodArb {
	Task t;
	NodArb* st;
    NodArb* dr;
};

NodArb* inserare(NodArb* a, Task ta, int& e) {
	if (a==NULL) {
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->st = NULL;
		nou->dr = NULL;
		nou->t = ta;
		a = nou;
	}
	else {
		if (a->t.id == ta.id) e = 1;
		else if (a->t.id< ta.id) {
			a->st = inserare(a->st, ta, e);
		}
		else {
			a->dr = inserare(a->dr, ta, e);
		}
		
	}
	return a;
}

void afisareArb(NodArb* radacina) {
	
     if(radacina) {
		afisareArb(radacina->st);
		afisareTask(radacina->t);
		afisareArb(radacina->dr);
	}
}

void nrTasks(NodArb* radacina, const char* nume) {
	
	if (radacina) {
		if (strcmp(radacina->t.nume, nume) == 0) {
			value++;
		}
		nrTasks(radacina->st, nume);
		nrTasks(radacina->dr, nume);
	}
}
void schimbareTask(NodArb* radacina) {
	if (radacina) {
		if (strcmp(radacina->t.stare, "nou") == 0) {
			strcpy(radacina->t.stare, "deschis");
		}
		schimbareTask(radacina->st);
		schimbareTask(radacina->dr);
	}
}
void determinareTasks(NodArb* radacina,int value) {
	if (radacina) {
		if (radacina->t.nivelComplexitate> value) {
			afisareTask(radacina->t);
		}
		determinareTasks(radacina->st, value);
		determinareTasks(radacina->dr, value);
	}
}



NodArb* deleteLeafNodes(NodArb* radacina) {
	if (radacina == NULL)
		return NULL;
	if (radacina->dr == NULL && radacina->st == NULL) {
		free(radacina);
		return NULL;
	}
	radacina->st=deleteLeafNodes(radacina->st);
	radacina->dr=deleteLeafNodes(radacina->dr);
	return radacina;
}
NodArb* displayLeafNodes(NodArb* radacina) {
	if (radacina == NULL)
		return NULL;
	if (radacina->dr == NULL && radacina->st == NULL) {
		afisareArb(radacina);
		free(radacina);
		return NULL;
	}
	radacina->st = displayLeafNodes(radacina->st);
	radacina->dr = displayLeafNodes(radacina->dr);
	return radacina;
}


void main() {
	Task t;
	NodArb* root = NULL;
	NodArb* radacina = NULL;
	FILE* f = fopen("task.txt", "r");
	char* buffer = (char*)malloc(DIM_BUFFER);
	if (f) {
		char* token, sep[] = ",";
		int id;
		char data[20];
		char nume[30];
		int nivelComplexitate;
		char stare[20];
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			id = atoi(token);
			token = strtok(NULL, sep);
			strcpy(data, token);
			token = strtok(NULL, sep);
			strcpy(nume, token);
			token = strtok(NULL, sep);
			nivelComplexitate = atof(token);
			token = strtok(NULL, sep);
			strcpy(stare, token);
			t = createTask(id, data, nume, nivelComplexitate, stare);
			int e = 0;
			root = inserare(root,t,e);
			radacina = inserare(radacina, t, e);
			if (e) {
				free(t.data);
				free(t.nume);
				free(t.stare);
			}
			else {
				/*printf("Task-ul cu id-ul %d a fost inserat.\n",root->t.id);*/
			}
		}
		fclose(f);
		/*adaugaPacient(heap, 9, "Harton Daniel", "Probleme de sanatate", 22, 1, 2,3);*/ //ex3
	}
	/*afisareArb(root);*/ //ex3
	/*nrTasks(root, "Harton Daniel"); //ex4
	printf("%d", value);*/
	/*schimbareTask(root);*/ //ex5
	/*afisareArb(root);*/
	/*determinareTasks(root, 5);*/ //ex6
	/*printf("Nodurile care nu sunt frunza sunt:\n");
	deleteLeafNodes(root); //ex7
	afisareArb(root);*/
	/*printf("\nNodurile frunza sunt:\n\n");
	displayLeafNodes(radacina);*/
}

