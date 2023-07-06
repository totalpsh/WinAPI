#pragma once
// ��� ����
#pragma warning(disable : 4005)
// 4005 : DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ��� �Ǵ� ���

/* 
 �� Stdafx

 - MG�� ���־� ��Ʃ����� �̿��Ͽ� ������Ʈ�� ����� �����Ǵ� Ŭ�����̴�.
 �� ��ģ���� �ǹ��ϴ� �ٴ� ǥ�� ���ø����̼� ������ ��ũ�� Ʋ

 - MS���� �����ڵ��� �ɷ� ����� ���� ������ PCH ����
 �� ���� ���̴� �������� ������� �̸� ������ �صξ� ���� �ٽ� ������ ���� �ʰ� ����ϰ� �ȴ�.

 - ���߿� �ʱ� ���� �ܰ迡���� �� �ʿ伺�� �� �������� ��������� ũ�Ⱑ Ŀ���ų� ���� ���� �� ���� Ȱ�뵵 �� ȿ���� �޻�¡��


*/


// ���α׷����� ������ OS�� ���� �Ǵ� ���̺귯���� ���� Windows ������� �ڵ忡 ���Ե� �Լ�/ ��� ���� �����ϴµ� ��� �Ѵ�.
#include <SDKDDKVER.h>

// stdafx.h : ���� ��������� ���� ���� ������ �ʴ� ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������ ����ִ� ���� ����
// ���� �ٲ��� �ʴ� �⺻���� ���̺귯������ ��쿡 ������ �ð��� ���̰��� �����Ϸ��� ������ ��������� ���� �س��� �� --> .pch ����
// Inline�� ������ ����.
// inline ������ �ص� �����Ϸ��� �ζ��� ȭ�� �ź� �Ҽ� ����
// inline ������ ���ص� �����Ϸ��� �ζ���ȭ�� �� �� ����
// 

//#include "targetver.h" // �ٸ� �ü������ ȣȯ���� ���� �� �ִ�. �� �ڵ带 ���Ƿ� �ü���� �°� �ٲ��ش�.

// #include <ole2.h> ��Ŀ� ���� ȸ�� ����
#define WIN32_LEAN_AND_MEAN				
// ���� ������ �ʴ� ������ WIndows ������� ����
// ��GDI+�� ����Ϸ��� ������Ͽ��� �����;� �Ѵ�.

// ����� �ܼ�â
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")

// ���̺귯�� �߰�
#pragma comment(lib, "msimg32.lib")


// WIndows �������
#include <windows.h>

//! C ��Ÿ�� ��� ����

#include <stdlib.h> // c����� ǥ�� ���̺귯�� �Լ��� �������
#include <malloc.h> // c���� �޸� �Ҵ��� �� ���
#include <memory.h> // �޸� ���� ������� -- memset/memcpy �� ����ϴ� �������
/* tchar
 �� ���ڿ� ��

 - �����쿡�� ����� ���ڿ� ��� ����(����)�� (TextOut, DrawText, wsprintf ���)
 �� �⺻������ �����ڵ� ���

 �� MBCS (��Ƽ ����Ʈ ĳ���� ��)

 - ������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ��� ���Ѵ�.

 - ��Ƽ����Ʈ �ڵ�� ���� ���� �ƽ�Ű �ڵ忡 ���ԵǴ� ���ڴ� 1����Ʈ�� ǥ���ϰ� ���Ե��� �ʴ� ���ڴ� 2����Ʈ�� ó���Ѵ�.

 �� WBCS (���̵� ����Ʈ ĳ���� ��)

  - ��� ���ڸ� 2����Ʈ�� ó���ϸ� �����ڵ� ����̴�.
 
 �� �����ڵ�� ��Ƽ����Ʈ�� ���
 
 - vs ������ ���߽� ��Ƽ/�����ڵ带 ���� �⺻������ ������ ����� �Ѵ�.

 - �����ڵ��� ��쿡�� ���ڿ��� ����ǥ�� ���ΰ� �� �տ� L�� �ٿ��� (L"") �̶�� ǥ���ϸ� �ȴ�.

 - ��Ƽ����Ʈ ���� ��쿡�� �׳� ""�� ����ϸ� �ȴ�.

 - �����ڵ�� ���ߵ� ���α׷��� ��Ƽ����Ʈ�� �̽��Ϸ��� �̵� ���ڿ��� ǥ�� ����� �ٽ� ������� �ϱ� ������ �ſ� �����ϴ�.
 �� �׷��� _T��ũ�θ� ����ؾ� �Ѵ�.

 - ���ڿ��� ����ǥ�� ���ΰ� �����ڵ忡�� ����� "L" ��� "_T"�� ����ϸ� ��ũ�ΰ� �˾Ƽ� ���� ȯ�濡 �°� ġȯ�� �ش�.


*/
#include <tchar.h>  
#include <stdio.h> // ǥ�� ����� ��� ����
#include <time.h>


