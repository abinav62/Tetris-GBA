#include "gba.h"
#include "game.h"
#include "draw.h"

#include "images/back.h"
#include "images/title.h"
#include "images/grayBlock.h"
#include "images/block1.h"
#include "images/block2.h"
#include "images/block3.h"
#include "images/block4.h"
#include "images/block5.h"
#include "images/block6.h"
#include "images/block7.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    START,
    START2,
    INIT,
    APP,
    EXIT,
    EXIT2,
} GBAState;

int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    GBAState state = START;

    App app, nextApp;

    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    while (1) {
        currentButtons = BUTTONS;

        switch(state) {
            case START:
                waitForVBlank();
                drawFullScreenImageDMA(title);
                state = START2;
                break;
            case START2:
                if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                    state = INIT;
                }
                break;
            case INIT:
                initApp(&app);

                drawFullApp(&app);

                state = APP;
                break;
            case APP:
                nextApp = processApp(&app, previousButtons, currentButtons);
                waitForVBlank();
                undrawApp(&app);
                drawApp(&nextApp);
                app = nextApp;
                if (nextApp.gameOver) {
                    state = EXIT;
                }
                
                if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                    state = START;
                }

                break;
            case EXIT:
                waitForVBlank();

                drawCenteredString(WIDTH/2-20, HEIGHT/2, 40, 40, "Game Over", WHITE);

                state = EXIT2;
                break;
            case EXIT2:
                if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons) || KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                    state = START;
                }

                break;
        }
        previousButtons = currentButtons;
    }

    return 0;
}