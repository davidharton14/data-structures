#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300

struct SejurTuristic {
	char* destinatie;
	float suma_plata;
	int zi_inceput;
	int zi_sfarsit;
	char* mijloc_de_transport;
	int nr_persoane;
	char* denumire_hotel;
	char* nume_coordonator;
};

struct Nod {
	SejurTuristic* info;
	Nod* next;
	Nod* prev;
};

void afisareSejurTuristic(SejurTuristic* s) {
	printf("Destinatie:%s\nSuma plata:%.2f\nZi inceput:%d\nZi sfarsit:%d\nMijloc de transport:%s\nNr persoane:%d\nDenumire hotel:%s\nNume coordonator:%s\n\n"
		,s->destinatie, s->suma_plata, s->zi_inceput,s->zi_sfarsit, s->mijloc_de_transport, 
		s->nr_persoane, s->denumire_hotel,s->nume_coordonator);
}

void adaugareNodInLista(Nod** cap, SejurTuristic* r) {
	if (*cap == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = r;
		nou->next = nou->prev = nou;
		(*cap) = nou;
	}
	else {
		Nod* last = (*cap)->prev;
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = r;
		nou->next = (*cap);
		(*cap)->prev = nou;
		nou->prev = last;
		last->next = nou;
	}
}

void push(Nod** head_ref, SejurTuristic* s)
{
	Nod* new_node= (Nod*)malloc(sizeof(Nod));
	new_node->info = s;

	new_node->next = (*head_ref);
	new_node->prev = NULL;

	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;

	(*head_ref) = new_node;
}

void parcurgereListaDubla(Nod* node) {
	Nod* last;
	while (node != NULL) {
		afisareSejurTuristic(node->info);
		last = node;
		node = node->next;
	}
}

int nrElemente(Nod* node) {
	int nr = 0;
	Nod* last;
	while (node != NULL) {
		if (node->info->zi_sfarsit - node->info->zi_inceput == 7) {
			nr++;
		}
		last = node;
		node = node->next;
	}
	return nr;
}


SejurTuristic** determinareSejururiTuristice(Nod* node) {
	SejurTuristic** vector = (SejurTuristic**)malloc(sizeof(SejurTuristic*)*nrElemente(node));
	int j = 0;
	Nod *last;
	while (node != NULL)
	{
		if (node->info->zi_sfarsit-node->info->zi_inceput == 7) {
			vector[j] = node->info;
			j++;
		}
		last = node;
		node = node->next;
	}
	return vector;
}

struct Lista {
	SejurTuristic* info;
	Lista* next;
};

struct ListaDeListe {
	Lista* lista;
	ListaDeListe* next;
};


int cautareString(char** sir, int j, const char* string) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (strcmp(sir[i], string) == 0) {
			sw = 1;
			break;
		}
	}
	if (sw == 1) {
		return sw;
	}
	else
		return sw;
}

int nrSejururi(Nod* cap) {
	Nod* temp = cap;
	int nr = 0;
	while (temp) {
		nr++;
		temp = temp->next;
	}
	return nr;
}

int nrDestinatii(Nod* cap) {
	Nod* temp = cap;
	char** charsArr = (char**)malloc(sizeof(char*)*nrSejururi(cap));
	int j = 0;
	while (temp) {
		if (cautareString(charsArr, j, temp->info->destinatie) == 0) {
			charsArr[j] = temp->info->destinatie;
			j++;
		}
		temp = temp->next;
	}
	return j;
}

void pushListaDeListe(Nod* cap, ListaDeListe** head_ref, Lista** l) {
	Nod* temp = cap;
	char** charsArr = (char**)malloc(sizeof(char*)*nrDestinatii(cap));
	int j = 0;
	while (temp) {
		if (cautareString(charsArr, j, temp->info->destinatie) == 0) {
			charsArr[j] = temp->info->destinatie;
			j++;
		}
		temp = temp->next;
	}
	int nr = j;
	for (int i = 0; i < nr; i++) {
		ListaDeListe* new_node = (ListaDeListe*)malloc(sizeof(ListaDeListe));
		temp = cap;
		while (temp) {
			if (strcmp(charsArr[i], temp->info->destinatie) == 0) {
				Lista* new_node = (Lista*)malloc(sizeof(Lista));
				new_node->info = temp->info;
				new_node->next = (*l);
				(*l) = new_node;
			}
			temp = temp->next;
		}
		new_node->lista = (*l);
		new_node->next = (*head_ref);
		(*head_ref) = new_node;
		*l = NULL;
	}
}

void parcurgereLista(Lista* cap) {

	Lista* temp = cap;
	while (temp) {
		afisareSejurTuristic(temp->info);
		temp = temp->next;
	}
}

void parcurgereListaDeListe(ListaDeListe* cap) {

	ListaDeListe* temp = cap;
	int i = 0;
	while (temp) {
		printf("Lista %d:\n\n", i);
		parcurgereLista(temp->lista);
		i++;
		temp = temp->next;
	}
}

float determinareTotalIncasari(Nod* node,int inceput,int sfarsit,const char* destinatie) {
	Nod *last;
	float sum = 0;
	while (node != NULL)
	{
		if (strcmp(node->info->destinatie, destinatie) == 0) {
			if (node->info->zi_inceput <= node->info->zi_sfarsit) {
				sum += node->info->suma_plata;
			}
		}
		last = node;
		node = node->next;
	}
	return sum;
}

void deleteListaDeListe(ListaDeListe**head_ref)
{
	ListaDeListe*current = *head_ref;
	ListaDeListe*next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void deleteLista(Lista**head_ref)
{
	Lista*current = *head_ref;
	Lista*next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void deleteAllNodes(Nod* node) {

	Nod* temp = (Nod*)malloc(sizeof(Nod));
	while (node != NULL) {
		temp = node;
		node = node->next;
		free(temp);
	}
}

void main() {
	SejurTuristic* s=NULL;
	Nod* cap = NULL;
	FILE* f = fopen("file.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			s = (SejurTuristic*)malloc(sizeof(SejurTuristic));
			token = strtok(buffer, sep);
		    s->destinatie = (char*)malloc(strlen(token) + 1);
			strcpy(s->destinatie, token);
			token = strtok(NULL, sep);
			s->suma_plata = atoi(token);
			token = strtok(NULL, sep);
			s->zi_inceput = atoi(token);
			token = strtok(NULL, sep);
			s->zi_sfarsit = atoi(token);
			token = strtok(NULL, sep);
			s->mijloc_de_transport = (char*)malloc(strlen(token) + 1);
			strcpy(s->mijloc_de_transport, token);
			token = strtok(NULL, sep);
			s->nr_persoane = atoi(token);
			token = strtok(NULL, sep);
			s->denumire_hotel = (char*)malloc(strlen(token) + 1);
			strcpy(s->denumire_hotel, token);
			token = strtok(NULL, sep);
			s->nume_coordonator = (char*)malloc(strlen(token) + 1);
			strcpy(s->nume_coordonator, token);
			push(&cap, s);
		}
		fclose(f);
	}
	parcurgereListaDubla(cap);///ex1
	//ex2
	printf("-----------------\n");
	printf("%d", nrElemente(cap));
	SejurTuristic** vector = (SejurTuristic**)malloc(sizeof(SejurTuristic*)*nrElemente(cap));
	vector = determinareSejururiTuristice(cap);
	for (int i = 0; i < nrElemente(cap); i++) {
		afisareSejurTuristic(vector[i]);
	}
	//ex3
	printf("--------------\n");
	ListaDeListe* lista = NULL;
	Lista* l = NULL;
	pushListaDeListe(cap, &lista, &l);
	parcurgereListaDeListe(lista);
	//ex4
	printf("--------------\n");
	printf("Incasarile totale pentru destinatia mamaia cu o perioada specificata sunt:%.2f\n",
	determinareTotalIncasari(cap, 1, 15, "Mamaia"));
	//ex5
	deleteAllNodes(cap);
	printf("Lista dubla a fost stearsa\n");
	free(vector);
	vector = NULL;
	printf("Vectorul a fost sters\n");
	deleteLista(&l);
	deleteListaDeListe(&lista);
	printf("Lista de liste a fost stearsa\n");

}