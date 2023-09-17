#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <omp.h>

// Функция для вычисления значения функции
int calculateFunction(int a, int b, int c) {
    if (a % 2 == 0) {
        return b + c;
    }
    else {
        return b - a;
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    // Задаем различные значения N для измерения времени работы программы
    std::vector<int> N_values = { 10000, 50000, 100000, 500000, 1000000 };

    for (int N : N_values) {
        // Инициализируем массивы A, B и C
        std::vector<int> A(N);
        std::vector<int> B(N);
        std::vector<int> C(N);

        #pragma omp for
        // Заполняем массивы случайными значениями
        for (int i = 0; i < N; i++) {
            A[i] = rand() % 100;
            B[i] = rand() % 100;
            C[i] = rand() % 100;
        }

        // Измеряем время работы программы
        double start_time = omp_get_wtime();


        int result = 0;

        // Используем OpenMP для распараллеливания вычислений
        #pragma omp sections
        {
            #pragma omp section 
            for (int i = 0; i < N / 2; i++) {
                if (A[i] != 1) {
                    #pragma omp atomic
                    result += calculateFunction(A[i], B[i], C[i]);
                }
            }

            #pragma omp section 
            for (int i = N/2; i < N ; i++) {
                if (A[i] != 1) {
                    #pragma omp atomic
                    result += calculateFunction(A[i], B[i], C[i]);
                }
            }
        }
        

        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;

        std::cout << "N = " << N << ", Результат = " << result << ", Время выполнения: " << elapsed_time << " секунд" << std::endl;
    }

    return 0;
}
