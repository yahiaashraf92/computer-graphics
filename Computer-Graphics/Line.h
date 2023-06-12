//
// Created by HaDiDi on 5/16/2023.
//

#ifndef COMPUTER_GRAPHICS_LINE_H
#define COMPUTER_GRAPHICS_LINE_H

void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

//line shape
void drawline(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {

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
            SetPixel(hdc, x, round(y), c);
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
            SetPixel(hdc, x, round(y), c);
        }
    }
}

//line shape with midpoint
void MidPoint(HDC hdc, int xs, int ys, int xe, int ye, COLORREF c) {
    int x, y;
    int dx = xe - xs;
    int dy = ye - ys;
    if (abs(dy) > 0 && abs(dx) > abs(dy)) {
        if (xs > xe) {
            swap(xs, xe);
            swap(ys, ye);
            dx = xe - xs;
            dy = ye - ys;
        }
        x = xs;
        y = ys;
        SetPixel(hdc, x, y, c);
        int d = dx - 2 * dy;
        int d1 = -dy;
        int d2 = 2 * dx - 2 * dy;
        while (x < xe) {
            if (d > 0) {
                d += d1;
            } else {
                d += d2;
                y++;
            }
            x++;
            SetPixel(hdc, x, y, c);

        }
    } else if (abs(dy) > abs(dx)) {
        if (ys > ye) {
            swap(xs, xe);
            swap(ys, ye);
            dx = xe - xs;
            dy = ye - ys;
        }
        x = xs;
        y = ys;
        SetPixel(hdc, x, y, c);
        int d = dx - 2 * dy;
        int d1 = -dx;
        int d2 = 2 * dy - 2 * dx;
        while (y < ye) {
            if (d > 0) {
                d += d1;
            } else {
                d += d2;
                x++;
            }
            y++;
            SetPixel(hdc, x, y, c);

        }
    }
}

// hermite curve shape
void hermite(HDC hdc, POINT p[], COLORREF c) {

    int m[4][4] = {
            {2,  1,  -2, 1},
            {-3, -2, 3,  -1},
            {0,  1,  0,  0},
            {1,  0,  0,  0}};

    int px[] = {p[0].x, 2 * (p[1].x - p[0].x), p[3].x, 2 * (p[3].x - p[2].x)};
    int py[] = {p[0].y, 2 * (p[1].y - p[0].y), p[3].y, 2 * (p[3].y - p[2].y)};
    int a[4];
    int b[4];
    for (int i = 0; i < 4; i++) {
        a[i] = 0;
        for (int j = 0; j < 4; j++) {
            a[i] += m[i][j] * px[j];
        }
    }
    for (int i = 0; i < 4; i++) {
        b[i] = 0;
        for (int j = 0; j < 4; j++) {
            b[i] += m[i][j] * py[j];
        }
    }
    double dt = 1.0 / (7000 - 1);
    double x = 0, y = 0;
    //int vt[4] = {};
    for (double t = 0; t <= 1; t += dt) {
        //double dd = 1;
        x = a[0] * t * t * t + a[1] * t * t + a[2] * t + a[3];
        y = b[0] * t * t * t + b[1] * t * t + b[2] * t + b[3];
        SetPixel(hdc, round(x), round(y), c);
    }
}

#endif //COMPUTER_GRAPHICS_LINE_H
