#include "Stdafx.h"
#include "MainGame0705.h"

HRESULT MainGame0705::init(void)
{
    GameNode::init(true);

    // 메인 퍼즐 이미지 초기화
    // IMAGEMANAGER->addImage("데드 스페이스", "Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
    // (이미지 경로, 사이즈, 최대 사이즈 MaxX, MaxY , X갯수, Y갯수)

    _alphaA = 255;

    _start = new StartScene;
    _start->init();

    _second = new SecondScene;
    _second->init();

    // _currentScene -> 시동이 안되면 그냥 실행 자체가 안된다 -> 굳이 돌려볼 필요도 없다 (절대 안됨)
    _currentScene = _start;

    // _crruentScene가 비어 있으면 실행이 안되게 예외처리

    // <->      assert를 구분하기 위한 부호 -> 완성후 나중에 없애기 위해서
    assert(_currentScene != nullptr, "MainGame 초기화 부분에서 노드 파트 오류 발생"); // 뒤에 협업자가 알기 쉽게 오류가 발생한 위치를 적어준다

    // C++
    // static_assert()

    /*
    ▶ assert 에러 검출용 매크로 함수 (C언어) -> 사용을 위해서는 assert 헤더파일을 따로 포함해야한다

    - 디버깅 모드에서 동작하는 오류 검출용 함수
    ㄴ 릴리즈 모드에서는 동작하지 않는다.

    - assert 함수에 걸리게 되면 버그 발생 위치 / 콜 스택들 여러 정보를 알 수 있다.
       ㄴ Expression -> false -> assert error 루틴?

    - 대부분의 문법이 true 일때만 동작하지만 assert()는 거짓일때 동작을 한다.
       ㄴ 그렇기 때문에 일어나면 안되는 조건이 아니라 꼭 일어나야 하는 조건을 명시해야 한다.

    EX) assert(A != NULL);
       ㄴ A가 NULL이 아니면 true가 나오게 되면 패스
       ㄴ A가 NULL이 맞다면 false 가 나오기 되므로 assert error에 걸린다.


    assert()      :   "C"     : 컴파일 타임을 지나 프로그램을 실행시키고 문제를 파악하겠다
    static_assert() :   "C++" : 컴파일 중에 문제를 파악하겠다 -> 상수 값을 넣어야한다

    assert 를 사용하기 위해서는 최상위가 있는지 생각해봐야한다 -> 왜??

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

과제 1. 캐릭터 공격 및 방어

- 이미지 -> 체력바, 플레이어(대기, 공격, 방어) / 적 (대기, 공격, 피격)
- 기본형식은 대전게임처럼 좌/ 우로 배치
ㄴ 체력바

- 플레이어는 공격및 방어를 할 수 있고 적은 공격 및 피격 모션이 존재

ㄴ 적 : 허수아비

- 플레이어는 상시 조정 - 적은 공격에 on/off 기능만

- 공격이나 방어 피격 등이 발생하면 상황에 맞는 결과를 화면에 렌더링 한다.
ㄴ막기, 빗나감, 치명타 등

- 데미지도 표기한다.
ㄴ 컨버팅 할 수 있으면 한다.

*/

