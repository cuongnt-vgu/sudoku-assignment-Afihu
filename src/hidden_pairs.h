#pragma once

#include "sudoku.h"

typedef struct HiddenPairs {
    Cell *p_cell1;
    Cell *p_cell2;
} HiddenPairs;

int hidden_pairs(SudokuBoard *p_board);

