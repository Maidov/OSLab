#include "second.h"

int PrimeCount(int A, int B) {
    // Проверка на корректность входных данных
    if (A > B || A < 2) {
        fprintf(stderr, "Invalid input range\n");
        exit(EXIT_FAILURE);
    }

    // Выделение памяти для массива "пометок" (true - простое, false - составное)
    bool *isPrime = (bool *)malloc((B + 1) * sizeof(bool));
    if (isPrime == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Инициализация массива: предполагаем, что все числа от 2 до B - простые
    for (int i = 2; i <= B; i++) {
        isPrime[i] = true;
    }

    // Решето Эратосфена
    for (int i = 2; i * i <= B; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= B; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Подсчет простых чисел в заданном диапазоне
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (isPrime[i]) {
            count++;
        }
    }

    // Освобождение выделенной памяти
    free(isPrime);

    return count;
}


char* Translation(long x) {
    // Максимальная длина троичного представления числа
    int maxLength = 42;  // для long (64 бита)
    char* ternary = (char*)malloc(maxLength + 1);  // +1 для завершающего нуля

    if (ternary == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Инициализация буфера нулями
    for (int i = 0; i < maxLength; i++) {
        ternary[i] = '0';
    }
    ternary[maxLength] = '\0';  // Завершающий нуль

    // Преобразование в троичную систему
    int index = maxLength - 1;
    while (x > 0) {
        ternary[index] = (x % 3) + '0';
        x /= 3;
        index--;
    }

    int start_index = 0;
    for (size_t i = 0; i < maxLength; i++)
    {
        if (ternary[i] == '0'){
            start_index += 1;
        } else {
            break;
        }
    }
    char* true_tern = (char*)malloc(maxLength - start_index + 1);
    for (size_t i = start_index; i < maxLength+1; i++)
    {
        true_tern[i - start_index] = ternary[i];
    }

    return true_tern;
}