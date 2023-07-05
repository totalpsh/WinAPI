#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "SecondScene.h"

/*

���ӳ�带 ���� ���� �ٲ��� ������ ���ν����� 2���� �þ�� -> ��?

*/

class MainGame0705 : public GameNode
{

private:

	StartScene* _start;
	SecondScene* _second;

	GameNode* _currentScene;   // ���ν����� ������ �������ֱ� ���� �Ҵ�

	int _alphaA;
	int _isAlphaIncrese;

	// ������ ����
	int _offsetX, _offsetY;
	int _bgSpeed;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	MainGame0705() : _currentScene(nullptr) {}
	~MainGame0705() {}
};
