#include "board.h"
#define TAILLE_MAX 9

struct board_s {
    int tab[TAILLE_MAX][TAILLE_MAX];
    int gameType;
    int actualPlayer;
};


*struct board_s new_game(){
    struct board_s board;
    for(int i = 0; i < NB_LINES; i++){
        for(int j = 0; j < NB_COLS; j++){
            board.tab[i][j] = 0; // EMPTY VOIR CHIFFRE SI ON PEUT PAS USE L'ENUM
        }
    }
    board.tab[0][(NB_LINES/2)]

}
