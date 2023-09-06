#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <omp.h>

// Функция для подсчета количества единиц в бинарной записи числа
int CountOnesInBinary(int num) {
    int count = 0;
    while (num > 0) {
        if (num % 2 == 1) {
            count++;
        }
        num /= 2;
    }
    return count;
}

int M = 600;
int N = 600;

int rowsCountAsync()
{
    std::vector<std::vector<int>> matrix(M, std::vector<int>(N));
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = distribution(rng);
        }
    }

    double start = omp_get_wtime();
    // Вычисление суммы единиц в бинарной записи числа всех попарных произведений элементов для каждой строки
#pragma omp parallel for
    for (int i = 0; i < M; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                int value = matrix[i][j] * matrix[i][k];
                sum += CountOnesInBinary(value);
            }
        }
        /*std::cout << "Summa " << i << ": " << sum << std::endl;*/
    }

    double end = omp_get_wtime();

    std::cout << "TimeAsync " << ": " << (end - start) << std::endl;

    return 0;
}

int rowsCount()
{
    std::vector<std::vector<int>> matrix(M, std::vector<int>(N));
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = distribution(rng);
        }
    }

    double start = omp_get_wtime();

    for (int i = 0; i < M; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                int value = matrix[i][j] * matrix[i][k];
                sum += CountOnesInBinary(value);
            }
        }
        /*std::cout << "Summa " << i << ": " << sum << std::endl;*/
    }

    double end = omp_get_wtime();

    std::cout << "Time " << ": " << (end - start) << std::endl;

    return 0;
}

int main() {
    rowsCountAsync();
    rowsCount();
}