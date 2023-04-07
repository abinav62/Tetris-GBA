#include "game.h"
#include "draw.h"
#include "images/grayBlock.h"

int pieces[7][4][4][4] = {
    {  // Hero
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        }
    },

    { // Smashboy
        { 
            {0, 0, 0, 0},
            {0, 2, 2, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0},
        },
        { 
            {0, 0, 0, 0},
            {0, 2, 2, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 0, 0},
            {0, 2, 2, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 0, 0},
            {0, 2, 2, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0},
        }
    },

    { // Teewee
        {
            {0, 0, 3, 0},
            {0, 3, 3, 3},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 3, 0},
            {0, 0, 3, 3},
            {0, 0, 3, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 0, 0},
            {0, 3, 3, 3},
            {0, 0, 3, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 3, 0},
            {0, 3, 3, 0},
            {0, 0, 3, 0},
            {0, 0, 0, 0},
        }
    },

    { // BlueR
        { 
            {0, 0, 4, 0},
            {0, 0, 4, 0},
            {0, 4, 4, 0},
            {0, 0, 0, 0},
        },
        { 
            {0, 4, 0, 0},
            {0, 4, 4, 4},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 4, 4},
            {0, 0, 4, 0},
            {0, 0, 4, 0},
            {0, 0, 0, 0},
        },
        { 
            {0, 0, 0, 0},
            {0, 4, 4, 4},
            {0, 0, 0, 4},
            {0, 0, 0, 0},
        }
    },

    { // Orange
        {
            {0, 0, 5, 0},
            {0, 0, 5, 0},
            {0, 0, 5, 5},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 0, 0},
            {0, 5, 5, 5},
            {0, 5, 0, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 5, 5, 0},
            {0, 0, 5, 0},
            {0, 0, 5, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 0, 5},
            {0, 5, 5, 5},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        }
    },
    
    { // Rhode Island
        {
            {0, 0, 0, 0},
            {0, 0, 6, 6},
            {0, 6, 6, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 6, 0, 0},
            {0, 6, 6, 0},
            {0, 0, 6, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 6, 6},
            {0, 6, 6, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 6, 0},
            {0, 0, 6, 6},
            {0, 0, 0, 6},
            {0, 0, 0, 0},
        }
    },

    { // Cleveland
        {
            {0, 0, 0, 0},
            {0, 7, 7, 0},
            {0, 0, 7, 7},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 7, 0},
            {0, 7, 7, 0},
            {0, 7, 0, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 7, 7, 0},
            {0, 0, 7, 7},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        },
        {
            {0, 0, 0, 7},
            {0, 0, 7, 7},
            {0, 0, 7, 0},
            {0, 0, 0, 0},
        }
    }
};

int timer = 0;
int currBlock[4][4];

void initApp(App *app) {
    for (int r = 0; r < STAGE_HEIGHT; r++) {
        for (int c = 0; c < STAGE_WIDTH; c++) {
            app->stage[r][c] = 0;
        }
    }

    app->currRate = 20;
    app->nRate = 20;
    app->rotation = 0;
    app->id = 0;
    app->lines = 0;
    app->score = 0;
    app->gameOver = 0;

    createPiece(app);
}

void createPiece(App* nextApp) {
    nextApp->rotation = 0;
    nextApp->id = randint(0, 7);
    nextApp->x = STAGE_WIDTH/2 - 2;
    nextApp->y = -1;
    nextApp->canFastFall = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            currBlock[i][j] = pieces[nextApp->id]
                                       [nextApp->rotation]
                                       [i][j];
}

int placeable(App* app, int piece[4][4], int x, int y) {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            int xcoord = x + a;
            int ycoord = y + b;
            if (piece[b][a] != 0) {
                if (xcoord < 0 || xcoord >= STAGE_WIDTH) {
                    return BLOCKED_LR;
                } else if (ycoord >= STAGE_HEIGHT
                        || app->stage[ycoord][xcoord] != 0) {
                    return BLOCKED_DOWN;
                }
            }
        }
    }
    return CAN_PLACE;
}

void place(App *nextApp, int piecex, int piecey) {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            int coordx = piecex + a;
            int coordy = piecey + b;
            if (currBlock[b][a] != 0) {
                nextApp->stage[coordy][coordx] = currBlock[b][a];
            }
        }
    }
    nextApp->score += 10;
}

