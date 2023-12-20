#pragma once

#include "sudoku.h"

typedef struct HiddenSingle_impl
{
    Cell *p_cell;
} HiddenPairs;

int hidden_pairs(SudokuBoard *p_board);
