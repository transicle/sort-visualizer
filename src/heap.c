#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sorter.h"
#include "heap.h"

static void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        print_array(arr, ARRAY_SIZE, i, largest);
        usleep(DELAY);
        heapify(arr, n, largest);
    }
}

void heap_sort() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));
    shuffle_array(arr, ARRAY_SIZE);
    printf("\033[H\033[J");
    for (int i = ARRAY_SIZE / 2 - 1; i >= 0; i--)
        heapify(arr, ARRAY_SIZE, i);
    for (int i = ARRAY_SIZE - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        print_array(arr, ARRAY_SIZE, 0, i);
        usleep(DELAY);
        heapify(arr, i, 0);
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_array(arr, ARRAY_SIZE, -2, i);
        usleep(DELAY);
    }
    printf("\nPress enter to return.");
    getchar();
}
