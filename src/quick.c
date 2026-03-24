#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sorter.h"
#include "quick.h"

static void quick_sort_rec(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            print_array(arr, ARRAY_SIZE, j, high);
            usleep(DELAY);
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                print_array(arr, ARRAY_SIZE, i, j);
                usleep(DELAY);
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        print_array(arr, ARRAY_SIZE, i + 1, high);
        usleep(DELAY);
        int pi = i + 1;
        quick_sort_rec(arr, low, pi - 1);
        quick_sort_rec(arr, pi + 1, high);
    }
}

void quick_sort() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));
    shuffle_array(arr, ARRAY_SIZE);
    printf("\033[H\033[J");
    quick_sort_rec(arr, 0, ARRAY_SIZE - 1);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_array(arr, ARRAY_SIZE, -2, i);
        usleep(DELAY);
    }
    printf("\nPress enter to return.");
    getchar();
}
