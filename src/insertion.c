#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sorter.h"
#include "insertion.h"

void insertion_sort() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));
    shuffle_array(arr, ARRAY_SIZE);
    printf("\033[H\033[J");
    for (int i = 1; i < ARRAY_SIZE; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            print_array(arr, ARRAY_SIZE, j, j + 1);
            usleep(DELAY);
            j--;
        }
        arr[j + 1] = key;
        print_array(arr, ARRAY_SIZE, j + 1, i);
        usleep(DELAY);
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_array(arr, ARRAY_SIZE, -2, i);
        usleep(DELAY);
    }
    printf("\nPress enter to return.");
    getchar();
}
