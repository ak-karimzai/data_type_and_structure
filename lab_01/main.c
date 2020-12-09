// #include <stdio.h>
// #include <stdlib.h>
#include "main.h"

/**
 * \fn int main(void)
 * \brief Program calculates the division of a long double number and a long intger (upto 30 digits)
**/
int main(void)
{
    int rc = ok;
    //           {Sign, Size, pointer for dynamic array}
    num_t float_t = {1, 0, NULL};
    num_t int_t = {1, 0, NULL};
    num_t res_t = {1, 0, NULL};

    int exponent = 0;

    float_t.mant = calloc(N, sizeof(short int));
    int_t.mant = calloc(N, sizeof(short int));
    res_t.mant = calloc(N, sizeof(short int));

    if (!float_t.mant || !int_t.mant || !res_t.mant)
    {
        puts("Stack Over Flow");
        rc = over_flow;
        goto finished;

    }
    else
    {
        puts("\nProgram calculates the division of a long double number and a long intger (upto 30 digits)");
        puts("for better result please Enter Meaningful numbers.");

        if (input_float(&float_t, &exponent))
        {
            rc = input_err;
            goto finished;
        }
        else if (input_int(&int_t)) 
        {
            rc = input_err;
            goto finished;
        }
        else if (zero_array(&float_t))
        {
            puts("Operation Result: 0.0e0");
            rc = ok;
            goto finished;
        }
        else
        {
            int diff = float_t.size - int_t.size;
            if (diff > 1)
            {
                move_digits(int_t.mant, N, -1 * (diff - 1));
                exponent += diff - 1;
            }

            // clean(&res_t);
            division(float_t.mant, int_t.mant, res_t.mant, &exponent);
            exponent += 1;
        }
    }

    if (exponent > 99999)
    {
        puts("Result power is greater than 99999\n");
        rc = input_err;
        goto finished;
    }
    else if (exponent < -99999)
    {
        puts("Result power is less than -99999");
        rc = input_err;
        goto finished;
    }
    else
    {
        // assign the sign of result after process
        res_t.sign = int_t.sign * float_t.sign;
        output_res(&res_t, exponent);
    }
    goto finished;
finished:
    free(float_t.mant);
    free(int_t.mant);
    free(res_t.mant);
    return rc;
}