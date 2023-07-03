
// WinMain

#pragma region WinAPI
/*
 �� API 

 - �ü���� ���� ���α׷� ������ ���� �����ϴ� �Լ��� ����

 - "��ɾ��� ����"���� ���ø����̼� ���α׷����� ���۷����� �ý����� �⺻���� ����� ����� �ʿ䰡 ���� ��� API���� ��ɾ� ȣ���� ����ȴ�.

 Ex)
 �ϵ���� ------------ �ü��(Windows) -------------- ���� ���α׷�\


 ( API �Լ� )


 �� ����

 - �ü���� ������ ���� ����� ������ ����ϱ⿡ Ȯ�强 �� ������, �׸��� ���������鿡�� ���� �����ϴ�. (�������� != ������)
 
 - �ü���� ���ӵǱ� ������ ���� Ȯ�强�� ���� ����. (����)

 �� ����

 - �÷����� ����ȭ
  ��C��� ����

  �� API ����
   - ũ�� �������� �޼��� ����, Window Produre�� ������ -> �ٵ� ����� ������ ������ �ݵ�� ��� �� ��-> ���� �������� �����غ���.




*/

#pragma endregion
#include "Stdafx.h"
#include "MainGame.h";
#include "MainGame0630.h"
#include "MainGame0703.h"

// ��������

/*
 �� �ν��Ͻ�
 - ������ OS�� ���� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��
 - �⺻������ ���� ���α׷��̸� ���� �ν��Ͻ� ���� ���´�.
 - Ŭ������ �޸𸮿� ������ ������ ��ü
 �� ����ǰ� �ִ� ������ ���α׷��� '�ν��Ͻ�'��� �� �� �ִ�.

*/
HINSTANCE _hInstance;
// ������ �ڵ�(������ â)
HWND _hWnd;
// ������ Ÿ��Ʋ
//LPTSTR _lpszClass = TEXT("Windows API"); // ���������� ����.
//TCHAR* pszStirng = _T("Windows API");

POINT _ptMouse = { 0, 0 };

/*
 �� TCHAR     ------>   ȣȯ��(Ȯ�强)�� ����.

 - TCHAR ���� ������Ʈ�� ���ڼ� ������ ���� �ڵ������� char �Ǵ� wchar_t�� Type_Casting �Ǵ� �߰� ��ũ�� �ڷ���

 - ��Ƽ ����Ʈ�� �����ڵ� ȯ�濡�� ������ ���� �۾� ���� ���α׷��� �����ϱ� ���ؼ��� TCHAR������ ���ڿ��� ǥ���� ���� ��õ -> �߿�!

 - �Ϲ������� ������ ���� ���α׷����� ���ڿ� ����� ���� ���ؼ��� �߰� ������ ���� char* �Ǵ� wcahr_t*�� ��ȯ �� �ִ� _t��ũ�θ� �̿��ؾ� �Ѵ�.


 
 
 
 
 */

/*
LPSTR           ->          Long POINTER        =       char*
LPCSTR          ->          Constant            =       const char*
LPCTSTR         ->          t_string            =       const tchar*




*/

// �ݹ� �Լ�
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// �� �ȸ´� ������ ����� �����ش�.
void setWindowSize(int x, int y, int width, int height);

/*

 hInstance: ���α׷� �ν��Ͻ� �ڵ�
 hPrevInstance: ������ ����� �ν��Ͻ� �ڵ�
 lpszCmdParam: ��������� �Էµ� ���α׷� �μ�
 nCmdShow: ���α׷��� ���۵� ����(�ּ�ȭ / ũ�� ���)

*/

// ���ڼ�
/*
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     TCHAR* lpszCmdParam,
                     int nCmdShow)
 */


 // �簢���� �߽��� �����
 //RECT RectMakeCenter(int x, int y, int width, int height)
 //{
 //    RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
 //    return rc;
 //}

RECT rc;
RECT _rc1, _rc2;

int centerX;
int centerY;

MainGame0703* _mg;


int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR _lpszCmdParam,
    int nCmdShow)