//! C++ ��Ÿ�� ��� ����
#include <iostream>
/* chrono
 - C++11 ���� �߰��� �ð����� ���̺귯��(STL)
 �� ���� C��Ÿ�ӿ��� �����ϴ� time �Լ����� �پ��� / Ȯ��� ����� ����
 �� ���е��� ����(���� �и� �� ����)
	�� time �Լ��� �ʴ��� ���� ������ �����ϱ� ������ ���е��� ���� �� �� �ִ�.
 �� OS�� ���������� �����Ѵ�.
*/
#include <chrono>
#include <random>
#include <vector>
#include <map>
// unordered_map: Hash �ڷᱸ��
// �� �Ϲ��� ��Ȳ���� map���� �˻� �ӵ��� �� ������.
// �� �˻� �ӵ��� �� ���� ������ �ߺ��� �����͸� ������� �ʱ� ����
// �� ��, ���� �����Ͱ� ���� ��(key), �ؽ� �浹�� �߻��� ������ ����� ������ ���� ���ϰ� �߻��Ѵ�.
#include <unordered_map>
// cassert : C++���α׷����� ��� -> �� ���餻(ų�� ���μ���)
// �ΰ� ���Ϸ� ����ؾ� �Ѵ�.
#include <cassert>

// bitset: ��Ʈ ������ ���� ���� �������ִ� �Լ��� �����ϴ� STL
// �� reset(), set(), flip(), all(), any(), size() ���
// bool ��뷮�� �ٿ� ���ǽĵ� ���� �� �ִ�. -> ���°� ǥ���� ����.
#include <bitset>

using namespace std;

/*
//! D2D/D3D ��� ����
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3Dx11.h> // �ٷ� 11
#include <d3d11shader.h> // ���̴��� �� ����� �Ѵ�.
#include <dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory* _ID2DFactory = nullptr;
ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr;
*/

// ����� ���� �������
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TempSoundManager.h"

// �̱���
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()

// ��üȭ��

#define FULLSCREEN

#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))

#ifdef FULLSCREEN 

#define WINSTART_X	0
#define WINSTART_Y	0
// GetSystemMetrics(): ���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ
// �� SM_CXSCREEN + SM_CYSCREEN = ���� ȭ�� �ػ� x��y�� ��ȯ
#define WINSIZE_X   GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE WS_POPUPWINDOW | WS_MAXIMIZE


#elif
// ��ũ�� (������â �ʱ�ȭ)
#define WINSTART_X	400
#define WINSTART_Y	100
#define WINSIZE_X   1280
#define WINSIZE_Y	800
// WS_CAPTION : Ÿ��Ʋ�ٸ� ������ ���� ����
// WS_SYSMENU: ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#endif

// ��ũ�� �Լ� (Ŭ�������� �����Ҵ� �� �κ� ����)
#define SAFE_DELETE(p)			{if(p) delete (p); (p) = nullptr;}
#define SAFE_DELETE_ARRAY(p)	{if(p) delete[] (p); (p) = nullptr;}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

// ���� ���� --> ������ �������� (�÷��̾��� �κ��丮 ��õ)
// extern Ű����� �ٸ� ��� / CPP���� ������ �����ؼ� ���� ���� ����Ѵ�.
// ����ü
// �⺻������ ���������� Ű���带 �����ص� �⺻������ externȭ �Ǵ� ��찡 ����.
extern HINSTANCE	  _hInstance;
extern HWND			  _hWnd;
// x��ǥ�� y��ǥ�� ����� ��ǥ�� ���� �� �� ����Ѵ�.
extern POINT		  _ptMouse;