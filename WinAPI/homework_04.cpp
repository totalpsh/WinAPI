#include "Stdafx.h"

//과제 1. 사각형 영혼 밀어넣기
//- 큰사각형 2개와 작은 사각형 1개
//- 내가 움직일 수 있는 사각형 안에는 작은 사각형이 들어있다.
//- 사각형을 움직이면 작은 사각형 역시 움직이는 버전 1개 / 움직이지 않는 버전 1개
//ㄴ예외처리 : 작은 사각형은 큰 사각형을 벗어날 수 없다.
//큰 사각형끼리의 모서리에 대한 정밀도를 예외처리한다.
//
//- 큰 사각형 끼리 충돌이 되면 작은 사각형은 충돌이 된 반대편 사각형으로 이동한다.
//
//※ 핵심 - 움직일 수 있는 주도권은 작은 사각형을 가지고 있는 "큰사각형"

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
