#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "sorter.h"
#include "bubble.h"

void bubble_sort() {
    int arr[ARRAY_SIZE];
    srand(time(NULL));
    shuffle_array(arr, ARRAY_SIZE);
    
    printf("\033[H\033[J"); 

    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
            print_array(arr, ARRAY_SIZE, j, j + 1);
            usleep(DELAY);

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                print_array(arr, ARRAY_SIZE, j, j + 1);
            }
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        print_array(arr, ARRAY_SIZE, -2, i);
        usleep(DELAY);
    }

    printf("\nPress enter to return.");
    getchar(); 
}