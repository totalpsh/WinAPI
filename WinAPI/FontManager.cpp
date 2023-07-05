#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontWeight, char* printString, int length, COLORREF color)
{
	//SetBkMode(hdc, TRANSPARENT);

	//HFONT font = CreateFont
	//(
	//	70, 0, 0, 0, 600,
	//	0, 0, 1,
	//	HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("ÈÞ¸Õ±¼¸²")
	//);
	//// »õ·Î¿î ¹æ½Ä
	//auto font = (HFONT)SelectObject(getMemDC(), font);;
	//auto oldFont;

	//SetTextColor(hdc, color);

	//const int stringLength = strlen(~~~);
	//wchar_t charBuffer[256];


	//ZeroMemory(charBuffer);

	//TextOut();
	//TextOutW();

	//SelectObject(getMemDC(), oldFont);
	//DeleteObject(font);

}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontWeight, LPCWSTR printString, int length, COLORREF color)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontWeight, LPCWSTR* printStringArr, int length, COLORREF color)
{
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);

	int lineCount = 0;

	for (int i = 0; i < arraySize; i++)
	{
		if (i == 0)
		{
			if ()
			{

			}
			else
			{
				break;
			}
		}
		else
		 {

		}
	}


}
