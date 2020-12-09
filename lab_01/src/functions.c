#include "functions.h"

/**
 * \fn int input_float(num_t *float_t, int *exponent)
 * \brief function takes float number and save it in float_t (arr)
 * \param float_t array for saving the numbers
 * \param exponent to take and save number after exponent(e/E)
**/
int input_float(num_t *float_t, int *exponent)
{
    puts("\nInput a double number:\n"
           "e/E should be always entered.\n"
           "Input format: -1e0, 0.5e-7, +.5e1\n"
           "1        10        20       30e1   5");
    printf("|");
    for (int i = 0; i < N + 1; i++)
    {
        if (i == N - 4){
            printf("|");
            continue;
        }
        printf("=");
    }
    printf("|\n->");

    char b;
    int flag = 0;
    int dot = N+1;
    int flag_sign = 0;

    float_t->size = 0;
    *exponent = FLAG;

    while ((scanf("%c", &b) && (b != EOF) && (b != '\n') && (b != 'E') && (b != 'e')))
    {

        // Check correctness
        if ((float_t->size != 0 || flag_sign) && (b == '+' || b == '-'))
        {
            puts("Wrong input!");
            return input_err;
        }
        else if (b == '-')
        {
            float_t->sign = -1;
            flag_sign = 1;
        }
        else if (b == '+')
        {
            float_t->sign = 1;
            flag_sign = 1;
        }
        else if ((b <= '9') && (b >= '0'))
            float_t->mant[float_t->size++] = b - 48;
        else if (b == '.' && dot == N+1)
            dot = float_t->size;
        else
        {
            puts("Wrong input");
            return input_err;
        }
    }

    // if nothing inputed
    if (float_t->size == 0)
    {
        printf("Empty input!");
        return empty_input;
    }

    if (float_t->size > 30)
    {
        printf("Too many digits");
        return over_flow;
    }

    // if dot wasn't inputed
    if (dot == N+1)
    {
        dot = float_t->size;
    }

    // Input power
    if ((b == 'E') || (b == 'e'))
    {
        flag = scanf("%d", exponent);
        if (!flag)
            return input_err;
    }


    if (*exponent > 99999 || *exponent < -99999) // NOTE error scanfing exponent
    {
        puts("Incorect Input: exponent overflow ( -100000, 100000 )");
        return input_err;
    }

    while (((b = getchar()) != EOF) && (b != '\n'))
    {
        puts("Something wrong with exponent!");
        return mantis_err;
    }
    normalize_float(float_t, dot, exponent);
    return ok;
}

/**
 * \fn int input_int(num_t *int_t)
 * \brief function takes integer number and save it in int_t (arr)
 * \param int_t array for saving the numbers
**/
int input_int(num_t *int_t)
{
    puts("\nInput a integer number:\n"
        "input format: +77, -35, 0003\n"
        "1        10        20       30");
    printf("|");
    for (int i = 0; i < N - 5; i++)
        printf("=");
    printf("|\n->");

    int flag = ok;
    int zero_flag = 1; // 1 - zero inputed
    char b;

    int_t->size = 0;

    while (((b = getchar()) != EOF) && (b != '\n'))
    {
        // Check correctness
        if (int_t->size != 0 && (b == '+' || b == '-'))
        {
            puts("Wrong input!");
            flag = input_err;
        }
        else if (b == '-')
            int_t->sign = -1;
        else if (b == '+')
            int_t->sign = 1;
        else if ((b <= '9') && (b >= '0'))
        {
            int_t->mant[int_t->size++] = b - 48;
            if (b != '0')
                zero_flag = 0;
        }
        else
        {
            puts("Wrong input");
            return input_err;
        }
    }

    // Check size of
    if (int_t->size > 30)
    {
        puts("Too many digits");
        return over_flow;
    }
    if (int_t->size == 0)
    {
        puts("Nothing inputed!");
        return input_err;
    }

    if (zero_flag)
    {
        puts("Exception: Division by Zero.");
        return division_by_zero;
    }

    if (!flag)
        normalize_int(int_t);

    return flag;
}

/**
* \fn void output_res(const num_t *t, const int exp)
* \brief output the result of division
**/
void output_res(const num_t *t, const int exp)
{
    int meaning_dig = 0; //amount of digits to show

    for (int i = 0; i < N; i++)
        if (t->mant[i] != 0)
            meaning_dig = i+1;

    puts("\nResult after operation: ");
    if (t->sign == -1)
        printf("-0.");
    else if(t->sign == 1)
        printf("+0.");

    for (int i = 0; i < meaning_dig; i++)
        printf("%d", t->mant[i]);
    printf("e%d\n", exp);
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