#include "Stdafx.h"
#include "MainGame0704.h"

HRESULT MainGame0704::init(void)
{
    GameNode::init(true);

    return S_OK;
}

void MainGame0704::release(void)
{
    GameNode::release();
   
}

void MainGame0704::update(void)
{
    GameNode::update(); 


}

void MainGame0704::render(void)
{

}


/*

���� 1. ���� PPT �ۼ�

- ��ǥ���� ���� ����

- �������ϰ� + ����ϰ�

���� 2. ��Ȧ

- �������� �����Ǵ� ������Ʈ ��ü
- �׸��� �ֺ� ������Ʈ�� ���Ƶ��̴� ��Ȧ�� �����.
�� ��Ȧ�� ������ ���� ������ �� �ִ�.
- ������Ʈ�� �����Ǵ� ��ġ�� �˱� ���� ǥ�ø� �Ѵ�.
- EX : �� / �̹���/ ũ��

- �ʼ� : STL ���� or ����Ʈ�� �Ἥ ����
- tip. ���ﰢ�Լ�

*/