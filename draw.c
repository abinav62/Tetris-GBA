#include "draw.h"
#include "gba.h"
#include <stdio.h>

#include "images/back.h"
#include "images/grayBlock.h"
#include "images/block1.h"
#include "images/block2.h"
#include "images/block3.h"
#include "images/block4.h"
#include "images/block5.h"
#include "images/block6.h"
#include "images/block7.h"

void drawFullApp(App *state) {
    drawFullScreenImageDMA(back);
    UNUSED(state);
}

void undrawApp(App *state) {
    drawRectDMA(H_OFFSET-5, V_OFFSET-5, STAGE_WIDTH*(SCALE_FACTOR+MARGIN)+10,
            STAGE_HEIGHT*(SCALE_FACTOR+MARGIN)+10, BLACK);
    drawRectDMA(160, 120, 70, 30, BLACK);
    UNUSED(state);
}

void drawApp(App *state) {
    for (int row = 0; row < STAGE_HEIGHT; row++) {
        for (int col = 0; col < STAGE_WIDTH; col++) {
            switch(state->stage[row][col]) {
                case 1:
                    drawImageDMA(H_OFFSET+col*(MARGIN+SCALE_FACTOR), V_OFFSET+row*(MARGIN+SCALE_FACTOR),
                            7, 7, block1);
                    break;
                case 2:
                    drawImageDMA(H_OFFSET+col*(MARGIN+SCALE_FACTOR), V_OFFSET+row*(MARGIN+SCALE_FACTOR),
                            7, 7, block2);
                    break;
                case 3:
                    drawImageDMA(H_OFFSET+col*(MARGIN+SCALE_FACTOR), V_OFFSET+row*(MARGIN+SCALE_FACTOR),
                            7, 7, block3);
                    break;
                case 4:
                    drawImageDMA(H_OFFSET+col*(MARGIN+SCALE_FACTOR), V_OFFSET+row*(MARGIN+SCALE_FACTOR),
                            7, 7, block4);
                    break;
                case 5:
                    drawImageDMA(H_OFFSET+col*(MARGIN+SCALE_FACTOR), V_OFFSET+row*(MARGIN+SCALE_FACTOR),
                            7, 7, block5);
                    break;
                case 6:
                    drawImageDMA(H_OFFSET+col*(MARGIN+SCALE_FACTOR), V_OFFSET+row*(MARGIN+SCALE_FACTOR),
                            7, 7, block6);
                    break;
                case 7:
                    drawImageDMA(H_OFFSET+col*(MARGIN+SCALE_FACTOR), V_OFFSET+row*(MARGIN+SCALE_FACTOR),
                            7, 7, block7);
                    break;
            }
        }
    }
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            int px = col + state->x;
            int py = row + state->y;
            switch(currBlock[row][col]) {
                case 1: 
                    drawImageDMA(H_OFFSET+px*(MARGIN+SCALE_FACTOR), V_OFFSET+py*(MARGIN+SCALE_FACTOR),
                            7, 7, block1);
                    break;
                case 2:
                    drawImageDMA(H_OFFSET+px*(MARGIN+SCALE_FACTOR), V_OFFSET+py*(MARGIN+SCALE_FACTOR),
                            7, 7, block2);
                    break;
                case 3:
                    drawImageDMA(H_OFFSET+px*(MARGIN+SCALE_FACTOR), V_OFFSET+py*(MARGIN+SCALE_FACTOR),
                            7, 7, block3);
                    break;
                case 4:
                    drawImageDMA(H_OFFSET+px*(MARGIN+SCALE_FACTOR), V_OFFSET+py*(MARGIN+SCALE_FACTOR),
                            7, 7, block4);
                    break;
                case 5:
                    drawImageDMA(H_OFFSET+px*(MARGIN+SCALE_FACTOR), V_OFFSET+py*(MARGIN+SCALE_FACTOR),
                            7, 7, block5);
                    break;
                case 6:
                    drawImageDMA(H_OFFSET+px*(MARGIN+SCALE_FACTOR), V_OFFSET+py*(MARGIN+SCALE_FACTOR),
                            7, 7, block6);
                    break;
                case 7:
                    drawImageDMA(H_OFFSET+px*(MARGIN+SCALE_FACTOR), V_OFFSET+py*(MARGIN+SCALE_FACTOR),
                            7, 7, block7);
                    break;
            }
        }
    }
    char buffer[51];
    sprintf(buffer, "Lines:%d", state->lines);
    drawString(164, 124, buffer, WHITE);
    sprintf(buffer, "Score:%d", state->score);
    drawString(164, 138, buffer, WHITE);
}