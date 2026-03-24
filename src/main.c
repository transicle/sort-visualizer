#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "sorter.h"
#include "bubble.h"
#include "insertion.h"
#include "selection.h"
#include "quick.h"
#include "merge.h"
#include <string.h>

int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

const char* algorithms[] = {
    "Bubble Sort",
    "Insertion Sort",
    "Selection Sort",
    "Quick Sort",
    "Merge Sort"
};

void pmenu(int selected) {
    int count = sizeof(algorithms) / sizeof(algorithms[0]);
    int max_len = 0;

    for (int i = 0; i < count; i++) {
        int len = strlen(algorithms[i]);
        if (len > max_len) max_len = len;
    }

    printf("\033[H\033[J"); 
    printf("Select an algorithm:\n\n");

    for (int i = 0; i < count; i++) {
        if (i == selected) {
            printf("\033[7m %s \033[0m", algorithms[i]);
            int padding = max_len - (int)strlen(algorithms[i]);
            for (int j = 0; j < padding; j++) printf(" ");
        } else {
            printf(" %s ", algorithms[i]);
            int padding = max_len - (int)strlen(algorithms[i]);
            for (int j = 0; j < padding; j++) printf(" ");
        }

        if ((i + 1) % 2 != 0 && (i + 1) < count) {
            printf("  "); 
        } else {
            printf("\n");
        }
    }
}

int main() {
    int selected = 0;
    int ch;
    int count = sizeof(algorithms) / sizeof(algorithms[0]);

    while (1) {
        pmenu(selected);
        ch = getch();

        if (ch == '\n') break;
        if (ch == '\033') {
            getch();
            switch(getch()) {
                case 'A': if (selected >= 2) selected -= 2; break;
                case 'B': if (selected + 2 < count) selected += 2; break;
                case 'C': if (selected % 2 == 0 && selected + 1 < count) selected += 1; break;
                case 'D': if (selected % 2 != 0) selected -= 1; break;
            }
        }
    }

    switch(selected) {
        case 0:
            bubble_sort();
            break;
        case 1:
            insertion_sort();
            break;
        case 2:
            selection_sort();
            break;
        case 3:
            quick_sort();
            break;
        case 4:
            merge_sort();
            break;
    }

    return 0;
}