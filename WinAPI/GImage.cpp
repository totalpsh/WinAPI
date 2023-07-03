#include "Stdafx.h"
#include "GImage.h"



GImage::GImage() : _imageInfo(nullptr), _fileName(nullptr), _isTrans(false), _transColor(RGB(0, 0, 0)), _blendImage(NULL)
{
}

HRESULT GImage::init(int width, int height)
{
    // 재초기화 방지 -> 포인터
    // 혹시 값이 있다면 이상한 짓말고 먼저 릴리즈 하고 접근해라
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    //resID = 0;
    //hMemDC = NULL;
    //hBit = NULL;
    //hOBit = NULL;
    //width = 0;
    //height = 0;
    //loadType = LOAD_RESOURCE;

    _imageInfo->loadType = LOAD_EMPTY;
    _imageInfo->resID = 0;
    // 서브DC 
    _imageInfo->hMemDC = CreateCompatibleDC(hdc); // 한줄조사
    // 복사 하겠다.
    _imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); // 한줄조사
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;


    _fileName = nullptr; //어차피 밑 함수드에서 파일 쓸거임
    //strcpy -> 인자 1개 더 추가
    // 고질적인 문자/문자열에서 사이즈 문제를 해결한 함수
    // 복사 받을 변수, 길이 원본




    _isTrans = false;
    _transColor = RGB(0, 0, 0);

    // 리소스를 얻어오는데 실패하면 그냥뻗어라
    // 오류가 뜨면 랜덤하게 뜨게 되는데 확실하게 무슨 오류가 뜨는지 본다.
    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{

    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_RESOURCE;
    _imageInfo->resID = resID;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID)); // 한줄조사
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    _fileName = nullptr;

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_RESOURCE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); // 한줄조사
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;


    int len = strlen(fileName);

    _fileName = new char[len + 1];

    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_RESOURCE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); // 한줄조사
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->x = x;
    _imageInfo->y = y;
    _imageInfo->width = width;
    _imageInfo->height = height;

    int len = strlen(fileName);

    _fileName = new char[len + 1];

    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_RESOURCE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->currentFrameX = 0;
    _imageInfo->currentFrameY = 0;
    _imageInfo->maxFrameX = maxFrameX - 1;
    _imageInfo->maxFrameY = maxFrameY - 1;
    _imageInfo->frameWidth = width / maxFrameX;          // 1프레임의 대한 넓이
    _imageInfo->frameHeight = height / maxFrameY;        // 1프레임의 대한 높이


    int len = strlen(fileName);

    _fileName = new char[len + 1];

    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr) this->release();

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO;

    _imageInfo->loadType = LOAD_RESOURCE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->x = x;
    _imageInfo->y = y;
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->currentFrameX = 0;
    _imageInfo->currentFrameY = 0;
    _imageInfo->maxFrameX = maxFrameX - 1;
    _imageInfo->maxFrameY = maxFrameY - 1;
    _imageInfo->frameWidth = width / maxFrameX;          // 1프레임의 대한 너비이
    _imageInfo->frameHeight = height / maxFrameY;        // 1프레임의 대한 높이

    int len = strlen(fileName);

    _fileName = new char[len + 1];

    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

// 사용할 이미지가 있어야 작동하기 때문에 랜더를 할때 초기화를 해줘야한다.
HRESULT GImage::initForAlphaBlend(void)
{
    HDC hdc = GetDC(_hWnd);

    // 알파블랜드 옵션
    _blendFunc.BlendFlags = 0;              // 블랜드 속성값 -> 랜드에서 사용할거기 때문에 기본값
    _blendFunc.AlphaFormat = 0;             // 알파가 빠진뒤 상황을 설정 -> 0 = 후처리
    _blendFunc.BlendOp = AC_SRC_OVER;       // 블랜드 이미지 처리 방식을 설정 
    // _blendFunc.SourceConstantAlpha = 0;     // 값을 지정한 만큼 선처리하고 내보내는 값 조절

    _blendImage = new IMAGE_INFO;
    _blendImage->loadType = LOAD_FILE;
    _blendImage->resID = 0;
    _blendImage->hMemDC = CreateCompatibleDC(hdc);
    _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height); // 한줄조사
    _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
    _blendImage->width = WINSIZE_X;
    _blendImage->height = WINSIZE_Y;

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
    _isTrans = isTrans;
    _transColor = transColor;
}

