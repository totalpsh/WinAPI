#include "Stdafx.h"
#include "GameNode.h"


//HRESULT GameNode::init(void)
//{
//	/*SetTimer(_hWnd, 1, 10, NULL);
//
//	RND->init();
//	KEYMANAGER->init();*/
//
//	//this->setDoubleBuffer();
//
//	return S_OK;
//}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//로케일 설정
		// ㄴ 프로그램의 명령어가 여러가지 언어로 주어져 있는 경우 이중에 어떤 언어의 것을 출력할 것인지에 대한 설정
		setlocale(LC_ALL, "korean");

		SetTimer(_hWnd, 1, 10, NULL);

		RND->init();
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TEMPSOUNDMANAGER->init();
	}

	return S_OK;
}

//void GameNode::setDoubleBuffer()
//{
//	_DoubleBuffer = new GImage;
//	_DoubleBuffer->init(WINSIZE_X, WINSIZE_Y);
//}

void GameNode::release(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		RND->releaseSingleton();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TEMPSOUNDMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
	//!do nothing
}

//void GameNode::render(HDC hdc)
//{
//}


LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();

		EndPaint(hWnd, &ps);
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
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

HRESULT init(bool managerInit)
{
	return S_OK;
}
