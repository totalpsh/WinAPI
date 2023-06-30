#include "Stdafx.h"

/* 06.13

 ���� 1. �簢�� �巡�� �̵�

 - ���콺�� �簢���� �����Ӱ� ������ �� ������ �ȴ�.
 - T / F

 ���� 2. �簢�� ũ�� ����
 - ���콺�� �簢���� ũ�⸦ �����Ӱ� ���� �� �� ������ �ȴ�.
 - ����ȭ�鿡�� �巡�� �غ��鼭 �Ȱ��� ����� OK

 ���� 3. �簢�� 4�� ����

 - �簢���� ������ �� 4��
 - ���콺�� ȭ�鿡 �׷��� 4���� 4������ �ƹ��ų� ������ ������� �����δ�.
 - ���콺�� �����̰� �ִ� �簢���� �ٸ� �簢���� �浹 �Ǹ� �浹�� �簢���� �ڿ������� �з�����.

  ������ �̿��ϰ� �׷����� ���⿡


  ���� ����. ����������

  - �̱��� + @ 4��


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