// 특이 이미지에서는 매우 종요한 함수
void GImage::release(void)
{
    if (_imageInfo)
    {
        // 이미지를 삭제
        SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
        DeleteObject(_imageInfo->hBit);
        DeleteDC(_imageInfo->hMemDC);


        // 포인터 삭제
        SAFE_DELETE(_imageInfo);
        SAFE_DELETE_ARRAY(_fileName);

        // 투명 컬러키 초기화
        _isTrans = false;
        _transColor = RGB(0, 0, 0);

    }

    if (_blendImage)
    {
        SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
        DeleteObject(_blendImage->hBit);
        DeleteDC(_blendImage->hMemDC);

        SAFE_DELETE(_blendImage);
    }

}

// 0,0에 랜더-> 배경?
void GImage::render(HDC hdc)
{
    // 색을 뺄건지 포함할건지 조건식
    if (_isTrans)
    {
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다
        GdiTransparentBlt
        (
            hdc,                                    // 복사할 장소의 DC (화면 DC)
            0,                                      // 복사 될 좌표 시작 X
            0,                                      // 복사 될 좌표 시작 Y
            _imageInfo->width,                      // 복사 될 이미지 가로 크기
            _imageInfo->height,                     // 복사 될 이미지 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            0, 0,                                   // 복사 시작지점 0, 0
            _imageInfo->width,                      // 복사 영역 가로 크기
            _imageInfo->height,                     // 복사 영역 세로 크기
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        // ㄴ SRCCOPY : 소스 영역을 영역에 복사한다,
        BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }

}

// 시작될 좌표를 정할 수 있는 렌더
// 좌표를 찍으면서 만드는 이유는 하나 하나가 무거운 함수이기 때문에
void GImage::render(HDC hdc, int destX, int destY)
{

    if (_isTrans)
    {
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다
        GdiTransparentBlt
        (
            hdc,                                    // 복사할 장소의 DC (화면 DC)
            destX,                                  // 복사 될 좌표 시작 X
            destY,                                  // 복사 될 좌표 시작 Y
            _imageInfo->width,                      // 복사 될 이미지 가로 크기
            _imageInfo->height,                     // 복사 될 이미지 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            0, 0,                                   // 복사 시작지점 0, 0
            _imageInfo->width,                      // 복사 영역 가로 크기
            _imageInfo->height,                     // 복사 영역 세로 크기
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        // ㄴ SRCCOPY : 소스 영역을 영역에 복사한다,
        BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

// 이미지 클리핑 : 
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight)
{

    if (_isTrans)
    {
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다
        GdiTransparentBlt
        (
            hdc,                                    // 복사할 장소의 DC (화면 DC)
            destX,                                  // 복사 될 좌표 시작 X
            destY,                                  // 복사 될 좌표 시작 Y
            sourwidth,                              // 복사 될 이미지 가로 크기
            sourheight,                             // 복사 될 이미지 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            sourX, sourY,                           // 복사 시작지점 0, 0
            sourwidth,                              // 복사 영역 가로 크기
            sourheight,                             // 복사 영역 세로 크기
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        // ㄴ SRCCOPY : 소스 영역을 영역에 복사한다,
        BitBlt(hdc, destX, destY, sourwidth, sourheight,
            _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
    }
}

void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, int sizeX, int sizeY)
{

    if (_isTrans)
    {
        // GdiTransparentBlt() : 비트맵을 불러올때 특정 색상을 제외하고 복사한다
        GdiTransparentBlt
        (
            hdc,                                    // 복사할 장소의 DC (화면 DC)
            destX,                                  // 복사 될 좌표 시작 X
            destY,                                  // 복사 될 좌표 시작 Y
            sizeX,                                     // 복사 될 이미지 가로 크기
            sizeY,                                    // 복사 될 이미지 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            sourX, sourY,                           // 복사 시작지점 0, 0
            sourwidth,                              // 복사 영역 가로 크기
            sourheight,                             // 복사 영역 세로 크기
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        // ㄴ SRCCOPY : 소스 영역을 영역에 복사한다,
        BitBlt(hdc, destX, destY, sourwidth, sourheight,
            _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
    }
}

// 기본 알파 랜더 -> 원하는 위치에 그리지 않으니까 위에 랜더와 같이 배경용
void GImage::alphaRender(HDC hdc, BYTE alpha)
{
    // 알파블랜드 처음 쓰니?
    // ㄴ 사용할 수 있도록 초기화부터 진행한다
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // 1. 출력해야 될 DC에 그려져 있는 내용을 블랜드 이미지에 그린다.
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            0, 0,
            SRCCOPY        // 랜덤복사
        );

        // 2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                     // 복사할 장소의 DC (화면 DC)
            0, 0,                                     // 복사 될 좌표 시작 X
            _imageInfo->width,                              // 복사 될 이미지 가로 크기
            _imageInfo->height,                             // 복사 될 이미지 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            0, 0,
            _imageInfo->width,                              // 복사 영역 가로 크기
            _imageInfo->height,                             // 복사 영역 세로 크기
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

        // 3. 블랜드 이미지를 화면에 그린다.
        AlphaBlend
        (
            hdc,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendFunc
        );


    }

    else
    {
        // 트랜스를 안하니까 그냥 알파블랜드 출력
        // 트랜스가 없어 블랜드처리를 안해줬기 때문이 기본 이미지 메모리 DC를 가져와야 한다.
        AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
}


// 위치값이 필요한 애들한테 쓸 수 있다 -> ex) 플레이어
void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // 1. 출력해야 될 DC에 그려져 있는 내용을 블랜드 이미지에 그린다.
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY        // 랜덤복사
        );

        // 2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                     // 복사할 장소의 DC (화면 DC)
            0, 0,                                     // 복사 될 좌표 시작 X
            _imageInfo->width,                              // 복사 될 이미지 가로 크기
            _imageInfo->height,                             // 복사 될 이미지 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            0, 0,
            _imageInfo->width,                              // 복사 영역 가로 크기
            _imageInfo->height,                             // 복사 영역 세로 크기
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

        // 3. 블랜드 이미지를 화면에 그린다.
        AlphaBlend
        (
            hdc,
            destX, destY,
            _imageInfo->width,
            _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            _blendFunc
        );
    }

    else
    {
        // 트랜스를 안하니까 그냥 알파블랜드 출력
        // 트랜스가 없어 블랜드처리를 안해줬기 때문이 기본 이미지 메모리 DC를 가져와야 한다.
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }

}

void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunc.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // 1. 출력해야 될 DC에 그려져 있는 내용을 블랜드 이미지에 그린다.
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width,
            _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY        // 랜덤복사
        );

        // 2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다.
        GdiTransparentBlt
        (
            _blendImage->hMemDC,                    // 복사할 장소의 DC (화면 DC)
            0, 0,                                   // 복사 될 좌표 시작 X
            _imageInfo->width,                      // 복사 될 이미지 가로 크기
            _imageInfo->height,                     // 복사 될 이미지 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            0, 0,
            _imageInfo->width,                      // 복사 영역 가로 크기
            _imageInfo->height,                     // 복사 영역 세로 크기
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

        /*
            hdc,
            destX,
            destY,
            sourwidth,
            sourheight,
            _imageInfo->hMemDC,
            sourX, sourY,
            sourwidth,
            sourheight,
            _transColor
        */

        // 3. 블랜드 이미지를 화면에 그린다.
        AlphaBlend
        (
            hdc,                              // 출력할 장소의 DC (화면 DC)      
            destX, destY,                     // 출력할 좌표 시작 X ,Y -> 원본 이미지의 시작점
            sourwidth,                        // 출력할 이미지 가로 크기
            sourheight,                       // 출력할 이미지 세로 크기
            _blendImage->hMemDC,              // 출력 할 블랜드 메모리 DC
            sourX, sourY,                     // 복사를 원하는 시작 좌표 SourX, SourY
            sourwidth, sourheight,            // 출력을 원하는 이미지의 가로, 세로 크기
            _blendFunc                        // 알파값
        );
    }

    else
    {
        // 트랜스를 안하니까 그냥 알파블랜드 출력
        // 트랜스가 없어 블랜드처리를 안해줬기 때문이 기본 이미지 메모리 DC를 가져와야 한다.
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
}

void GImage::frameRender(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                                    // 복사할 장소의 DC (화면 DC)
            destX,                                  // 복사 될 좌표 시작 X
            destY,                                  // 복사 될 좌표 시작 Y
            _imageInfo->frameWidth,                 // 복사 될 이미지 1프레임의 가로 크기
            _imageInfo->frameHeight,                // 복사 될 이미지 1프레임의 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            _imageInfo->currentFrameX * _imageInfo->frameWidth,              // 복사의 프레임 시작 지점
            _imageInfo->currentFrameY * _imageInfo->frameHeight,              // 복사의 프레임 시작 지점
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );
    }
    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        // ㄴ SRCCOPY : 소스 영역을 영역에 복사한다,
        BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
    }
}

