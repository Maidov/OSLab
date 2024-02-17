#include <stdio.h>
#include <stdlib.h> 
#include "first.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int A, B;
    if (fscanf(file, "%d", &A) != 1) {
        fprintf(stderr, "Error reading A\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    if (fscanf(file, "%d", &B) != 1) {
        fprintf(stderr, "Error reading B\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    long x;
    if (fscanf(file, "%ld", &x) != 1) {
            fprintf(stderr, "Error reading x\n");
            fclose(file);
            return EXIT_FAILURE;
    }

    fclose(file);

    printf("PrimeCount from A to B: ");
    printf("%d ", PrimeCount(A, B));
    printf("\n");
    printf("Translation from base 10: ");
    printf("%s ", Translation(x));
    printf("\n");

    return 0;
}