void rotate(App *nextApp, App *app, int dir) {
    if (dir == LEFT) {
        int newRot = (app->rotation - 1);
        if (newRot < 0) newRot = 3;
        switch(placeable(app,
                pieces[app->id][newRot],
                app->x, 
                app->y)) {
            case CAN_PLACE:
                nextApp->rotation = newRot;
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        currBlock[i][j] = pieces[nextApp->id]
                                                [nextApp->rotation]
                                                [i][j];
                break;
            case BLOCKED_LR:
                break;
            case BLOCKED_DOWN:
                break;
        }
    } else if (dir == RIGHT) {
        int newRot = (app->rotation + 1) % 4;
        switch(placeable(app,
                pieces[app->id][newRot],
                app->x, 
                app->y)) {
            case CAN_PLACE:
                nextApp->rotation = newRot;
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        currBlock[i][j] = pieces[nextApp->id]
                                                [nextApp->rotation]
                                                [i][j];
                break;
            case BLOCKED_LR:
                break;
            case BLOCKED_DOWN:
                break;
        }
    }
}

void removeLines(App *nextApp) {
    // check for loss
    for (int x = 0; x < STAGE_WIDTH; x++) {
        if (nextApp->stage[0][x] > 0) {
            nextApp->gameOver = 1;
        }
    }
    // check the rest of the board
    if (nextApp->gameOver != 1) {
        for (int y = STAGE_HEIGHT - 1; y > 0; y--) {
            unsigned char isComplete = 1;
            for (int x = 0; x < STAGE_WIDTH; x++) {
                if (nextApp->stage[y][x] == 0) {
                    isComplete = 0;
                }
            }
            if (isComplete == 1) {
                for (int yc = y; yc > 0; yc--) {
                    for (int x = 0; x < STAGE_WIDTH; x++) {
                        nextApp->stage[yc][x] = nextApp->stage[yc - 1][x];
                    }
                }
                nextApp->lines += 1;
                nextApp->score += 100;
                y++;
            }
        }
        switch (nextApp->lines) {
            case 10: nextApp->nRate = 17;
                break;
            case 20: nextApp->nRate = 14;
                break;
            case 30: nextApp->nRate = 11;
                break;
            case 40: nextApp->nRate = 8;
                break;
            case 50: nextApp->nRate = 5;
                break;
        }
    }
}

App processApp(App *app, u32 oldButtons, u32 currButtons) {
    App nextApp = *app;
    int a = app->x;
    int b = app->y;

    if (vBlankCounter % app->currRate == 0) {
        switch(placeable(app, currBlock, a, b + 1)) {
            case CAN_PLACE:
                nextApp.y = b + 1;
                break;
            case BLOCKED_LR:
                break;
            case BLOCKED_DOWN:
                place(&nextApp, a, b);
                removeLines(&nextApp);
                createPiece(&nextApp);
                break;
        }
    }

    if (KEY_JUST_PRESSED(BUTTON_LEFT, currButtons, oldButtons)) {
        switch(placeable(app, currBlock, a - 1, b)) {
            case CAN_PLACE:
                nextApp.x -= 1;
                break;
            case BLOCKED_LR:
                break;
            case BLOCKED_DOWN:
                break;
        }
    } else if (KEY_JUST_PRESSED(BUTTON_RIGHT, currButtons, 
            oldButtons)) {
        switch(placeable(app, currBlock, a + 1, b)) {
            case CAN_PLACE:
                nextApp.x += 1;
                break;
            case BLOCKED_LR:
                break;
            case BLOCKED_DOWN:
                break;
        }
    }

    if (KEY_HELD(BUTTON_LEFT, currButtons, oldButtons)) {
        timer += 1;
        if (timer > MOVE_DELAY && vBlankCounter % 4 == 0) {
            switch(placeable(app, currBlock, a - 1, b)) {
                case CAN_PLACE:
                    nextApp.x -= 1;
                    break;
                case BLOCKED_LR:
                    break;
                case BLOCKED_DOWN:
                    break;
            }
        }
    } else if (KEY_HELD(BUTTON_RIGHT, currButtons, oldButtons)) {
        timer += 1;
        if (timer > MOVE_DELAY && vBlankCounter % 4 == 0) {
            switch(placeable(app, currBlock, a + 1, b)) {
                case CAN_PLACE:
                    nextApp.x += 1;
                    break;
                case BLOCKED_LR:
                    break;
                case BLOCKED_DOWN:
                    break;
            }
        }
    } else {
        timer = 0;
    }

    if (KEY_JUST_PRESSED(BUTTON_A, currButtons, oldButtons)) {
        rotate(&nextApp, app, LEFT);
    } else if (KEY_JUST_PRESSED(BUTTON_B, currButtons, oldButtons)) {
        rotate(&nextApp, app, RIGHT);
    }

    if (KEY_JUST_PRESSED(BUTTON_DOWN, currButtons, oldButtons)) {
        nextApp.canFastFall = 1;
    }

    if (KEY_DOWN(BUTTON_DOWN, currButtons)) {
        if (app->canFastFall == 1) {
            nextApp.currRate = 3;
            nextApp.score += 2;
        }
    } else {
        nextApp.currRate = nextApp.nRate;
    }
    return nextApp;
}