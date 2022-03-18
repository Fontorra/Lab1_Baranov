#ifndef ringinfo_h
#define ringinfo_h

#include <stdio.h>

typedef struct RingInfo {
	size_t size;
	void (*zero)(void*);
	void (*sum)(void*, void*, void*);
	void (*mult)(void*, void*, void*); 
	void* (*scan)();
	void (*output)(void*);
} RingInfo;

typedef struct Complex {
	double Re;
	double Im;
} Complex;

RingInfo* CreateRing(
	size_t size,
	void (*zero)(void*),
	void (*sum)(void*, void*, void*),
	void (*mult)(void*, void*, void*),
	void* (*scan)(),
	void (*output)(void*));
void zero_int(void* x);
void zero_double(void* x);
void zero_complex(void* x);
void sum_int(void* x, void* y, void* res);
void sum_double(void* x, void* y, void* res);
void sum_complex(void* x, void* y, void* res);
void mult_int(void* x, void* y, void* res);
void mult_double(void* x, void* y, void* res); 
void mult_complex(void* x, void* y, void* res);
void* scan_double();
void* scan_int();
void* scan_complex(void* x);
void output_int(void* x);
void output_double(void* x);
void output_complex(void* x);
#endif