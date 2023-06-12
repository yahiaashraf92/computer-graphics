#ifndef GRAPHICSPROJECT_FILLINGALGORITHMS_H
#define GRAPHICSPROJECT_FILLINGALGORITHMS_H
// #include <Line.h>

void swap(MyPoint& P1,MyPoint& P2)
{
    MyPoint temp = P1;
    P1= P2;
    P2 = temp;
    return;
}


// ======================================
//       Recursive Flood Filling
// ======================================

void RecursiveFloodFill(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf)
{
    COLORREF C = GetPixel(hdc, x, y);
    if (C == Cb || C == Cf)return;
    SetPixel(hdc, x, y, Cf);
    RecursiveFloodFill(hdc, x + 1, y, Cb, Cf);
    RecursiveFloodFill(hdc, x - 1, y, Cb, Cf);
    RecursiveFloodFill(hdc, x, y + 1, Cb, Cf);
    RecursiveFloodFill(hdc, x, y - 1, Cb, Cf);

}

// ======================================
//       NonRecursive Flood Filling
// ======================================
struct Vertex
{
    double x, y;
    Vertex(int x1 = 0, int y1 = 0)
    {
        x = x1;
        y = y1;
    }
};
        
void NonRecursiveFloodFill(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf)
{
    stack<Vertex> myStack;

    myStack.push(Vertex(x, y));
    while (!myStack.empty())
    {
        Vertex v = myStack.top();
        myStack.pop();
        COLORREF c = GetPixel(hdc, v.x, v.y);
        if (c == Cb || c == Cf)continue;
        SetPixel(hdc, v.x, v.y, Cf);
        myStack.push(Vertex(v.x + 1, v.y));
        myStack.push(Vertex(v.x - 1, v.y));
        myStack.push(Vertex(v.x, v.y + 1));
        myStack.push(Vertex(v.x, v.y - 1));
    }
}



// ======================================
//              Convex Filling
// ======================================
typedef struct {
    int xmin,xmax;

} Table[1000];


void InitTable(Table t)
{
    for(int i =0; i<1000; i++)
    {
        t[i].xmin=INT_MAX;
        t[i].xmax=-INT_MAX;
    }
}

void Edge2Table(MyPoint P1, MyPoint P2, Table table)
{

    
    // Horizontal Case
    if(P1.y==P2.y) return;

    if(P1.y > P2.y)
    {
        swap(P1,P2);

    }
    double x = P1.x;
    int y=P1.y;
    double invslope = (double)(P2.x-P1.x )/(P2.y-P1.y);

    while(y <P2.y)
    {
        if(x < table[y].xmin)
        {
                table[y].xmin =(int)ceil(x);
        } 
        if(x > table[y].xmax) 
        {
            table[y].xmax =(int)floor(x);
        }
        y++;
        x += invslope;
    }
}
void Polygon2Table(MyPoint points[], int size, Table table)
{
    MyPoint v1 = points[size-1];

    for(int i=0; i < size; i++)
    {
        MyPoint v2= points[i];
        Edge2Table(v1, v2, table);
        v1 = v2;
    }
}
void Table2Screen(HDC hdc, Table table, COLORREF color)
{
        for(int i=0; i < 1000; i++)
        if(table[i].xmin < table[i].xmax)
            for(int j=table[i].xmin; j <= table[i].xmax; j++)
                SetPixel(hdc, j, i, color);
}

void ConvexFill(HDC hdc, MyPoint p[], int n, COLORREF color)
{
    Table table;
    InitTable(table);
    MyPoint v1 = p[n - 1];
    Polygon2Table(p,n,table);
    Table2Screen(hdc, table, color);
}

// ======================================
//       General Polygon Filling
// ======================================
const int MAX_EDGES = 1000;

struct MyPolygonPoint
{
    int x, y;
    MyPolygonPoint(int x=0, int y=0) :x(x), y(y)
    {
    }
};
struct EdgeDesc
{
    // Line Description
    double x;
    double inv_slope;
    int y_max;
    EdgeDesc(MyPolygonPoint& P1,MyPolygonPoint& P2)
    {
        if(P1.y>P2.y)
            swap(P1,P2);
        this->x=P1.x;
        this->y_max=P2.y;
        this->inv_slope=(double)(P2.x-P1.x)/(P2.y-P1.y);
    }

    bool operator<(EdgeDesc r)
    {
        return x<r.x;
    }
};
typedef list<EdgeDesc> EdgeList;

void InitEdgeTable(MyPolygonPoint points[],int size,EdgeList table[])
{
    MyPolygonPoint v1=points[size-1];
    for(int i=0;i<size;i++)
    {
        MyPolygonPoint v2=points[i];
        if(v1.y==v2.y)
        {
            v1=v2;
            continue;
        }
        EdgeDesc edge(v1, v2);
        table[(int)v1.y].push_back(edge);
        v1=points[i];
    }

}
void GeneralPolygonFill(HDC hdc, MyPolygonPoint points[],int size,COLORREF c)
{
    int y=0;
    EdgeList table[MAX_EDGES];
    InitEdgeTable(points,size,table);

    while(y<MAX_EDGES && table[y].size()==0)
        y++;

    EdgeList ActiveList=table[y];
    while (!ActiveList.empty())
    {
        // Step 1 : Sort
        ActiveList.sort();

        // Step 2:  Draw a line between the two edges
        EdgeList::iterator it;
        for(it=ActiveList.begin();it!=ActiveList.end();it++)
        {
            int x1=(int)ceil(it->x);
            it++;
            int x2=(int)floor(it->x);
            drawline(hdc, x1, y, x2, y, c);

        }

        // Step 3 : Increase the Y value
        y++;
        
        // Step 4 : Check if y value equals the Y max,
        // and if it is delete it
        it=ActiveList.begin();
        while(it!=ActiveList.end())
            if(y==it->y_max)
                it=ActiveList.erase(it);
            else
                it++;

        // Step 5 : Updating X for Each Node,
        // adding the inverse slope
        for(it=ActiveList.begin();it!=ActiveList.end();it++)
            it->x+=it->inv_slope;

        //Step 6: Append the linked list (table[y])
        // to the Active Linked List
        ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
    }

}

#endif //GRAPHICSPROJECT_FILLINGALGORITHMS_H


