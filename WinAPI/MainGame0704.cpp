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

과제 1. 포폴 PPT 작성

- 발표일은 아직 미정

- 디테일하게 + 깔끔하게

과제 2. 블랙홀

- 무작위로 생성되는 오브젝트 객체
- 그리고 주변 오브젝트를 빨아들이는 블랙홀을 만든다.
ㄴ 블랙홀은 조작을 통해 움직일 수 있다.
- 오브젝트가 생성되는 위치를 알기 위해 표시를 한다.
- EX : 색 / 이미지/ 크기

- 필수 : STL 벡터 or 리스트를 써서 진행
- tip. 역삼각함수

*/