//
// Created by lenovo on 5/16/2023.
//

#ifndef GRAPHICSPROJECT_ALLCIRCLES_H
#define GRAPHICSPROJECT_ALLCIRCLES_H

using namespace std;

#include<math.h>
#include <tchar.h>
#include <windows.h>
#include "allLines.h"




void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{
    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc + a, color);
    SetPixel(hdc, xc - b, yc + a, color);
    SetPixel(hdc, xc - b, yc - a, color);
    SetPixel(hdc, xc + b, yc - a, color);
}
void drawCircleMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color) {
    int x = R;
    int y = 0;
    int d = 1 - R;

    while (x > y) {
        SetPixel(hdc, xc + x, yc + y, color);
        SetPixel(hdc, xc + y, yc + x, color);
        SetPixel(hdc, xc - y, yc + x, color);
        SetPixel(hdc, xc - x, yc + y, color);
        SetPixel(hdc, xc - x, yc - y, color);
        SetPixel(hdc, xc - y, yc - x, color);
        SetPixel(hdc, xc + y, yc - x, color);
        SetPixel(hdc, xc + x, yc - y, color);

        if (d < 0) {
            d += 2 * y + 3;
        }
        else {
            d += 2 * (y - x) + 5;
            x--;
        }

        y++;
    }
}
void CircleIterativePolar(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    double x = R, y = 0;
    double dtheta = 1.0 / R;
    double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
    Draw8Points(hdc, xc, yc, R, 0, color);
    while (x > y)
    {
        double x1 = x * cdtheta - y * sdtheta;
        y = x * sdtheta + y * cdtheta;
        x = x1;
        Draw8Points(hdc, xc, yc, round(x), round(y), color);
    }
}
void CirclePolar(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = R, y = 0;
    double theta = 0, dtheta = 1.0 / R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x > y)
    {
        theta += dtheta;
        x = round(R * cos(theta));
        y = round(R * sin(theta));
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}
void directCircle(HDC hdc, int Xc, int Yc, int R, COLORREF C)
{
    double dtheta = 1.0 / R;
    for (double theta = 0; theta < 6.28; theta += dtheta) {
        double X = Xc + R * cos(theta);
        double Y = Yc + R * sin(theta);
        SetPixel(hdc, round(X), round(Y), C);
    }
}


/*
 * case WM_RBUTTONDOWN:
        if (!isDrawing) {
            x1 = LOWORD(lParam);
            y1 = HIWORD(lParam);
            isDrawing = 1;
        }
        else {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            isDrawing = 0;

            int radius = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
            drawCircleMidpoint(hdc, x1, y1, radius, RGB(255, 0, 0));
        }
        break;
 */


#endif //GRAPHICSPROJECT_ALLCIRCLES_H
