//
// Created by lenovo on 5/8/2023.
//

#ifndef MAIN_CPP_CURVEFILLING_H
#define MAIN_CPP_CURVEFILLING_H

#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;

void Hermite(HDC hdc, POINT p[],COLORREF c);
void bezier(HDC hdc, POINT p[],COLORREF c);

double distance(POINT a,POINT b){
    return sqrt(pow((a.x-b.x),2) + pow((a.y-b.y),2));
}

POINT midpoint(POINT a,POINT b){
    POINT temp;
    temp.x = (a.x + b.x)/2;
    temp.y = (a.y + b.y)/2;
    return temp;
}

void hermitefill(HDC hdc, POINT p,int length,COLORREF c){
    int part = length/20;
    int xinc = part,yinc = part;
    POINT cur;
    cur.x = xinc + p.x;
    cur.y = yinc + p.y;
    bool flag = true;
    while(flag){
        POINT four[4];
        four[0] = cur;
        for(int i=1;i<=3;i++){
            if(cur.y + yinc > p.y+length || cur.y + yinc < p.y){
                yinc *= -1;
                if(cur.x < p.x+length){
                    cur.x += xinc;
                }
                else{
                    flag = false;
                }
            }
            else{
                cur.y += yinc;
            }
            four[i] = cur;
        }
        Hermite(hdc,four,c);
    }
}

void bezierfill(HDC hdc, POINT p1,POINT p2,COLORREF c){ // for rectangle
    int xlen = abs(p1.x-p2.x);
    int ylen = abs(p1.y-p2.y);
    int xinc = xlen/10,yinc = ylen/10;
    POINT cur;
    cur.x = min(p1.x,p2.x);
    cur.y = min(p1.y,p2.y);
    cur.x += xinc;
    cur.y += yinc;
    bool flag = true;
    while(flag){
        POINT four[4];
        four[0] = cur;
        for(int i=1;i<=3;i++){
            if(cur.x + xinc > max(p1.x,p2.x) || cur.x + xinc < min(p1.x,p2.x)){
                xinc *= -1;
                if(cur.y + yinc < max(p1.y,p2.y)){
                    cur.y += yinc;
                }
                else
                    flag = false;
            }
            else{
                cur.x += xinc;
            }
            four[i] = cur;
        }
        bezier(hdc,four,c);
    }
}

void square(HDC hdc, POINT p,int length,COLORREF c){
    for(int i = 0,x = p.x,y = p.y;i<=length;i++){
        SetPixel(hdc,x,y+i,c);
        SetPixel(hdc,x+i,y,c);
        SetPixel(hdc,x+length,y+i,c);
        SetPixel(hdc,x+i,y+length,c);
    }
    hermitefill(hdc,p,length,c);
}

void rectangle(HDC hdc, POINT p1,POINT p2,COLORREF c){
    if(p1.y > p2.y){
        swap(p1.x,p2.x);
        swap(p1.y,p2.y);
    }
    for(int i=0;i+p1.y<p2.y;i++){
        SetPixel(hdc,p1.x,p1.y+i,c);
        SetPixel(hdc,p2.x,p2.y-i,c);
    }
    if(p1.x > p2.x){
        swap(p1.x,p2.x);
        swap(p1.y,p2.y);
    }
    for(int i=0;i+p1.x<p2.x;i++){
        SetPixel(hdc,p1.x+i,p1.y,c);
        SetPixel(hdc,p2.x-i,p2.y,c);
    }
    bezierfill(hdc,p1,p2,c);
}

int hermitematrix[4][4] = {
        {2,  1,  -2, 1},
        {-3, -2, 3,  -1},
        {0,  1,  0,  0},
        {1,  0,  0,  0}
};

const double s = 0.75;

double cardinalmatrix[4][4] = {
        {0, 1, 0, 0},
        {-1 * s, 0, s,0},
        {2 * s, s - 3, 3 - 2 * s, -1 * s},
        {-s, 2 - s, s - 2, s}
};


void bezier(HDC hdc, POINT p[],COLORREF c) {
    int px[] = {p[0].x, p[1].x, p[2].x, p[3].x};
    int py[] = {p[0].y, p[1].y, p[2].y, p[3].y};
    cout << endl;
    double dt = 1.0 / (120000 - 1);
    double x = 0, y = 0;
    for (double t = 0; t <= 1; t += dt) {
        x = pow(1-t,3)*px[0] + 3*t*pow(1-t,2)*px[1] + 3*pow(t,2)*(1-t)*px[2] + pow(t,3)*px[3];
        y = pow(1-t,3)*py[0] + 3*t*pow(1-t,2)*py[1] + 3*pow(t,2)*(1-t)*py[2] + pow(t,3)*py[3];
        SetPixel(hdc, round(x), round(y), c);
    }
}


void Hermite(HDC hdc, POINT p[],COLORREF c) {
    int px[] = {p[0].x, 2*(p[1].x - p[0].x), p[3].x, 2*(p[3].x - p[2].x)};
    int py[] = {p[0].y, 2*(p[1].y - p[0].y), p[3].y, 2*(p[3].y - p[2].y)};
    double a[4];
    double b[4];
    for (int i = 0; i < 4; i++) {
        a[i] = 0;
        for (int j = 0; j < 4; j++) {
            a[i] += hermitematrix[i][j] * px[j];
        }
    }
    for (int i = 0; i < 4; i++) {
        b[i] = 0;
        for (int j = 0; j < 4; j++) {
            b[i] += hermitematrix[i][j] * py[j];
        }
    }
    double dt = 1.0 / (120000 - 1);
    double x = 0, y = 0;
    for (double t = 0; t <= 1; t += dt) {
        double dd = 1;
        x = a[0] * t*t*t + a[1]* t*t + a[2] * t + a[3];
        y = b[0] * t*t*t + b[1]* t*t + b[2] * t + b[3];
        SetPixel(hdc, round(x), round(y), c);
    }
}

void cardinalspline(HDC hdc, POINT p[],COLORREF c) {
    int px[] = {p[0].x, p[1].x, p[2].x, p[3].x};
    int py[] = {p[0].y, p[1].y, p[2].y, p[3].y};
    int a[4];
    int b[4];
    for (int i = 0; i < 4; i++) {
        a[i] = 0;
        for (int j = 0; j < 4; j++) {
            a[i] += cardinalmatrix[i][j] * px[j];
        }
    }
    for (int i = 0; i < 4; i++) {
        b[i] = 0;
        for (int j = 0; j < 4; j++) {
            b[i] += cardinalmatrix[i][j] * py[j];
        }
    }
    double dt = 1.0 / (120000 - 1);
    double x = 0, y = 0;
    for (double t = 0; t <= 1; t += dt) {
        double dd = 1;
        x = a[3] * t*t*t + a[2]* t*t + a[1] * t + a[0];
        y = b[3] * t*t*t + b[2]* t*t + b[1] * t + b[0];
        SetPixel(hdc, round(x), round(y),c);
    }
}



#endif //MAIN_CPP_CURVEFILLING_H
