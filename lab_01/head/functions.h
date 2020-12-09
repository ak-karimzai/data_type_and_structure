#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

int count_zero(const num_t *input);
void move_digits(short int *arr_, const int size, int num_order);
void check_ten(short int *arr_float, short int *arr_int, int size, int *exp);

int comparison(short int *a, short int *b);
void subtract(short int *a, short int *b);
void division(short int *arr_float, short int *arr_int, short int *result, int *exp);
void rounding(short int *arr, const int size, const int last_digit);


// void clean(num_t *t);
int zero_array(const num_t *input);
void print_array(const short int *array, const int size);

#endif //FUNCTION_H