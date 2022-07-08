#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>


double y(double x) {	// Подынтегральная функция
	return 1. / x;
}

double intgr0(double f(double), double a, double b, int *n, double e) {		// Метод Эйлера
	double J0, J, h, x;
	J = 0.;
	h = (b - a) / *n; x = a;
	for (int i = 0; i < *n; i++) {	// Вычисление с начальным шагом
		J += h * f(x);
		x += h;
	}
	*n = 2 * *n;
	do {
		h = (b - a) / *n;		// Вычисление шага
		x = a;
		J0 = J; J = 0.;
		for (int i = 0; i < *n; i++) {
			J += h * f(x);
			x += h;
		}
		*n = 2 * *n;		// Увеличение количества разбиений интервала
	} while (fabs(J - J0) > e);		// Проверка достижения абсолютной прогрешности
	return J;
}

double intgr2(double f(double), double a, double b, int* n, double e) {		// Метод 1/3 Симпсона
	double J0, J, h, f1, f2;
	h = (b - a) / *n; f1 = 0, f2 = 0;
	for (int i = 1; i < *n; i += 2) {	// Вычисление с начальным шагом
		f1 += f(a + i * h);
		f2 += f(a + (i + 1) * h);
	}
	J = (h / 3) * (f(a) + 4 * f1 + 2 * f2 + f(b));
	*n = 2 * *n;
	do {
		h = (b - a) / *n;
		f1 = 0, f2 = 0;
		J0 = J;
		for (int i = 1; i < *n; i += 2) {
			f1 += f(a + i * h);
			f2 += f(a + (i + 1) * h);
		}
		J = (h / 3) * (f(a) + 4 * f1 + 2 * f2 + f(b));
		*n = 2 * *n;
	} while (fabs(J - J0) > e);
	return J;
}

int main() {
	FILE* output_file = fopen("output.txt", "w");
	double l, r, eps, J1, J2;
	printf("Enter limits of integration:\n");
	printf("Left border: "); scanf("%lf", &l);
	printf("Right border: "); scanf("%lf", &r);
	printf("Enter accurancy: "); scanf("%lf", &eps);
	int N1 = 1, N2 = 1;
	J1 = intgr0(y, l, r, &N1, eps);
	printf("\nEuler method: %lf", J1);
	fprintf(output_file, "%s", "Euler method: "); fprintf(output_file, "%lf\n", J1);
	J2 = intgr2(y, l, r, &N2, eps);
	printf("\nSimpson method: %lf", J2);
	fprintf(output_file, "%s", "Simpson method: "); fprintf(output_file, "%lf\n", J2);
	if (N1 > N2) {
		printf("\nEuler amt (%d) > Simpson amt (%d) \n", N1/2, N2/2);
		fprintf(output_file, "Euler amt (%d) > Simpson amt (%d) \n", N1/2, N2/2);
	}
	else {
		printf("\nEuler amt (%d) <= Simpson amt (%d) \n", N1/2, N2/2);
		fprintf(output_file, "Euler amt (%d) > Simpson amt (%d) \n", N1/2, N2/2);
	} fclose(output_file); return 0;
}