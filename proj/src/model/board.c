/**
 * @file board.c
 * @brief Implementation of the Board module, providing functions for managing the game board.
 */

#include <lcom/lcf.h>
#include "board.h"

/**
 * @brief Creates a new Hint structure.
 *
 * @param count The count value for the hint.
 * @return A pointer to the newly created Hint structure.
 */
struct Hint* create_hint(int count) {
    struct Hint* hint = (struct Hint*) malloc(sizeof(Hint));
    hint->count = count;
    hint->next = NULL;
    return hint;
}

/**
 * @brief Constructs a new Board.
 *
 * @param x The x-coordinate of the board.
 * @param y The y-coordinate of the board.
 * @param size The size of the board.
 * @return A pointer to the newly constructed Board.
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
        for(int i = 0; i < size; i++){
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
 * @brief Checks if the player has won the game.
 *
 * @param board The game board.
 * @return True if the player has won, false otherwise.
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
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param board The game board.
 * @return 1 if the tile coordinates are out of bounds, 0 otherwise.
 */
int toggle_board_tile(uint16_t x, uint16_t y, Board *board){
    if(x >= board->size || y >= board->size){
        return 1;
    }

    return toggle_tile(&board->tiles[x][y]);
}

/**
 * @brief Prints the game board to the console.
 *
 * @param board The game board.
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
 * @brief Prints the horizontal hints of the board to the console.
 *
 * @param board The game board.
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
 * @brief Destroys a linked list of hints.
 *
 * @param first The first hint in the linked list.
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
 * @brief Destroys the game board and frees memory.
 *
 * @param board The game board to destroy.
 */
void destroy_board(Board *board){
    if(!board){
        return;
    }

    if(board->tiles){
        for(int i = 0; i < board->size; i++){
            free(board->tiles[i]);
        }
        free(board->tiles);
    }

    if(board->h_hints){
        for(int i = 0; i < board->size; i++){
            destroy_hints(board->h_hints[i]);
        }
        free(board->h_hints);
    }

    if(board->v_hints){
        for(int i = 0; i < board->size; i++){
            destroy_hints(board->v_hints[i]);
        }
        free(board->v_hints);
    }

    free(board);
}
