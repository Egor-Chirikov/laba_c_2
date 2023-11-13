#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include "windows.h"

#define N 42
#define TIME_TO_SLEEP_ITERATIONS_STANDARD 1000
#define TIME_TO_SLEEP_INPUT 10

void clear() {
	char buff;
	while (scanf("%c", &buff))
		if (buff == '\n')
			return;
}

int myIntInput(char str_out[], char str_err[]) {
	int inp;	
	while (1) {
		printf(str_out);
		if (scanf("%i", &inp))
			break;
		printf(str_err);
		clear();
	}
	clear();
	return inp;
}

int scanMat(int pMat[][N], int clStr, int clSlb) {
	for (int i = 0; i < clStr; ++i)
		for (int j = 0; j < clSlb; ++j)
			if (!scanf("%i", &pMat[i][j])) {
				clear();
				return 0;
			}
	clear();
	return 1;
}

void printMat(int pMat[][N], int clStr, int clSlb) {
	for (int i = 0; i < clStr; ++i) {
		for (int j = 0; j < clSlb; ++j)
			printf("%i ", pMat[i][j]);
		printf("\n");
	}
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void step(int mas[][N], int strt_i, int strt_j, int end_i, int end_j, int dl_j) {
	int i = strt_i;
	int j = strt_j;
	int buff = mas[i][j];

	for (j++; dl_j >= 1 && j < end_j; j++) {
		swap(&mas[i][j], &buff);
	}
	j--;

	for (i++; i < end_i; i++) {
		swap(&mas[i][j], &buff);
	}
	i--;

	for (j -= dl_j; j >= strt_j && j < end_j; j -= dl_j) {
		swap(&mas[i][j], &buff);
	}
	j += dl_j;

	for (i--; i >= strt_i; i--) {
		swap(&mas[i][j], &buff);
	}
	i++;

	for (j--; dl_j <= -1 && j >= strt_j; j--) {
		swap(&mas[i][j], &buff);
	}
}

int checkTheKeyDown(char key) {
	if (_kbhit() && _getch() == key)
		return 1;
	return 0;
}

long long myPow(unsigned int num, unsigned int stepn) {
	long ret = 1;
	long retRem = 1;
	for (int i = 0; i < stepn; i++) {
		retRem = ret;
		ret *= num;
		if (ret < retRem)
			return -1;
	}
	return ret;
}

int myAtoi(char str[], int ln) {
	char strtNum = '0', endNum = '9';
	int sum = 0, sumRem = 0, mnoch;
	for (int i = ln - 1; i >= 0; i--) {
		mnoch = myPow(10, ln - i - 1);
		if (mnoch == -1)
			return -1;

		if (!(strtNum <= str[i] && str[i] <= endNum))
			return -1;

		sumRem = sum;
		sum += (str[i] - strtNum) * mnoch;

		if (sum < sumRem)
			return -1;
	}
	return sum;
}

int strLen(char str[]) {
	int ln = 0;
	for (; str[ln] != '\0'; ln++);
	return ln;
}

int main(int argc, char* argv[]) {
	int ln, mat[N][N], dl_j, strt_i, strt_j, end_i, end_j, time = 0, tim_to_sleep_iter = TIME_TO_SLEEP_ITERATIONS_STANDARD;

	setlocale(LC_ALL, "Russian");

	if (argc >= 2) {
		tim_to_sleep_iter = myAtoi(argv[1], strLen(argv[1]));
		if (tim_to_sleep_iter == -1) {
			printf("Использование параметра {%s} не возможно. Используется значение по умолчанию {%i}", argv[1], TIME_TO_SLEEP_ITERATIONS_STANDARD);
			tim_to_sleep_iter = TIME_TO_SLEEP_ITERATIONS_STANDARD;
		}
	}

	ln = myIntInput("\nВведите размер массива: ", "\n!!!Неверный ввод!!!");
	do {
		printf("Введите массив размером %i*%i\n", ln, ln);
	} while (!scanMat(mat, ln, ln));
	

	while (42){
		Sleep(TIME_TO_SLEEP_INPUT);
		time += TIME_TO_SLEEP_INPUT;

		if (checkTheKeyDown(' ')) 
			while (!checkTheKeyDown(' '))
				Sleep(TIME_TO_SLEEP_INPUT);		

		if (time >= tim_to_sleep_iter) {
			time = 0;
			dl_j = -1;
			strt_i = 0;
			strt_j = 0;
			end_i = ln;
			end_j = ln;

			while (strt_i < end_i && strt_j < end_j) {
				step(mat, strt_i, strt_j, end_i, end_j, dl_j);
				strt_i++;
				strt_j++;
				end_i--;
				end_j--;
				dl_j = -dl_j;
			}

			printf("\n");
			printMat(mat, ln, ln);
		}
	}
}

/*

5
1 2 3 4 1
5 6 7 8 2
9 0 1 2 3
3 4 5 6 4
5 6 7 8 9


4
1 2 3 4
5 6 7 8
9 0 1 2
3 4 5 6

3
1 2 3 
5 6 7 
9 0 1 

*/