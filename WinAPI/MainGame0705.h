#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "SecondScene.h"

/*

게임노드를 통해 씬을 바꾸지 않으면 프로시저가 2개로 늘어난다 -> 왜?

*/

class MainGame0705 : public GameNode
{

private:

	StartScene* _start;
	SecondScene* _second;

	GameNode* _currentScene;   // 프로시저를 씬에게 전달해주기 위해 할당

	int _alphaA;
	int _isAlphaIncrese;

	// 루프용 변수
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
