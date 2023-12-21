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
                int check_count = 0;//count the instance of compatible cell is a house
                // Check other cells in the row
                for (int col = 0; col < BOARD_SIZE; col++) {
                    if (col!=j && is_candidate(p_board->p_rows[i][col],c_candidates[1]) 
                        && is_candidate(p_board->p_rows[i][col],c_candidates[0])){
                        Cell *otherCell = p_board->p_rows[i][col];
                        if(otherCell->num_candidates>2){
                            if(check_count!=0){
                                nakedPairs[nakedPairsCount].p_cell1 = NULL;
                                nakedPairs[nakedPairsCount].p_cell2 = NULL;
                                nakedPairsCount--;
                                check_count--;
                            }
                            break;
                        }
                        if (otherCell->num_candidates==2){
                            if (check_count==0){
                                nakedPairs[nakedPairsCount].p_cell1 = currentCell;
                                nakedPairs[nakedPairsCount].p_cell2 = otherCell;
                                nakedPairsCount++;
                                check_count++;
                            } else{
                                nakedPairs[nakedPairsCount].p_cell1 = NULL;
                                nakedPairs[nakedPairsCount].p_cell2 = NULL;
                                nakedPairsCount--;
                                check_count--;
                            }
                        }                    
                    }
                }
                check_count = 0;
                // Check other cells in the column
                for (int row = 0; row < BOARD_SIZE; row++) {
                    if (row != i && is_candidate(p_board->p_cols[j][row], c_candidates[1]) 
                        && is_candidate(p_board->p_cols[j][row], c_candidates[0])) {
                        Cell *otherCell = p_board->p_cols[j][row];
                        if (otherCell->num_candidates > 2) {
                            if (check_count != 0) {
                                nakedPairs[nakedPairsCount].p_cell1 = NULL;
                                nakedPairs[nakedPairsCount].p_cell2 = NULL;
                                nakedPairsCount--;
                                check_count--;
                            }
                            break;
                        }
                        if (otherCell->num_candidates == 2) {
                            if (check_count == 0) {
                                nakedPairs[nakedPairsCount].p_cell1 = currentCell;
                                nakedPairs[nakedPairsCount].p_cell2 = otherCell;
                                nakedPairsCount++;
                                check_count++;
                            } else {
                                nakedPairs[nakedPairsCount].p_cell1 = NULL;
                                nakedPairs[nakedPairsCount].p_cell2 = NULL;
                                nakedPairsCount--;
                                check_count--;
                            }
                        }                    
                    }
                }
                check_count = 0;

                check_count = 0;
                // Check other cells in the box
                int boxStartRow = (i / 3) * 3;
                int boxStartCol = (j / 3) * 3;
                for (int row = boxStartRow; row < boxStartRow + 3; row++) {
                    for (int col = boxStartCol; col < boxStartCol + 3; col++) {
                        if ((row != i || col != j) && p_board->data[row][col].num_candidates > 1) {
                            if (is_candidate(&p_board->data[row][col], c_candidates[0]) &&
                                is_candidate(&p_board->data[row][col], c_candidates[1])){ 
                            
                                //If a cell that has more than 2 candidates and fulfills the condition
                                if (p_board->data[row][col].num_candidates > 2){
                                    if(check_count != 0){
                                        nakedPairs[nakedPairsCount].p_cell1 = NULL;
                                        nakedPairs[nakedPairsCount].p_cell2 = NULL;
                                        nakedPairsCount--;
                                    }
                                    break;                           
                                }
                                //If this is the first time a cell fulfills the condition
                                if (p_board->data[row][col].num_candidates == 2){
                                    if(check_count == 0){
                                        nakedPairs[nakedPairsCount].p_cell1 = currentCell;
                                        nakedPairs[nakedPairsCount].p_cell2 = &p_board->data[row][col];
                                        check_count++;
                                        nakedPairsCount++;
                                    }else{
                                        nakedPairs[nakedPairsCount].p_cell1 = NULL;
                                        nakedPairs[nakedPairsCount].p_cell2 = NULL;
                                        nakedPairsCount--;
                                        break;
                                    }
                                }   
                            }
                        }
                    }
                }
                check_count = 0;
                free(c_candidates);
            }
        }
    }

    

    // // Process naked pairs if found
    // for (int k = 0; k < nakedPairsCount; k++) {
    //     // Implement the logic to handle the naked pairs, e.g., remove candidates from other cells in the row/column
    //     if (nakedPairs[k].p_cell1 != NULL) {
    //         // Your logic here
    //         // Example: remove_candidates_from_other_cells_in_row(p_board, nakedPairs[k].p_cell1, nakedPairs[k].p_cell2);
    //     }
    // }

    return nakedPairsCount;
}

// bool are_values_candidates(Cell **p_cells, Cell *currentCell, int value1, int value2)
// {
//     for (int i = 0; i < BOARD_SIZE; i++)
//     {
//         if (p_cells[i]->num_candidates == 2)
//         {
//             if (is_candidate(p_cells[i], value1) && is_candidate(p_cells[i], value2))
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }


