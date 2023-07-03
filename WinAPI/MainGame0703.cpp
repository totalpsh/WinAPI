#include "Stdafx.h"
#include "MainGame0703.h"

HRESULT MainGame0703::init(void)
{
	GameNode::init(true);

	//IMAGEMANAGER->addFrameImage("데드스페이스", "Resource/Images/BackGround/DeadSpace.bmp", WINSIZE_X / 2, WINSIZE_Y / 2);

	IMAGEMANAGER->addImage("배경 루프", "Resource/Images/BackGround/loop.bmp", 1570, WINSIZE_Y);

	_alphaA = 0;
	_isAlphaIncrease = false;

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	return S_OK;
}

void MainGame0703::release(void)
{
	GameNode::release();
}

void MainGame0703::update(void)
{
	GameNode::update();

	_bgSpeed += 4;
}

void MainGame0703::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	IMAGEMANAGER->loopRender("배경 루프", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);

	this->getBackBuffer()->render(getHDC());
}


/*
 과제 1. 레이싱 게임

  - 이미지 필수 구축 : 배경 + 자동차 (플레이어 + 적) + 계기판
  - 계기판은 차 속력에 따라 변환을 해야하고 최저 속도와 최대속도를 예외처리한다.
  - 중요한건 스피드감이 느껴져야 한다.
  - 점수 시스템 구현
  - + 스킬 3개 구현
  ㄴ 1. 보호막
  ㄴ 2. @
  ㄴ 3. 홍해가르기

  - 전자 계기판은 사망


*/