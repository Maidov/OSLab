#include "first.h"

int isPrime(int x) {
    for (int i = 2; i * i <= x; ++i)
    {
        if (x % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int PrimeCount(int a, int b)
{
    int count = 0;
    for (int i = a; i <= b; ++i)
    {
        if (isPrime(i) == 1)
        {
            ++count;
        }
    }
    return count;
}

char* Translation(long x) {
    // Максимальная длина бинарного представления числа
    int maxLength = 64;  // для long (64 бита)
    char* binary = (char*)malloc(maxLength + 1);  // +1 для завершающего нуля

    if (binary == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Инициализация буфера нулями
    for (int i = 0; i < maxLength; i++) {
        binary[i] = '0';
    }
    binary[maxLength] = '\0';  // Завершающий нуль

    // Преобразование в двоичную систему
    int index = maxLength - 1;
    while (x > 0) {
        binary[index] = (x % 2) + '0';
        x /= 2;
        index--;
    }

    int start_index = 0;
    for (size_t i = 0; i < maxLength; i++)
    {
        if (binary[i] == '0'){
            start_index += 1;
        } else {
            break;
        }
    }
    char* true_bin = (char*)malloc(maxLength - start_index + 1);
    for (size_t i = start_index; i < maxLength+1; i++)
    {
        true_bin[i - start_index] = binary[i];
    }

    return true_bin;
}