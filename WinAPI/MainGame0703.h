#pragma once
#include "GameNode.h"

class MainGame0703 : public GameNode
{
private:

	int _alphaA;
	bool _isAlphaIncrease;

	//루프용 변수
	int _bgSpeed;

	int _offsetY;

	int	_offsetX;
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame0703() {}
	~MainGame0703() {}
};

