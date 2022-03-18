#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "RingInfo.h"
RingInfo* CreateRing(
	size_t size,
	void (*zero)(void*),
	void (*sum)(void*, void*, void*),
	void (*mult)(void*, void*, void*),
	void* (*scan)(),
	void (*output)(void*)) {
	RingInfo* ringinfo = calloc(1, sizeof(RingInfo));
	ringinfo->size = size;
	ringinfo->zero = zero;
	ringinfo->sum = sum;
	ringinfo->mult = mult;
	ringinfo->scan = scan;
	ringinfo->output = output;
	//ringinfo->mult_scalar->mult->scalar;
}

//output

void output_int(void* x) {
	printf("%d ", *((int*)x));
}

void output_double(void* x) {
	printf("%lf ", *((double*)x));
}

void output_complex(void* x) {
	printf("%.1lf + %.1lfi ", ((Complex*)x)->Re, ((Complex*)x)->Im);
}
//zero

void zero_int(void* x) {
	*(int*)x = 0;
}

void zero_double(void* x) {
	*(double*)x = 0.0;
}

void zero_complex(void* x) {
	((Complex*)x)->Re = 0;
	((Complex*)x)->Im = 0;
}
//sum

void sum_int(void* x, void *y, void *res) {
	*(int*)res = *(int*)x + *(int*)y;
}

void sum_double(void* x, void* y, void* res) {
	*(double*)res = *(double*)x + *(double*)y;
}

void sum_complex(void* x, void* y, void* res) {
	((Complex*)res)->Re = ((Complex*)x)->Re + ((Complex*)y)->Re;
	((Complex*)res)->Im = ((Complex*)x)->Im + ((Complex*)y)->Im;
}
//mult

void mult_int(void* x, void* y, void* res) {
	*(int*)res = *(int*)x * *(int*)y;
}

void mult_double(void* x, void* y, void* res) {
	*(double*)res = *(double*)x * *(double *)y;
}

void mult_complex(void* x, void* y, void* res) {
	((Complex*)res)->Re = ((Complex*)x)->Re * ((Complex*)y)->Re - ((Complex*)x)->Im * ((Complex*)y)->Im;
	((Complex*)res)->Im = ((Complex*)x)->Re * ((Complex*)y)->Im + ((Complex*)x)->Im * ((Complex*)y)->Re;
}
//scan

void* scan_int(void *x) {
	int* res = (int *)x;
	int a = 0;
	int b = scanf("%d", &a);
	if (b <= 0) return NULL;
	*res = a;
	return res;
}

void* scan_double(void *x) {
	double* res = (double*)x;
	double a = 0;
	int b = scanf("%lf", &a);
	if (b <= 0) return NULL;
	*res = a;
	return res;
}

void* scan_complex(void* x) {
	Complex* res = (Complex*)x;
	double a = 0;
	double c = 0;
	int b = scanf("%lf", &a);
	if (b <= 0) return	NULL;
	b = scanf("%lf", &c);
	if (b <= 0) return NULL;
	res->Re = a;
	res->Im = c;
	return res;
}

//mult_scalar
