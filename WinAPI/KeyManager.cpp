#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		setKeyUp(i, false);
		setKeyDown(i, false);
	}

	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!getKeyDown()[key])
		{
			setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		setKeyDown(key, false);
	}
	return false;
}
bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		setKeyUp(key, true);
	}
	else
	{
		if (getKeyUp()[key])
		{
			setKeyUp(key, false);
			return true;
		}
		
	}
	return false;
}
bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	else
		return false;
}



bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}
