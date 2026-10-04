#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    NONE,
    PLAYER_X,
    OPONNENT
}Player;

typedef struct {
    Player board[3][3];
    bool gameOver;
    Player current_player;
}Game;

void printBoard(const Player board[3][3]) {
    for (uint8_t i = 0; i<3; i++) {
        printf("\n----------------\n");
        for (uint8_t j = 0; j<3; j++) {
            printf("|");
            if (board[i][j] == NONE) printf("   ");
            else if (board[i][j] == PLAYER_X) printf(" X ");
            else if (board[i][j] == OPONNENT) printf( " O ");
            printf("|");
        }
    }
    printf("\n----------------\n");
}

Game* startGame() {
    Game* game = malloc(sizeof(Game));
    if (game == NULL) {
        printf("Falha ao alocar memoria\n");
        return NULL;
    }

    game->gameOver = false;
    game->current_player = PLAYER_X;

    for (__uint8_t i = 0; i < 3; i++) {
        for (__uint8_t j = 0; j <3; j++) {
            game->board[i][j] = NONE;
        }
    }

    return game;
}

int checkWinner(int col[3], int row[3], int dia1, int dia2) {
    // dia1 and 2 are the diagonals, top left -> bottom right and top right -> bottom left, respectivally
    if (col[0] == 3 || col[1] == 3 || col[2] == 3 || row[0] == 3 || row[1] == 3 || row[2] == 3 || dia1 == 3 || dia2 == 3) {
        return 1; // the player wins
    }else if (col[0] == -3 || col[1] == -3 || col[2] == -3 || row[0] == -3 || row[1] == -3 || row[2] == -3 || dia1 == -3 || dia2 == -3) {
        return -1; // the oponent wins
    }else {
        return 0; // it's draw
    }
}

int8_t* minimax(Player board[3][3], int depth, bool is_maximizing) {
    // this array have the board best move's cords on the first two index
    // and the best score for the minimax on the third one
    int8_t scores[3];

    int8_t result = checkWinner();

    if (result != 0) {
        scores[0] = -1;
        scores[1] = -1;
        scores[2] = result;

        return scores;
    }
    if (is_maximizing) { // searching for the best player move
        scores[0] = -1;
        scores[1] = -1;
        scores[3] = INT8_MIN;

        for (int8_t i = 0; i < 3; i++) {
            for (int8_t j = 0; j < 3; j++) {
                if (board[i][j] == NONE){
                    board[i][j] = PLAYER_X;
                    int8_t* score = minimax(board, depth + 1, false);
                    board [i][j] = NONE;
                    if (score[2] > scores[2]) {
                        scores[2] = score[2];
                        scores[0] = i;
                        scores[1] = j;
                    }
                }
            }
        }
    }else { // search for the better machine move
        scores[0] = -1;
        scores[1] = -1;
        scores[3] = INT8_MIN;

        for (int8_t i = 0; i < 3; i++) {
            for (int8_t j = 0; j < 3; j++) {
                if (board[i][j] == NONE) {
                    board[i][j] = OPONNENT;
                    int8_t* score = minimax(board, depth + 1, true);
                    board [i][j] = NONE;
                    if (score[2] < scores[2]) {
                        scores[2] = score[2];
                        scores[0] = i;
                        scores[1] = j;
                    }
                }
            }
        }
    }
    return scores; // put those on a struct
}

int8_t* findBestMove(Player board[3][3]) {
    int8_t* scores = minimax(board, 0, true);
    int8_t move[2] = {scores[0], scores[1]};

    return move;
}

int main(void){

    Game* game = startGame();

    while (true) {
        do {
            printf("Enter row (0 - 2) for your move\n")
            scanf();
            printf("Enter row (0 - 2) for your move\n")
            scanf();
        }while (true);
    }

    free(game);
    return 0;
}