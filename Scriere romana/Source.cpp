#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#include<math.h>
using namespace std;
typedef struct {
	const char *sym;
	int val;
}numeral;
int maxNume(const numeral *nu, int num) {
	int i, index;
	for (i = 0; i < 15; i++) {//15 numerals in array
		if (nu[i].val <= num)
			index = i;
	}
	//gretest value numeral index, not greater than number
	return index;
}
void decToRoman(const numeral *nu, int num) {
	int max;
	if (num != 0) {
		max = maxNume(nu, num);
		printf("%s", nu[max].sym);
		num -= nu[max].val;//decrease number
		decToRoman(nu, num);//recursively print numerals
	}
}

void main() {
	double a, b, c;
	int m, n, p;
	char c1, c2;
	printf("a=");
	scanf("%ld", &a);
	printf("b=");
	scanf("%ld", &b);
	printf("c=");
	scanf("%ld", &c);

	printf("m=");
	scanf("%d", &m);
	printf("n=");
	scanf("%d", &n);
	printf("p=");
	scanf("%d", &p);

	/*printf("c1 si c2 ");
	scanf("%c%c", &c1, &c2);*/
	//ex1
	char caracter='A';
	int tasta=2;
	tasta = caracter;
	while (tasta != 43) {
		if(tasta!=10)
		printf("Tasteaza un caracter: ");
		caracter = getchar();
		tasta = caracter;
		if (tasta != 10) {
			if (caracter >= 'a'&&caracter <= 'z') {
				caracter = caracter - 32;
				printf("Caracterul tastat este: ");
				putchar(caracter);
				printf("\n");
			}
			else {
				printf("Caracterul tastat este: ");
				putchar(caracter);
				printf("\n");
			}
		}
	}
	//ex2
	int produs = 1;
	float suma = 0;
	int k = 0;
	if (m > 0) {
		if (m % 2 == 0) {
			produs *= m;
		}
	}
	if (n > 0) {
		if (n % 2 == 0) {
			produs *= n;
		}
	}
	if (p > 0) {
		if (p % 2 == 0) {
			produs *= p;
		}
	}
	printf("\nProdusul numerelor pare este: %d", produs);
	if (m > 0) {
		suma += m;
		k++;
	}
	if (n > 0) {
		suma += n;
		k++;
	}
	if (p > 0) {
		suma += p;
		k++;
	}
	printf("\nMedia aritmetica a numerelor pozitive este: %.2f", suma/k);
	//ex3
	int number;
	numeral nume[15] = { {"I",1},{"IV",4},{"V",5},{"IX",9}, {"X",10},{"XL",40},{"L",50},{"XC",90},
 {"C",100},{"CD",400},{"D",500},{"CM",900},{"M",1000},{"MMMM",4000},{"V'",5000} };
	printf("\nEnter a decimal number: ");
	scanf("%d", &number);
	if (number > 0 && number <= 100) {//checking input number
		printf("The Roman equivalent of %d is ", number);
		decToRoman(nume, number);
	}
	else {
		printf("Invalid Input");
	}
	printf("\n");
}
