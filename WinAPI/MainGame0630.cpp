#include "stdafx.h"
#include "MainGame0630.h"

HRESULT MainGame0630::init(void)
{
	GameNode::init(true);

	IMAGEMANAGER->addImage("���彺���̽�", "Resource/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);

	_alphaA = 255;
	
	return S_OK;
}

void MainGame0630::release(void)
{
	GameNode::release();

}

// ������ ©�� ������Ʈ�� �����ϸ� �������� �۾��Ұ�? -> �߻����غ���
void MainGame0630::update(void)
{
	GameNode::update();
}

void MainGame0630::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	IMAGEMANAGER->alphaRender("���彺���̽�", getMemDC(), _alphaA);

	this->getBackBuffer()->render(getHDC());
}


/*
���� 1. ĳ���� �����

- �̹��� �ʼ�: ���, ��, ĳ����(���, �̵�, ����, ����� �ִ� ���)

- �⺻������ ���� ���� ���� ���� ���� �𼭸��� ������ �� �߰��� ���� ��� õõ�� �������� �����´�.

- ĳ���Ͱ� ���� ��� �ִ� ���¿��� ��/ �Ǵ� �Ʒ� ����Ű�� ������ �ö󰡰ų� �������� �־�� �Ѵ�.

- ���� ĳ���Ͱ� �� ���� �ö� ���� �ٽ� �Ʒ��� �����ϸ� ĳ���ʹ� ���鿡 ���� �� �� �־�� �Ѵ�.

- ĳ���� ���� ������ ������ �ְ� ĳ���ʹ� ���� �ؿ��� ������ ���� ���� �ö� �� �� �ִ�.

- ĳ���ʹ� ������ �ö� ���¿��� �������� �ٽ� ������ �� ������ OK

���� 2. �̴ϸ� ����

- �÷��̾��� �������� �̴ϸʿ��� �״�� Ȯ���ؾ� �Ѵ�.

- �����ӱ��� �����ϰ�

*/