{
    _mg = new MainGame0703;


    // �ν��Ͻ��� ���������� ��´�.
    _hInstance = hInstance;

    /*
     - WinMain�� ����

     1. ������ â�� ���� �� ȭ�鿡 ����
        �� ȭ�鿡 â�� ���� ���ؼ� 4������ ��� ó���ؾ� �Ѵ�.


     2. �޼��� ����



    */


    // 1 - 1. ������ â ����ü ���� �� �ʱ�ȭ
    //WDNCLASS: �� ����ü�� �������� �ü�� ���� ������ ������ ����ϱ� ���ؼ� Ŀ������ �����츦 �ĺ��� �� �ִ� ���� ���� ����ϴ� ���� ����
    WNDCLASS wndClass;


    wndClass.cbClsExtra = 0;                                            // Ŭ���� ���� �޸� -> ���ӿ����� �����Ҵ����� ���� �޸� �Ҵ�� ������ ���� �ϹǷ� ���� �ʿ����� �ʴ�.
    wndClass.cbWndExtra = 0;                                            // ������ ���� �޸� ->
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);       // ��׶��� -> 
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                     //���콺 Ŀ��
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   //������
    wndClass.hInstance = hInstance;                                     // �����츦 �ҿ��� ���α׷��� �ĺ��� ����
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                            //������ ���ν���
    wndClass.lpszClassName = WINNAME;                                //Ŭ���� �̸�(�ĺ��� ����)
    wndClass.lpszMenuName = NULL;
    // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                           // ������ ��Ÿ��(�ٽ� �׸��� ����)


    // ����̽��� ���� ȯ���̱� ������ ���α׷��� ���۰� ���ÿ� ������ ���ߵǰ� ���α׷��� ���ᰡ �Ǳ� �������� �����Ǿ�� �ϴ� ��ɵ��̶� Ŭ������ �Լ��� ������� �������� �ʰ�
    // ���� �� ���� ��ġ�ؼ� ����� ���� ���̴�.
    // ���ε� �Լ��� �ϳ��ϱ� ����� ���ÿ� ���̴µ� �ٸ� Ŭ������ �Լ���� ���� ���ÿ� ���̸� ���Ḧ �ϴ� ���������� ������ Ư���� ������� ���ᰡ �ǹǷ� ���� ������� ���� ���� �ƴϴ�.


    // 1- 2. ������ Ŭ���� ���
    RegisterClass(&wndClass);


#ifdef FULLSCREEN 
    // ����̽� ��� ����ü (ȭ�� ���÷��� ���� ����ü)
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(DEVMODE));

    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32; //32��Ʈ Ʈ���÷�
    dm.dmPanningWidth = 1580;      //����
    dm.dmPelsHeight = 1020;         //����
    dm.dmDisplayFrequency = 60; // �ֻ���

    // �ʵ� ����
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    // ����Ǹ� ���÷��� ������ ������� ������.
    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }

    _hWnd = CreateWindow
    (
        WINNAME,             // ������ Ŭ���� �ĺ���
        WINNAME,             // ������ Ÿ��Ʋ �� �̸�
        WINSTYLE,    // ������ ��Ÿ��
        WINSTART_X,                    // ������ ȭ�� X��ǥ
        WINSTART_Y,                    // ������ ȭ�� Y��ǥ
        WINSIZE_X,                    // ������ ȭ�� ���� ũ��
        WINSIZE_Y,                    // ������ ȭ�� ���� ũ��
        NULL,                   // �θ� ������ -> GetDesktopWindow
        (HMENU)NULL,            // �޴� �ڵ�
        hInstance,              // �ν��Ͻ� ����
        NULL                    //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� �ʴٸ� NULL�� ��ƶ�
                                //�� �ʿ信 ���ؼ� ����ϱ⵵ ������ ������ NULL�� �����̴�.
    );

#else 
    // 1 - 3. ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindow
    (
        WINNAME,             // ������ Ŭ���� �ĺ���
        WINNAME,             // ������ Ÿ��Ʋ �� �̸�
        WINSTYLE,    // ������ ��Ÿ��
        WINSTART_X,                    // ������ ȭ�� X��ǥ
        WINSTART_Y,                    // ������ ȭ�� Y��ǥ
        WINSIZE_X,                    // ������ ȭ�� ���� ũ��
        WINSIZE_Y,                    // ������ ȭ�� ���� ũ��
        NULL,                   // �θ� ������ -> GetDesktopWindow
        (HMENU)NULL,            // �޴� �ڵ�
        hInstance,              // �ν��Ͻ� ����
        NULL                    //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� �ʴٸ� NULL�� ��ƶ�
                                //�� �ʿ信 ���ؼ� ����ϱ⵵ ������ ������ NULL�� �����̴�.
    );
