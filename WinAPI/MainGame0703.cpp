#include "Stdafx.h"
#include "MainGame0703.h"

HRESULT MainGame0703::init(void)
{
	GameNode::init(true);

	//IMAGEMANAGER->addFrameImage("���彺���̽�", "Resource/Images/BackGround/DeadSpace.bmp", WINSIZE_X / 2, WINSIZE_Y / 2);

	IMAGEMANAGER->addImage("��� ����", "Resource/Images/BackGround/loop.bmp", 1570, WINSIZE_Y);

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

	IMAGEMANAGER->loopRender("��� ����", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);

	this->getBackBuffer()->render(getHDC());
}


/*
 ���� 1. ���̽� ����

  - �̹��� �ʼ� ���� : ��� + �ڵ��� (�÷��̾� + ��) + �����
  - ������� �� �ӷ¿� ���� ��ȯ�� �ؾ��ϰ� ���� �ӵ��� �ִ�ӵ��� ����ó���Ѵ�.
  - �߿��Ѱ� ���ǵ尨�� �������� �Ѵ�.
  - ���� �ý��� ����
  - + ��ų 3�� ����
  �� 1. ��ȣ��
  �� 2. @
  �� 3. ȫ�ذ�����

  - ���� ������� ���


*/