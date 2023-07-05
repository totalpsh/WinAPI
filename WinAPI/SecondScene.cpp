#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
    IMAGEMANAGER->addImage("��� ����", "Resources/Images/BackGround/BackGroundImage.bmp", 1570, WINSIZE_Y);
    //IMAGEMANAGER->addImage("Ʈ��", "Resources/Images/BackGround/RacingTrack.bmp", WINSIZE_X, 650);
    // SetBkMode : �ؽ�Ʈ ���۵��� �����ϰ� ���ִ� �Լ�
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

    IMAGEMANAGER->loopRender("��� ����", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);
    //IMAGEMANAGER->loopRender("Ʈ��", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), 0, _bgSpeed);

    // ���� �ؽ�Ʈ
    char str[128];
    wsprintf(str, "����");
    TextOut(getMemDC(), 230, 350, str, strlen(str));

    // ���ο� ���
    HFONT font;
    HFONT oldFont;

    /* vǥ ģ�͵��� �츮�� ���� ���͵� -> ��Ȯ�� ���� ���ǽ����� �����Ұ���
    font = CreateFont
    (
       v����ũ��, ������, ��ü ����, ���� ����, v���� ����,
       ���� ���뿩��(T/F), ���� ���뿩��(T/F), ��Ҽ�,
       v���� ����, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
    );
    */

    font = CreateFont
    (
        70, 0, 0, 0, 600,
        0, 0, 1,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���")
    );

    oldFont = (HFONT)SelectObject(getMemDC(), font);
    wsprintf(str, "���ο���Ʈ");
    TextOut(getMemDC(), 100, 400, str, strlen(str));

    SelectObject(getMemDC(), oldFont);
    DeleteObject(font);


}