#endif
    // Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ֱ� ����
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    // 1-4. ȭ�鿡 ������â �����ֱ�
    ShowWindow(_hWnd, nCmdShow);

    // ���� ������Ʈ (�ܱ�/����) ������Ʈ ó�� �ؾ� �Ѵ�.
    // UpdateWindow(_hWnd);

    // 2. �޼��� ����
    // MSG: �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
    
   if (FAILED(_mg->init()))
    {
        return 0;
    }
    
    
    MSG message;
    //ZeroMemory(&message, sizeof(message)); // ���� ������Ʈ������ �� ������ ������ �Ѵ�.

    /*
    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) break;
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
    */

    /*
    �ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�

    �� �޼��� ���� ����
    
    1. GetMessage (�ٸ� �÷����� ��ȿ�ϴ�.)
    �� �޼����� ������ �� ���� ������ �����ִ� �Լ�(���)
    �� GetMessage�� �޼��� ť�κ��� �ϳ��� �޼����� �������� ������ �����Ѵ�.
    �� ��, �޼��� ť�� ��� ���� ��� �޼�����(�߻��� �޽��� x) ���Ë����� ����Ѵ�.

    2. PeekMessage (������ peekmessage�� ����Ѵ�.)
    �� �޼����� ������ ��ȯ �Ǵ� �Լ�
    
    
    */

    // �����Ϸ��� ������ ���۹���� ���´�.
    while (GetMessage(&message, 0, 0, 0))
    {
            TranslateMessage(&message);
            DispatchMessage(&message); // ���ν����� ��ȯ ���� �޾� ���ν����� ���Ϸ� �����Ѵ�.
    }

    /*
    TranslateMessage:
    �� Ű������ �Է� �޼��� ó���� ���
    �� �Էµ� Ű�� ����Ű ���� Ȯ�� �� �빮�� Ȥ�� �ҹ���, �ѱ� / ���������� ���� WM_CHAR�޼����� �߻� ��Ų��.
    �� ���� ��� Ű���尡 �ȵȴ�. -> ���콺�� ���� ó������ ���⼭�� �ٲ� �� ����.

    DispatchMessage:
    �� ������ ���ν������� ���޵� �޼����� ���� ������� ������ �ش�.


    */
    _mg->release();
    UnregisterClass(WINNAME, hInstance);

    


    return (int)message.wParam;
}

