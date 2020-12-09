#include "../head/functions.h"

/**
* \fn void check_ten(int *arr_float, int *arr_int, int size, int *exp)
* \brief check the 10 first number of first array greather than second one if greather than move digits by 1 to left
* \param arr_float inputed float array
* \param arr_int inputed int array
* \param size size of array
* \param exp for increasing the exp if job is successfull
**/
void check_ten(short int *arr_float, short int *arr_int, const int size, int *exp)
{
    int count = 0;
    // int equal;

    while (comparison(arr_float, arr_int) == 1 && count < 10)
        count++;

    if (count == 10)
    {
        move_digits(arr_int, size, -1);
        (*exp)++;
    }
}

/**
* \fn void division(int *arr_float, int *arr_int, int *result, int *exp)
* \brief divides two inputed array
* \param arr_float inputed float array
* \param arr_int inputed int array
* \param result result array to saving the result
* \param exp for increasing or decreasing the exp if job is successfull
**/
void division(short int *arr_float, short int *arr_int, short int *result, int *exp)
{
    int current_pos = 0;
    int equal, counter, flag, flag_zero;
    // int last_digit = FLAG;
    int beggining_flag = 1; // used to

    check_ten(arr_float, arr_int, N, exp);

    flag_zero = 1;
    while (current_pos < N_MAX + 1)
    {
        equal = comparison(arr_float, arr_int);

        // if two arrays are equal
        if (equal == 0)
        {
            result[current_pos] = 1;
            break;
        }
        // if first one is greater
        else if (equal == 1)
        {
            flag_zero = 0;
            counter = 0;
            // while arr_float bigger than arr_int
            while ((flag = comparison(arr_float, arr_int)) != -1)
            {
                if (flag == 0)
                {
                    counter++;
                    break;
                }
                subtract(arr_float, arr_int);
                counter++;
            }

            if (current_pos == N_MAX) // if overflow happened
            {
                rounding(result, N_MAX, counter);
                break;
            }
            else
            {
                result[current_pos] = counter;
                current_pos++;
                beggining_flag = 0;
                if (flag == 0)
                    break;
            }
        }
        // if first one is smaller
        else
        {
            if (flag_zero)
            {
                if (beggining_flag)
                {
                    //printf(" +");
                    (*exp)--;
                }
                else
                {
                    result[current_pos] = 0;
                    current_pos++;
                }
            }
            flag_zero = 1;
            move_digits(arr_float, N, -1);
        }
    }
}

/**
* \fn void rounding(int *arr, const int size, const int last_digit)
* \brief rounds the elements of array if giving last digit is greather than 5
* \param arr inputed arr
* \param size size of array
* \param last_digit inputed last digit
**/
void rounding(short int *arr, const int size, const int last_digit)
{
    if (last_digit >= 5)
    {
        arr[size - 1]++;
        for (int i = size - 1; i >= 0; i--)
        {
            if (arr[i] == 10)
            {
                arr[i] -= 10;
                arr[i-1]++;
            }
            else
                break;
        }
    }
}


/**
* \fn int comparison(int *a, int *b)
* \brief compares two array returns 0 when elements are equal 1 if first one is greather else -1;
* \param arr inputed arr
* \param size size of array
**/
int comparison(short int *a, short int *b)
{
    int res = 0;
    for (int i = 0; i < N; i++)
    {
        if (a[i] > b[i])
        {
            res = 1;
            break;
        }
        else if (a[i] < b[i])
        {
            res = -1;
            break;
        }
    }
    return res;
}

/**
* \fn void subtract(int *a, int *b)
* \brief subtract the elements of first array from second
    1 - if first one element is bigger or equal than second one function 
            subtract's second one from first one
    2 - if second element is bigger than first one function 
            mutliply first element by 10 and subtract second one
            from first.
* \param a first array
* \param b second array
**/
void subtract(short int *a, short int *b)
{
    for (int i = N - 1; i >= 0; i--)
    {
        if (a[i] >= b[i])
            a[i] -= b[i];
        else
        {
            a[i] += 10 - b[i];
            a[i - 1]--;
        }
    }
}

/**
* \fn int zero_array(const num_t *input)
* \brief checks if all the elements are zero
* \param input inputed object
**/
int zero_array(const num_t *input)
{
    for (int i = 0; i < N; i++)
        if (input->mant[i] != 0)
            return 0;
    return 1;
}