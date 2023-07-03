#include "stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
	//! do nothing

	return S_OK;
}

void ImageManager::release(void)
{
	this->deleteAll();
}

GImage* ImageManager::addImage(string strKey, int width, int height)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인하겠다.
	GImage* img = findImage(strKey);

	if (img) return img;

	// 이미지가 없다..
	// 없으니까 새로 만든다.

	img = new GImage;

    // 원본을 손상시키지 않게 원본을 보존해주는 작업
	//실패시에 원본을 건들지 못하게 한다.
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		
		//1. C++ 에 포함 되어있는 언어 ----- API는 C로 만들어 졌기 때문에 컴파일러가 인식을 하지 못하므로 결과는 같지만 스택에서 나왔던 컴파일러가 다시 들어간다.
		//return nullptr;
		//2.
		return NULL;
	}

	//
	_mImageList.insert(pair<string, GImage*>(strKey, img));
	//
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	// 이미지가 없다..
	// 없으니까 새로 만든다.

	// 재귀
	img = new GImage;

	// 원본을 손상시키지 않게 원본을 보존해주는 작업
	//실패시에 원본을 건들지 못하게 한다.
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);

		// C / C++ 
		// ㄴ 지역
		return NULL;
		//return nullptr;
	}

	//
	_mImageList.insert(pair<string, GImage*>(strKey, img));
	//
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	// 이미지가 없다..
	// 없으니까 새로 만든다.

	// 재귀
	img = new GImage;

	// 원본을 손상시키지 않게 원본을 보존해주는 작업
	//실패시에 원본을 건들지 못하게 한다.
	if (FAILED(img->init(fileName,x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);

		// C / C++ 
		// ㄴ 지역
		return NULL;
		//return nullptr;
	}

	//
	_mImageList.insert(pair<string, GImage*>(strKey, img));
	//
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	// 이미지가 없다..
	// 없으니까 새로 만든다.

	// 재귀
	img = new GImage;

	// 원본을 손상시키지 않게 원본을 보존해주는
	//실패시에 원본을 건들지 못하게 한다.
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor )))
	{
		SAFE_DELETE(img);

		// C / C++ 
		// ㄴ 지역
		return NULL;
		//return nullptr;
	}

	//
	//_mImageList.insert(pair<string, GImage*>(strKey, img));
	//
	_mImageList.insert(make_pair(fileName, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	return nullptr;
}

GImage* ImageManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	// 검색한 키를 찾은 경우
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	// 검색한 키를 찾은 경우
	if (key != _mImageList.end())
	{
		// 접근할 수 있는 시작점만 삭제 
		// 그러므로 순차적으로 뺴주고 end를 만나면 뺴주도록 한다.
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		//이미지가 있다면
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}

		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return true;
}

HRESULT ImageManager::initForAlphaBlend(void)
{
	return E_NOTIMPL;
}

void ImageManager::render(string strKey, HDC hdc)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc);

}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourwidth, sourheight);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sizeX, int sizeY, int sourwidth, int sourheight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sizeX, sizeY, sourwidth, sourheight);
}

void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourwidth, sourheight, alpha);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);

}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	GImage* img = findImage(strKey);

	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void ImageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	GImage* img = findImage(strKey);

	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

void ImageManager::setTransImage(const char* fileName)
{
}
