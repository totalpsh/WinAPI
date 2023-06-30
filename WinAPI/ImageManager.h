#pragma once
#include "SingletonBase.h"
#include "GImage.h"

// 1. 객체에 따른 new
// 2. 관리 문제 --> 2번의 형태에 따라서 1번의 형태가 정해진다.
// ㄴ 어떻게 관리 할 것인가? 에 따라 1번이 정해진다.
// -> STL->Map 관리에 굉장히 탁월한 친구
// Key 와 Value가 가지고 있는 값이 매우 유효하다.
// map과 unordered map 둘중 하나를 골라야 한다.
// 하지만 이미지는 검색 속도가 무의미 하기 때문에 map을 써야 한다는 생각을 해내야 한다.


// 래핑 클래스로서 이미지를 외부로부터 받아서 빼주기 위한 작업

#pragma region STL 맵
/*

- 키 + 값을 잊지 말자.
ㄴ 첫번쨰 first -> 키
ㄴ 두번쨰 second -> 값

- 추가하는 방법은 insert()를 사용하고 키와 벨류를 동시에 추가해야 하니 pair / make pair를 사용

- pair : 두가지 자료형을 하나로 묶어주는 구조체 (템플릿 -> 어떤 자료형도 OK)

- make_pair : pair를 만들어주는 함수
ㄴ pair.first = x; / pair.second = y;
ㄴ pair = make_pair(x, y);

-하나에 키에 여러개의 값을 저장하고 싶다면 멀티맥을 사용하는 것도 고려

- pair를 확장시켜 구조를 작성하거나 다수의 반환값을 가지고 싶다면 tuple도 고려해야 한다.

*/
#pragma endregion

class ImageManager : public SingletonBase<ImageManager> // 싱글톤 : 객체의 고유성을 보존 해주기 위함
{
private:
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*>::iterator mapimageIter;
	/*
		- string 을 쓰는 이유
		반복자는 시작점과 끝이 있는데 
		char* 에 들어가서 한번씩 확인하는 작업이 필요하다.
		맵과 연동이 되는 string 를 사용한다.
	*/

private:
	mapImageList _mImageList;


public:
    //전역 처리 과정이 없었음
    // 싱글톤 래핑클래스를 만들어 GImage를 참조하는 형태
	HRESULT init(void);
	void release(void);
	// 단독 처리시 문제점
	// ㄴ 1. 프레임워크 코드 불일치
	// ㄴ 2. 객체간 (이미지) 충돌 가능성


   GImage* addImage(string strKey,int width, int height);
   GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
   GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

   GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
   GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

   GImage* findImage(string strKey);

   bool deleteImage(string strkey);
   bool deleteAll();


    HRESULT initForAlphaBlend(void);    // 알파 블랜드 초기화 함수

    //해제

    void render(string strKey,HDC hdc);
    // 0,0 기준으로 그린다.
    void render(string strKey, HDC hdc, int destX, int destY);

    //이미지 클리핑 -> 원하는 만큼 이미지를 잘라서 그린다
    void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight);
    void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sizeX, int sizeY, int sourwidth, int sourheight);
    // 알바 랜더
    void alphaRender(string strKey, HDC hdc, BYTE alpha);      // BYTE 자료형은 0~255 크기를 가진다 -> 알파값에 딱 맞음
    void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, BYTE alpha);

    //프레임 랜더
    void frameRender(string strKey, HDC hdc, int destX, int destY);
    void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    void setTransImage(const char* fileName);

    ImageManager() {}
    ~ImageManager() {}
};

