#include <lcom/lcf.h>

#include "board.h"

struct Hint* create_hint(int count) {
    struct Hint* hint = (struct Hint*) malloc(sizeof(Hint));

    hint->count = count;
    hint->next = NULL;

    return hint;
}

Board *construct_board(uint16_t x, uint16_t y, uint16_t size){
    Board *board = (Board *) malloc(sizeof(Board));

    board->tiles = (Tile **) malloc(sizeof(Tile *)*size);
    board->h_hints = (Hint **) malloc(sizeof(Hint *)*size);
    board->v_hints = (Hint **) malloc(sizeof(Hint *)*size);

    for(int i = 0; i < size; i++){
        board->tiles[i] = (Tile *) malloc(sizeof(Tile)*size);
        board->h_hints[i] = create_hint(0);
        board->v_hints[i] = create_hint(0);
    }

    uint8_t random_solution;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            random_solution = rand() % 2;

            board->tiles[i][j] = construct_tile(x+j,y+i, random_solution);
        }
    }

    board->size = size;
    return board;
}

bool check_win(Board *board){
    if(!board){
        printf("error toggling tile -> NULL\n");
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

int toggle_board_tile(uint16_t x, uint16_t y, Board *board){
    if(x >= board->size || y >= board->size){
        return 1;
    }

    return toggle_tile(&board->tiles[x][y]);
}

void print_board(Board *board){
    for(int i = 0; i < board->size; i++){
        for(int j = 0; j < board->size; j++){
            printf("[%d]", board->tiles[i][j].on);
        }
        printf("\n");
    }
}

void destroy_hints(struct Hint* first) {
    struct Hint* temp;
    while (first != NULL) {
        temp = first;
        first = first->next;
        free(temp);
    }
}

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
