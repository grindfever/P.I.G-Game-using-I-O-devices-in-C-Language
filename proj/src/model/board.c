#include <lcom/lcf.h>

#include "board.h"

Board *construct_board(uint16_t x, uint16_t y, uint16_t size){
    Board *board = (Board *) malloc(sizeof(Board));

    board->tiles = (Tile **) malloc(sizeof(Tile *)*size);

    for(int i = 0; i < size; i++){
        board->tiles[i] = (Tile *) malloc(sizeof(Tile)*size);
    }

    uint8_t random_solution;
    uint8_t chance = 2;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            random_solution = rand() % chance;

            if (random_solution == 1) {
                chance *= 2;
            } else {
                random_solution = 0;
                chance = 2;
            } 

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

void print_board(Board *board){
    for(int i = 0; i < board->size; i++){
        for(int j = 0; j < board->size; j++){
            printf("[%d]", board->tiles[i][j].solution);
        }
        printf("\n");
    }
}

void destroy_board(Board *board){
    if(!board){
        return;
    }

    for(int i = 0; i < board->size; i++){
        free(board->tiles[i]);
    }

    free(board->tiles);

    free(board);
}
