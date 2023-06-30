#pragma once
#include "GameNode.h"
#include "MOLE.h"
//#define _USE_MATH_DEFINES
//#include "math.h"
//
//#define PI 3.141592653f
//
//// 각도 표기 -> 라디안 표기 변환
//#define DEGREE_PADIAN(_deg)			(M_PI* (_deg) / 180.0f)

struct STAR
{
	int x;
	int y;
};



// 설계 연습 
// 똥피하기 + 총쏘기
//define -> 상수화를 시킬 무언가를 떠올려라
// 상수화를 컴파일타임? 런타임?
// 배열을 떠올려보자  ->  확장(STL)
// STL이 들어가면 코드가 완전히 바뀐다.
// 객체 자체가 미비하다.
#define BULLET_MAX 10
#define PLAYER_SPEED 5
// STL x -> 데이터의 양이 많이 않다.
// 적객체의 속성을 고려해봐야 한다.
// 단일? 이미지를 덧씌은다.
// 만약에 객체에 애니매이션이 입혀진다면 메모리사용량이 높아진다. 그러면 STL -> O
// 꼭 고민을 해보자!
#define ENEMY_MAX 80

//====================================================================================================================================

// 객체 지향 프로그래밍 -> 설계의 기반한 효율적인 방법론과 관리 체계

/* 생각해볼 문제
 과제가 두더지.....

 1. 두더지 + 맵  객체
 ㄴ 클래스 분할...?
	ㄴ 상속? / 클래스는 몇개? / STL이 필요할까?
	(대부분 개념이 STL에 있다. -> 들어가면 좋은가 안좋은가에 대한 판단을 해보자 => 그리고 웬만하면 많이 써보자)
	(상속 --> 정말 많이 생각해보고 사용해보자(정말 상속을 해야 하는가? -> 프레임워크에서 상속 없이 엮어줄 수 있는가? 많이 고민해보고 사용하자))
 ㄴ 연결이 매끄럽지 못하다..? => 아직 프레임워크에 대한 이해가 부족함.

 2. 체계(열거 / 클래스 / 구조체) - 확장성과 유지보수
 1번에서 여러 설계를 해보고 난뒤에는 항상 열거/클래스/구조체를 생각해보고 선행되어야 한다.
 -> 재사용성과 확장성 생산성을 올릴 수 있다.
 -> 여러 많은 생각을 논리적으로 해본다.

 두더지
 ㄴ 클래스 , 구조체 , 열거형 -> 어떤게 효율적일까? 나열이 되기 때무에 열거형을 사용할 것이다. (과제 할땐 내맘데로해라)
 ㄴ 그럼 정했다면 컨테이너를 무엇을 써야 할까?
 ㄴ STL을 설게하고 구조적으로 접근을 할수 있곘끔 해야 한다.

 3. 구체화
	ㄴ PCH / 함수 -> 로직 구현
	
	위의 항목을 기반으로 해야 객체지향을 구현할 수 있다.

	MOLE 은 동적으로 생성된다.
*/

//enum CURRENT_RECT : UINT8 // 모호함이 발생 할 수 있는지 생각해보고 enum class로 명시할지 고민해보자.
//{
//	CURRENTRECT_A,
//	CURRENTRECT_B,
//	CURRENTRECT_C,
//	CURRENTRECT_D,
//	CURRENTRECT_E,
//	CURRENTRECT_F,
//	CURRENTRECT_G,
//	CURRENTRECT_H,
//	CURRENTRECT_NULL
//};

//struct tagEnemy
//{
//	RECT rc;
//	int speed;
//	bool die;
//};
//struct tagBullet
//{
//	RECT rc;
//	bool fire;
//};


class MainGame : public GameNode
{
private:
	//MOLE* _mole;

	//CURRENT_RECT _currentRect;

	//RECT _rc[8];
	//int _index;		// 두더지 인덱스(8개)	
	//int _count;		// 타이머용 카운트
	//int _time;		// 랜덤 시간 변수
	//int _score;		// 점수

	//bool _bIsSelected; // 두더지 선택 여부
	//bool _bIsOnceCheck; // 두더지 한번만 체크

	/*tagBullet _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];*/

	//RECT _rc;

	GImage* _bgImage;
	GImage* _plImage;
	RECT _rc;

	//float _radian;
	//float _degree;

	// 시간 관련 구조체
	//SYSTEMTIME _st;

	//HPEN _currentStarPen;
	//STAR _star[5];

	int _countA, _countB;
	int _alphaA, _alphaB;
	int _alphaNum;

	bool _isAlphaIncrease;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	//void fireBullet(void);

	MainGame() {}
	~MainGame() {}
};

