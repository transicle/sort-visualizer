#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sorter.h"
#include "shell.h"

void shell_sort() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));
    shuffle_array(arr, ARRAY_SIZE);
    printf("\033[H\033[J");
    for (int gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < ARRAY_SIZE; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                print_array(arr, ARRAY_SIZE, j, j-gap);
                usleep(DELAY);
            }
            arr[j] = temp;
            print_array(arr, ARRAY_SIZE, j, i);
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
