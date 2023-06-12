//
// Created by lenovo on 5/15/2023.
//

#ifndef MAIN_CPP_CLIPPING_H
#define MAIN_CPP_CLIPPING_H

#include <bits/stdc++.h>
#include <Windows.h>
#include "allLines.h"
using namespace std;

using Point = std::pair<double, double>;
constexpr auto eps = 1e-14;

class MyPoint{
public:
    double x, y;
    MyPoint(double x=0,double y=0):x(x),y(y){}
};
typedef vector<MyPoint> PVector;

bool InLeft(MyPoint& p, double xleft)
{
    return p.x >= xleft;
}
bool InRight(MyPoint& p, double xright)
{
    return p.x <= xright;
}
bool InBottom(MyPoint& p, double ybottom)
{
    return p.y >= ybottom;
}
bool InTop(MyPoint& p, double ytop)
{
    return p.y <= ytop;
}
MyPoint VIntersect(MyPoint& v1, MyPoint& v2, double xedge)
{
    MyPoint r;
    r.x = xedge;
    r.y = v1.y + (xedge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return r;
}
MyPoint HIntersect(MyPoint& v1, MyPoint& v2, double yedge)
{
    MyPoint r;
    r.y = yedge;
    r.x = v1.x + (yedge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return r;
}
PVector ClipWithEdge(PVector& P, double edge,bool (*In)(MyPoint&, double),MyPoint(*Intersect)(MyPoint&, MyPoint&, double))
{
    PVector out;
    size_t n =  P.size();
    MyPoint v1 = P[n - 1];
    bool in1 = In(v1, edge);
    for (int i = 0;i < n;i++)
    {
        MyPoint v2 = P[i];
        bool in2 = In(v2, edge);
        if (in1 && in2)
            out.push_back(v2);
        else if (in1)
            out.push_back(Intersect(v1, v2, edge));
        else if (in2)
        {
            out.push_back(Intersect(v1, v2, edge));
            out.push_back(v2);
        }
        v1 = v2;
        in1 = in2;
    }
    return out;
}
PVector PolyClip(PVector P, double xleft, double xright,double ybottom, double ytop)
{

    PVector out;
    out=ClipWithEdge(P, xleft, InLeft, VIntersect);
    out=ClipWithEdge(out, xright, InRight, VIntersect);
    out=ClipWithEdge(out, ybottom, InBottom, HIntersect);
    return ClipWithEdge(out, ytop, InTop, HIntersect);
}



void SimpleDDA(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    SetPixel(hdc,xs,ys,color);
    if(abs(dx)>=abs(dy))
    {
        int x=xs,xinc= dx>0?1:-1;
        double y=ys,yinc=(double)dy/dx*xinc;
        while(x!=xe)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,x,round(y),color);
        }
    }
    else
    {
        int y=ys,yinc= dy>0?1:-1;
        double x=xs,xinc=(double)dx/dy*yinc;
        while(y!=ye)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,round(x),y,color);
        }
    }
}

void drawpolygon(HDC hdc,PVector P,COLORREF c){
    if(P.empty())
        return;
    size_t n =  P.size();
    MyPoint v1 = P[n - 1];
    for (int i = 0;i < n;i++){
        MyPoint v2 = P[i];
        SimpleDDA(hdc,v1.x,v1.y,v2.x,v2.y,c);
        v1 = v2;
    }
}

//point clipping
void PointClipping(HDC hdc,int xc,int yc,int x,int y,int r,COLORREF color)
{
    int dist = sqrt( pow(xc-x,2) + pow(yc-y,2) );

    if(dist < r){
        SetPixel(hdc,x,y,color);
        SetPixel(hdc,x-1,y-1,color);
        SetPixel(hdc,x+1,y+1,color);
        SetPixel(hdc,x+2,y+2,color);
        SetPixel(hdc,x-2,y-2,color);
    }
}

//point clipping
void LineClipping(HDC hdc,int xc,int yc,int x,int y,int r,COLORREF color)
{
    int dist = sqrt( pow(xc-x,2) + pow(yc-y,2) );

    if(dist < r){
        SetPixel(hdc,x,y,color);
    }
}



void CircleLineClipping(HDC hdc,int xs,int ys,int xe,int ye,int xc,int yc,int r,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    LineClipping(hdc,xc,yc,xs,ys,r,color);
    if(abs(dx)>=abs(dy))
    {
        int x=xs,xinc= dx>0?1:-1;
        double y=ys,yinc=(double)dy/dx*xinc;
        while(x!=xe)
        {
            x+=xinc;
            y+=yinc;
            LineClipping(hdc,xc,yc,x,round(y),r,color);
        }
    }
    else
    {
        int y=ys,yinc= dy>0?1:-1;
        double x=xs,xinc=(double)dx/dy*yinc;
        while(y!=ye)
        {
            x+=xinc;
            y+=yinc;
            LineClipping(hdc,xc,yc,round(x),y,r,color);
        }
    }
}


#endif //MAIN_CPP_CLIPPING_H
