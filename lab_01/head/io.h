#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <limits.h>

#define N 33
#define N_MAX 30
#define FLAG -8928342

typedef struct
{
    int sign;
    int size;
    short int *mant;
} num_t;

enum error_code
{
    ok,
    input_err,
    mantis_err,
    empty_input,
    over_flow,
    division_by_zero
};

void normalize_int(num_t *int_t);
void normalize_float(num_t *float_t, int dot, int *exponent);

#endif // IO_H