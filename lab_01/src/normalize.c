#include "../head/normalize.h"

/**
* \fn void move_digits(int *arr, const int size, int num_order)
* \brief move the digits by giving number order
* \param arr inputed array
* \param size size of array
* \param num_order givied number order to move digits if num < 0 left else right
**/
void move_digits(short int *arr, const int size, int num_order)
{
    if (num_order <= -1)
    {
        num_order *= -1;
        for (int i = 0; i < size - num_order; i++)
            arr[i] = arr[i + num_order];
        for (int i = size - num_order; i < size; i++)
            arr[i] = 0;
    }
    else if (num_order >= 1)
    {
        for (int i = size - 1; i >= num_order; i--)
            arr[i] = arr[i-num_order];
        for (int i = num_order - 1; i >= 0; i--)
            arr[i] = 0;
    }
}


/**
* \fn int count_zero(const num_t *input)
* \brief return the index of non-zero element
* \param input inputed structure to do the work
**/
int count_zero(const num_t *input)
{
    int zero = 0;

    for(int i = 0; i < input->size; i++)
    {
        if (input->mant[i] != 0)
        {
            zero = i;
            break;
        }
    }
    return zero;
}


/**
* \fn void normalize_int(num_t *int_t)
* \brief remove zeros in the begginnig of a integer number 
* \param int_t inputed structure to do the work
**/
void normalize_int(num_t *int_t)
{
    int zero = count_zero(int_t);
    move_digits(int_t->mant, N, N - int_t->size);
    int_t->size -= zero;
}

/**
* \fn void normalize_float(num_t *float_t, int dot, int *exponent)
* \brief remove zeros in the begginnig of a float number 
* \param int_t inputed structure to do the work
* \param dot helps to decrease exponent after normalizing
* \param exponent to save the exponent part of number after normalizing
**/
void normalize_float(num_t *float_t, int dot, int *exponent)
{
    int zero = count_zero(float_t);

    *exponent -= float_t->size - dot;
    move_digits(float_t->mant, N, N - float_t->size);
    float_t->size -= zero;
}