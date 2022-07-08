#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Интерполяция полинома Лагранжа

double lagr(int n, double* xt, double* yt, double x) {
    double res = 0;
    double p;
    for (int i = 0; i < n; i++) {
        p = 1;
        for (int j = 0; j < n; j++) {
            if (j == i) p *= (x - xt[j]) / (xt[i] - xt[j]);
        }
        res += p * yt[i];
    }
    return res;
}

int main(void) {
    const int size = 8;
    double* xt = (double*)malloc(size * sizeof(double));
    double* yt = (double*)malloc(size * sizeof(double));
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");
    if (input_file == NULL) return 0;
    for (int i = 0; i < size; i++) {
        fscanf(input_file, "%lf", &xt[i]);
        fscanf(input_file, "%lf", &yt[i]);
    }
    fclose(input_file);
    double y, x = 0.0;
    for (;;) {
        if (x <= 5) {
            y = lagr(size, xt, yt, x);
            printf("%f : %lf\n", x, y);
            fprintf(output_file, "%f : %lf\n", x, y);
            x += 0.1;
        }
    }
    fclose(output_file);
    return 0;
}