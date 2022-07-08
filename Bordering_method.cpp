#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int invmatr(int n, const double* a, double* b) {
	double* p = (double*)malloc(n * sizeof(double));
	double* w = (double*)malloc(n * sizeof(double));
	if (a[0] == 0.) return 1;
	else {
		b[0] = 1 / a[0];
		for (int k = 1; k < n; k++) {
			for (int j = 0; j < k; j++) {	// Вычисление столбца
				double sum = 0;
				for (int m = 0; m < k; m++) sum += b[j * n + m] * a[m * n + k];
				p[j] = sum;
			}
			for (int j = 0; j < k; j++) {	// Вычисление строки
				double sum = 0;
				for (int m = 0; m < k; m++) sum += b[m * n + j] * a[k * n + m];
				w[j] = sum;
			}
			double sum = 0;
			for (int i = 0; i < k; i++) sum += a[k * n + i] * p[i];
			double alf = a[k * n + k] - sum;	// Вычисление скаляра
			if (alf == 0.) return 1;
			else {
				for (int i = 0; i < k; i++) {	// Создание обратной матрицы
					for (int j = 0; j < k; j++) {
						b[i * n + j] += ((p[i] * w[j]) / alf);
					}
				}
				for (int i = 0; i < k; i++) {	// Окаймление матрицы
					b[i * n + k] = -p[i] / alf;
					b[k * n + i] = -w[i] / alf;
				}
				b[n * k + k] = 1 / alf;
			}
		}
		free(p); free(w);
		return 0;
	}
}

int main() {
	int n;
	FILE* input_file = fopen("input.txt", "r");
	FILE* output_file = fopen("output.txt", "w");
	if (input_file == NULL) return 0;
	printf("%s","Enter matrix size: "); scanf("%d", &n);
	double* A = (double*)malloc(n * n * sizeof(double));
	double* B = (double*)malloc(n * n * sizeof(double));
	double* C = (double*)malloc(n * n * sizeof(double));
	for (int i = 0; i < n * n; i++) fscanf(input_file, "%lf", &A[i]);
	for (int i = 0; i < n * n; i++) fscanf(input_file, "%lf", &C[i]);
	fclose(input_file);
	if (invmatr(n, A, B) == 0) {
		fprintf(output_file, "%s", "Matrix 1 successfully inverted\n");
		for (int i = 0; i < n * n; i++) fprintf(output_file, "%f\n", B[i]);
		printf("%s", "\nMatrix 1 successfully inverted:\n");
		for (int i = 0; i < n * n; i++) {
			printf("%lf", B[i]); printf("%s", ",");
			if ((i + 1) % n == 0) printf("%s", "\n");
		}
		printf("%s", "\n");
		double tmp;
		printf("%s", "Matrix multiplication check:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tmp = 0;
				for (int k = 0; k < n; k++) tmp += A[j * n + k] * B[k * n + i];
				if (((i == j) & (fabs(round(tmp)) == 1)) || ((i != j) & (fabs(round(tmp)) == 0))) {
					printf("%f", tmp); printf("%s", ",");
				}
				else {
					printf("%s", "Checking failed\n");
					return 1;
				}
			}
			printf("%s", "\n");
		}
	}
	else {
		fprintf(output_file, "%s", "Matrix 1 can't be inverted by this method\n");
		printf("%s", "\nMatrix 1 can't be inverted by this method\n");
	}
	if (invmatr(n, C, B) == 0) {
		fprintf(output_file, "%s", "Matrix 2 successfully inverted\n");
		for (int i = 0; i < n * n; i++) fprintf(output_file, "%f\n", B[i]);
		printf("%s", "\nMatrix 2 successfully inverted:\n");
		for (int i = 0; i < n * n; i++) {
			printf("%f", B[i]); printf("%s", ",");
			if ((i + 1) % n == 0) printf("%s", "\n");
		}
		printf("%s", "\n");
		double tmp;
		printf("%s", "Matrix multiplication check:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tmp = 0;
				for (int k = 0; k < n; k++) tmp += C[j * n + k] * B[k * n + i];
				if (((i == j) & (fabs(round(tmp)) == 1)) || ((i != j) & (fabs(round(tmp)) == 0))) {
					printf("%f", tmp); printf("%s", ",");
				}
				else {
					printf("%s", "Checking failed\n");
					return 1;
				}
			}
			printf("%s", "\n");
		}
	}
	else {
		fprintf(output_file, "%s", "Matrix 2 can't be inverted by this method\n");
		printf("%s", "\nMatrix 2 can't be inverted by this method\n");
	}
	fclose(output_file);
	free(A); free(B); free(C);
	return 0;
}
