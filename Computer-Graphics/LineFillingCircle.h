//
// Created by lenovo on 5/16/2023.
//

#ifndef GRAPHICSPROJECT_LINEFILLINGCIRCLE_H
#define GRAPHICSPROJECT_LINEFILLINGCIRCLE_H

#include <bits/stdc++.h>
#include<iostream>
using namespace std;

#include<math.h>
#include <tchar.h>
#include <windows.h>
#include "allLines.h"


void drawCircle(HDC hdc, int Xc, int Yc, int R, COLORREF C)
{
    double theta;
    float userInput;
    double dtheta = 1.0 / R;
    for (double theta = 0; theta < 6.28; theta += dtheta) {
        double X = Xc + R * cos(theta);
        double Y = Yc + R * sin(theta);
        SetPixel(hdc, round(X), round(Y), C);



    }
    cout<<"Enter the Quarter You want to Fill it : ";
    cin>>userInput;
    if(userInput==1)
    {
        theta=3.14;
        userInput=4.7;


    }

    else if(userInput==2)
    {
        theta=4.7;
        userInput=6.28;


    }
    else if(userInput==3)
    {
        theta=0;
        userInput=1.57;


    }
    else if(userInput==4)
    {
        theta=1.57;
        userInput=3.14;


    }

    for ( theta; theta < userInput; theta += dtheta) {
        double X = Xc + R * cos(theta);
        double Y = Yc + R * sin(theta);
        SetPixel(hdc, round(X), round(Y), C);
        LinaDDA(hdc, Xc, Yc, round(X), round(Y), C);

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



            drawCircle(hdc, x1, y1, radius, RGB(255, 0, 0));
        }
        break;

 */



#endif //GRAPHICSPROJECT_LINEFILLINGCIRCLE_H