void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    // 이미지 예외처리
    _imageInfo->currentFrameX = currentFrameX;
    _imageInfo->currentFrameY = currentFrameY;

    if (currentFrameX > _imageInfo->maxFrameX)
    {
        _imageInfo->currentFrameX = _imageInfo->maxFrameX;
    }

    if (currentFrameY > _imageInfo->maxFrameY)
    {
        _imageInfo->currentFrameY = _imageInfo->maxFrameY;
    }

    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,                                    // 복사할 장소의 DC (화면 DC)
            destX,                                  // 복사 될 좌표 시작 X
            destY,                                  // 복사 될 좌표 시작 Y
            _imageInfo->frameWidth,                 // 복사 될 이미지 1프레임의 가로 크기
            _imageInfo->frameHeight,                // 복사 될 이미지 1프레임의 세로 크기
            _imageInfo->hMemDC,                     // 복사 될 대상 메모리 DC
            _imageInfo->currentFrameX * _imageInfo->frameWidth,              // 복사의 프레임 시작 지점
            _imageInfo->currentFrameY * _imageInfo->frameHeight,              // 복사의 프레임 시작 지점
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor                             // 복사 할때 제외할 색상 (등록된 컬러 = 마젠타 색상)
        );

    }

    else
    {
        // ◈ BitBlt() : DC간의 영역끼리 서로 고속 복사를 해준다.
        // ㄴ SRCCOPY : 소스 영역을 영역에 복사한다,
        BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
    }
}

