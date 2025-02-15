#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funktion för att byta plats på två element
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection Sort för att sortera siffror
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) { // Hitta minsta värdet
                minIndex = j;
            }
        }
        swap(&arr[i], &arr[minIndex]); // Byt plats
    }
}

// Funktion för att skriva ut en array (används för små arrays)
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Funktion för att beräkna tid i nanosekunder
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}

// Benchmark-funktion för Selection Sort
long benchmark(int n) {
    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        printf("Minnesallokering misslyckades!\n");
        return -1;
    }

    // Fyll arrayen med slumpmässiga tal
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Slumpmässiga värden mellan 0 och 9999
    }

    struct timespec t_start, t_stop;

    // Starta tidtagning
    clock_gettime(CLOCK_MONOTONIC, &t_start);

    // Sortera siffrorna
    selectionSort(arr, n);

    // Stoppa tidtagning
    clock_gettime(CLOCK_MONOTONIC, &t_stop);

    // Beräkna exekveringstid
    long time_taken = nano_seconds(&t_start, &t_stop);

    // Frigör minne
    free(arr);

    return time_taken;
}

// Huvudprogrammet
int main() {
    int sizes[] = {10, 100, 1000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL)); // Initiera slumpgenerator

    for (int i = 0; i < num_sizes; i++) {
        printf("\nSorterar array av storlek %d...\n", sizes[i]);
        long time_taken = benchmark(sizes[i]);
        printf("Selection Sort tog %ld nanosekunder för %d element.\n", time_taken, sizes[i]);
    }
    return 0;
}