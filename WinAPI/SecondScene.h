#pragma once
#include "GameNode.h"

class SecondScene : public GameNode
{
private:
	int _alphaA;
	int _isAlphaIncrese;

	// ������ ����
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
