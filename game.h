#ifndef GAME_H
#define GAME_H

#define STAGE_HEIGHT 21
#define STAGE_WIDTH 10
#define NUM_PIECES 7
#define WINNING_LINES 50
#define BLOCKED_LR 0
#define BLOCKED_DOWN 1
#define CAN_PLACE 2
#define LEFT 0
#define RIGHT 1
#define MOVE_DELAY 10

#include "gba.h"

typedef struct {
    int stage[STAGE_HEIGHT][STAGE_WIDTH];
    int x;
    int y;
    int id;
    int rotation;
    int nRate;
    int currRate;
    int canFastFall;
    int lines;
    int score;
    int gameOver;
} App;

extern int currBlock[4][4];
void initApp(App *appState);
void createPiece(App *nextAppState);
int placeable(App *currentAppState, int piece[4][4], int piecex, int piecey);
void place(App *nextAppState, int piecex, int piecey);
void rotate(App *nextAppState, App *currentAppState, int dir);
void removeLines(App *nextAppState);
App processApp(App *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);
#endif