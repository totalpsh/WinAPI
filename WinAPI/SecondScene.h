#pragma once
#include "GameNode.h"
#include "TempSoundScene.h"

class SecondScene : public GameNode
{
private:
	TempSoundScene* _tempSound;

	int _alphaA;
	int _isAlphaIncrese;

	// 루프용 변수
	int _offsetX, _offsetY;
	int _bgSpeed;

	int choice;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SecondScene() {}
	~SecondScene() {}

};
