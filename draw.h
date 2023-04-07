#ifndef DRAW_H
#define DRAW_H

#include "game.h"

#define V_OFFSET 5
#define H_OFFSET 87
#define SCALE_FACTOR 6
#define MARGIN 1

void drawFullApp(App *state);
void undrawApp(App *state);
void drawApp(App *state);

#endif