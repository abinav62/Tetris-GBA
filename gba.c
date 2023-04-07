#include "gba.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *) 0x6000000;
u32 vBlankCounter = 0;

void waitForVBlank(void) {
    while (*SCANLINECOUNTER > 160);
    while (*SCANLINECOUNTER < 160);
    vBlankCounter += 1;

}

static int __qran_seed= 42;
static int qran(void) {
    __qran_seed= 1664525*__qran_seed+1013904223;
    return (__qran_seed>>16) & 0x7FFF;
}

int randint(int min, int max) {
    return (qran()*(max-min)>>15)+min;
}

void setPixel(int row, int col, u16 color) {
    videoBuffer[OFFSET(row, col, WIDTH)] = color;
}

void drawRectDMA(int row, int col, int width, int height, volatile u16 color) {
    for (int x = 0; x < height; x++) {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(col + x, row, 240)];
        DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
    }
}

void drawFullScreenImageDMA(const u16 *image) {
    DMA[3].src = image;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (WIDTH * HEIGHT) | DMA_ON | DMA_16 | DMA_SOURCE_INCREMENT;
}

void drawImageDMA(int row, int col, int width, int height, const u16 *image) {
    for (int x = 0; x < height; x++) {
        DMA[3].src = &image[OFFSET(x, 0, width)];
        DMA[3].dst = &videoBuffer[OFFSET(col + x, row, 240)];
        DMA[3].cnt = (width) | DMA_ON | DMA_16 | DMA_SOURCE_INCREMENT;
    }
}

// void fillScreenDMA(volatile u16 color) {
//     DMA[3].src = &color;
//     DMA[3].dst = videoBuffer;
//     DMA[3].cnt = WIDTH * HEIGHT | DMA_ON | DMA_16 | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT;
// }

void drawChar(int col, int row, char ch, u16 color) {
    for(int r = 0; r<8; r++) {
        for(int c=0; c<6; c++) {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
                setPixel(row + r, col + c, color);
            }
        }
    }
}

void drawString(int col, int row, char *str, u16 color) {
    while(*str) {
        drawChar(col, row, *str++, color);
        col += 6;
    }
}

void drawCenteredString(int x, int y, int width, int height, char *str, u16 color) {
    u32 len = 0;
    char *strCpy = str;
    while (*strCpy) {
        len++;
        strCpy++;
    }

    u32 strWidth = 6 * len;
    u32 strHeight = 8;

    int col = x + ((width - strWidth) >> 1);
    int row = y + ((height - strHeight) >> 1);
    drawString(col, row, str, color);
}