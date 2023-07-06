#pragma once
// 경고 무시
#pragma warning(disable : 4005)
// 4005 : DXGI 등 그래픽 인터페이스에서 매크로 관련하여 출력 되는 경고

/* 
 ▶ Stdafx

 - MG의 비주얼 스튜디오를 이용하여 프로젝트를 만들면 생성되는 클래스이다.
 ㄴ 이친구가 의미하는 바는 표준 어플리케이션 프레임 워크의 틀

 - MS에서 개발자들의 능률 향상을 위해 만들어둔 PCH 파일
 ㄴ 자주 쓰이는 여러가지 헤더들은 미리 컴파일 해두어 이후 다시 컴파일 하지 않고 사용하게 된다.

 - 개발에 초기 구축 단계에서는 별 필요성을 못 느끼지만 헤더파일의 크기가 커지거나 양이 많아 질 수록 활용도 및 효율이 급상승↑↑


*/


// 프로그램에서 지원할 OS에 따라 또는 라이브러리에 따라 Windows 헤더에서 코드에 포함될 함수/ 상수 등을 제어하는데 사용 한다.
#include <SDKDDKVER.h>

// stdafx.h : 자주 사용하지만 자주 변경 되지는 않는 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이 들어있는 포함 파일
// 자주 바뀌지 않는 기본적인 라이브러리들의 경우에 컴파일 시간을 줄이고자 컴파일러가 사전에 헤더파일을 정의 해놓는 것 --> .pch 파일
// Inline과 궁합이 좋다.
// inline 선언을 해도 컴파일러가 인라인 화를 거부 할수 있음
// inline 선언을 안해도 컴파일러가 인라인화를 할 수 있음
// 

//#include "targetver.h" // 다른 운영체제와의 호환성을 높일 수 있다. 내 코드를 임의로 운영체제에 맞게 바꿔준다.

// #include <ole2.h> 행렬에 의한 회전 구현
#define WIN32_LEAN_AND_MEAN				
// 거의 사용되지 않는 내용은 WIndows 헤더에서 제외
// ㄴGDI+를 사용하려면 헤더파일에서 꺼내와야 한다.

// 디버깅 콘솔창
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")

// 라이브러리 추가
#pragma comment(lib, "msimg32.lib")


// WIndows 헤더파일
#include <windows.h>

//! C 런타임 헤더 파일

#include <stdlib.h> // c언어의 표준 라이브러리 함수의 헤더파일
#include <malloc.h> // c언어에서 메모리 할당할 때 사용
#include <memory.h> // 메모리 관련 헤더파일 -- memset/memcpy 를 사용하는 헤더파일
/* tchar
 ▶ 문자열 셋

 - 윈도우에서 사용할 문자열 출력 파일(문자)셋 (TextOut, DrawText, wsprintf 등등)
 ㄴ 기본적으로 유니코드 기반

 ▷ MBCS (멀티 바이트 캐릭터 셋)

 - 기존에 사용하던 멀티바이트 형태의 문자열을 뜻한다.

 - 멀티바이트 코드는 영어 같은 아스키 코드에 포함되는 문자는 1바이트로 표현하고 포함되지 않는 문자는 2바이트로 처리한다.

 ▷ WBCS (와이드 바이트 캐릭터 셋)

  - 모든 문자를 2바이트로 처리하며 유니코드 기반이다.
 
 ▶ 유니코드와 멀티바이트의 사용
 
 - vs 에서는 개발시 멀티/유니코드를 쓸지 기본적으로 지정을 해줘야 한다.

 - 유니코드인 경우에는 문자열을 따옴표로 감싸고 그 앞에 L을 붙여서 (L"") 이라고 표기하면 된다.

 - 멀티바이트 같은 경우에는 그냥 ""만 사용하면 된다.

 - 유니코드로 개발된 프로그램을 멀티바이트로 이식하려면 이들 문자열의 표현 방식을 다시 고쳐줘야 하기 때문에 매우 불편하다.
 ㄴ 그래서 _T매크로를 사용해야 한다.

 - 문자열을 따옴표로 가싸고 유니코드에서 사용한 "L" 대신 "_T"를 사용하면 매크로가 알아서 개발 환경에 맞게 치환해 준다.


*/
#include <tchar.h>  
#include <stdio.h> // 표준 입출력 헤더 파일
#include <time.h>


