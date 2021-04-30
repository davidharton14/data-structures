#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DIM_BUFFER 300
struct Examen {
	int codExamen;
	char* materie;
	unsigned int nrCredite;
	int nrStudenti;
	int* note;
};

struct NodArb {
	Examen info;
	NodArb* left;
	NodArb* right;
};

void afisareExamen(Examen e) {
	printf("Cod examen:%d\nMaterie:%s\nNr credite:%d\nNr studenti:%d\n", e.codExamen, e.materie, e.nrCredite, e.nrStudenti, e.note);
	printf("Note:\n");
	for (int i = 0; i < e.nrStudenti; i++) {
		printf("%d ", e.note[i]);
	}
	printf("\n\n");
}

NodArb* inserareArb(NodArb* rad, Examen e) {
	if (rad) {
		if (e.codExamen < rad->info.codExamen) {
			rad->left = inserareArb(rad->left, e);
		}
		else
			rad->right = inserareArb(rad->right, e);
		return rad;
	}
	else {
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->info = e;
		nou->left = NULL;
		nou->right = NULL;
	}
}
void afisareArb(NodArb* rad) {
	if (rad) {
		afisareExamen(rad->info);
		afisareArb(rad->left);
		afisareArb(rad->right);
	}
}

NodArb* minValueNode(struct NodArb* node) {
	NodArb* current = node;
	while (current && current->left != NULL)
		current = current->left;
	return current;
}
NodArb* deleteNode(NodArb* root, int key) {
	if (root == NULL) return root;
	if (key < root->info.codExamen)
		root->left = deleteNode(root->left, key);
	else if (key > root->info.codExamen)
		root->right = deleteNode(root->right, key);
	else {
		if (root->left == NULL) {
			NodArb* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			NodArb* temp = root->left;
			free(root);
			return temp;
		}
		NodArb* temp = minValueNode(root->right);
		root->info.codExamen = temp->info.codExamen;
		root->right = deleteNode(root->right, temp->info.codExamen);
	}
	return root;
}
bool promovabilitateExamen(NodArb* rad, int nr,int i,int cod) {
	if (rad) {
		if (rad->info.codExamen == cod) {
				if (rad->info.note[i] >= 5) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		promovabilitateExamen(rad->left, nr,i,cod);
		promovabilitateExamen(rad->right,nr,i,cod);
}

int getLevelUtil(NodArb* node,int data, int level)
{
	if (node == NULL)
		return 0;

	if (node->info.codExamen == data)
		return level;

	int downlevel = getLevelUtil(node->left,
		data, level + 1);
	if (downlevel != 0)
		return downlevel;

	downlevel = getLevelUtil(node->right,
		data, level + 1);
	return downlevel;
}

int getLevel(NodArb* node, int data)
{
	return getLevelUtil(node, data, 1);
}



int nrExamene(NodArb* node, int l) {
	int nr = 0;
	for (int x = 1; x <= 100; x++)
	{
		int level = getLevel(node, x);
		if (l == level) {
			if (level) {
				nr++;
			}
		}
	}
	return nr;
}

int* coduri = (int*)malloc(sizeof(int)*100);
int* coduriExamen(NodArb* node, int l) {
	int i = 0;
	for (int x = 1; x <= 100; x++)
	{
		int level = getLevel(node, x);
		if (l == level) {
			if (level) {
				coduri[i] = x;
				i++;
			}
		}
	}
	return coduri;
}
void afisareArbDupaId(NodArb* rad, int id) {
	if (rad) {
		if (rad->info.codExamen == id) {
			afisareExamen(rad->info);
		}
		afisareArbDupaId(rad->left,id);
		afisareArbDupaId(rad->right,id);
	}
}


void main() {
	Examen e;
	NodArb* rad = NULL;
	FILE* f = fopen("examene.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			e.codExamen = atoi(token);
			token = strtok(NULL, sep);
			e.materie = (char*)malloc(strlen(token) + 1);
			strcpy(e.materie, token);
			token = strtok(NULL, sep);
			e.nrCredite = atoi(token);
			token = strtok(NULL, sep);
			e.nrStudenti = atoi(token);
			e.note = (int*)malloc(sizeof(int)*e.nrStudenti);
			for (int i = 0; i < e.nrStudenti; i++) {
				token = strtok(NULL, sep);
				e.note[i] = atoi(token);
			}
			rad = inserareArb(rad, e);//ex2
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu a fost deschis");
	}
	/*afisareArb(rad);//ex3
	rad = deleteNode(rad, 20);//ex4
	afisareArb(rad);*/
	/*int p = 0;
	int n = 0;
	for (int i = 0; i < 20; i++) {
		if (promovabilitateExamen(rad, 20, i, 50))//ex5
			p++;
		else
			n++;
	}
	printf("\nExamenul a fost promovat de %d studenti si nepromovat de %d studenti", p,n);*/
	/*coduriExamen(rad, 2);*/
	coduri = coduriExamen(rad, 2);
	for (int i = 0; i < nrExamene(rad, 2); i++) {
		afisareArbDupaId(rad, coduri[i]); 
		/*printf("%d ", coduri[i]);*/ //ex6
	}
	//printf("%d", nrExamene(rad,5));
}



