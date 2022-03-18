#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Matrix.h"
#include "in_output.h"

void* Input(Matrix* matr) {
	for (int i = 0; i < matr->num_line; i++) {
		for (int j = 0; j < matr->num_column; j++) {
			char* t = matr->ring->scan((char*)(*((char**)matr->matrix + i)) + j * matr->ring->size);
			if (t == NULL) {
				printf("Некорректный ввод\n");
				return NULL;
			}
		}
	}
}

void* Output(Matrix* matr) {
	if (matr == NULL) return NULL;
	for (int i = 0; i < matr->num_line; i++) {
		for (int j = 0; j < matr->num_column; j++) {
			matr->ring->output((char*)(*((char**)matr->matrix + i)) + j * matr->ring->size);
		}
		printf("\n");
	}
}