//! C++ 런타임 헤더 파일
#include <iostream>
/* chrono
 - C++11 에서 추가된 시간관련 라이브러리(STL)
 ㄴ 기존 C런타임에서 제공하는 time 함수보다 다양한 / 확장된 기능을 지원
 ㄴ 정밀도가 높다(나노 밀리 초 단위)
	ㄴ time 함수는 초단위 값만 측정이 가능하기 때문에 정밀도가 떨어 질 수 있다.
 ㄴ OS와 독립적으로 동작한다.
*/
#include <chrono>
#include <random>
#include <vector>
#include <map>
// unordered_map: Hash 자료구조
// ㄴ 일반적 상황에서 map보다 검색 속도가 더 빠르다.
// ㄴ 검색 속도가 더 빠른 이유는 중복된 데이터를 허용하지 않기 때문
// ㄴ 단, 유사 데이터가 많을 시(key), 해시 충돌이 발생할 여지가 생기기 때문에 성능 저하가 발생한다.
#include <unordered_map>
// cassert : C++프로그래머의 희망 -> 잘 쓰면ㅋ(킬링 프로세스)
// 두개 이하로 사용해야 한다.
#include <cassert>

// bitset: 비트 연산을 좀더 쉽게 관리해주는 함수를 지원하는 STL
// ㄴ reset(), set(), flip(), all(), any(), size() 등등
// bool 사용량을 줄여 조건식도 줄일 수 있다. -> 상태값 표현에 좋다.
#include <bitset>

using namespace std;

/*
//! D2D/D3D 헤더 파일
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3Dx11.h> // 다렉 11
#include <d3d11shader.h> // 쉐이더는 꼭 써줘야 한다.
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

// 사용자 정의 헤더파일
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TempSoundManager.h"

// 싱글톤
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()

// 전체화면

#define FULLSCREEN

#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))

#ifdef FULLSCREEN 

#define WINSTART_X	0
#define WINSTART_Y	0
// GetSystemMetrics(): 인자로 전달되는 시스템 설정 정보를 반환
// ㄴ SM_CXSCREEN + SM_CYSCREEN = 현재 화면 해상도 x축y축 반환
#define WINSIZE_X   GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE WS_POPUPWINDOW | WS_MAXIMIZE


#elif
// 매크로 (윈도우창 초기화)
#define WINSTART_X	400
#define WINSTART_Y	100
#define WINSIZE_X   1280
#define WINSIZE_Y	800
// WS_CAPTION : 타이틀바를 가지기 위한 옶견
// WS_SYSMENU: 제목 표시줄에 컨트롤 메뉴 상자 창
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#endif

// 매크로 함수 (클래스에서 동적할당 된 부분 해제)
#define SAFE_DELETE(p)			{if(p) delete (p); (p) = nullptr;}
#define SAFE_DELETE_ARRAY(p)	{if(p) delete[] (p); (p) = nullptr;}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

// 전역 변수 --> 완전한 전역변수 (플레이어의 인벤토리 추천)
// extern 키워드는 다른 헤더 / CPP에서 변수를 공유해서 쓰기 위해 사용한다.
// ㄴ객체
// 기본적으로 전역변수는 키워드를 생략해도 기본적으로 extern화 되는 경우가 많다.
extern HINSTANCE	  _hInstance;
extern HWND			  _hWnd;
// x좌표와 y좌표를 평면의 좌표에 정의 할 때 사용한다.
extern POINT		  _ptMouse;