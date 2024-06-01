/**
 * @file board.c
 * @brief Implementation of the Board module, providing functions for managing the game board.
 */

#include <lcom/lcf.h>
#include "board.h"

/**
 * @brief Creates a new hint with the specified count.
 * 
 * @param count The count for the hint.
 * @return Pointer to the created hint.
 */
struct Hint* create_hint(int count) {
    struct Hint* hint = (struct Hint*) malloc(sizeof(Hint));
    hint->count = count;
    hint->next = NULL;
    return hint;
}

/**
 * @brief Constructs a new board.
 * 
 * Initializes the board with random solutions and calculates horizontal and vertical hints.
 * 
 * @param x The X coordinate of the board's position.
 * @param y The Y coordinate of the board's position.
 * @param size The size of the board.
 * @return Pointer to the constructed board.
 */
Board *construct_board(uint16_t x, uint16_t y, uint16_t size){
    Board *board = (Board *) malloc(sizeof(Board));
    board->tiles = (Tile **) malloc(sizeof(Tile *) * size);
    board->h_hints = (Hint **) malloc(sizeof(Hint *) * size);
    board->v_hints = (Hint **) malloc(sizeof(Hint *) * size);
    board->x = x;
    board->y = y;

    for(int i = 0; i < size; i++){
        board->tiles[i] = (Tile *) malloc(sizeof(Tile) * size);
        board->h_hints[i] = create_hint(0);
        board->v_hints[i] = create_hint(0);
    }

    uint8_t random_solution;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            random_solution = rand() % 2;
            if(random_solution){
                board->v_hints[i]->count += 1;
            } else {
                if(board->v_hints[i]->count != 0){
                    Hint* temp = create_hint(0);
                    temp->next = board->v_hints[i];
                    board->v_hints[i] = temp;
                }
            }
            board->tiles[i][j] = construct_tile(x + j, y + i, random_solution);
        }
    }

    for(int j = 0; j < size; j++){
        for(int i = size - 1; i >= 0; i--){
            int v_solution = board->tiles[i][j].solution;
            if(v_solution){
                board->h_hints[j]->count += 1;
            } else {
                if(board->h_hints[j]->count != 0){
                    Hint* temp = create_hint(0);
                    temp->next = board->h_hints[j];
                    board->h_hints[j] = temp;
                }
            }
        }
    }

    board->size = size;
    return board;
}

/**
 * @brief Checks if the board is in a winning state.
 * 
 * Verifies that all tiles are in the correct state.
 * 
 * @param board Pointer to the board.
 * @return True if the board is in a winning state, false otherwise.
 */
bool check_win(Board *board){
    if(!board){
        return false;
    }

    for(int i = 0; i < board->size; i++){
        for(int j = 0; j < board->size; j++){
            if(is_wrong(board->tiles[i][j])){
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Toggles the state of a tile on the board.
 * 
 * @param x The X coordinate of the tile.
 * @param y The Y coordinate of the tile.
 * @param board Pointer to the board.
 * @return 0 upon success, non-zero otherwise.
 */
int toggle_board_tile(uint16_t x, uint16_t y, Board *board){
    if(x >= board->size || y >= board->size){
        return 1;
    }

    return toggle_tile(&board->tiles[x][y]);
}

/**
 * @brief Prints the board to the console.
 * 
 * Displays the current state of the board tiles.
 * 
 * @param board Pointer to the board.
 */
void print_board(Board *board){
    for(int i = 0; i < board->size; i++){
        for(int j = 0; j < board->size; j++){
            printf("[%d]", board->tiles[i][j].on);
        }
        printf("\n");
    }
}

/**
 * @brief Prints the horizontal hints of the board.
 * 
 * @param board Pointer to the board.
 */
void print_h_hints(Board *board) {
    for(int i = 0; i < board->size; i++){
        Hint* current = board->v_hints[i];

        printf("Hints->%d:\n", i);
        while (current != NULL) {
            if(current->count != 0){
                printf("%d\n", current->count);
            }
            current = current->next;
        }
    }
}

/**
 * @brief Destroys the hint linked list.
 * 
 * Frees the memory allocated for the hints.
 * 
 * @param first Pointer to the first hint in the list.
 */
void destroy_hints(struct Hint* first) {
    struct Hint* temp;
    while (first != NULL) {
        temp = first;
        first = first->next;
        free(temp);
    }
}

/**
 * @brief Destroys the board and frees allocated memory.
 * 
 * @param board Pointer to the board.
 */
void destroy_board(Board *board){
    if(!board){
        return;
    }

    for(int i = 0; i < board->size; i++){
        free(board->tiles[i]);

        if(board->h_hints){
            destroy_hints(board->h_hints[i]);
        }

        if(board->v_hints){
            destroy_hints(board->v_hints[i]);
        }
    }

    free(board->tiles);
    free(board->h_hints);
    free(board->v_hints);
    free(board);
}
