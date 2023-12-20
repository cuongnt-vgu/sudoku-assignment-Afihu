#include "hidden_pairs.h"
#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>

int hidden_pairs(SudokuBoard *p_board) {
    // int hiddenPairsCounter = 0;
    // HiddenPairs hiddenPairs[BOARD_SIZE * BOARD_SIZE];

    // // Read each cell
    // for (int i = 0; i < BOARD_SIZE; i++) {
    //     for (int j = 0; j < BOARD_SIZE; j++) {

    //         Cell *currentCell = &p_board->data[i][j];

    //         // Check if cell is unsolved
    //         if (currentCell->num_candidates >= 2) {
    //             int *currentCandidates = get_candidates(currentCell);

    //             //Check in row
    //             for(int col=0; col<BOARD_SIZE;col++){
    //                 Cell *otherCell = &p_board->data[i][col];
    //                 //Check for an unsolved cell
    //                 if (col!=j && otherCell->num_candidates>=2){
    //                     int *otherCandidate = get_candidates(otherCell);

    //                 }
    //             }

    //             free(currentCandidates);
    //         }
    //     }
    // }

    // // Process the found hidden pairs if needed

    return 0;
}
// bool check_candidate(Cell *currentCell, Cell *otherCell, int *candidates){
//     for (int i=0; i < (currentCell->num_candidates-1);i++){
//         for (int j=i; j < currentCell->num_candidates){
            
//             if (is_candidate(otherCell,candidates[i])&&is_candidate(otherCell,candidates[j])){
//                 return true;
//             }
//         }
//     }
// }
// bool check_candidate_to_be_hidden(SudokuBoard *p_board, Cell* currentCell, Cell* otherCell){

// }

