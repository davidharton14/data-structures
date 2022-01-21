#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
struct Produs {
	char* nume;
	/*unsigned char numar_magazine;*/
	int id_produs;
	float pret;
	int cantitate;
};
struct hashtable_item
{
	Produs*data;
};
void init_array(hashtable_item* arr,int nr)
{
	for (int i = 0; i < nr; i++)
	{
		arr[i].data = NULL;
	}
}
void displayProdus(Produs* p) {
	printf("Nume:%s\nId produs:%d\n", p->nume, p->id_produs);
	printf("\n");
	printf("Pret:%.2f\nCantitate:%d\n\n", p->pret, p->cantitate);
}

int CalculateHash(int key,int m,int a,int b)
{
	printf("---------------------\n\n%d", ((a*key) + ((3 * b)*(key ^ 2))) % m);
	return ((a*key) + ((3 * b)*(key ^ 2))) % m;
}

void Insert(hashtable_item* &arr, Produs* p, int m, int a, int b)
{
	int probe = CalculateHash(p->id_produs, m, a, b);
	int sw = 0;
	while (arr[probe].data != NULL)
	{
		sw = 1;
		probe = (probe + 1) % m;
	}
	arr[probe].data = p;
}
void PrintTabelaDeDispersie(hashtable_item* arr,int m)
{
	for (int i = 0; i < m; i++) {
		if (arr[i].data) {
			displayProdus(arr[i].data);
		}
	}
}
int Search(hashtable_item* arr, Produs* p, int m, int a, int b)
{
	int probe = CalculateHash(p->id_produs,m,a,b);
	while (arr[probe].data != 0)
	{
		if (arr[probe].data == p)
			return probe;
		probe = (probe + 1) % m;
	}
	printf("\nElement %d not found.\n", p);
	return -1;
}

void Delete(hashtable_item* arr, Produs* p, int m, int a, int b)
{
	int loc = Search(arr, p,m,a,b);
	if (loc != NULL)
	{
		arr[loc].data = NULL;
	}
}
void deleteHT(hashtable_item* arr,int m) {

	for (int i = 0; i < m; i++)
	{
		if (arr[i].data) {
			free(arr[i].data);
		}
	}
	free(arr);
}
void main() {
	Produs* p = NULL;
	int dim,a,b;
	printf("Dimensiunea tabelei de dispersie:");
	scanf("%d", &dim);
	printf("a=");
	scanf("%d", &a);
	printf("b=");
	scanf("%d", &b);
	hashtable_item* array = (hashtable_item*)malloc(dim * sizeof(hashtable_item));
	init_array(array,dim);
	for (int i = 0; i < dim; i++) {
		
		p = (Produs*)malloc(sizeof(Produs));
		char numee[50];
		printf("Denumire produs:");
		scanf("%s", &numee);
		p->nume = (char*)malloc(strlen(numee) + 1);
		strcpy(p->nume, numee);
		int id;
		printf("Id produs:");
		scanf("%d", &id);
		p->id_produs = id;
		int prett;
		printf("Pret produs:");
		scanf("%d", &prett);
		p->pret = prett;
		int cantitatee;
		printf("Cantitate produs:");
		scanf("%d", &cantitatee);
		p->cantitate = cantitatee;
		Insert(array, p, dim, a, b);
	}
	PrintTabelaDeDispersie(array,dim);
}
