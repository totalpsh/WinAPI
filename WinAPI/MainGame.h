#pragma once
#include "GameNode.h"
#include "MOLE.h"
//#define _USE_MATH_DEFINES
//#include "math.h"
//
//#define PI 3.141592653f
//
//// ���� ǥ�� -> ���� ǥ�� ��ȯ
//#define DEGREE_PADIAN(_deg)			(M_PI* (_deg) / 180.0f)

struct STAR
{
	int x;
	int y;
};



// ���� ���� 
// �����ϱ� + �ѽ��
//define -> ���ȭ�� ��ų ���𰡸� ���÷���
// ���ȭ�� ������Ÿ��? ��Ÿ��?
// �迭�� ���÷�����  ->  Ȯ��(STL)
// STL�� ���� �ڵ尡 ������ �ٲ��.
// ��ü ��ü�� �̺��ϴ�.
#define BULLET_MAX 10
#define PLAYER_SPEED 5
// STL x -> �������� ���� ���� �ʴ�.
// ����ü�� �Ӽ��� ����غ��� �Ѵ�.
// ����? �̹����� ��������.
// ���࿡ ��ü�� �ִϸ��̼��� �������ٸ� �޸𸮻�뷮�� ��������. �׷��� STL -> O
// �� ����� �غ���!
#define ENEMY_MAX 80

//====================================================================================================================================

// ��ü ���� ���α׷��� -> ������ ����� ȿ������ ����а� ���� ü��

/* �����غ� ����
 ������ �δ���.....

 1. �δ��� + ��  ��ü
 �� Ŭ���� ����...?
	�� ���? / Ŭ������ �? / STL�� �ʿ��ұ�?
	(��κ� ������ STL�� �ִ�. -> ���� ������ ���������� ���� �Ǵ��� �غ��� => �׸��� �����ϸ� ���� �Ẹ��)
	(��� --> ���� ���� �����غ��� ����غ���(���� ����� �ؾ� �ϴ°�? -> �����ӿ�ũ���� ��� ���� ������ �� �ִ°�? ���� ����غ��� �������))
 �� ������ �Ų����� ���ϴ�..? => ���� �����ӿ�ũ�� ���� ���ذ� ������.

 2. ü��(���� / Ŭ���� / ����ü) - Ȯ�强�� ��������
 1������ ���� ���踦 �غ��� ���ڿ��� �׻� ����/Ŭ����/����ü�� �����غ��� ����Ǿ�� �Ѵ�.
 -> ���뼺�� Ȯ�强 ���꼺�� �ø� �� �ִ�.
 -> ���� ���� ������ �������� �غ���.

 �δ���
 �� Ŭ���� , ����ü , ������ -> ��� ȿ�����ϱ�? ������ �Ǳ� ������ �������� ����� ���̴�. (���� �Ҷ� ���������ض�)
 �� �׷� ���ߴٸ� �����̳ʸ� ������ ��� �ұ�?
 �� STL�� �����ϰ� ���������� ������ �Ҽ� �ցٲ� �ؾ� �Ѵ�.

 3. ��üȭ
	�� PCH / �Լ� -> ���� ����
	
	���� �׸��� ������� �ؾ� ��ü������ ������ �� �ִ�.

	MOLE �� �������� �����ȴ�.
*/

//enum CURRENT_RECT : UINT8 // ��ȣ���� �߻� �� �� �ִ��� �����غ��� enum class�� ������� ����غ���.
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
	//int _index;		// �δ��� �ε���(8��)	
	//int _count;		// Ÿ�̸ӿ� ī��Ʈ
	//int _time;		// ���� �ð� ����
	//int _score;		// ����

	//bool _bIsSelected; // �δ��� ���� ����
	//bool _bIsOnceCheck; // �δ��� �ѹ��� üũ

	/*tagBullet _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];*/

	//RECT _rc;

	GImage* _bgImage;
	GImage* _plImage;
	RECT _rc;

	//float _radian;
	//float _degree;

	// �ð� ���� ����ü
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

