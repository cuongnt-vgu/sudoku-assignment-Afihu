#include "hidden_pairs.h"
#include "sudoku.h"
int hidden_pairs(SudokuBoard *p_board)
{
    int hiddenPairsCounter = 0;
    HiddenPairs hiddenPairs [BOARD_SIZE*BOARD_SIZE];
    //Read each cell
    for(int i=0;i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            
            Cell *currentCell = &p_board->data[i][j];

            //Check if cell is unsolved
            if (currentCell->num_candidates>1){
                int *candidates = get_candidates(currentCell);
                int potentialPairs = 0;
                for (int col=0; col<BOARD_SIZE; col++){
                        if (col !=j && is_candidate(&p_board->data[i][col],candidates[c])){
                            potentialPairs++;
                            if(potentialPairs >2){break;}
                        }
                
                    if ()
                for (int c = 0; c < currentCell->num_candidates; c++){
                    //Check in row
                    
                }
                }
                free(candidates);
            }
        }
    }
    return hiddenPairsCounter;
}