void GImage::setTransImage(const char* fileName)
{
    int len = strlen(fileName);

    _fileName = new char[len + 1];

    strcpy_s(_fileName, len + 1, fileName);
}

// 잘쓰면 카메라가 편해질 수 있다.
void GImage::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
    // offset 값이 음수 인 경우 보정 작업
    if (offsetX < 0)
    {
        offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
    }

    if (offsetY < 0)
    {
        offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
    }

    // 그려질 복사 영역 세팅 -> 이동할 다음 위치의 맵을 미리 복사
    RECT rcSour;
    int sourWidth;
    int sourHeight;

    // 그려지는 DC 영역 (화면 크기)
    RECT rcDest;

    // 렉트 인자값을 포인터로 받아오기 때문에 값을 받아서 사용한다
    // 그려야 할 전체 영역
    int drawAreaX = drawArea->left;
    int drawAreaY = drawArea->top;
    int drawAreaW = drawArea->right - drawArea->left;
    int drawAreaH = drawArea->bottom - drawArea->top;

    // 세로 루프
    for (int y = 0; y < drawAreaH; y += sourHeight)
    {
        // 소스 영역의 높이 계산
        rcSour.top = (y + offsetY) % _imageInfo->height;
        rcSour.bottom = _imageInfo->height;
        sourHeight = rcSour.bottom - rcSour.top;


        // 예외 처리 소스의 역역이 그리는 화면을 넘어갔다면 (화면 밖으로 나갔다면)
        if (y + sourHeight > drawAreaH)
        {
            // 화면이 넘어간 만큼 바텀값을 되돌려준다 -> 화면을 이전 상태로 리셋
            rcSour.bottom -= (y + sourHeight) - drawAreaH;
            sourHeight = rcSour.bottom - rcSour.top;
        }

        // 그려질 영역 세팅
        rcDest.top = y + drawAreaY;
        rcDest.bottom = rcDest.top + sourHeight;

        // 가로 루프
        for (int x = 0; x < drawAreaW; x += sourWidth)
        {
            // 소스 영역의 높이 계산
            rcSour.left = (x + offsetX) % _imageInfo->width;
            rcSour.right = _imageInfo->width;
            sourWidth = rcSour.right - rcSour.left;


            // 예외 처리 소스의 역역이 그리는 화면을 넘어갔다면 (화면 밖으로 나갔다면)
            if (x + sourWidth > drawAreaW)
            {
                // 화면이 넘어간 만큼 바텀값을 되돌려준다 -> 화면을 이전 상태로 리셋
                rcSour.right -= (x + sourWidth) - drawAreaW;
                sourWidth = rcSour.right - rcSour.left;
            }

            // 그려질 영역 세팅
            rcDest.left = x + drawAreaX;
            rcDest.right = rcDest.left + sourWidth;

            render(hdc, rcDest.left, rcDest.top,
                rcSour.left, rcSour.top,
                sourWidth, sourHeight);

        }
    }
}

void GImage::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{

}

// 더블 버퍼와 백버퍼가 있다

/*
한줄조사
CreateCompatibleDC(hdc)
CreateCompatibleBitmap(hdc, width, height)
LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID))

*/