/*
 hWnd: ��� �����쿡�� �߻��� �޼������� ����
 iMessage: �޼��� ���� ��ȣ
 wParam: usigned int -> ������ ó������ ���� ���콺 ��ư�� ����, Ű���� ���� Ű�� ���¸� ����
 lParam: usigned long -> ���콺 Ŭ�� ��ǥ�� ����
*/

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{ 
#pragma region ����
    //HDC hdc; // �ڵ� DC
    //                                                    // �� ���� ������ GDI�� ���÷���,  HDC�� �ƴ� ���� API�� �ƴϴ�.
    //PAINTSTRUCT ps; // ����Ʈ ����ü   

    //static POINT pt = { 0,0 };
    //char strPT[128];

    ////char str[] = "�׷�";

    ///*
    //char[]; ���õ����͸� ������ ������ ������ �����ϴ�.
    //char*;  �۷ι� ����ƽ �����͸� ������ ������ ������ �Ұ��ϴ�.
    //*/

    ////RECT rc = { 100, 100, 200, 200 }; // ����ȭ

    ///*
    //�� RECT : �簢���� ��ǥ�� �����ϱ� ���� ����ü

    //�⺻�ڷ���
    //l,P 
    //rect
    //
    //*/

    //// �ַ� ����ٰ� �ڵ��� �ϰ� �ɰ�
    ///*
    //�� Window Procedure
    //�� �޼����� �ü���� ���� -> ������ �ü���� ȣ��ǰ� ���ش�.
    //�� WinMain() �� �ƴ� �ü���� ���� ȣ���� �Ǵ� �ݹ� �Լ�
    //�� �����츦 ������ �� �ݵ�� ������ ����� �Ѵ�.

    //- ����ؾ� �Ұ� ������ ���ν��� ���ο����� �����쿡�� �߻��� ��� �޼����� ó���ϴ� ���� �ƴ϶� Ư���޼��� ���� ó���ϰ� 
    //������ �޼����� DefWindowProc �Լ��� ó���ϵ��� ������ �����ϴ°� �Ϲ����̴�.

    //�� �� ������ �ݵ�� ����� ��    
    //*/

    //switch (iMessage)
    //{
    //case WM_CREATE: // ������

    //    //rc = RectMakeCenter(400, 400, 100, 100);
    //    _rc1 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
    //    _rc2 = RectMakeCenter(WINSIZE_X / 2 + 200, 400, 100, 100);

    //    centerX = WINSIZE_X / 2;
    //    centerY = WINSIZE_Y / 2;

    //    break;

    //    /*
    //     �� WM_PAINT

    //     - �����츦 �ٽ� �׷��� �Ҷ� ����ϴ� �޼���
    //     
    //     1. �����찡 ó�� ��������� ��
    //     2. ������ ũ�⸦ �����ϰ� ������
    //     3. �����찡 �ٸ� �����쿡 �������ٰ� �ٽ� ���϶�
    //     4. Ư�� �Լ��� ȣ���� �ɶ� -> InvalidateRect, Invalidate, UpdataAllViews ���
    //        �� �⺻������ ������ �Լ��� ������ PAINT�� ���÷��� �Ѵ�.
    //    */

    //case WM_PAINT:      // ��¿� ���� ��� �͵��� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ��� ��)

    //    hdc = BeginPaint(hWnd, &ps);

    //    wsprintf(strPT, "X: %d     y: %d" ,pt.x, pt.y);
    //    TextOut(hdc, 10, 10, strPT, strlen(strPT));

    //    //Rectangle(hdc, _rc1.left, _rc1.top, _rc1.right, _rc1.bottom);
    //    Rectangle(hdc, centerX, centerY, 10, 100);
    //   // DrawRectMake(hdc, _rc2);

    //    //EllipseMakeCenter(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
    //    EndPaint(hWnd, &ps);

    //    /*
    //    strcpy(x, y) : y�� x�� ����
    //    strcat(x, y) : x���ڿ� + y���ڿ�
    //    strlen(x, y) : ���ڿ� ����
    //    strcmp(x, y) : �� ���ڿ��� ������ Ȯ��
    //    �� ���� -> 0����
    //    �� x < y -> -1
    //    �� x > y -> 1

    //    strcpy      -> wcscpy       -> _tcscpy
    //    strcat      -> wcscat       -> _tcscat
    //    strlen      -> wcslen       -> _tcslen
    //    strcmp      -> wcscmp       -> _tcscmp
    //    strtok      -> wcstok       -> _tcstok      ���ڿ� �ڸ���
    //    strchr      -> wcschr       -> _tcschr      ���� ã��
    //    strstr      -> wcsstr       -> _tcsstr      ���ڿ� ã��
    //    */

    //    // ��ī��Ʈ ��ǥ != ������ ��ǥ��

    //    // AABB�浹 - ���е��� ��������� ������ ������. ,OBB�浹 - ���е��� ������ ���귮�� ���� ������.
    //    // API�� C ����̱� ������ ȸ���ϱⰡ �����.
    //    // C++�� const�� ���� �� ������ DC������ ����� ���� �ʱ� ������ �ȼ��� ���������µ� ����ä�� ȸ���ϱ� ������ �� ������� �ʴ´�.

    //    // �ȼ� �浹 - ���� ȣ��: �浹ó���� �ؾ��� �ؽ��Ŀ� ������ ȣ���Ͽ� ����������.
    //    // ���� �簢������ �浹�� �������� ��� �� ��ٷο� �κп��� �ȼ��浹�� �ϴ°� ����.
    //    // �ᱹ�� AABB�� �ȼ��浹�� ȥ���Ͽ� ����ϴ°� ����.
    //    // 2D�迭 -> ��������� OBB���� ������.

    //    //Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    //    //DrawRectMake(hdc, rc);

    //    //SetPixel(hdc, 300, 200, RGB(255, 0, 0));

    //    //for (int i = 0; i < 10000; i++)
    //    //{
    //        //SetPixel(hdc, rand() % 800, rand() % 800, RGB( rand() % 255, rand() % 255, rand() % 255));
    //    //}


    //    // TextOut() : ���� ���(hdc, 
    //    //TextOut(hdc, 300, 300, "������ �ʹ� ��մ� ^^", strlen("������ �ʹ� ��մ�^^")); // ��Ƽ����Ʈ
    //    //(DC����, x��ǥ, y��ǥ, ���ڿ�, ���ڿ� ����)
    //    //��strlen�� �Ҵ� ���� �޸𸮿� ���ε� �� ���ڿ����� NULL���� ������ ���ڿ� ����

    //    //���ڿ� ���ڻ� ����
    //    //SetTextColor(hdc, RGB(255, 0, 0));
    //    //TextOut(hdc, 300, 400, "���� �� �� ���ּ���.", strlen("���� �� �� ���ּ���."));

    //   // MoveToEx(hdc, 400, 400, NULL);
    //   //LineTo(hdc, 200, 400);

    //    //MoveToEx(hdc, 400, 400, NULL);
    //    //LineTo(hdc, 200, 200);

    //    //Ellipse(hdc, 100, 100, 200, 200);

    //    //Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

    //    //EndPaint(hWnd, &ps);
    //    break;

    //case WM_MOUSEMOVE:
    //    pt.x = LOWORD(lParam);
    //    pt.y = HIWORD(lParam);

    //    InvalidateRect(hWnd, NULL, true);

    //    break;

    //case WM_LBUTTONDOWN: // ���콺 ���� ��ư�� ������ �� �޼��� �߻�

    //    centerX = RND->getInt(WINSIZE_X);
    //    centerY = RND->getInt(WINSIZE_Y);

    //    InvalidateRect(hWnd, NULL, true);
    //    break;

    //    /*hdc = GetDC(hWnd);

    //    SetTextColor(hdc, RGB(0, 0, 255));
    //    TextOut(hdc, 350, 500, str, strlen(str));

    //    ReleaseDC(hWnd, hdc);
    //    break;*/

    //case WM_RBUTTONDOWN:


    //case WM_LBUTTONUP:
    //    
    //    break;

    //case WM_KEYDOWN:

    //    switch (wParam)
    //    {
    //    case VK_LEFT:
    //        break;
    //    case VK_RIGHT:
    //        break;
    //    case VK_ESCAPE:
    //        PostMessage(hWnd, WM_DESTROY, 0, 0);
    //        break;
    //    }


    //case WM_DESTROY: // �Ҹ���
    //    // PostQuitMessage(): �� �Լ��� �޼��� ť�� Quit �޼����� ������ ������ �Ѵ�.
    //    // ��, Quit�޼����� �����ϴ� ���� GetMessage �Լ��� FALSE�� ��ȯ������ �޼��� ������ ����ȴ�.
    //    PostQuitMessage(0);
    //    return 0;
    //}

    //// ������ ���ν������� ó�� ���� ���� ������ �޼����� ó���� �ش�.
    //return DefWindowProc(hWnd, iMessage, wParam, lParam);
#pragma endregion
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
    
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };
    
    // ���� ������ ũ�� ����
    //AdjustWindowRect() : RECT ����ü, ������ ��Ÿ��, �޴� ����
    AdjustWindowRect(&rc, WINSTYLE, false);

    // ���� ��Ʈ�� ������ ������ ������ ����
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

    // zorder : ������ ��� ���� ���, ĳ���Ͱ� �ٸ� ������Ʈ�� ��ĥ �� ������Ʈ�� ���İ��� �����μ� ĳ���͸� �ν��ϱ� ���� �� �� �ִ�.
}


















