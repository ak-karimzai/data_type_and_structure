#include "./inc/main.h"

int main()
{
    system("clear");
    welcome();

    matrix_t matrix_a, matrix_b, matrix_res;
    sparse_t sparse_a, sparse_b, sparse_res;

    int dots_a, dots_b, dots_sum;
    int percent_a, percent_b;

    int cur_command = -1;

    while (cur_command != 0)
    {
        if (input_interval(&cur_command, 0, 6))
        {
            puts("Incorect Input!, try again.");
            welcome();
        }
        else
        {
            if (cur_command == 1)
            {
                puts("Enter the num of rows A (from 1 to 1000):");
                if (input_interval(&matrix_a.rows, 1, 1000))
                {
                    puts("Incorect Input!, try again.");
                    return ok;
                }
                puts("Enter the num of columns A (from 1 to 1000):");
                if (input_interval(&matrix_a.columns, 1, 1000))
                {
                    puts("Incorect Input!, try again.");
                    return ok;
                }
                puts("Enter the number of non-zero elements A (from 1 to 1000)");
                if (input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns))
                {
                    puts("Incorect Input! try again");
                    welcome();
                }
                puts("Enter the elements of matrix A in {row, col, val} format:");
                create(&matrix_a);
                if (input(&matrix_a, dots_a))
                {
                    puts("Incorrect Input! try again");
                    return ok;
                }


                matrix_b.rows = matrix_a.rows;
                matrix_b.columns = matrix_a.columns;
                puts("Enter the number of non-zero elements B (from 1 to 1000)");
                if (input_interval(&dots_b, 0, matrix_b.rows * matrix_b.columns))
                {
                    puts("Incorect Input! try again");
                    welcome();
                }
                puts("Enter the elements of matrix B in {row, col, val} format:");
                create(&matrix_b);
                if (input(&matrix_b, dots_b))
                {
                    puts("Incorrect Input! try again");
                    return ok;
                }
                matrix_res.rows = matrix_a.rows;
                matrix_res.columns = matrix_a.columns;
                create(&matrix_res);

                screate(&sparse_a, dots_a, matrix_a.columns);
                sinput(&sparse_a, matrix_a);
                fill_col_entry(&sparse_a, matrix_a);

                screate(&sparse_b, dots_b, matrix_b.columns);
                sinput(&sparse_b, matrix_b);
                fill_col_entry(&sparse_b, matrix_b);

                sdots(sparse_a, sparse_b, &dots_sum);
                screate(&sparse_res, dots_sum, matrix_a.columns);


                welcome();
            }
            
            if (cur_command == 2)
            {
                puts("Enter the sum of rows A (from 1 to 1000):");
                if (input_interval(&matrix_a.rows, 1, 1000))
                {
                    puts("Incorrect Input! try again");
                    return ok;
                }
                puts("Enter the sum of columns A (from 1 to 1000):");
                if (input_interval(&matrix_a.columns, 1, 1000))
                {
                    puts("Incorrect Input! try again");
                    return ok;
                }
                puts("Enter the percentage of non-zero elements of matrix А (from 0 to 100):");
                if (input_interval(&percent_a, 1, 100))
                {
                    puts("Incorrect Input! try again");
                    return ok;
                }

                puts("Enter the percentage of non-zero elements of matrix B (from 0 to 100):");
                if (input_interval(&percent_b, 1, 100))
                {
                    puts("Incorrect Input! try again");
                    return ok;
                }
                matrix_b.rows = matrix_a.rows;
                matrix_b.columns = matrix_a.columns;

                create(&matrix_a);
                create(&matrix_b);

                int to_fill_a = floor(matrix_a.rows * matrix_a.columns * percent_a / 100.0);
                int a_create = to_fill_a;
                while (to_fill_a)
                {
                    gorandom(&matrix_a, percent_a);
                    to_fill_a--;
                }
                int to_fill_b = floor(matrix_b.rows * matrix_b.columns * percent_a / 100.0);
                int b_create = to_fill_b;
                while (to_fill_b)
                {
                    gorandom(&matrix_b, percent_b);
                    to_fill_b--;
                }

                matrix_res.rows = matrix_a.rows;
                matrix_res.columns = matrix_a.columns;

                create(&matrix_res);

                screate(&sparse_a, a_create, matrix_a.columns);
                sinput(&sparse_a, matrix_a);
                fill_col_entry(&sparse_a, matrix_a);

                screate(&sparse_b, b_create, matrix_a.columns);
                sinput(&sparse_b, matrix_b);
                fill_col_entry(&sparse_b, matrix_b);

                sdots(sparse_a, sparse_b, &dots_sum);
                screate(&sparse_res, dots_sum, matrix_a.columns);

                welcome();
            }
            if (cur_command == 3)
            {
                uint64_t ticks = 0;
                classic_sum(matrix_a, matrix_b, &matrix_res, &ticks);
                printf("%s%ju\n", "Addition method using standard method", ticks);
                welcome();
            }

            if (cur_command == 4)
            {
                uint64_t ticks = 0;
                classic_sum(matrix_a, matrix_b, &matrix_res, &ticks);
                ticks = 0;
                fill_col_entry(&sparse_a, matrix_a);
                fill_col_entry(&sparse_b, matrix_b);
                sparse_sum(sparse_a, sparse_b, &sparse_res, &ticks);
                fill_col_entry(&sparse_res, matrix_res);
                printf("%s%ju\n", "Addition Time using standard method = ", ticks);
                
                int mat_size = sizeof(type_t **) + sizeof(type_t *) * matrix_res.rows +
                               sizeof(type_t) * matrix_res.rows * matrix_res.columns + 2 * sizeof(int);
                int sparse_size = sizeof(type_t *) * 3 + sizeof(type_t) * sparse_res.elems_amount * 2 + 
                                  sizeof(type_t) * sparse_res.cols_amount + 2 * sizeof(int);

                printf("%d        %d\n", sparse_size, mat_size);
                welcome();
            }
            if (cur_command == 5)
            {
                puts("Matrix A:");
                output(&matrix_a);

                puts("Matrix B:");
                output(&matrix_b);

                puts("Matrix res:");
                output(&matrix_res);
                welcome();
            }
            if (cur_command == 6)
            {
                puts("Matrix A:");
                soutput(sparse_a);

                puts("Matrix B:");
                soutput(sparse_b);

                puts("Matrix res:");
                soutput(sparse_res);
                welcome();
            }
        }
    }
    deletee(&matrix_a);
    deletee(&matrix_b);
    deletee(&matrix_res);
    sdelete(&sparse_a);
    sdelete(&sparse_b);
    sdelete(&sparse_res);
    return ok;
}