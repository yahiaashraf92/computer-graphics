//
// Created by HaDiDi on 5/16/2023.
//
#include "Line.h"
#include "allCircles.h"

#ifndef COMPUTER_GRAPHICS_CIRCLE_H
#define COMPUTER_GRAPHICS_CIRCLE_H

void draw8points_quarterlinefill(HDC hdc, int xc, int yc, int a, int b, COLORREF color) {

    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc + b, yc + a, color);

    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - b, yc + a, color);

    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc - b, yc - a, color);

    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc - a, color);


    drawline(hdc, xc + b, yc + a, xc, yc, color);
    drawline(hdc, xc + a, yc + b, xc, yc, color);

}

// circle shape
void drawCircle_quarterlinefill(HDC hdc, int xc, int yc, int r, COLORREF c) {

    int x = 0;
    int y = r;

    int d = 1 - r;

    while (x < y) {
        if (d <= 0) {
            d += 2 * x + 3;

        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        draw8points_quarterlinefill(hdc, xc, yc, x, y, c);
    }


}


int quadX, quadY;


void draw8points(HDC hdc, int xc, int yc, int a, int b, COLORREF color) {

    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc + b, yc + a, color);

    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - b, yc + a, color);

    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc - b, yc - a, color);

    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc - a, color);

}

//void drawCircle(HDC hdc, int xc, int yc, int r, COLORREF color) {
//
//    int x = 0;
//    int y = r;
//
//    int d = 1 - r;
//
//    while (x < y) {
//        if (d <= 0) {
//            d += 2 * x + 3;
//
//        } else {
//            d += 2 * (x - y) + 5;
//            y--;
//        }
//        x++;
//        draw8points(hdc, xc, yc, x, y, color);
//    }
//}

int base = 0;
int base1;

void draw8pointsWithCircles(HDC hdc, int xc, int yc, int a, int b, int r, COLORREF color) {

    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc + b, yc + a, color);

    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - b, yc + a, color);

    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc - b, yc - a, color);

    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc - a, color);

    if (xc + a >= (base + (r / 16))) {
        base = (xc + a) + (r / 16);
        for (int i = yc; i <= yc + b; i += (r / 8)) {
            if (quadX < xc && quadY < yc) {
                drawCircleMidpoint(hdc, xc - a, i - b, r / 16, color);
            } else if (quadX > xc && quadY < yc)
                drawCircleMidpoint(hdc, xc + a, i - b, r / 16, color);
            else if (quadX > xc && quadY > yc)
                drawCircleMidpoint(hdc, xc + a, i, r / 16, color);
            else if (quadX < xc && quadY > yc)
                drawCircleMidpoint(hdc, xc - a, i, r / 16, color);

        }
    }
    if (xc + b <= base1 - (r / 16)) {
        base1 = (xc + b) - (r / 16);
        for (int i = yc; i <= yc + a; i += (r / 8)) {
            if (quadX < xc && quadY < yc)
                drawCircleMidpoint(hdc, xc - b, i - a, r / 16, color);
            else if (quadX > xc && quadY < yc)
                drawCircleMidpoint(hdc, xc + b, i - a, r / 16, color);
            else if (quadX > xc && quadY > yc)
                drawCircleMidpoint(hdc, xc + b, i, r / 16, color);
            else if (quadX < xc && quadY > yc)
                drawCircleMidpoint(hdc, xc - b, i, r / 16, color);
        }
    }


}

// the quarter that is going to be filled is depending on the place of the second click
void drawCircleWithCircles(HDC hdc, int xc, int yc, int r, COLORREF color) {

    base = xc;
    base1 = xc + r;
    int x = 0;
    int y = r;

    int d = 1 - r;

    while (x < y) {
        if (d <= 0) {
            d += 2 * x + 3;

        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        draw8pointsWithCircles(hdc, xc, yc, x, y, r, color);
    }


}

#endif //COMPUTER_GRAPHICS_CIRCLE_H
