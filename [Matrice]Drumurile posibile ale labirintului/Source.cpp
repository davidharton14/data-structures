#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

int main() {
	int n, numar;
	int arr[100][100];
	printf("Introduceti dimensiunea matricei:");
	scanf("%d", &n);
	int k = 0;
	int a, b;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("a[%d][%d]=", i, j);
			scanf("%d", &numar);
			arr[i][j] = numar;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	printf("ALEGE PUNCTUL DE PORNIRE\n");
	printf("a=");
	scanf("%d", &a);
	printf("b=");
	scanf("%d", &b);
	int sw = 0;
	int* arrS = (int*)malloc(sizeof(int)*n);
	int* arrD = (int*)malloc(sizeof(int)*n);
	int* arrJ = (int*)malloc(sizeof(int)*n);
	int* arrSu = (int*)malloc(sizeof(int)*n);
	int l = 0;
	int m = 0, nr = 0,o=0,p=0;
	printf("Drumul catre iesire parcurs la stanga este:START -> ");
	for (int i = 0; i < n; i++) {
		int j = 0;
		while (j < n) {
			if (i == a && j == b) {
				sw = 1;
			}
			if (sw) {
				if (arr[i][j] == 1) {
					printf("a[%d][%d]=1 -> ", i, j);
					//arrS[l] = 1;
					if (j == 0) {
						if (nr == 0)
							l = -1;
						i = n;
						j = n;
					}
					j = j - 1;
					l++;
					nr++;
				}else {
					i = n;
					j = n;
				}
			}else {
				j++;
			}
		}
	}
	sw = 0;
	m = 0,nr=0;
	printf("IESIRE");
	printf("\n\n");
	printf("Drumul catre iesire parcurs in jos este:START -> ");
	for (int i = 0; i < n; i++) {
		int j = 0;
		while (j < n) {
			if (i == a && j == b) {
				sw = 1;
			}
			if (sw) {
				nr = 0;
				if (arr[i][j] == 1) {
					printf("a[%d][%d]=1 -> ", i, j);
					//arrJ[m] = 1;
					if (i == n+1) {
						if (nr == 0)
							m = -1;
						i = n;
						j = n;
					}
					i++;
					m++;
					nr++;
				}else {
					i = n;
					j = n;
				}
			}else {
				j++;
			}
		}
	}
	nr = 0;
	o = 0;
	p = 0;
	sw = 0;
	printf("IESIRE");
	printf("\n\n");
	printf("Drumul catre iesire parcurs la dreapta este:START -> ");
	for (int i = 0; i < n; i++) {
		int j = 0;
		while (j < n) {
			if (i == a && j == b) {
				sw = 1;
			}
			if (sw) {
				nr = 0;
				if (arr[i][j] == 1) {
					printf("a[%d][%d]=1 -> ", i, j);
					//arrD[o] = 1;
					if (j == n + 1) {
						if (nr == 0)
							o = -1;
						i = n;
						j = n;
					}
					i++;
					o++;
					nr++;
				}
				else {
					i = n;
					j = n;
				}
			}
			else {
				j++;
			}
		}
	}
	sw = 0;
	printf("IESIRE");
	printf("\n\n");
	printf("Drumul catre iesire parcurs in sus este:START -> ");
	for (int j = 0; j < n; j++) {
		int i = 0;
		while (i < n) {
			if (i == a && j == b) {
				sw = 1;
			}
			if (sw) {
				nr = 0;
				if (arr[i][j] == 1) {
					printf("a[%d][%d]=1 -> ", i, j);
					//arrSu[p] = 1;
					if (i == 0) {
						if (nr == 0)
							p = -1;
						i = n;
						j = n;
					}
					i--;
					p++;
					nr++;
				}
				else {
					i = n;
					j = n;
				}
			}
			else {
				i++;
			}
		}
	}
	printf("IESIRE");
	printf("\n\n");
	//printf("Lungimea drumului este %d\n\n", l);
	//if (l !=0) {
	//	printf("Drumul catre iesire parcurs la stanga este:\n");
	//	for (int i = 0; i < l; i++) {
	//		printf("%d ", arrS[i]);
	//	}
	//}
	//printf("\n");
	//printf("Lungimea drumului este %d\n\n", o);
	//if (o != 0) {
	//	printf("Drumul catre iesire parcurs in dreapta este:\n");
	//	for (int i = 0; i < o; i++) {
	//		printf("%d ", arrD[i]);
	//	}
	//}
	//printf("\n");
	//printf("Lungimea drumului este %d\n\n", p);
	//if (p != 0) {
	//	printf("Drumul catre iesire parcurs in sus este:\n");
	//	for (int i = 0; i < p; i++) {
	//		printf("%d ", arrSu[i]);
	//	}
	//}
	//printf("\n");
	//printf("Lungimea drumului este %d\n\n", m);
	//if (m != 0) {
	//	printf("Drumul catre iesire parcurs in jos este:\n");
	//	for (int i = 0; i < m; i++) {
	//		printf("%d ", arrJ[i]);
	//	}
	//}
}