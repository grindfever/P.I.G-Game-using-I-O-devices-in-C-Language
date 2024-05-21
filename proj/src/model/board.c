#include <lcom/lcf.h>

#include "board.h"

Board *construct_board(int16_t x, int16_t y, int16_t size){
    Board *board = (Board *) malloc(sizeof(Board));

    board->tiles = (Tile **) malloc(sizeof(Tile *)*size);

    for(int i = 0; i < size; i++){
        board->tiles[i] = (Tile *) malloc(sizeof(Tile)*size);
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board->tiles[i][j] = construct_tile(x+j,y+i, 0);
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
