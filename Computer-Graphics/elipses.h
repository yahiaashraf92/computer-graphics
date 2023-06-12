//
// Created by lenovo on 5/13/2023.
//

#ifndef MAIN_CPP_ELIPSES_H
#define MAIN_CPP_ELIPSES_H

#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;

void draw4points(HDC hdc,int xc,int yc,int x,int y,COLORREF c){
    SetPixel(hdc,xc+x,yc+y, RGB(255,1,1));
    SetPixel(hdc,xc-x,yc+y, RGB(255,1,1));
    SetPixel(hdc,xc-x,yc-y, RGB(255,1,1));
    SetPixel(hdc,xc+x,yc-y, RGB(255,1,1));
}

void directelipse(HDC hdc,int xc,int yc,int a,int b,COLORREF c){
    double x = 0,y = b;
    draw4points(hdc,xc,yc,x,y,c);
    for(;x<=a;x+=0.01){
        double temp = 1.0 - (pow(x,2) / pow(a,2));
        y = + b * sqrt(abs(temp));
        draw4points(hdc,xc,yc,x,y,c);
    }
}

void polarelipse(HDC hdc,int xc,int yc,int a,int b,COLORREF c){
    double dtheta = 1.0/max(a,b);
    double x = a,y = 0;
    draw4points(hdc,xc,yc,x,y,c);
    for(double t = 0.0;t<1.5708;t+=dtheta){
        x = a * cos(t);
        y = b * sin(t);
        draw4points(hdc,xc,yc,round(x),round(y),c);
    }
}

void midpointelipse(HDC hdc,int xc,int yc,int a,int b,COLORREF c){
    double x= 0,y = b;
    double d = 1.0/ pow(a,2) - 1.0/ b + 1.0/ (4 * pow(b,2));
    double slope = -1 * (x*b*b) / (y*a*a);
    //cout<<d<<endl;
    draw4points(hdc,xc,yc,x,y,c);
    while(slope > -1){
        if(d < 0) {
            x++;
            d += (2*x + 3) * pow(b,2);
        }
        else{
            x++;
            y--;
            d += ( (2*x + 3) * pow(b,2) ) + ( (2 - 2*y) * pow(a,2) );
        }
        draw4points(hdc,xc,yc,x,y,c);
        slope = -1 * (x*b*b) / (y*a*a);
    }
    d = pow(x + 0.5,2)/(a*a) + pow(y-1,2)/(b*b) - 1;
    while(y){
        if(d < 0) {
            x++;
            y--;
            d += (2*x + 2)/(a*a) + (3 - 2*y)/(b*b);
        }
        else{
            y--;
            d += (3 - 2*y)/(b*b);
        }
        draw4points(hdc,xc,yc,x,y,c);
    }
}

#endif //MAIN_CPP_ELIPSES_H
