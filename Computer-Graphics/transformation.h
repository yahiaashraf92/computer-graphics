//
// Created by HaDiDi on 5/17/2023.
//

#ifndef COMPUTER_GRAPHICS_TRANSFORMATION_H
#define COMPUTER_GRAPHICS_TRANSFORMATION_H
void traslateLine(HDC hdc,int x1,int y1,int x2, int y2, COLORREF c, int xshift, int yshift){
    int dx = x2 - x1;
    int dy = y2 - y1;
    SetPixel(hdc, x1, y1, c);
    if (abs(dx) >= abs(dy)) {
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        int x = x1, xinc = 1;
        double y = y1, yinc = (double) dy / dx;
        while (x != x2) {
            x += xinc;
            y += yinc;
            SetPixel(hdc, x + xshift, round(y) + yshift, c);
        }
    } else {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        int y = y1, yinc = 1;
        double x = x1, xinc = (double) dx / dy;
        while (y != y2) {
            x += xinc;
            y += yinc;
            SetPixel(hdc, x + xshift, round(y) + yshift, c);
        }
    }
}
#endif //COMPUTER_GRAPHICS_TRANSFORMATION_H
