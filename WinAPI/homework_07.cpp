#include "stdafx.h"
#include "homework_07.h"

HRESULT homework_07::init(void)
{
    // Ÿ�̸� �ʱ�ȭ
    SetTimer(_hWnd, 1, 10, NULL);

    // �Լ��� ���������� ���� �Ǿ����� �˸���.
    return S_OK;
}

void homework_07::release(void)
{
    // ���� �Ҵ� �� ���� �������� �ʰ� �����ϸ� �޸𸮰� ����.
    KillTimer(_hWnd, 1);

}

void homework_07::update(void)
{
    InvalidateRect(_hWnd, NULL, true);
}

void homework_07::render(HDC hdc)
{
    // ! do noting ����ܰ�
    // ������ �׳� �߻�ü�θ� �����.
}

// ���� ���ν���
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