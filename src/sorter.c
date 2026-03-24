#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorter.h"

void shuffle_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = (rand() % 15) + 1;
    }
}

void print_array(int arr[], int n, int active1, int active2) {
    int max_height = 16;
    printf("\033[H"); 

    for (int h = max_height; h > 0; h--) {
        for (int i = 0; i < n; i++) {
            if (arr[i] >= h) {
                if (active1 == -2 && i <= active2) {
                    printf("\033[38;5;82m█ \033[0m"); 
                } else if (i == active1 || i == active2) {
                    printf("\033[38;5;196m█ \033[0m");
                } else {
                    printf("\033[38;5;%dm█ \033[0m", 33 + (arr[i] % 6));
                }
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    fflush(stdout);
}