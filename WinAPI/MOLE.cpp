#include "Stdafx.h"
#include "MOLE.h"

#define Center_x WINSIZE_X/2
#define Center_y WINSIZE_Y/2

HRESULT MOLE::init(void)
{
    rc = RectMakeCenter(Center_x, Center_y, 100, 100);
    return E_NOTIMPL;
}

void MOLE::release(void)
{
}

void MOLE::update(void)
{
}

void MOLE::render(HDC hdc)
{
    DrawRectMake(hdc, rc);
}
