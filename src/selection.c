#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sorter.h"
#include "selection.h"

void selection_sort() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));
    shuffle_array(arr, ARRAY_SIZE);
    printf("\033[H\033[J");
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < ARRAY_SIZE; j++) {
            print_array(arr, ARRAY_SIZE, min_idx, j);
            usleep(DELAY);
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            print_array(arr, ARRAY_SIZE, i, min_idx);
            usleep(DELAY);
        }
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_array(arr, ARRAY_SIZE, -2, i);
        usleep(DELAY);
    }
    printf("\nPress enter to return.");
    getchar();
}
