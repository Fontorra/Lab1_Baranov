#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Matrix.h"

Matrix* CreateMatrix(int a, int b, RingInfo* ring) {
    Matrix* matr = (Matrix*)calloc(1, sizeof(struct Matrix));
    void** matrix = calloc(a, sizeof(void*));
    for (int i = 0; i < a; i++) {
        void* new_line = calloc(b, ring->size);
        *((char**)matrix + i) = new_line;
    }
    matr->matrix = matrix;
    matr->ring = ring;
    matr->num_line = a;
    matr->num_column = b;
    return matr;
}

void* DeleteMatrix(Matrix *matrix) {
    if (matrix == NULL) return NULL;
    for (int i = 0; i < matrix->num_line;i++) {
        free(*((char**)matrix->matrix + i));
    }
    free(matrix->matrix);
    free(matrix);
}

void* SumMatrix(Matrix* matrix1, Matrix* matrix2, Matrix* res) {
    if (matrix1 == NULL || matrix2 == NULL) return res;
    if (matrix1->num_line != matrix2->num_line || matrix1->num_column != matrix2->num_column) {
        printf("Ќевозможно сложить две матрицы.\n");
        return res;
    }
    DeleteMatrix(res);
    int line = matrix1->num_line;
    int column = matrix1->num_column;
    RingInfo* ring = matrix1->ring;
    res = CreateMatrix(line, column, ring);
    size_t size = ring->size;
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            ring->sum((char*)(*((char**)matrix1->matrix + i)) + j * size,
                (char*)(*((char**)matrix2->matrix + i)) + j * size,
                (char*)(*((char**)res->matrix + i)) + j * size);
        }
    }
    return res;
}

void* MultMatrix(Matrix* matrix1, Matrix* matrix2, Matrix* res) {
    if (matrix1 == NULL || matrix2 == NULL) return res;
    if (matrix1->num_column != matrix2->num_line) {
        printf("Ќевозможно найти произведение двух матриц\n");
        return res;
    }
    DeleteMatrix(res);
    int line = matrix1->num_line;
    int column = matrix2->num_column;
    int kol = matrix1->num_column;
    RingInfo* ring = matrix1->ring;
    size_t size = ring->size;
    res = CreateMatrix(line, column, ring);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            ring->zero((char*)(*((char**)res->matrix + i)) + j * size);
            for (int k = 0; k < kol; k++) {
                char* t = calloc(1, size);
                ring->mult((char*)(*((char**)matrix1->matrix + i)) + k * size, (char*)(*((char**)matrix2->matrix + k)) + j * size, t),
                    ring->sum((char*)(*((char**)res->matrix + i)) + j * size, t, 
                    (char*)(*((char**)res->matrix + i)) + j * size);
                free(t);
            }
        }
    }
    return res;
}

void* Transposition(Matrix* matrix) {
    if (matrix == NULL) return NULL;
    int line = matrix->num_line;
    int column = matrix->num_column;
    RingInfo* ring = matrix->ring;
    size_t size = ring->size;
    Matrix* new_matrix = CreateMatrix(column, line, ring);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            memcpy((char*)(*((char**)new_matrix->matrix + j)) + i * size,
                (char*)(*((char**)matrix->matrix + i)) + j * size,
                size);
        }
    }
    DeleteMatrix(matrix);
    return new_matrix;
}

void* LinearComb(Matrix* matrix, void* coeff, int position) {
    RingInfo* ring = matrix->ring;
    size_t size = ring->size;
    for (int j = 0; j < matrix->num_column; j++) { //j элемент строки position
        for (int i = 0; i < matrix->num_line; i++) {
            for (int k = 0; k < matrix->num_line; k++) { // k элемент строки i
                char* t = calloc(1, size);
                ring->mult((char*)(*((char**)matrix->matrix + i)) + k * size, (char*)coeff + k * size, t);
                ring->sum((char*)(*((char**)matrix->matrix + position)) + j * size,
                    t, (char*)(*((char**)matrix->matrix + position)) + j * size);
                free(t);
            }
        }
    }
    return matrix;
}

//транспонирование, прибавление к строке линейной комбинации других.





