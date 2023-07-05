#include "Stdafx.h"
#include "MainGame0705.h"

HRESULT MainGame0705::init(void)
{
    GameNode::init(true);

    // ���� ���� �̹��� �ʱ�ȭ
    // IMAGEMANAGER->addImage("���� �����̽�", "Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
    // (�̹��� ���, ������, �ִ� ������ MaxX, MaxY , X����, Y����)

    _alphaA = 255;

    _start = new StartScene;
    _start->init();

    _second = new SecondScene;
    _second->init();

    // _currentScene -> �õ��� �ȵǸ� �׳� ���� ��ü�� �ȵȴ� -> ���� ������ �ʿ䵵 ���� (���� �ȵ�)
    _currentScene = _start;

    // _crruentScene�� ��� ������ ������ �ȵǰ� ����ó��

    // <->      assert�� �����ϱ� ���� ��ȣ -> �ϼ��� ���߿� ���ֱ� ���ؼ�
    assert(_currentScene != nullptr, "MainGame �ʱ�ȭ �κп��� ��� ��Ʈ ���� �߻�"); // �ڿ� �����ڰ� �˱� ���� ������ �߻��� ��ġ�� �����ش�

    // C++
    // static_assert()

    /*
    �� assert ���� ����� ��ũ�� �Լ� (C���) -> ����� ���ؼ��� assert ��������� ���� �����ؾ��Ѵ�

    - ����� ��忡�� �����ϴ� ���� ����� �Լ�
    �� ������ ��忡���� �������� �ʴ´�.

    - assert �Լ��� �ɸ��� �Ǹ� ���� �߻� ��ġ / �� ���õ� ���� ������ �� �� �ִ�.
       �� Expression -> false -> assert error ��ƾ?

    - ��κ��� ������ true �϶��� ���������� assert()�� �����϶� ������ �Ѵ�.
       �� �׷��� ������ �Ͼ�� �ȵǴ� ������ �ƴ϶� �� �Ͼ�� �ϴ� ������ ����ؾ� �Ѵ�.

    EX) assert(A != NULL);
       �� A�� NULL�� �ƴϸ� true�� ������ �Ǹ� �н�
       �� A�� NULL�� �´ٸ� false �� ������ �ǹǷ� assert error�� �ɸ���.


    assert()      :   "C"     : ������ Ÿ���� ���� ���α׷��� �����Ű�� ������ �ľ��ϰڴ�
    static_assert() :   "C++" : ������ �߿� ������ �ľ��ϰڴ� -> ��� ���� �־���Ѵ�

    assert �� ����ϱ� ���ؼ��� �ֻ����� �ִ��� �����غ����Ѵ� -> ��??

    */

    return S_OK;
}

void MainGame0705::release(void)
{
    GameNode::release();

    SAFE_DELETE(_start);
    SAFE_DELETE(_second);

}

void MainGame0705::update(void)
{
    GameNode::update();

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _currentScene = _second;
    if (KEYMANAGER->isOnceKeyDown(VK_BACK)) _currentScene = _start;

}

void MainGame0705::render(void)
{
    PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

    _currentScene->render();

    this->getBackBuffer()->render(getHDC());
}

/*

���� 1. ĳ���� ���� �� ���

- �̹��� -> ü�¹�, �÷��̾�(���, ����, ���) / �� (���, ����, �ǰ�)
- �⺻������ ��������ó�� ��/ ��� ��ġ
�� ü�¹�

- �÷��̾�� ���ݹ� �� �� �� �ְ� ���� ���� �� �ǰ� ����� ����

�� �� : ����ƺ�

- �÷��̾�� ��� ���� - ���� ���ݿ� on/off ��ɸ�

- �����̳� ��� �ǰ� ���� �߻��ϸ� ��Ȳ�� �´� ����� ȭ�鿡 ������ �Ѵ�.
������, ������, ġ��Ÿ ��

- �������� ǥ���Ѵ�.
�� ������ �� �� ������ �Ѵ�.

*/

