#include <omp.h>
#include <stdio.h>
#include <iostream>

const int NMAX = 90;
const int LIMIT = 90;

void main()
{
    int i, j;
    float sum;
    float a[NMAX][NMAX];

    for (i = 0; i < NMAX; i++)
        for (j = 0; j < NMAX; j++)
            a[i][j] = i + j;

    double start = omp_get_wtime();
#pragma omp parallel shared(a) if (NMAX>LIMIT)
    {
#pragma omp for private(i,j,sum) 
        for (i = 0; i < NMAX; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX; j++)
                sum += a[i][j];
            printf("Sum elements rows %d : %f\n", i, sum);
        }
    } /* Завершение параллельного фрагмента */

    double end = omp_get_wtime();

    std::cout << "Time " << ": " << (end - start) << std::endl;
}


