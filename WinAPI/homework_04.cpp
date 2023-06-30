#include "Stdafx.h"

//���� 1. �簢�� ��ȥ �о�ֱ�
//- ū�簢�� 2���� ���� �簢�� 1��
//- ���� ������ �� �ִ� �簢�� �ȿ��� ���� �簢���� ����ִ�.
//- �簢���� �����̸� ���� �簢�� ���� �����̴� ���� 1�� / �������� �ʴ� ���� 1��
//������ó�� : ���� �簢���� ū �簢���� ��� �� ����.
//ū �簢�������� �𼭸��� ���� ���е��� ����ó���Ѵ�.
//
//- ū �簢�� ���� �浹�� �Ǹ� ���� �簢���� �浹�� �� �ݴ��� �簢������ �̵��Ѵ�.
//
//�� �ٽ� - ������ �� �ִ� �ֵ����� ���� �簢���� ������ �ִ� "ū�簢��"

#define HOMEWORK_04
#define HOMEWORK_TYPE
#define SOULFIX 1
#define SOULMOVE 2

#define HOMEWORK_TYPE  2

RECT rcL_1;
RECT rcL_2;
RECT rcS;

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _lpszClass = TEXT("Windws API");

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WinProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow
	(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		400,
		100,
		800,
		800,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(_hWnd, nCmdShow);

	MSG message;

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	PAINTSTRUCT ps;

	static int xL_1 = 500;
	static int yL_1 = 500;
	static int xL_2 = 300;
	static int yL_2 = 300;
	static int xS = 300;
	static int yS = 300;
	const int widthL = 80;
	const int heightL = 80;
	const int widthS = 30;
	const int heightS = 30;

	switch (iMessage)
	{
	case WM_CREATE:

		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		rcL_1 = RectMakeCenter(xL_1, yL_1, widthL, heightL);
		rcL_2 = RectMakeCenter(xL_2, yL_2, widthL, heightL);
		rcS = RectMakeCenter(xS, yS, widthS, heightS);

		DrawRectMake(hdc, rcL_1);
		DrawRectMake(hdc, rcL_2);
		DrawRectMake(hdc, rcS);
		EndPaint(hWnd, &ps);

		break;
#if HOMEWORK_TYPE == SOULFIX
	case WM_KEYDOWN:

		if ((yL_2 == yS && xL_2 == xS))
		{
			switch (wParam)
			{
			case VK_UP:

				if (rcL_2.top == rcL_1.bottom && (rcL_2.left <= rcL_1.right && rcL_2.right >= rcL_1.left))
				{
					xS = xL_1;
					yS = yL_1;
				}

				if (rcL_2.top > 0 && (yL_2 == yS && xL_2 == xS))
				{
					yL_2 -= 10;
					yS -= 10;
				}
				break;

			case VK_DOWN:

				if (rcL_2.bottom == rcL_1.top && (rcL_2.left <= rcL_1.right && rcL_2.right >= rcL_1.left))
				{
					xS = xL_1;
					yS = yL_1;
				}

				if (rcL_2.bottom < 760 && (yL_2 == yS && xL_2 == xS))
				{
					yL_2 += 10;
					yS += 10;
				}
	
				break;

			case VK_LEFT:

				if (rcL_2.left > 0 && (yL_2 == yS && xL_2 == xS))
				{
					xL_2 -= 10;
					xS -= 10;
				}

				if (rcL_2.left == rcL_1.right && (rcL_2.top <= rcL_1.bottom && rcL_2.bottom >= rcL_1.top))
				{
					xS = xL_1;
					yS = yL_1;
				}

				break;

			case VK_RIGHT:

				if (rcL_2.left < 700 && (yL_2 == yS && xL_2 == xS))
				{
					xL_2 += 10;
					xS += 10;
				}

				if (rcL_2.right == rcL_1.left && (rcL_2.top <= rcL_1.bottom && rcL_2.bottom >= rcL_1.top))
				{
					xS = xL_1;
					yS = yL_1;
				}

				break;
			}
		}


		if (yL_1 == yS && xL_1 == xS)
		{
			switch (wParam)
			{
			case VK_UP:

				if (rcL_1.top == rcL_2.bottom && (rcL_1.left <= rcL_2.right && rcL_1.right >= rcL_2.left))
				{
					xS = xL_2;
					yS = yL_2;
				}

				if (rcL_1.top > 0 && yL_1 == yS && xL_1 == xS)
				{
					yL_1 -= 10;
					yS -= 10;
				}

				break;

			case VK_DOWN:

				if (rcL_1.bottom == rcL_2.top && (rcL_1.left <= rcL_2.right && rcL_1.right >= rcL_2.left))
				{
					xS = xL_2;
					yS = yL_2;
				}

				if (rcL_1.bottom < 760 && yL_1 == yS && xL_1 == xS)
				{
					yL_1 += 10;
					yS += 10;
				}
				break;

			case VK_LEFT:


				if (rcL_1.left > 0 && (yL_1 == yS && xL_1 == xS))
				{
					xL_1 -= 10;
					xS -= 10;
				}

				if (rcL_1.left == rcL_2.right && (rcL_1.top <= rcL_2.bottom && rcL_1.bottom >= rcL_2.top))
				{
					xS = xL_2;
					yS = yL_2;
				}


				break;

			case VK_RIGHT:

				if (rcL_1.left < 700 && (yL_1 == yS && xL_1 == xS))
				{
					xL_1 += 10;
					xS += 10;
				}

				if (rcL_1.right == rcL_2.left && (rcL_1.top <= rcL_2.bottom && rcL_1.bottom >= rcL_2.top))
				{
					xS = xL_2;
					yS = yL_2;
				}

				break;
			}
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
#elif HOMEWORK_TYPE == SOULMOVE
case WM_KEYDOWN:

	if (rcS.top >= rcL_2.top && rcS.bottom <= rcL_2.bottom && rcS.left >= rcL_2.left && rcS.right <= rcL_2.right)
	{
		switch (wParam)
		{
		case VK_UP:

			if (rcL_2.top == rcL_1.bottom && (rcL_2.left <= rcL_1.right && rcL_2.right >= rcL_1.left))
			{
				xS = xL_1;
				yS = yL_1;
			}

			if (rcL_2.top > 0)
			{
				yL_2 -= 1;
				if (rcS.bottom == rcL_2.bottom)
				{
					yS -= 1;
				}
			}
			break;

		case VK_DOWN:

			if (rcL_2.bottom == rcL_1.top && (rcL_2.left <= rcL_1.right && rcL_2.right >= rcL_1.left))
			{
				xS = xL_1;
				yS = yL_1;
			}

			if (rcL_2.bottom < 760)
			{
				yL_2 += 1;
				if (rcS.top == rcL_2.top)
				{
					yS += 1;
				}
			}

			break;

		case VK_LEFT:

			if (rcL_2.left == rcL_1.right && (rcL_2.top <= rcL_1.bottom && rcL_2.bottom >= rcL_1.top))
			{
				xS = xL_1;
				yS = yL_1;
			}

			if (rcL_2.left > 0)
			{
				xL_2 -= 1;
				if (rcS.right == rcL_2.right)
				{
					xS -= 1;
				}
			}

			break;

		case VK_RIGHT:

			if (rcL_2.right == rcL_1.left && (rcL_2.top <= rcL_1.bottom && rcL_2.bottom >= rcL_1.top))
			{
				xS = xL_1;
				yS = yL_1;
			}

			if (rcL_2.left > 0)
			{
				xL_2 += 1;
				if (rcS.left == rcL_2.left)
				{
					xS += 1;
				}
			}

			break;
		}
	}


	if (rcS.top >= rcL_1.top && rcS.bottom <= rcL_1.bottom && rcS.left >= rcL_1.left && rcS.right <= rcL_1.right)
	{
		switch (wParam)
		{
		case VK_UP:

			if (rcL_1.top == rcL_2.bottom && (rcL_1.left <= rcL_2.right && rcL_1.right >= rcL_2.left))
			{
				xS = xL_2;
				yS = yL_2;
			}

			if (rcL_1.top > 0)
			{
				yL_1 -= 1;
				
				if (rcS.bottom == rcL_1.bottom)
				{
					yS -= 1;
				}

			}

			break;

		case VK_DOWN:

			if (rcL_1.bottom == rcL_2.top && (rcL_1.left <= rcL_2.right && rcL_1.right >= rcL_2.left))
			{
				xS = xL_2;
				yS = yL_2;
			}

			if (rcL_1.bottom < 760)
			{
				yL_1 += 1;
				if (rcS.top == rcL_1.top)
				{
					yS += 1;
				}
			}
			break;

		case VK_LEFT:

			if (rcL_1.left == rcL_2.right && (rcL_1.top <= rcL_2.bottom && rcL_1.bottom >= rcL_2.top))
			{
				xS = xL_2;
				yS = yL_2;
			}

			if (rcL_1.left > 0)
			{
				xL_1 -= 1;
				if (rcS.right == rcL_1.right)
				{
					xS -= 1;
				}
			}

			break;

		case VK_RIGHT:

			if (rcL_1.right == rcL_2.left && (rcL_1.top <= rcL_2.bottom && rcL_1.bottom >= rcL_2.top))
			{
				xS = xL_2;
				yS = yL_2;
			}


			if (rcL_1.left > 0)
			{
				xL_1 += 1;
				if (rcS.left == rcL_1.left)
				{
					xS += 1;
				}
			}

			break;
		}
	}

	InvalidateRect(hWnd, NULL, TRUE);
	break;
#endif
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
