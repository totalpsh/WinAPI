#include "stdafx.h"
#include "homework_07.h"

HRESULT homework_07::init(void)
{
    // 타이머 초기화
    SetTimer(_hWnd, 1, 10, NULL);

    // 함수가 성공적으로 실행 되었음을 알린다.
    return S_OK;
}

void homework_07::release(void)
{
    // 동적 할당 과 같이 삭제하지 않고 종료하면 메모리가 샌다.
    KillTimer(_hWnd, 1);

}

void homework_07::update(void)
{
    InvalidateRect(_hWnd, NULL, true);
}

void homework_07::render(HDC hdc)
{
    // ! do noting 설계단계
    // 렌더는 그냥 추상객체로만 남긴다.
}

// 메인 프로시저
LRESULT homework_07::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;

    case WM_CREATE:
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        this->render(hdc);

        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:

        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);

        break;

    case WM_LBUTTONUP:

        break;

    case WM_KEYDOWN:

        switch (wParam)
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);

}