//
// Created by lenovo on 5/16/2023.
//

#ifndef GRAPHICSPROJECT_ALLLINES_H
#define GRAPHICSPROJECT_ALLLINES_H

#include <bits/stdc++.h>
#include<iostream>
using namespace std;

#include<math.h>
#include <tchar.h>
#include <windows.h>


void SwapValue(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}
void ParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    // Calculate dx and dy
    float dx = static_cast<float>(x2 - x1);
    float dy = static_cast<float>(y2 - y1);

    // Determine whether line is steep or not
    bool isSteep = abs(dy) > abs(dx);

    // If the line is vertical, iterate over y instead of x
    if (dx == 0) {
        int startY = min(y1, y2);
        int endY = max(y1, y2);

        for (int y = startY; y <= endY; y++) {
            if (isSteep) {
                SetPixel(hdc, x1, y, c);
            }
            else {
                SetPixel(hdc, x1, y, c);
            }
        }
    }
    else {
        // Calculate slope and y-intercept
        float m = dy / dx;
        float b = y1 - m * x1;

        // Determine the direction of iteration
        int step = x2 > x1 ? 1 : -1;

        // Iterate over parameter t from 0 to 1
        for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
            // Calculate x and y using parameter t
            float x = x1 + t * dx;
            float y = m * x + b;

            // Round x and y to nearest integer
            int ix = static_cast<int>(round(x));
            int iy = static_cast<int>(round(y));

            // Draw pixel at (x, y)
            SetPixel(hdc, ix, iy, c);

            // Iterate over x or y depending on the steepness of the line
            if (isSteep) {
                iy += step;
            }
            else {
                ix += step;
            }
        }
    }
}

void MidpointLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    bool isSteep = abs(y2 - y1) > abs(x2 - x1);
    if (isSteep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int d = 2 * dy - dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);
    int x = x1;
    int y = y1;
    int ystep = (y2 > y1) ? 1 : -1;

    if (isSteep) {
        SetPixel(hdc, y, x, c);
    }
    else {
        SetPixel(hdc, x, y, c);
    }

    while (x < x2) {
        x++;
        if (d < 0) {
            d += incrE;
        }
        else {
            y += ystep;
            d += incrNE;
        }

        if (isSteep) {
            SetPixel(hdc, y, x, c);
        }
        else {
            SetPixel(hdc, x, y, c);
        }
    }
}

void LinaDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dx) >= abs(dy))
    {
        if (x1 > x2)
        {

            swap(x1, x2);
            swap(y1, y2);
        }
        int x = x1;
        double y = y1;
        SetPixel(hdc, x1, y1, c);
        double m = (double)dy / dx;
        while (x < x2)
        {
            x++;
            y += m;
            SetPixel(hdc, x, round(y), c);
        }


    }
    else
    {

        if (y1 > y2)
        {

            swap(x1, x2);
            swap(y1, y2);
        }
        int y = y1;
        double x = x1;
        SetPixel(hdc, x1, y1, c);
        double mi = (double)dx / double(dy);
        while (y < y2)
        {
            y += 1;
            x += mi;
            SetPixel(hdc, round(x), y, c);
        }
    }






}

/*
 * case WM_LBUTTONDOWN:
        if (!firstPointSet) {
            x1 = LOWORD(lParam);
            y1 = HIWORD(lParam);
            firstPointSet = 1;
        }
        else {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            MidpointLine(hdc, x1, y1, x2, y2, RGB(0, 0, 255));
            firstPointSet = 0;

        }
        break;

 */


#endif //GRAPHICSPROJECT_ALLLINES_H
