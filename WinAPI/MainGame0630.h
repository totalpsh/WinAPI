#pragma once
#include "GameNode.h"
#include "MOLE.h"

class MainGame0630 : public GameNode
{
private:
	
	int _countA, _countB;
	int _alphaA, _alphaB;
	int _alphaNum;

	bool _isAlphaIncrease;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame0630() {}
	~MainGame0630() {}
};

