#include "../head/io.h"

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