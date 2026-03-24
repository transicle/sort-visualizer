#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sorter.h"
#include "radix.h"

static int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

static void countSort(int arr[], int n, int exp) {
    int output[ARRAY_SIZE];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        print_array(arr, ARRAY_SIZE, i, -1);
        usleep(DELAY/2);
    }
}

void radix_sort() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));
    shuffle_array(arr, ARRAY_SIZE);
    printf("\033[H\033[J");
    int m = getMax(arr, ARRAY_SIZE);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, ARRAY_SIZE, exp);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_array(arr, ARRAY_SIZE, -2, i);
        usleep(DELAY);
    }
    printf("\nPress enter to return.");
    getchar();
}
