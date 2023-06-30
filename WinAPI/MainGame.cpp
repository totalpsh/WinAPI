#include "Stdafx.h"
#include "MainGame.h"

// STL 꼭 써보자


/*
이미지 크기의 기준은 애니메이션 동작 중 제일 큰 이미지에 맞춘다 -> 최대 프레임 x,y값이 있기 때문
애니메이션에 첫 이미지 미리 작업해둘것
세팅 다 했을때 백업용 이미지 저장해둘것 -> 1픽셀 실수 했을수도 있음


*/
HRESULT MainGame::init(void)
{
	GameNode::init();

	// 메인 퍼즐 이미지 초기화
	_slImage = new GImage;
	//_slImage->init("Resources/Images/Object/Tekken8.bmp", 450, 450, true, RGB(255, 0, 255));

	_nine = new GImage;
	//_nine->init("Resources/Images/Object/Nine.bmp", WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200, ? , ? , ? , ?, true, RGB(255, 0, 255));

	// 제로 공격
	_zero_attack1 = new GImage;
	_zero_attack1->init("Resources/Images/Character/zero_attack_first.bmp", 1092, 126, 12, 2, true, RGB(255, 0, 255));
	//init(const char* fileName, float x, float y, int width, int height
	//	,int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	_zero_attack2 = new GImage;
	//_zero_attack2->init("Resources/Images/Character/zero_attack_second.bmp", 1160, 92, true, RGB(255, 0, 255));

	_zero_attack3 = new GImage;
	//_zero_attack3->init("Resources/Images/Character/zero_attack_third.bmp", 1368, 142, true, RGB(255, 0, 255));




	// (이미지 경로, 사이즈, 최대사이즈 MaxX, MaxY , X갯수, Y갯수)
	_alphaA = 0;
	_count = _index = 0;
	_isLeft = false;
	_isAttack = false;
	_isAlphaIncrese = false;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_slImage);
	SAFE_DELETE(_nine);
	SAFE_DELETE(_zero_attack1);
	SAFE_DELETE(_zero_attack2);
	SAFE_DELETE(_zero_attack3);
}

// 로직을 짤때 업데이트는 웬만하면 마지막에 작업할걸? -> 잘생각해볼것
void MainGame::update(void)
{
	GameNode::update();

	// 무작위 랜덤으로 배치를 하면 완성이 안되는 퍼즐이 만들어질 때도 있어서 직접 섞는다
	// 랜덤으로 섞는 과정 MIXCOUNT번까지 반복 -> COUNT가 높을 수록 깊은 swap이 일어난다

	// 종료 키
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}

	// 키 입력
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_nine->setX(_nine->getX() - 8.0f);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_nine->setX(_nine->getX() + 8.0f);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isAttack = true;
	}

	/*if (_isAttack && _isLeft)
	{
		_count++;

		_zero_attack1->setFrameY(1);

		if (_count % 3 == 0 )
		{
			_index--;

			if (_index < 0)
			{
				_index = 12;
			}

			_zero_attack1->setFrameX(_index);
		}
	}*/

	if (_isLeft)
	{
		_count++;

		_zero_attack1->setFrameY(1);		// 왼쪽 이동 애니메이션이 몇번째 줄에 있냐?

		if (_count % 3 == 0)
		{
			_index--;

			if (_index < 0)
			{
				_index = 12;
			}
			_zero_attack1->setFrameX(_index);
		}
	}

	else
	{
		_count++;
		_zero_attack1->setFrameY(0);

		if (_count % 3 == 0)
		{
			_index++;

			if (_index > 12)
			{
				_index = 0;
			}
			_zero_attack1->setFrameX(_index);
		}
	}

}

void MainGame::render(HDC hdc)
{

	HDC memDC = this->getDoubleBuffer()->getMemDc();
	//============================================================================
	// 당분간 터치하지말것
	//PatBlt() : 사각형 안에 영역을 브러쉬로 채우는 함수
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	//============================================================================

	_zero_attack1->frameRender(memDC, _zero_attack1->getX(), _zero_attack1->getY());

	this->getDoubleBuffer()->render(hdc, 0, 0);

}



/*

 - 주말 과제 제출

 ㄴ 언리얼 1기_얼굴 그리기_박성한
 ㄴ 내일 오전 9시
 ㄴ 오늘 과제 포함해서

 과제1. 똥 피하기

 - 시작 버튼을 누르면서 게임 시작
 - 게임이 시작 되고 플레이억 ㅏ죽을 때까지 버틴 시간을 화면에 출력한다.
 - 필수 : 재시작 + 다시하기
 - 플레이어는 사람 모양으로 좌우 모양이 다르게 구현


 과제 2. 총알 발사

 - 하단에서 좌우로 움직일 수 있는 플레이어가 존재

 - 스페이스바를 누르면 플레이어가 총알을 발사한다.


 과제 3. 악어 이빨 게임

 -악어 이빨 게임은최소 8개 이상

 - 악어 이빨에 물렸는지 아닌지에 대해서 확인이 가능해야 한다.

 - 필수 : 악어이빨이 닫히는 애니매이션 구현


*/

/* 06.20

과제 1. 종스크롤 슈팅 게임

- 플레이어 체력바 설정
ㄴ 적과 충돌 시 체력 감소 체력바 3단계 처리
ㄴ 빨 / 주 / 초

- 플레이어가 발사하는 총알로 적을 제거

과제 2. 1 vs 1횡스크롤 슈팅

- 외쪽에 1P 오른쪽에 2P
-  체력바는 대전게임 처럼 중앙을 기준으로 좌우 배치
ㄴ 체력바 초 노 빨

- 공격당하면 감소
- 필수 요소 스킬 구현  = 4개
아이템 2종 구현



*/

