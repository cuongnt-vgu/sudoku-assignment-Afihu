#include "hidden_singles.h"
#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Function to find hidden singles in the board and update cell values
int hidden_singles(SudokuBoard *p_board) {
    int hiddenSingleCounter = 0;

    // Create a temporary array to store hidden singles
    HiddenSingle hiddenSingles[BOARD_SIZE * BOARD_SIZE];

    // Iterate through each unsolved cell
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *currentCell = &p_board->data[i][j];

            // Check if cell is unsolved
            if (currentCell->num_candidates > 1) {
                int *candidates = get_candidates(currentCell);

                // Checking each candidate in the candidates list
                for (int c = 0; c < currentCell->num_candidates; c++) {
                    int isHiddenSingle[3] = {1, 1, 1};

                    // Check uniqueness in the row
                    for (int col = 0; col < BOARD_SIZE; col++) {
                        if (col != j && is_candidate(&p_board->data[i][col], candidates[c])) {
                            // The candidate is not unique in that row
                            isHiddenSingle[0] = 0;
                            break;
                        }
                    }

                    // Check uniqueness in the column
                    for (int row = 0; row < BOARD_SIZE; row++) {
                        if (row != i && is_candidate(&p_board->data[row][j], candidates[c])) {
                            // The candidate is not unique in the column
                            isHiddenSingle[1] = 0;
                            break;
                        }
                    }

                    // Check uniqueness in the box
                    int boxStartRow = (i / 3) * 3;
                    int boxStartCol = (j / 3) * 3;
                    for (int row = boxStartRow; row < boxStartRow + 3; row++) {
                        if (isHiddenSingle[2] == 0) {
                            break;
                        }
                        for (int col = boxStartCol; col < boxStartCol + 3; col++) {
                            if ((row != i || col != j) && is_candidate(&p_board->data[row][col], candidates[c])) {
                                // The candidate is not unique in the same box
                                isHiddenSingle[2] = 0;
                                break;
                            }
                        }
                    }

                    // If the candidate is a hidden single, store it in the temporary array
                    if (isHiddenSingle[0] || isHiddenSingle[1] || isHiddenSingle[2]) {
                        printf("SINGLE: %d set to row %d, col %d\n",candidates[c],i+1,j+1);
                        hiddenSingles[hiddenSingleCounter].p_cell = currentCell;
                        hiddenSingles[hiddenSingleCounter].value = candidates[c];
                        hiddenSingleCounter++;
                    }
                }
                free(candidates);
            }
        }
    }

    // Update the board with the found hidden singles
    for (int k = 0; k < hiddenSingleCounter; k++) {
        Cell *currentCell = hiddenSingles[k].p_cell;
        int value = hiddenSingles[k].value;

        // Update the cell's value
        currentCell->value = value;
        for (int i=0; i<BOARD_SIZE; i++){
            if (i != (value-1)){
                currentCell->candidates[i]=0;
            }
        }
        currentCell->num_candidates = 1;
    }

    return hiddenSingleCounter;
}
