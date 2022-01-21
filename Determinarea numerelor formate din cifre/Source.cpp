#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

int main() {
	int nr_c, n;
	int* arr,*sir,k=0,contor;
	printf("Introduceti numarul de cifre:");
	scanf("%d", &nr_c);
	printf("n=");
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int)*nr_c);
	int number = 0;
	for (int i = 0; i < nr_c; i++) {
		printf("Enter a digit: ");
		int tmp;
		scanf("%d", &tmp);
		arr[k] = tmp;
		k++;
	}
	contor=0;
	for (int i = 0; i < nr_c; i++) {
		int number_2digits = 0;
		int number_2digitss = 0;
		if (arr[i] % 2 == 0) {
			contor++;
		}
		for (int j = i+1; j < nr_c; j++) {
				number_2digits = arr[j] * 10 + arr[i];
				number_2digitss = arr[i] * 10 + arr[j];
				if (number_2digits % 2 == 0 &&
					number_2digits != number_2digitss) {
					contor++;
				}
				if (number_2digitss % 2 == 0 &&
					number_2digits != number_2digitss) {
					contor++;
				}
	
		}	
	}
	int m = 0;
		for (int i = 0; i < nr_c; i++) {
			int number_3digits = 0;
			int number_3digitss = 0;
			for (int j = 0; j < nr_c; j++) {
				number_3digits = arr[i] * 10 + arr[j];
				number_3digitss = arr[j] * 10 + arr[i];
				for (int k = j + 1; k < nr_c; k++) {
					
					number_3digits = number_3digits * 10 + arr[k];
					number_3digitss = number_3digitss * 10 + arr[k];
					if (number_3digits < n) {
						if (number_3digits % 2 == 0) {
							contor++;
						}
					}
					if (number_3digitss < n) {
						if (number_3digitss % 2 == 0) {
							contor++;
						}
					}
				}
			}
	}
	sir = (int*)malloc(sizeof(int)*contor);
	int l = 0;
	for (int i = 0; i < nr_c; i++) {
		int number_2digits = 0;
		int number_2digitss = 0;
		if (arr[i] % 2 == 0) {
			sir[l]=arr[i];
			l++;
		}
		for (int j =i+1; j < nr_c; j++) {
				number_2digits = arr[j] * 10 + arr[i];
				number_2digitss = arr[i] * 10 + arr[j];
				if (number_2digits % 2 == 0 &&
					number_2digits != number_2digitss) {
					sir[l] = number_2digits;
					l++;
				}
				if (number_2digitss % 2 == 0 &&
					number_2digits != number_2digitss) {
					sir[l] = number_2digitss;
					l++;
				}
		}
	}
		for (int i = 0; i < nr_c; i++) {
			int number_3digits = 0;
			int number_3digitss = 0;
			for (int j = 0; j < nr_c; j++) {
				number_3digits = arr[i] * 10 + arr[j];
				number_3digitss = arr[j] * 10 + arr[i];
				for (int k = j + 1; k < nr_c; k++) {
					number_3digits = number_3digits * 10 + arr[k];
					number_3digitss = number_3digitss * 10 + arr[k];
					if (number_3digits < n) {
						if (number_3digits % 2 == 0) {
							sir[l] = number_3digits;
							l++;
						}
					}
					if (number_3digitss < n) {
						if (number_3digitss % 2 == 0) {
							sir[l] = number_3digitss;
							l++;
						}
					}
				}
			}
	}
	for (int i = 0; i < contor; i++) {
		printf("%d\n", sir[i]);
	}
}