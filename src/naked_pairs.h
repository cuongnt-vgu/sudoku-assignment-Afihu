#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "sudoku.h"
typedef struct {
    Cell *p_cell1;
    Cell *p_cell2;
} NakedPairs;

int naked_pairs(SudokuBoard *p_board);
void add_naked_pairs(int *nakedPairsCount, NakedPairs*nakedPairs,Cell*currentCell, Cell*otherCell);
void remove_naked_pairs(int *nakedPairsCount, NakedPairs*nakedPairs);