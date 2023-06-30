#include <Windows.h>
#include <tchar.h>
#include <math.h>

#define HOMEWORK_02
#define MULTIPICATION_TABLE 1
#define TEXTOUT 2

#define HOMEWORK_TYPE 2

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

	static int click = 0;

	char str[20] = "";
	char d_str[100] = "";
	static int i = 1;
	static int k = 0; // Å¬¸¯ È½¼ö
	static int x = 50;
	static int y = 50;

	const double PI = 3.1415926;

	switch (iMessage)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:

		break;
#if HOMEWORK_TYPE == MULTIPICATION_TABLE

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		
		if (i == 9)
		{
			
			break;
		}

		i++;

		for (int j = 1; j < 10; j++)
		{
			wsprintf(str, "%d  x  %d  =  %d", i, j, i * j);
			TextOut(hdc, x, y + (j * 20), str, strlen(str));
		}
		
		k++;
		
		x += 100;
		

		if (k == 3 || k == 6)
		{
			x = 50;
			y += 200;
		}
		
		ReleaseDC(hWnd, hdc);

		break;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);

	

		for (int j = 9; j > 0; j--)
		{
			wsprintf(d_str, "                              ");
			TextOut(hdc, (x- 100), y + (j * 20), d_str, strlen(d_str));
		}
		
		x -= 100;


		k--;

		if (k == 6 || k == 3)
		{
			x = 350;
			y -= 200;
		}

		ReleaseDC(hWnd, hdc);

		break;


		
#elif HOMEWORK_TYPE == TEXTOUT
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		if (click == 0)
		{
			MoveToEx(hdc, 100, 100, NULL);
			LineTo(hdc, 100, 200);
			MoveToEx(hdc, 100, 150, NULL);
			LineTo(hdc, 150, 150);
			MoveToEx(hdc, 100, 200, NULL);
			LineTo(hdc, 150, 200);
			MoveToEx(hdc, 150, 100, NULL);
			LineTo(hdc, 150, 200);
			MoveToEx(hdc, 180, 80, NULL);
			LineTo(hdc, 180, 220);
			MoveToEx(hdc, 180, 150, NULL);
			LineTo(hdc, 200, 150);
			MoveToEx(hdc, 100, 230, NULL);
			LineTo(hdc, 180, 230);
			MoveToEx(hdc, 180, 230, NULL);
			LineTo(hdc, 180, 280);
		}
		else if (click == 1)
		{
			MoveToEx(hdc, 260, 100, NULL);
			LineTo(hdc, 210, 150);
			MoveToEx(hdc, 235, 125, NULL);
			LineTo(hdc, 270, 150);
			MoveToEx(hdc, 250, 125, NULL);
			LineTo(hdc, 290, 125);
			MoveToEx(hdc, 290, 100, NULL);
			LineTo(hdc, 290, 180);
			/*for (int x = 240; x < 280; x++)
			{
				for (int y = 180; y < 220; y++)
				{
					MoveToEx(hdc, x, y, NULL);
					LineTo(hdc, x + 1, y + 1);
				}
			}*/
			/*MoveToEx(hdc, 240, 180, NULL);
			LineTo(hdc, 260, 180);
			LineTo(hdc, 280, 190);
			LineTo(hdc, 290, 210);
			LineTo(hdc, 290, 230);
			LineTo(hdc, 280, 250);
			LineTo(hdc, 260, 260);
			LineTo(hdc, 240, 260);
			LineTo(hdc, 220, 250);
			LineTo(hdc, 210, 230);
			LineTo(hdc, 210, 210);
			LineTo(hdc, 220, 190);
			LineTo(hdc, 240, 180);
			LineTo(hdc, 260, 180);*/

			for (int i = 0; i < 180; i++)
			{
				MoveToEx(hdc, 210 + (40 + sin(i * PI / 180)), 180, NULL);
				LineTo(hdc, 210 - (40 + sin(i + 1 * PI / 180)), 180 - (40 + cos(i + 1 * PI / 180)));
			}
		}
		else if (click == 3)
		{

		}



		click++;

		ReleaseDC(hWnd, hdc);
		break;
#endif

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
