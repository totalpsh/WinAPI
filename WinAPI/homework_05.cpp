#include "Stdafx.h"

/* 06.13

 과제 1. 사각형 드래그 이동

 - 마우스로 사각형을 자유롭게 움직일 수 있으면 된다.
 - T / F

 과제 2. 사각형 크기 조절
 - 마우스로 사각형의 크기를 자유롭게 조절 할 수 있으면 된다.
 - 바탕화면에서 드래그 해보면서 똑같이 만들면 OK

 과제 3. 사각형 4단 열기

 - 사각형의 갯수는 총 4개
 - 마우스로 화면에 그려진 4개의 4각형중 아무거나 선택해 자유룝게 움직인다.
 - 마우스로 움직이고 있는 사각형이 다른 사각형과 충돌 되면 충돌된 사각형은 자연스럽게 밀려난다.

  관성을 이용하고 그럴싸해 보기에


  한줄 조사. 디자인패턴

  - 싱글톤 + @ 4개


*/

#define HOMEWORK_05
#define HOMEWORK_TYPE
#define DRAGMOVE 1
#define SIZECONTROL 2
#define CRASHMOVE 3

#define HOMEWORK_TYPE 2

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

RECT rc;
RECT _rc1, _rc2;

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




LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc; 
    PAINTSTRUCT ps;
    static POINT pt = { 0, 0 };
    char strPT[128];
  
    static int clickD_x = 0;
    static int clickD_y = 0;
    static int rc_x = 400;
    static int rc_y = 400;
    static int rc_w = 100;
    static int rc_h = 100;
    static bool down = false;

    

    switch (iMessage)
    {
    case WM_CREATE:
        rc = RectMakeCenter(rc_x, rc_y, rc_w, rc_h);
        break;

#if HOMEWORK_TYPE == DRAGMOVE
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawRectMake(hdc, rc);

        wsprintf(strPT, "X: %d     y: %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        EndPaint(hWnd, &ps);

        

        break;

    case WM_MOUSEMOVE:
       
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam); 
        
        if (down == true)
        {
            rc.left = pt.x - clickD_x;
            rc.top = pt.y - clickD_y;
            rc.right = pt.x - clickD_x + 100;
            rc.bottom = pt.y - clickD_y + 100;

            if (rc.left <= 0)
            {
                down = false;
                rc.left = 0;
            }

        }
        
        InvalidateRect(hWnd, NULL, TRUE);
        
        break;

    case WM_LBUTTONDOWN:
     
        if (pt.x <= rc.right && pt.x >= rc.left && pt.y <= rc.bottom && pt.y >= rc.top)
        {
                down = true;
                clickD_x = pt.x - rc.left;
                clickD_y = pt.y - rc.top;
        }

        
        break;

    case WM_LBUTTONUP:
        down = false;

        break;
#elif HOMEWORK_TYPE == SIZECONTROL
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawRectMake(hdc, rc);
        wsprintf(strPT, "X: %d     y: %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:

        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (down == true)
        {
            if (pt.y < rc.bottom)
            {
                rc.top = pt.y;
            }
        }

        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_LBUTTONDOWN:

        if (pt.x <= rc.right && pt.x >= rc.left && pt.y <= rc.bottom && pt.y >= rc.top)
        {
            down = true;

            clickD_x = pt.x;
            clickD_y = pt.y;            
        }
        break;

    case WM_LBUTTONUP:
    
        down == false;

        break;

#elif HOMEWORK_TYPE == CRASHMOVE
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


