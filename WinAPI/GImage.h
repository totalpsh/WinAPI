#pragma once

/*
- 이미지를 불러오는 방법


*/

class GImage
{

public:

    enum IMAGE_LOAD_KIND
    {
        LOAD_RESOURCE = 0, LOAD_FILE,      // 리소스, 파일
        LOAD_EMPTY, LOAD_END            // 빈 비트맵, 로드 done

    };

    typedef struct tagImage
    {
        DWORD   resID;
        HDC      hMemDC;
        HBITMAP hBit;
        HBITMAP hOBit;

        float   x;                      // 이미지 x좌표
        float   y;                      // 이미지 y좌표
        int     width;                  // 이미지 가로 크기
        int     height;                 // 이미지 세로크기
        int     currentFrameX;          // 현재 프레임 x
        int     currentFrameY;          // 현재 프레임 y
        int     maxFrameX;              // 최대 프레임 x 갯수
        int     maxFrameY;              // 최대 프레임 y 갯수
        int     frameWidth;             // 1 프레임 가로 크기
        int     frameHeight;            // 1 프레임 가로 크기
        BYTE    loadType;               // 


        tagImage()
        {
            resID = 0;                          //long
            hMemDC = nullptr;                   // 메모리에 들어갈 메모리DC
            hBit = nullptr;                     // 메모리에 그릴 것과 화면에 그릴 것을 분리 화면이 지나가면 메모리에 있던것을 복사하겠다!
            hOBit = nullptr;
            x = y = 0;
            width = 0;
            height = 0;
            currentFrameX = 0;
            currentFrameY = 0;
            maxFrameX = 0;
            maxFrameY = 0;
            frameWidth = 0;
            frameHeight = 0;
            width = 0;
            height = 0;
            loadType = LOAD_RESOURCE;          // unsigned char
        }
    }IMAGE_INFO, * LPIMAGE_INFO;
    // 별도로 받아와서 찍어주는것

private:
    LPIMAGE_INFO   _imageInfo; // 이미지 정보 구조체
    char* _fileName;  // 파일 패스로 외부에서 가져오는걸 전제해서 ㅍㅏ일을 찾기 위한 변수
    bool            _isTrans;   // 배경색을 뺼건지 안뺼건지(캐릭터나 기타 오브젝트) -> 어떤 색을 뺼것인가?(마젠타 색상) -> 게임에서 거의 안쓰는 색상이다(255, 0, 255)
    COLORREF      _transColor; // 

    BLENDFUNCTION   _blendFunc;     // 알파블랜드 기능     -> 알파값 조절로 메모리 사용량 감소도 가능
    LPIMAGE_INFO    _blendImage;    // 알바블랜드 이미지


public:

    /*
   COLORREF - 중요하다 기억하자

   - 윈도우즈 에서 색상값을 표현하기 위한 부호없는 32비트 정수형
   ㄴ R, G, B 각각 1바이트(8비트)이며 0~255까지 표현하는데 최적화 되어 있다.

   */
   // ★★★★★★★★★★★★★★★★★★★★★★★★★★★
   // 딱봐도 하나로 만들수도 있는데? 인자값에 따라서 나뉜 이유 -> 이미지는 메모리를 많이 먹는데 최적화에 따라 메모리를 줄일 수 있다?
   // -> 동적할당을 하고 이미지 로딩을하고 랜더를 만들고동기를 하고 그린다
   // ㄴ 이미지를 출력하기 위해 메모리 보관이 시작되는데 런타임에서 실행이 되어 인자값을 줄인 후 코스트를 줄여 함수의 무게를 줄인다
   // ★★★★★★★★★★★★★★★★★★★★★★★★★★★

    HRESULT init(int width, int height);
    // 이미지 리소스로 초기화 (만약 bool을 BOOL로 바꾼다면 함수 오버로딩 규칙에 어긋나기 때문에 잘못 불러올 수 있다.)
    // 함수 오버로드에 대해서 한번더 공부하자.
    HRESULT init(const DWORD resId, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    // 이미지 파일로 초기화
    HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

    // 한번쓰고 다시 안불러오는 애들 -> 배경
    HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    // 
    HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    // 플레이어 위치와 넓이로 활용
    HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

    HRESULT initForAlphaBlend(void);    // 알파 블랜드 초기화 함수

    // 프레임 이미지 파일로 초기화



    // 투명 컬러키 세팅
    void setTransColor(bool isTrans, COLORREF transColor);

    //해제
    void release(void);

    void render(HDC hdc);
    // 0,0 기준으로 그린다.
    void render(HDC hdc, int destX, int destY);

    //이미지 클리핑 -> 원하는 만큼 이미지를 잘라서 그린다
    void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight);
    void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sizeX, int sizeY, int sourwidth, int sourheight);
    // 알바 랜더
    void alphaRender(HDC hdc, BYTE alpha);      // BYTE 자료형은 0~255 크기를 가진다 -> 알파값에 딱 맞음
    void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, BYTE alpha);

    //프레임 랜더
    void frameRender(HDC hdc, int destX, int destY);
    void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    void setTransImage(const char* fileName);

    // 루프 렌더
    // ㄴ 반복 / 이미지를 밀고 당기는 방식
    void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
    void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

    // 인라인 함수
    inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

    // 이미지 x좌표
    inline float getX(void) { return _imageInfo->x; }
    inline void setX(float x) { _imageInfo->x = x; }

    // 이미지 y좌표
    inline float getY(void) { return _imageInfo->y; }
    inline void setY(float y) { _imageInfo->y = y; }

    // 이미지 센터 좌표
    inline void setCenter(float x, float y)
    {
        _imageInfo->x = x - (_imageInfo->width / 2);
        _imageInfo->y = y - (_imageInfo->height / 2);
    }

    // 이미지 가로 / 세로 크기
    inline int getWidth(void) { return _imageInfo->width; }
    inline int getHeight(void) { return _imageInfo->height; }

    // 바운딩 박스(충돌용 렉트)
    inline RECT boundingBox(void)
    {
        RECT rc =
        {
            _imageInfo->x,
            _imageInfo->y,
            _imageInfo->x + _imageInfo->width,
            _imageInfo->y + _imageInfo->height
        };
        return rc;
    }

    // 프레임을 포함한 바운딩 박스(충돌용 렉트)
    inline RECT boundingBoxWithFrame(void)
    {
        RECT rc =
        {
            _imageInfo->x,
            _imageInfo->y,
            _imageInfo->x + _imageInfo->frameWidth,
            _imageInfo->y + _imageInfo->frameHeight
        };
        return rc;
    }

    // 프레임 X
    inline int getFrameX(void) { return _imageInfo->currentFrameX; }
    inline void setFrameX(int frameX)
    {
        _imageInfo->currentFrameX = frameX;

        if (frameX > _imageInfo->maxFrameX)
        {
            _imageInfo->currentFrameX = _imageInfo->maxFrameX;
        }


    }

    // 프레임 Y
    inline int getFrameY(void) { return _imageInfo->currentFrameY; }
    inline void setFrameY(int frameY)
    {
        _imageInfo->currentFrameY = frameY;

        if (frameY > _imageInfo->maxFrameX)
        {
            _imageInfo->currentFrameY = _imageInfo->maxFrameY;
        }


    }

    // 이미지 1프레임 가로 / 세로 크기
    inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
    inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

    // 최대 프레임 X / Y 갯수
    inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
    inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }







    GImage(); // 추상객체로 만들었는데 생성자에서 초기화를 해주어야 한다.(private:)
    ~GImage() {} // 1. 우선순위 기반 함수의 호출 2. release 함수에서 처리해 줄수 있기 때문
};