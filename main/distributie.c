#include <stdlib.h>
#include <limits.h>
#include "distribution.h"

void backtrack(int* book_sizes, int num_books, int num_employees, int* current_distribution, int** best_distribution, int* min_diff, int* sums, int current_book) {
    if (current_book == num_books) {
        int max_sum = INT_MIN;
        int min_sum = INT_MAX;
        for (int i = 0; i < num_employees; i++) {
            if (sums[i] > max_sum) max_sum = sums[i];
            if (sums[i] < min_sum) min_sum = sums[i];
        }
        int diff = max_sum - min_sum;
        if (diff < *min_diff) {
            *min_diff = diff;
            for (int i = 0; i < num_books; i++) {
                best_distribution[i][0] = current_distribution[i];
            }
        }
        return;
    }

    for (int i = 0; i < num_employees; i++) {
        current_distribution[current_book] = i;
        sums[i] += book_sizes[current_book];
        backtrack(book_sizes, num_books, num_employees, current_distribution, best_distribution, min_diff, sums, current_book + 1);
        sums[i] -= book_sizes[current_book];
    }
}

int** distribute_books(int* book_sizes, int num_books, int num_employees) {
    int** best_distribution = (int**)malloc(num_books * sizeof(int*));
    for (int i = 0; i < num_books; i++) {
        best_distribution[i] = (int*)malloc(sizeof(int));
    }

    int* current_distribution = (int*)malloc(num_books * sizeof(int));
    int* sums = (int*)calloc(num_employees, sizeof(int));
    int min_diff = INT_MAX;

    backtrack(book_sizes, num_books, num_employees, current_distribution, best_distribution, &min_diff, sums, 0);

    free(current_distribution);
    free(sums);

    int** final_distribution = (int**)malloc(num_employees * sizeof(int*));
    for (int i = 0; i < num_employees; i++) {
        final_distribution[i] = (int*)malloc(num_books * sizeof(int));
        for (int j = 0; j < num_books; j++) {
            final_distribution[i][j] = 0;
        }
    }

    for (int i = 0; i < num_books; i++) {
        int employee = best_distribution[i][0];
        for (int j = 0; j < num_books; j++) {
            if (final_distribution[employee][j] == 0) {
                final_distribution[employee][j] = book_sizes[i];
                break;
            }
        }
    }

    for (int i = 0; i < num_books; i++) {
        free(best_distribution[i]);
    }
    free(best_distribution);

    return final_distribution;
}
