#define _CRT_SECURE_NO_WARNINGS
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "RingInfo.h"
#include "Matrix.h"
#include "in_output.h"



char* readline2() {
    char buf[81] = { 0 };  // BUFSIZ - константа для длины буфера
    char* res = NULL;
    int len = 0;
    int n = 0;

    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

int menu() {
    printf("0. Выход\n");
    printf("1. Ввод\n");
    printf("2. Вывод\n");
    printf("3. Обработка\n");
    int i;
    scanf("%d", &i);
    if (i == 0) {
        return -1;
    }
    return i;
}

Matrix* mtr(Matrix* matrix1, RingInfo *Ring) {
    int a = 0;
    int b = 0;
    int k = 0;
    while (a <= 0 || b <= 0) {
        scanf("%*c");
        if (k) printf("Некорректный ввод, попробуйте еще раз\n");
        scan_int(&a);
        scan_int(&b);
        k++;

    }
    matrix1 = CreateMatrix(a, b, Ring);
    return matrix1;
}

int dialog() {
    int i = 0;
    Matrix* matrix1 = NULL;
    Matrix* matrix2 = NULL;
    Matrix* matrix3 = NULL;
    char* x = NULL;
    RingInfo* Ring = NULL;
    int type = 0;
    while (i != -1) {
        switch (i) {
        case 0:
            i = menu();
            break;
        case 1:           
            i = 0;
            if (matrix1 != NULL) free(matrix1->ring);
            DeleteMatrix(matrix1);
            DeleteMatrix(matrix2);
            DeleteMatrix(matrix3);
            printf("Введите тип данных: 1 - Int\n2 - Double\n3 - Complex\n");
            int* ident = calloc(1, sizeof(int));
            scan_int(ident);
            if (ident == NULL) {
                printf("Некорректный ввод\n");
                scanf("%*c");
                break;
            }
            int k = 1;
            switch (*ident) {
            case 1:
                Ring = CreateRing(sizeof(int), zero_int, sum_int, mult_int, scan_int, output_int);
                type = 1;
                break;
            case 2:
                Ring = CreateRing(sizeof(double), zero_double, sum_double, mult_double, scan_double, output_double);
                type = 2;
                break;
            case 3:
                Ring = CreateRing(sizeof(Complex), zero_complex, sum_complex, mult_complex, scan_complex, output_complex);
                type = 3;
                break;
            default:
                k = 0;
                break;
            }
            free(ident);
            if (k == 0) break;
            printf("Введите размеры матрицы 1: ");
            matrix1 = mtr(matrix1, Ring);
            printf("Введите матрицу. Для этого введите %d строк по %d элементов в каждой\n", matrix1->num_line, matrix1->num_column);
            matrix1 = Input(matrix1);
            printf("Введите размеры матрицы 2: ");
            matrix2 = mtr(matrix2, Ring);
            printf("Введите матрицу. Для этого введите %d строк по %d элементов в каждой\n", matrix2->num_line, matrix2->num_column);
            matrix2 = Input(matrix2);
            break;
        case 2:
            i = 0;
            if (matrix1 == NULL) {
                printf("Матрица 1 не существует\n");
                break;
            }
            printf("Матрица 1\n");
            Output(matrix1);
            if (matrix2 == NULL) {
                printf("Матрица 2 не существует\n");
                break;
            }
            printf("Матрица 2\n");
            Output(matrix2);
            printf("Результат обработки: Матрица 3\n");
            Output(matrix3);
            break;
        case 3:
            i = 0;
            int* j = calloc(1, sizeof(int));
            printf("0. Выход\n");
            printf("1. Сумма двух матриц\n");
            printf("2. Произведение двух матриц\n");
            printf("3. Транспонирование матрицы\n");
            printf("4. Прибавление к строке линейной комбинации других\n");
            scan_int(j);
            if (j == NULL) {
                printf("Некорректный ввод");
                free(j);
                scanf("%*c");
                break;
            }
            int l = 0;
            char ident2 = ' ';
            char ident3 = ' ';
            char ident4 = ' ';
            switch (*j) {
            case 0:
                break;
            case 1:
                matrix3 = (Matrix*)SumMatrix(matrix1, matrix2, matrix3);
                break;
            case 2:
                matrix3 = (Matrix*)MultMatrix(matrix1, matrix2, matrix3);
                break;
            case 3:
                if (matrix1 != NULL) ident2 = '1';
                if (matrix2 != NULL) ident3 = '2';
                if (matrix3 != NULL) ident4 = '3';
                printf("Какую матрицу требуется транспонировать(%c %c %c)\n", ident2, ident3, ident4);
                scanf("%d", &l);
                if (l == 1)
                    matrix1 = (Matrix*)Transposition(matrix1);
                if (l == 2)
                    matrix2 = (Matrix*)Transposition(matrix2);
                if (l == 3)
                    matrix3 = (Matrix*)Transposition(matrix3);
                break;
            case 4:
                printf("Выберите матрицу: ");
                scanf("%d", &l);
                int num_line = 0;
                int position = 0;
                char* coeff = NULL;
                if (l == 1 && matrix1 != NULL) {
                    num_line = matrix1->num_line;
                    coeff = calloc(num_line, Ring->size);
                }
                if (l == 2 && matrix2 != NULL) {
                    num_line = matrix2->num_column;
                    coeff = calloc(num_line, Ring->size);
                }
                if (l == 3 && matrix3 != NULL) {
                    num_line = matrix2->num_column;
                    coeff = calloc(num_line, Ring->size);
                }                
                printf("Введите номер строки от 0 до %d: ", num_line - 1);
                scanf("%d", &position);
                if (l < 1 || l > 3 || position < 0 || position > num_line - 1) break;
                printf("\nВведите %d коэффициентов: \n", num_line);
                for (int i = 0; i < num_line; i++) {
                    Ring->scan(coeff + i * Ring->size);
                }
                Ring->zero(coeff + i * position);
                if (l == 1) LinearComb(matrix1, coeff, position);
                if (l == 2) LinearComb(matrix1, coeff, position);
                if (l == 3) LinearComb(matrix1, coeff, position);
                break;
            }
            free(j);
            break;
        default:
            x = readline2();
            free(x);
            i = 0;
        }
    }
    free(Ring);
    DeleteMatrix(matrix1);
    DeleteMatrix(matrix2);
    DeleteMatrix(matrix3);
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    dialog();
    _CrtDumpMemoryLeaks();
	return 0;
}