/*
이미지 추가 과제 1. 두더지 게임

- 상황에 맞는 이미지를 필수적으로 적용한다.

- 두더지가 없을때/ 나왔을때 /때렸을때 /망치(대기, 때렸을때)

- 마우스 커서는 ShowCursor()를 활용한다.

과제 1. 틀린 그림 찾기
 - 이미지는 포토샵 편집 검색으로 처리한다.
 - 스테이지는 총 두개의 스테이지
 ㄴ 틀린곳 다섯곳 이상
 - 게임 시작 되면 타임 게이지가 줄어들고 오답일때 게이지 감소
 - 정답일경우 시간 증가
 - 타임 게이지가 모두 소진 되면 타임오버 메세지를 화면에 띄우며 게임 종료

과제 3. 포토샵 설치

- CS6 썰쮜

- 각 버전마다 기능이 매우 상이하거나 단축키가 다르다.

*/


/* 06.23
과제 1. 아날로그 시계

- 초침 분침 시침

- 오늘 사용한 SYSTEMTIME을 이용해서 만든다.

- 필수 : 시간 표시

과제 2. 포신 각도에 따른 총알 박사

예외 처리 : 포신 앵글을 막아준다. -> 화면 밖으로 안나가게

- 필수 요소 : 수동 / 자동 -> 2가지

과제 3. 발사된 총알끼리 충돌

- 핵심 요소는 총알 끼리 충돌 되면 자연스러게 튕겨 나가야 한다.

- 역삼각함수 사용하면 좋다.

과제 4. 발사한 총알에 중력 적용

- 총알이 중력을 받아 떨이진다. -> 힘이 다하면


발사된 총알 예외 처리
ㄴ 4번과제 제외

발사된 총알은 화면 밖으로 못나가
ㄴ 주의 사항 : 발사된 총알이 화면 끝점에 닿아 튕겨 나갈때 각도에 신경쓴다.

도전과제 1. 도형 회전

- 사각형 회전
- hdc를 통해 그려온다.
ㄴ winapi를 통해 구현
ㄴ Rantangle 함수

- 화면축이 바뀐 상태면 상대 좌표로 이동하게 구현


*/

/* 06.26
씨이이이이이이ㅣ이이이이발 좀 적당히 내주세요오오ㅗ오오ㅗ오오오ㅗ오오ㅗ오오ㅗ오오오ㅗ오오오오ㅗ오오ㅗㅇ

과제0. 포트폴리오 선행작업

과제 1. 슬라이스 게임

- 치트 필수
ㄴ 1개의 퍼즐을 제외하고 나머지는 정렬
ㄴ 플레이어가 남은 1개를 맞추면서 종료되는 구조

- 화면 왼쪽에 원손 사진 출력 < - > 화면 오른쪽에는 9등분된 이미지 출력

- 9등분 된 이미지 제일 아래 오른쪽 칸이 시작칸

- 퍼즐이 완성 되면 알파 블렌딩 효과로 이미지가 나타난다.
ㄴ 중앙에서 완성된 이미지를 보여주면 된다.

과제 2. 미니맵 만들기
씨발 살려줘 제발

- 플레이어의 움직임을 미니맵에서도 확인 할 수 있어야 한다.

- 2가지 버전

- 화면에 표시되는 작은 GUI형태의 미니맵
- 화면위에 그려지는 전체화면 미니맵


살려줘......



*/

/* 06. 27

과제 1. 지렁이 만들기
 - 지렁이는 구슬이 꼬리를 물고 이어지는 형태
 ㄴ 각 구슬마다 번호를 표기한다.

 - 지렁이는 화면 밖의 무작위 위치에서 등장을 한다.

 - 특별한 키 입력이 없어도 지령이는 화면안에서 움직인다.

 - 벽에 부딪히면 튕겨 나가야 하고 왼쪽/ 오른쪽 방향키로 조조이 가능해야 함.

 - 따라오는 구슬은 머리가 방항을 튼다고 같이 틀면 안되고 머리가 있던 위치까지
 와서 방향을 전환한다.

 - 임의의 숫자가 표시된 아이템이 게임이 시작되면 생성되고 지렁이가 아이템을
 먹으면 해당하는 번호의 지렁이 구슬이 커진다.

 - 얼마나 자연스러운지가 핵심

 - 못해도 50개
*/

/*

23.06.29

과제1. 제로 3단 콤보 이미지 깔끔하게 만들어오기

- 스페이스 바를 누르면 1타부터 -> 마지막 공격까지 자동으로 재생
ㄴ 무한 반복

과제2. 프레임 이미지 처리?

- 시작 씬 + 게임 씬

- 게임 씬에서는 아래의 이미지를 GUI화 시켜서 재생 시킨다.(버튼) -> 캐릭터의 모션 구경하는 화면을 만들어라
ㄴ 프레임 랜더

- 필수 이미지
ㄴ 배경, 대기, 이동(좌+우), 찌르기(좌+우), 대각선 찌르기, 연속 찌르기(좌+우)
ㄴ 원 돌리기(원을 돌릴때 중점을 잘 잡고 이미지 범위를 정해서 잘림을 방지하는 연습), 승리포즈(옷 던지기), 스킬 클라이막스 연출(어떤 캐릭터가 스킬을 썻는지 보여주는 그런 장면), 패배



*/