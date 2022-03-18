#ifndef matrix_h
#define matrix_h

#include <stdio.h>

#include "RingInfo.h"

typedef struct Matrix {
	void** matrix; //указатель на начало матрицы
	int num_line; //stroki
	int num_column; // stolbci
	RingInfo* ring;
} Matrix;


Matrix* CreateMatrix();
void* DeleteMatrix(Matrix* matrix);
void* Transposition(Matrix* matrix);
void* MultMatrix(Matrix* matrix1, Matrix* matrix2, Matrix* res);
void* SumMatrix(Matrix* matrix1, Matrix* matrix2, Matrix* res);
#endif