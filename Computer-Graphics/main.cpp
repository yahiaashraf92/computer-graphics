#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
#include <fstream>
#include "Circle.h"
#include "CurveFilling.h"
#include "Clipping.h"
#include "elipses.h"
#include "allLines.h"
#include "allCircles.h"
#include "LineFillingCircle.h"
#include "FillingAlgorithms.h"
#include "transformation.h"


using namespace std;

HMENU hMenu;

void add_menu(HWND); //prototype


//shape color menu
int shape_color() {
    int c, color;
    cout << "choose the color of the shape" << endl;
    cout << "0 --> black" << endl;
    cout << "1 --> white" << endl;
    cout << "2 --> blue" << endl;
    cout << "3 --> red" << endl;
    cout << "4 --> yellow" << endl;
    cout << "5 --> green" << endl;
    cout << "6 --> purple" << endl;
    cout << "7 --> orange" << endl;
    cin >> c;
    switch (c) {
        case 0:
            color = RGB(0, 0, 0);
            break;
        case 1:
            color = RGB(255, 255, 255);
            break;
        case 2:
            color = RGB(18, 82, 255);
            break;
        case 3:
            color = RGB(255, 0, 0);
            break;
        case 4:
            color = RGB(255, 255, 0);
            break;
        case 5:
            color = RGB(40, 128, 34);
            break;
        case 6:
            color = RGB(160, 32, 240);
            break;
        case 7:
            color = RGB(255, 165, 0);
            break;
        default:
            color = RGB(0, 0, 0);
            break;
    }
    return color;
}


POINT p[4];
int cnt = 0;
COLORREF c = shape_color();


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    //    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    ////// change the background color to WHITE
    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Code::Blocks Template Windows App"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            544,                 /* The programs width */
            375,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void save(HDC hdc) {
    ofstream out("file.txt");
    for (int i = 0; i < 529; ++i) {
        for (int j = 0; j < 336; ++j) {
            COLORREF col = GetPixel(hdc, i, j);
            if (col != 0x00FFFFFF) {
                out << i << ' ' << j << ' ' << col << ' ';
            }
        }

    }
    cout << "DONE" << endl;
    out.close();

}

void clear(HDC hdc) {
    for (int i = 0; i < 529; ++i) {
        for (int j = 0; j < 336; ++j) {
            COLORREF col = GetPixel(hdc, i, j);
            if (col != 0x00FFFFFF) {
                SetPixel(hdc, i, j, 0x00FFFFFF);
            }
        }
    }
    cout << "DONE" << endl;
}


void load(HDC hdc) {
    ifstream input("file.txt");
    int x, y;
    COLORREF col;
    while (input >> x) {
        input >> y;
        input >> col;
        SetPixel(hdc, x, y, col);
    }
    input.close();
}

MyPoint* GetPoints(MyPoint points[], int size, LPARAM lParam)
{
    for(int i =0; i < size; i++)
    {
        points[i].x=LOWORD(lParam);
        points[i].y=HIWORD(lParam);
        cout << "Point " << i <<endl;
    }
    return points;
}

PVector poly;
MyPoint mp;

