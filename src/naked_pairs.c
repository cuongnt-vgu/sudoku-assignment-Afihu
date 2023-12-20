#include "naked_pairs.h"
#include "sudoku.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int naked_pairs(SudokuBoard *p_board)
{  
    int nakedPairsCount = 0;
    NakedPairs nakedPairs[BOARD_SIZE * BOARD_SIZE];
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Check for cell with only 2 candidates
            if (p_board->data[i][j].num_candidates == 2) { 
                Cell *currentCell = &p_board->data[i][j];
                int* c_candidates = get_candidates(currentCell);
                int check_count = 0;

                for (int col = 0; col < BOARD_SIZE; col++) {
                    // Check for unsolved cell
                    if (col != j && p_board->data[i][col].num_candidates == 2) {
                        if (check_count>1){
                            nakedPairs[nakedPairsCount].p_cell1=NULL;
                            nakedPairs[nakedPairsCount].p_cell2=NULL;
                            check_count=0;
                            break;
                        }
                        if (is_candidate(&p_board->data[i][col],c_candidates[0])&&is_candidate(&p_board->data[i][col],c_candidates[1])) {
                            nakedPairs[nakedPairsCount].p_cell1=currentCell;
                            nakedPairs[nakedPairsCount].p_cell2=&p_board->data[i][col];
                            check_count++;
                        }
                    }
                }
                nakedPairsCount+=check_count;
                check_count=0;
               
                for (int row = 0; row < BOARD_SIZE; row++) {
                    // Check for unsolved cell in col
                    if (row != j && p_board->data[row][j].num_candidates == 2) {
                        if (check_count>1){
                            nakedPairs[nakedPairsCount].p_cell1=NULL;
                            nakedPairs[nakedPairsCount].p_cell2=NULL;
                            check_count=0;
                            break;
                        }
                        if (is_candidate(&p_board->data[row][j],c_candidates[0])&&is_candidate(&p_board->data[row][j],c_candidates[1])) {
                            nakedPairs[nakedPairsCount].p_cell1=currentCell;
                            nakedPairs[nakedPairsCount].p_cell2=&p_board->data[row][i];
                            check_count++;
                        }
                    }
                }
                nakedPairsCount+=check_count;
                check_count=0;
                int boxStartRow = (i / 3) * 3;
                int boxStartCol = (j / 3) * 3;
                for (int row = boxStartRow; row < boxStartRow + 3; row++) {
                    for (int col = boxStartCol; col < boxStartCol + 3; col++){
                        if((row != i || col != j) && (p_board->data[row][col].num_candidates == 2) && (p_board->data[row][col].value > 0)){
                            if (check_count>1){
                                nakedPairs[nakedPairsCount].p_cell1=NULL;
                                nakedPairs[nakedPairsCount].p_cell2=NULL;
                                check_count=0;
                                break;
                            }
                            if (is_candidate(&p_board->data[row][col],c_candidates[0])&&is_candidate(&p_board->data[row][col],c_candidates[1])) {
                                nakedPairs[nakedPairsCount].p_cell1=currentCell;
                                nakedPairs[nakedPairsCount].p_cell2=&p_board->data[row][col];
                                check_count++;
                            }

                        }
                    }
                }
                nakedPairsCount+=check_count;
                free(c_candidates);
            }
        }
    }

    // // Process naked pairs if found
    // for (int k = 0; k < nakedPairsCount; k++) {
    //     // Implement the logic to handle the naked pairs, e.g., remove candidates from other cells in the row/column}


    return nakedPairsCount;
}


// void add_naked_pairs(int *nakedPairsCount, NakedPairs*nakedPairs,Cell*currentCell, Cell*otherCell){
//     nakedPairs[*nakedPairsCount].p_cell1=currentCell;
//     nakedPairs[*nakedPairsCount].p_cell2=otherCell;
//     nakedPairsCount++;
// }
// void remove_naked_pairs(int *nakedPairsCount, NakedPairs*nakedPairs){
//     nakedPairs[*nakedPairsCount].p_cell1=NULL;
//     nakedPairs[*nakedPairsCount].p_cell2=NULL;
//     nakedPairsCount--;
// }