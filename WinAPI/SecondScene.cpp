#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
    IMAGEMANAGER->addImage("배경 루프", "Resources/Images/BackGround/BackGroundImage.bmp", 1570, WINSIZE_Y);
    //IMAGEMANAGER->addImage("트랙", "Resources/Images/BackGround/RacingTrack.bmp", WINSIZE_X, 650);
    // SetBkMode : 텍스트 버퍼등을 투명하게 해주는 함수
    // SetBkMode(getMemDC(), TRANSPARENT);

    _alphaA = 0;
    _isAlphaIncrese = false;

    _offsetX = _offsetY = 0;
    _bgSpeed = 0;

    return S_OK;

}

void SecondScene::release(void)
{
}

void SecondScene::update(void)
{
    _bgSpeed += 4;
}

void SecondScene::render(void)
{

    IMAGEMANAGER->loopRender("배경 루프", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);
    //IMAGEMANAGER->loopRender("트랙", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), 0, _bgSpeed);

    // 기존 텍스트
    char str[128];
    wsprintf(str, "기존");
    TextOut(getMemDC(), 230, 350, str, strlen(str));

    // 새로운 방식
    HFONT font;
    HFONT oldFont;

    /* v표 친것들은 우리가 자주 쓸것들 -> 정확도 질은 조건식으로 세팅할것임
    font = CreateFont
    (
       v문자크기, 문자폭, 전체 기울기, 문자 방향, v문자 굵기,
       기울기 적용여부(T/F), 밑줄 적용여부(T/F), 취소선,
       v문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
    );
    */

    font = CreateFont
    (
        70, 0, 0, 0, 600,
        0, 0, 1,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림")
    );

    oldFont = (HFONT)SelectObject(getMemDC(), font);
    wsprintf(str, "새로운폰트");
    TextOut(getMemDC(), 100, 400, str, strlen(str));

    SelectObject(getMemDC(), oldFont);
    DeleteObject(font);


}