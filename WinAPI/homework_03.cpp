#include <Windows.h>
#include <tchar.h>
#include <math.h>

const double PI = 3.14159265358979323846;

#define HOMEWORK_03
#define PENTAGRAM 1
#define OUTAPPLELOGO 2
#define SQUARMOVE 3
#define TWOSQUARMOVE 4

#define HOMEWORK_TYPE 4

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

RECT RectMakeCenter_1(int x, int y, int width, int height)
{
	RECT rc1 = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc1;
}

RECT RectMakeCenter_2(int x, int y, int width, int height)
{
	RECT rc2 = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc2;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	PAINTSTRUCT ps;

	static int x = 20;
	static int y = 20;

	static int x1 = 20;
	static int y1 = 20;

	static int x2 = 400;
	static int y2 = 400;

	RECT rc1 = { x1 - 20, y1 - 20, x1 + 20, y1 + 20 };
	RECT rc2 = { x2 - 20, y2 - 20, x2 + 20, y2 + 20 };

	RectMakeCenter_1(rc1.left, rc1.top, rc1.right, rc1.bottom);
	RectMakeCenter_1(rc2.left, rc2.top, rc2.right, rc2.bottom);

	int angle_Arr[5] = { 144, 288, 72, 216, 0 };

	switch (iMessage)
	{
	case WM_CREATE:

		break;
#if HOMEWORK_TYPE == PENTAGRAM
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// 중심점 400, 400
		// 반지름 300
		// MoveToEx는 x가 700 y는 400 이다.
		/*MoveToEx(hdc, 700, 400, NULL);

		for (int i = 0; i < 360; i++)
		{
			LineTo(hdc, 400 + (300 * cos(i * PI / 180)), 400 - (300 * sin(i * PI / 180)));
		}*/

		// 배열 뭘 넣을까? - 각도, 횟수, 원 중점


		Ellipse(hdc, 100, 100, 700, 700); // 반지름 300
		MoveToEx(hdc, 400 + (300 * cos(90 * PI / 180)), 400 - (300 * sin(90 * PI / 180)), NULL);
		for (int i = 0; i < 5; i++)
		{
			LineTo(hdc, 400 + (300 * cos((90 + angle_Arr[i]) * PI / 180)), 400 - (300 * sin((90 + angle_Arr[i]) * PI / 180)));
		}


		EndPaint(hWnd, &ps);

		break;
#elif HOMEWORK_TYPE == OUTAPPLELOGO
		// 1. 81, 164, 48
		// 2. 248, 205, 66
		// 3. 238, 100, 51
		// 4. 238, 74, 47
		// 5. 185, 65, 90
		// 6. 49, 109, 219

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		for (int i = 50; i < 250; i++)
		{
			for (int j = 100; j < 700; j++)
			{
				SetPixel(hdc, j, i, RGB(81, 164, 48));
			}
		}

		for (int i = 250; i < 350; i++)
		{
			for (int j = 100; j < 700; j++)
			{
				SetPixel(hdc, j, i, RGB(248, 205, 66));
			}
		}

		for (int i = 350; i < 450; i++)
		{
			for (int j = 100; j < 700; j++)
			{
				SetPixel(hdc, j, i, RGB(238, 100, 51));
			}
		}

		for (int i = 450; i < 550; i++)
		{
			for (int j = 100; j < 700; j++)
			{
				SetPixel(hdc, j, i, RGB(238, 74, 47));
			}
		}

		for (int i = 550; i < 650; i++)
		{
			for (int j = 100; j < 700; j++)
			{
				SetPixel(hdc, j, i, RGB(185, 65, 90));
			}
		}

		for (int i = 650; i < 750; i++)
		{
			for (int j = 100; j < 700; j++)
			{
				SetPixel(hdc, j, i, RGB(49, 109, 219));
			}
		}


		break;

#elif HOMEWORK_TYPE == SQUARMOVE
		// 사각형 생성
		// 키보드를 입력 받으면 해당 방향으로 일정 좌표를 옮긴다.
		// 좌표를 옮기고 다시 그린다. 
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, x - 20, y - 20, x + 20, y + 20);
		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_UP:
			y -= 20;
			break;
		case VK_DOWN:
			y += 20;
			break;
		case VK_LEFT:
			x -= 20;
			break;
		case VK_RIGHT:
			x += 20;
			break;
		}

		if (x > 760)
		{
			x = 760;
		}
		else if (y > 740)
		{
			y = 740;
		}
		else if (x < 20)
		{
			x = 20;
		}
		else if (y < 20)
		{
			y = 20;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;

#elif HOMEWORK_TYPE == TWOSQUARMOVE
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 0, 0, 800, 800);
		Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
		Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_UP:
			if (rc1.top > 0)
			{
				y1 -= 20;
			}

			if (rc1.top == rc2.bottom && (x1 <= rc2.right && x1 >= rc2.left))
			{
				if (rc2.top > 0)
				{
					y2 -= 20;
				}
				else if (rc2.top - 20 < 10)
				{
					y1 = 60;
				}
			}

			break;
		case VK_DOWN:
			if (rc1.bottom < 760)
			{
				y1 += 20;
			}
			if (rc1.bottom == rc2.top && (x1 <= rc2.right && x1 >= rc2.left))
			{
				if (rc2.bottom < 760)
				{
					y2 += 20;
				}
				else if (rc2.bottom + 20 > 770)
				{
					y1 = 700;
				}
			}
			break;
		case VK_LEFT:
			if (rc1.left > 0)
			{
				x1 -= 20;
			}
			if (rc1.left == rc2.right && (y1 >= rc2.top && y1 <= rc2.bottom))
			{
				if (rc2.left > 0)
				{
					x2 -= 20;
				}
				else if (rc2.left - 20 < 10)
				{
					x1 = 60;
				}
			}
			break;
		case VK_RIGHT:
			if (rc1.right < 780)
			{
				x1 += 20;
			}
			if (rc1.right == rc2.left && (y1 >= rc2.top && y1 <= rc2.bottom))
			{
				if (rc2.right < 780)
				{
					x2 += 20;
				}
				else if (rc2.right + 20 > 770)
				{
					x1 = 720;
				}
			}
			break;
		case VK_SPACE:
			x1 = 20;
			y1 = 20;
			x2 = 400;
			y2 = 400;
			break;
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
