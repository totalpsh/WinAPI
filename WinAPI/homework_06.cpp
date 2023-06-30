#include "Stdafx.h"

/* 06.14

 과제1. 마우스로 무작위 도형 출력

 - 마우스로 클릭한 좌표에 무작위 도형을 출력한다.
 - 도형의 크기 + 도형의 모양 + 도형의 종류까지 모두 무작위 처리한다.
 - 도형의 종류 : 사각형 원, 삼각형 및 다각형

 삼각형 + 다각형 -> polygon() + 배열을 이용한다.

 <2일 진행 과제>
 과제2. 도형을 활용한 내 얼굴 그려오기
  - 도형을 활용한다.

 과제3. 공 튕기기

 - 큰 사각형 안에 작은 공이 있다.

 - 작은 공은 큰 사각형 안에서 사용자의 별다른 입력이 없어도 사각형 면에 튕기면서 지속적으로 움직인다.

 - 큰 사각형은 키보드 입력을 바으며 크기를 늘리거나 줄일 수 있다.

 - 크기가 늘어나거나 줄어들면 당연히 안쪽에 있는 공도 영향을 받는다.
 ㄴ 마우스 왼클릭시 : 공 속도 증가
 ㄴ 마우스 우클릭시 : 공 속도 감소

 한줄 조사.

 - GetAsyncKeyState 상태값까지 조사 해올 것

*/

#define HOMEWORK_06
#define HOMEWORK_TYPE
#define RANDOM_FIGUREMAKE 1
#define MYFACEMAKE 2
#define BALLBOUNCE 3

#define HOMEWORK_TYPE 3

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

RECT rc;
RECT _rc1, _rc2;

int centerX;
int centerY;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR _lpszCmdParam,
    int nCmdShow)
{

    _hInstance = hInstance;

    WNDCLASS wndClass;


    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.lpszClassName = WINNAME;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME,
        WINNAME,
        WINSTYLE,
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X,
        WINSIZE_Y,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    MSG message;

    while (GetMessage(&message, 0, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return (int)message.wParam;
}

RECT ground;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;
    static POINT pt = { 0, 0 };
    static bool click = 0;
    static int down_x = 0;
    static int down_y = 0;
    char strPT[128];
    static int rndShape = 0;
    rc = RectMakeCenter(5, 25, 50, 5);
    
    POINT pot[] = { {50,100}, {60, 400}, {120, 600}, {200, 700}, {300, 750}, {400, 750}, {500, 700}, {580, 600}, {640, 400}, {650 ,100} };
    HPEN hNewPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

    static int trix1=0;
    static int trix2=0;
    static int trix3=0;
    static int triy1=0;
    static int triy2=0;
    static int triy3=0;
  
    //if (down_x == (trix1 + trix2 + trix3 / 3) && down_y == (triy1 + triy2 + triy3 / 3))
    //{
    POINT tri[3] = { {trix1, triy1}, {trix2, triy2}, {trix3, triy3} };
    //}

    // 3번
    static int ball_x = 400;
    static int ball_y = 400;
    ground = RectMakeCenter(400, 400, 300, 400);
    // 가로 300 세로 400
    static int speed = 1000;

    switch (iMessage)
    {
    case WM_CREATE:
        
        break;

#if HOMEWORK_TYPE == RANDOM_FIGUREMAKE
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        if (click == true)
        {
            rndShape = 3; // (RND->getInt(4)) + 3;

            switch (rndShape)
            {
            case 3:
 
                Polygon(hdc, tri, 3);

                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            }
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:

        

        break;

    case WM_LBUTTONDOWN:
        click = true;

        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        trix1 = pt.x - RND->getInt(800);
        trix2 = pt.x + RND->getInt(500);
        trix3 = RND->getInt(800 - pt.x);
        triy1 = RND->getInt(800 - pt.y);
        triy2 = pt.y + RND->getInt(500);
        triy3 = pt.y + RND->getInt(500);
        
        InvalidateRect(hWnd, NULL, false);
        break;

#elif HOMEWORK_TYPE == MYFACEMAKE
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        wsprintf(strPT, "X: %d               y: %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));

        Polyline(hdc, pot, 10);

        SelectObject(hdc, hNewPen);
        Ellipse(hdc, 125, 232 );

        EndPaint(hWnd, &ps);

    case WM_MOUSEMOVE:

        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        InvalidateRect(hWnd, NULL, true);

        break;

    case WM_LBUTTONDOWN:



        break;
#elif HOMEWORK_TYPE == BALLBOUNCE
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawRectMake(hdc, ground);
        EllipseMake(hdc, ball_x, ball_y, 15, 15);

        
        SetTimer(hWnd, 1, speed, NULL);

        if (ball_x - 15 <= ground.left)
        {   
            KillTimer(hWnd, 1);
            SetTimer(hWnd, 2, speed, NULL);
        }

        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        speed -= 100;

        break;
        
    case WM_RBUTTONDOWN:
        speed += 100;

        break;

    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            ball_y -= 10;
            ball_x -= 10;
            break;

        case 2:
            ball_y -= 10;
            ball_x += 10;
        }
        
        InvalidateRect(hWnd, NULL, true);
        break;

#endif
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}