/* 06.07
���� 1. ������ â �����

 - �ð��� 10��

 - ���н� ���� 7��

 - ������ �⺻Ʋ�� �����ϰ� ����� �� �˾ƾ� �Ѵ�.


 �� �� ����. ��Ʈ�� ������ ����

 - Callback Function, DC, GetDC / Realease DC, BeginPaint / EndPaint
    WM_PAINT, PAINTSTRUCT
    -> DC �ø���� Callback�� �ʹ� ��� ���� ����
    -> DC �ø���� ������ ������������ ������ �������Ͷ�
    -> Callback�� delicate, void pointer, functional

*/

/* 06.08
 ���� 1. ������

 - ����ó�� �ʼ��� ���� (1�� ���� / 9�� �̻� ����)

 - ���콺 ���� Ŭ���� ���� �� 1�ܾ� ����� ��Ŭ���� �ϸ� 1�ܾ� ��������.

 - 3�ܾ� �����Ѵ�.



 ���� 2. WInAPI ���

 - MoveToEx() + LineTo()�� �̿��Ѵ�.
 - ���� ���� �Լ� x 
 - �ڱ� �̸� ���(�ѱ�)
 - Unreal Engine (����)
 - ���콺 ������ ������ �ѱ��ھ� ����� �ǰ� �������� ������ �ѱ��ھ� ��������.


  - ���� â ũ�� ���� ���� �̻��� ������� �ؿ´�.

 ���� ����.

 -SetTimer

 -KillTimer

 -InvalidateRect

*/

