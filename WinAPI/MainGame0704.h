#pragma once
#include "GameNode.h"

class MainGame0704 : public GameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	MainGame0704() {}
	~MainGame0704(){}
};

