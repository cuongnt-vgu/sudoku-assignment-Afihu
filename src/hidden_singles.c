#include "hidden_singles.h"
#include <stdlib.h>

void find_hidden_single_values(Cell **row, int *hidden_single_values) {
    int i, j, count;
    for (i = 0; i < BOARD_SIZE; i++) {
        hidden_single_values[i] = 0;
        count = 0;
        for (j = 0; j < BOARD_SIZE; j++) {
            int *candidates = get_candidates(row[j]);
            if (candidates[i]) {
                if (++count > 1) {
                    free(candidates);
                    break;
                }
            }
            free(candidates);
        }
        if (count == 1) hidden_single_values[i] = 1;
    }
}

void find_hidden_single(Cell **row, HiddenSingle *hidden_singles, int *counter) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            int *candidates = get_candidates(row[j]);
            if (candidates[i]) {
                if (*counter < BOARD_SIZE - 1) {
                    hidden_singles[*counter].value = i + 1;
                    hidden_singles[*counter].p_cell = row[j];
                    (*counter)++;
                }
                free(candidates);
                break;
            }
            free(candidates);
        }
    }
}

int hidden_singles(SudokuBoard *p_board) {
    int i, num;
    int hidden_single_values[BOARD_SIZE];
    HiddenSingle hidden_singles[BOARD_SIZE];
    int counter = 0;

    // Check rows
    for (i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single_values(p_board->p_rows[i], hidden_single_values);
        for (num = 0; num < BOARD_SIZE; num++) {
            if (hidden_single_values[num] == 1) {
                find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);
            }
        }
    }

    // Check columns
    for (i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single_values(p_board->p_cols[i], hidden_single_values);
        for (num = 0; num < BOARD_SIZE; num++) {
            if (hidden_single_values[num] == 1) {
                find_hidden_single(p_board->p_cols[i], hidden_singles, &counter);
            }
        }
    }

    // Check boxes
    for (i = 0; i < BOARD_SIZE; i++) {
        find_hidden_single_values(p_board->p_boxes[i], hidden_single_values);
        for (num = 0; num < BOARD_SIZE; num++) {
            if (hidden_single_values[num] == 1) {
                find_hidden_single(p_board->p_boxes[i], hidden_singles, &counter);
            }
        }
    }

    return counter;
}


