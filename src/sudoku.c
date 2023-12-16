#include "sudoku.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hidden_singles.h"

// sudoku.c
#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

void init_sudoku(SudokuBoard *p_board) {
    // Initialize solved_counter to 0
    p_board->solved_counter = 0;

    // Allocate memory for the data array (9x9 grid of cells)
    p_board->data = (Cell**)malloc(BOARD_SIZE * sizeof(Cell*));
    for (int i = 0; i < BOARD_SIZE; i++) {
        p_board->data[i] = (Cell*)malloc(BOARD_SIZE * sizeof(Cell));
    }

    // Initialize other pointers to NULL
    for (int i = 0; i < BOARD_SIZE; i++) {
        p_board->p_rows[i] = NULL;
        p_board->p_cols[i] = NULL;
        p_board->p_boxes[i] = NULL;
    }

    // Initialize solved_cells array to NULL
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        p_board->solved_cells[i] = NULL;
    }
}

void load_sudoku(SudokuBoard *p_board, char *input_text) {
    // Implement your code to load a Sudoku puzzle from input_text
    // This function should update the data array in the SudokuBoard structure
}

bool apply_constraint(Cell **p_cells, int value) {
    // Implement your code to apply a constraint to the given cells
    // This function should return true if the constraint is successfully applied
}

bool is_in_list(Cell **p_array, int size, Cell *p) {
    // Implement your code to check if a cell is in the given list
    // This function should return true if the cell is in the list
}

void print_candidate_num(SudokuBoard *p_board) {
    // Implement your code to print the number of candidates for each cell
}

void print_solution(SudokuBoard *p_board) {
    // Implement your code to print the solved Sudoku solution
}

void set_candidate(Cell *cell, int value) {
    // Implement your code to set a candidate for the given cell
}

void unset_candidate(Cell *cell, int value) {
    // Implement your code to unset a candidate for the given cell
}

void set_candidates(Cell *cell, int *candidates, int size) {
    // Implement your code to set candidates for the given cell
}

int *get_candidates(Cell *cell) {
    // Implement your code to get the candidates for the given cell
    // This function should return a dynamically allocated array of candidates
}

int check_solved_cells(SudokuBoard *p_board, Cell ***p_solved_cells) {
    // Implement your code to check for solved cells and update the solved_cells array
    // This function should return the number of newly solved cells
}

bool show_possible(SudokuBoard *p_board, Cell **p_solved_cells, int counter) {
    // Implement your code to show possible solutions for unsolved cells
    // This function should return true if possible solutions are shown
}

void free_sudoku(SudokuBoard *p_board) {
    // Free the data array (9x9 grid of cells)
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(p_board->data[i]);
    }
    free(p_board->data);

    // Free other pointers
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(p_board->p_rows[i]);
        free(p_board->p_cols[i]);
        free(p_board->p_boxes[i]);
    }

    // Free solved_cells array
    for (int i = 0; i < p_board->solved_counter; i++) {
        free(p_board->solved_cells[i]);
    }

    // Finally, free the SudokuBoard structure itself
    free(p_board);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <sudoku string>\n", argv[0]);
        return 1;
    }

    SudokuBoard *board = (SudokuBoard*)malloc(sizeof(SudokuBoard));
    init_sudoku(board);
    load_sudoku(board, argv[1]);

    Cell **p_solved_cells = board->solved_cells;
    int solved_counter = board->solved_counter;
    while (board->solved_counter < BOARD_SIZE * BOARD_SIZE)
    {
        solved_counter = check_solved_cells(board, &p_solved_cells);
        printf("check_solved_cells %d\n", solved_counter);
        if (show_possible(board, p_solved_cells, solved_counter))
        {
            printf("show_possible -> Yes\n");
            continue;
        }
        // Uncomment the line below to activate the hidden_singles function
        solved_counter = hidden_singles(board);
        if (solved_counter)
        {
            printf("hidden_singles %d\n", solved_counter);
            continue;
        }
    }

    // Call hidden_singles and handle the return value
    // int hidden_singles_count = hidden_singles(board);
    // if (hidden_singles_count > 0)
    // {
    //     printf("hidden_singles %d\n", hidden_singles_count);
    //     // Additional logic if needed
    // }

    print_solution(board);

    // Clean up (free_sudoku already frees the board)
    free_sudoku(board);

    return 0;
}
