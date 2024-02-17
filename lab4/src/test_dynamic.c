#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*PrimeCount)(float A, float B);
typedef char* (*Translation)(long x);

int main() {
    void *libHandle;
    int number_lib = 1;
    PrimeCount primecount;
    Translation traslation;
    libHandle = dlopen("./libfirst.so", RTLD_LAZY);
    int choice = 1;  

    while (choice != -1) {
        printf("Select operation (-1 - exit, 0 - change lib, 1 - calculate primecount, 2 - calculate traslation): ");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        } else if (choice == 0) {

            if (libHandle) {
                dlclose(libHandle);
            }

            if (number_lib == 2) {
                libHandle = dlopen("./libfirst.so", RTLD_LAZY);
                number_lib = 1;
            } else {
                libHandle = dlopen("./libsecond.so", RTLD_LAZY);
                number_lib = 2;
            }

            if (libHandle == NULL) {
                fprintf(stderr, "Error loading lib: %s\n", dlerror());
                continue;
            }
        } else if (choice == 1) {
            primecount = (PrimeCount)dlsym(libHandle, "PrimeCount");
            if (!primecount) {
                fprintf(stderr, "Error recieving function PrimeCount: %s\n", dlerror());
                dlclose(libHandle);
                return 1;
            }

            int A, B;
            scanf("%d %d", &A, &B);
            int result = primecount(A, B);
            printf("PrimeCount in A: %d\n", result);
        } else if (choice == 2) {
            traslation = (Translation)dlsym(libHandle, "Translation");
            if (!traslation) {
                fprintf(stderr, "Error recieving Translation function: %s\n", dlerror());
                dlclose(libHandle);
                return 1;
            }

            long x;
            scanf("%ld", &x);
            char* result = traslation(x);
            printf("Translation: %s\n", result);

        } else {
            printf("Некорректный выбор операции.\n");
        }
    }

    if (libHandle) {
        dlclose(libHandle);
    }

    return 0;
}