/* 06.09

 ���� 1. ������ ���
 
 - �������� ������ó�� ����� �´�.
 
 - ����� �������� ������ ���������� ���� ȿ������ �������
 �� Ư�� �迭�� ������ ����غ���.

 - ������ 3���̸� �����ϴ�.

 ���� 2. ���� �ΰ� ���

 - SetPixel�� �̿��ؼ� �����.

 - �� �Ȱ���

 ���� 3. �簢�� �̵�

 - ����Ű�� ���� �簢���� �����δ�.

 - ����ó�� : �簢���� ȭ�� ������ ���� �� ����.

 ���� 4. �簢�� 2�� �����̱�

 - 3���� ����Ǿ�� �Ѵ�.

 - �� �簢�� ���� 2��

 - �ϳ��� ������ �� �ִ� �簢��/ �ٸ� �ϳ��� ������ �� ���� �簢��

 - ������ �� ���� �簢���� ������ �� �ִ� �簢���� �о �� ������ �ȴ�.

 - 2���� �簢���� ȭ�� ������ ���� �� ����.

 - 2���� �簢���� �ʱ� ��ġ�� ������ ��ɵ� �߰��Ѵ�.

 - ���ٸ� ����� �ϱ� �������� �浹 �Լ� ��� ����

*/

/* 06.12

���� 1. �簢�� ���� �о�ֱ�
 - ū�簢�� 2���� ���� �簢�� 1��
 - ���� ������ �� �ִ� �簢�� �ȿ��� ���� �簢���� ����ִ�.
 - �簢���� �����̸� ���� �簢�� ���� �����̴� ���� 1��/�������� �ʴ� ���� 1��
 ������ó�� : ���� �簢���� ū �簢���� ��� �� ����.
             ū �簢�������� �𼭸��� ���� ���е��� ����ó���Ѵ�.

 - ū �簢�� ���� �浹�� �Ǹ� ���� �簢���� �浹�� �� �ݴ��� �簢������ �̵��Ѵ�.

 �� �ٽ�- ������ �� �ִ� �ֵ����� ���� �簢���� ������ �ִ� "ū�簢��"

*/

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

/* 06.14

 ����1. ���콺�� ������ ���� ���

 - ���콺�� Ŭ���� ��ǥ�� ������ ������ ����Ѵ�.
 - ������ ũ�� + ������ ��� + ������ �������� ��� ������ ó���Ѵ�.
 - ������ ���� : �簢�� ��, �ﰢ�� �� �ٰ���

 �ﰢ�� + �ٰ��� -> polygon() + �迭�� �̿��Ѵ�.

 <2�� ���� ����>
 ����2. ������ Ȱ���� �� �� �׷�����
  - ������ Ȱ���Ѵ�.
 
 ����3. �� ƨ���

 - ū �簢�� �ȿ� ���� ���� �ִ�.

 - ���� ���� ū �簢�� �ȿ��� ������� ���ٸ� �Է��� ��� �簢�� �鿡 ƨ��鼭 ���������� �����δ�.

 - ū �簢���� Ű���� �Է��� ������ ũ�⸦ �ø��ų� ���� �� �ִ�.

 - ũ�Ⱑ �þ�ų� �پ��� �翬�� ���ʿ� �ִ� ���� ������ �޴´�.
 �� ���콺 ��Ŭ���� : �� �ӵ� ����
 �� ���콺 ��Ŭ���� : �� �ӵ� ����

 ���� ����. 

 - GetAsyncKeyState ���°����� ���� �ؿ� ��

*/