int x1;
int y11;
int xs, ys, xe, ye;
int x2;
int y2;
int x3;
int y3;
int x4;
int y4;
int shape_no = 1;
int FillingSize;
MyPoint ConvexPoints[5];
MyPolygonPoint NonConvexPoints[7];
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE://create menu on top of screen
            add_menu(hwnd);
            break;
        case WM_COMMAND:// function of every button in menu
        switch (wParam) {
            case 1://shapes button
            break;
            case 2://clear button
            clear(hdc);
            break;
            case 3:// save button
            save(hdc);
            break;
            case 4:// load button
            load(hdc);
            break;
            case 5://Exit button
            exit(0);
            break;
            default:
                shape_no = (int)wParam;
                break;
                // shape_no = 6;
                // break;
                // case 7:
                //     shape_no = 7;
                //     break;
                //     case 8:
                //         shape_no = 8;
                //         break;
                //         case 9:
                //             shape_no = 9;
                //             break;
                //             case 10:
                //                 shape_no = 10;
                //                 break;
                //                 case 11:
                //                     shape_no = 11;
                //                     break;
                //                     case 12:
                //                         shape_no = 12;
                //                         break;
                //                         case 13:
                //                             shape_no = 13;
                //                             break;
                //                             case 14:
                //                                 shape_no = 14;
                //                                 break;
                //                                 case 15:
                //                                     shape_no = 15;
                //                                     break;
                //                                     case 16:
                //                                         shape_no = 16;
                //                                         break;
                //                                         case 17:
                //                                             shape_no = 17;
                //                                             break;case 18:
                //                                                 shape_no = 18;
                //                                                 break;
                //                                                 case 19:
                //                                                     shape_no = 19;
                //                                                     break;
                //                                                     case 20:
                //                                                         shape_no = 20;
                //                                                         break;

            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:
            switch (shape_no) {
                //draw line with midpoint
                case 6:
                    if (cnt == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        cnt++;
                    } else if (cnt == 1) {
                        x2 = LOWORD(lParam);
                        y2 = HIWORD(lParam);
                        MidpointLine(hdc, x1, y11, x2, y2, c);
                        cnt = 0;
                    }
                    break;
                case 7:
                    if (cnt == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        cnt++;
                    } else if (cnt == 1) {
                        x2 = LOWORD(lParam);
                        y2 = HIWORD(lParam);
                        cnt = 0;

                        int radius = sqrt(pow(x2 - x1, 2) + pow(y2 - y11, 2));
                        drawCircleMidpoint(hdc, x1, y11, radius, c);
                    }
                    break;
                case 8:
                    if (cnt == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        cnt++;
                    } else if (cnt == 1) {
                        x2 = LOWORD(lParam);
                        y2 = HIWORD(lParam);
                        cnt = 0;

                        int radius = sqrt(pow(x2 - x1, 2) + pow(y2 - y11, 2));


                        drawCircle(hdc, x1, y11, radius, c);
                    }
                    break;
                case 9:
                    if (cnt % 2 == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        cnt++;
                    } else if (cnt % 2 == 1) {
                        quadX = LOWORD(lParam);
                        quadY = HIWORD(lParam);
                        int r = sqrt((y11 - quadY) * (y11 - quadY) + (x1 - quadX) * (x1 - quadX));

                        drawCircleWithCircles(hdc, x1, y11, r, c);
                        cnt = 0;
                    }
                    break;
                case 10: // hermit square fill
                    xs = LOWORD(lParam);
                    ys = HIWORD(lParam);
                    POINT b;
                    b.x = xs;
                    b.y = ys;
                    square(hdc, b, 100, c);
                    break;
                case 11:
                    if (cnt % 2 == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        cnt++;
                    } else if (cnt % 2 == 1) {
                        x2 = LOWORD(lParam);
                        y2 = HIWORD(lParam);
                        POINT a;
                        a.x = x1;
                        a.y = y11;
                        POINT b;
                        b.x = x2;
                        b.y = y2;
                        rectangle(hdc, b, a, c);
                        cnt = 0;
                    }
                    break;
                case 12:
                    if (cnt == 3) {
                        p[cnt].x = LOWORD(lParam);
                        p[cnt].y = HIWORD(lParam);
                        cardinalspline(hdc, p, c);
                        cnt = 0;

                    } else {
                        p[cnt].x = LOWORD(lParam);
                        p[cnt].y = HIWORD(lParam);
                        cnt++;
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                    //draw hermite curve
                case 13:
                    if (cnt == 3) {
                        p[cnt].x = LOWORD(lParam);
                        p[cnt].y = HIWORD(lParam);
                        hermite(hdc, p, c);
                        cnt = 0;

                    } else {
                        p[cnt].x = LOWORD(lParam);
                        p[cnt].y = HIWORD(lParam);
                        cnt++;
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                case 14:
                    xs = LOWORD(lParam);
                    ys = HIWORD(lParam);
                    midpointelipse(hdc, xs, ys, 100, 70, c);
                    //polarelipse(hdc, xs + 200, ys, 100, 70, c);
                    //directelipse(hdc, xs - 200, ys, 100, 70, c);
                    break;
                case 15:
                    if (cnt == 3) {
                        mp.x = LOWORD(lParam);
                        mp.y = HIWORD(lParam);
                        poly.push_back(mp);
                        drawpolygon(hdc, PolyClip(poly, 100, 400, 100, 500), c);
                        poly.clear();
                        cnt = 0;
                    } else {
                        mp.x = LOWORD(lParam);
                        mp.y = HIWORD(lParam);
                        poly.push_back(mp);
                        cnt++;
                    }
                    break;
                case 16:
                    if (cnt % 2 == 1) {
                        mp.x = LOWORD(lParam);
                        mp.y = HIWORD(lParam);
                        poly.push_back(mp);
                        drawpolygon(hdc, PolyClip(poly, 100, 400, 100, 400), c);
                        poly.clear();
                        cnt = 0;
                    } else {
                        mp.x = LOWORD(lParam);
                        mp.y = HIWORD(lParam);
                        poly.push_back(mp);
                        cnt++;
                    }
                    break;
                case 17:
                    x1 = LOWORD(lParam);
                    y11 = HIWORD(lParam);
                    RecursiveFloodFill(hdc, x1, y11, c, c);
                case 18:
                    x1 = LOWORD(lParam);
                    y11 = HIWORD(lParam);
                    NonRecursiveFloodFill(hdc, x1, y11, c, c);
                    break;
                case 19:
                    if (cnt == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        Ellipse(hdc, x1 - 100, y11 - 100, x1 + 100, y11 + 100);
                        cnt++;
                    } else {
                        x2 = LOWORD(lParam);
                        y2 = HIWORD(lParam);
                        PointClipping(hdc, x1, y11, x2, y2, 100, c);
                    }

                    break;
                case 20:
                    if (cnt == 0) {
                        x1 = LOWORD(lParam);
                        y11 = HIWORD(lParam);
                        Ellipse(hdc, x1 - 100, y11 - 100, x1 + 100, y11 + 100);
                        cnt++;
                    } else if (cnt % 2 == 1) {
                        xs = LOWORD(lParam);
                        ys = HIWORD(lParam);
                        cnt++;
                    } else if (cnt % 2 == 0) {
                        xe = LOWORD(lParam);
                        ye = HIWORD(lParam);
                        CircleLineClipping(hdc, xs, ys, xe, ye, x1, y11, 100, c);
                        cnt++;
                    }
                    cout << cnt << endl;

                    break;
                case 25:
                    int x, y;
                    cout << "ENTER X and Y values: ";
                    cin >> x >> y;
                    MidpointLine(hdc, x1, y11, x2, y2, 0x00FFFFFF);
                    traslateLine(hdc,x1, y11, x2, y2, c, x,y);
                    break;
                default:
                    if(shape_no> 30 & shape_no < 40)
                    {
                        FillingSize = (shape_no-30)+2;

                        ConvexPoints[cnt].x = LOWORD(lParam);
                        ConvexPoints[cnt].y = HIWORD(lParam);
                        if(cnt == FillingSize-1)
                        {
                            ConvexFill(hdc, ConvexPoints, FillingSize, c);
                            cnt = 0;
                        }else
                        {
                            cnt++;
                        }
                    }
                    if(shape_no > 40)
                    {
                        FillingSize = (shape_no-40)+4;

                        NonConvexPoints[cnt].x = LOWORD(lParam);
                        NonConvexPoints[cnt].y = HIWORD(lParam);
                        if(cnt == FillingSize-1)
                        {
                            GeneralPolygonFill(hdc, NonConvexPoints, FillingSize, c);
                            cnt = 0;
                        }else
                        {
                            cnt++;
                        }
                    }
                    break;




            }

            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// the built in menu in window
void add_menu(HWND hWnd) {
    hMenu = CreateMenu();
    HMENU hshapemenu = CreateMenu();
    HMENU hConvexSubMenu = CreatePopupMenu();
    HMENU hNonConvexSubMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hshapemenu, "Shapes");
    AppendMenu(hMenu, MF_STRING, 2, "Clear");
    AppendMenu(hMenu, MF_STRING, 3, "save");
    AppendMenu(hMenu, MF_STRING, 4, "load");
    AppendMenu(hMenu, MF_STRING, 5, "Exit");
    AppendMenu(hshapemenu, MF_STRING, 6, "line");// lesa
    AppendMenu(hshapemenu, MF_STRING, 7, "circle");// lesa
    AppendMenu(hshapemenu, MF_STRING, 8, "Circle with quad filled with lines");//
    AppendMenu(hshapemenu, MF_STRING, 9, "Circle with quad filled with circles");//
    AppendMenu(hshapemenu, MF_STRING, 10, "Hermite square fill");//
    AppendMenu(hshapemenu, MF_STRING, 11, "Bezier rectabgle fill");
    AppendMenu(hshapemenu, MF_STRING, 12, "cardinal spline");
    AppendMenu(hshapemenu, MF_STRING, 13, "hermit curve");
    AppendMenu(hshapemenu, MF_STRING, 14, "elipses");
    AppendMenu(hshapemenu, MF_STRING, 15, "polygon clipping");
    AppendMenu(hshapemenu, MF_STRING, 16, "line clipping");
    AppendMenu(hshapemenu, MF_STRING, 17, "Recursive Flood Fill");
    AppendMenu(hshapemenu, MF_STRING, 18, "NonRecursive Flood Fill");
    AppendMenu(hshapemenu, MF_STRING, 19, "circle point clipping");
    AppendMenu(hshapemenu, MF_STRING, 20, "circle line clipping");
    AppendMenu(hshapemenu, MF_STRING, 25, "translate");
    AppendMenu(hshapemenu, MF_STRING, 26, "scale");
    AppendMenu(hshapemenu, MF_STRING | MF_POPUP, (UINT_PTR)hConvexSubMenu, "Convex Filling");
    AppendMenu(hConvexSubMenu, MF_STRING , 31, "3 Points");
    AppendMenu(hConvexSubMenu, MF_STRING , 32, "4 Points");
    AppendMenu(hConvexSubMenu, MF_STRING , 33, "5 Points");
    AppendMenu(hshapemenu, MF_STRING | MF_POPUP, (UINT_PTR)hNonConvexSubMenu, "General Polygon Filling");
    AppendMenu(hNonConvexSubMenu, MF_STRING , 41, "5 Points");
    AppendMenu(hNonConvexSubMenu, MF_STRING , 42, "6 Points");
    AppendMenu(hNonConvexSubMenu, MF_STRING , 43, "7 Points");



    SetMenu(hWnd, hMenu);
}
