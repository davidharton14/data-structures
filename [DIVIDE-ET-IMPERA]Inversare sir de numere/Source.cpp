#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void dac(int *v, int begin, int end);

void dac(int *v, int beg, int enn)
{

	//base: size==1
	if (enn == beg) {  //don't do anything
	}
	else
	{
		int mid = (beg + enn) / 2;
		int j;
		dac(v, beg, mid);
		dac(v, mid + 1, enn);
		if (mid % 2 == 0)   //size is even
		{
			int g = 0;
			for (j = beg; j <= mid; j++, g++)
			{
				int aux = v[j];
				v[j] = v[g + mid + 1];
				v[g + mid + 1] = aux;
			}
		}

		else {     //odd
			int h, aux2, g;
			g = 1;
			for (h = beg + 1; h <= mid; h++, g++)
			{
				aux2 = v[h];
				v[h] = v[mid + g];
				v[mid + g] = aux2;
			}
			int z;
			for (z = beg; z < mid; z++)
			{
				int aux3;
				aux3 = v[z];
				v[z] = v[z + 1];
				v[z + 1] = aux3;
			}
		}
	}
}
int main()
{
	int i, k;     //iterators
	int *v = (int*)malloc(6 * sizeof(int));
	//int v[6];
	for (i = 0; i < 7; i++)
	{
		printf(" v[%d]: ", i);
		scanf("%d", &v[i]);
	}
	printf("\nThe array is:\n");
	for (k = 0; k < 7; k++)
	{
		printf("v[%d]= %d ", k, v[k]);
	}
	printf("\n");
	dac(v, 0, 6);   //first call
	printf("The array, in the reverse order, is:\n");
	for (k = 0; k < 7; k++)
	{
		printf("v[%d]= %d ", k, v[k]);
	}
	printf("\n");
	return 0;
}