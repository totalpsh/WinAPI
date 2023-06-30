#pragma once
#include "SingletonBase.h"
#include "GImage.h"

// 1. ��ü�� ���� new
// 2. ���� ���� --> 2���� ���¿� ���� 1���� ���°� ��������.
// �� ��� ���� �� ���ΰ�? �� ���� 1���� ��������.
// -> STL->Map ������ ������ Ź���� ģ��
// Key �� Value�� ������ �ִ� ���� �ſ� ��ȿ�ϴ�.
// map�� unordered map ���� �ϳ��� ���� �Ѵ�.
// ������ �̹����� �˻� �ӵ��� ���ǹ� �ϱ� ������ map�� ��� �Ѵٴ� ������ �س��� �Ѵ�.


// ���� Ŭ�����μ� �̹����� �ܺηκ��� �޾Ƽ� ���ֱ� ���� �۾�

#pragma region STL ��
/*

- Ű + ���� ���� ����.
�� ù���� first -> Ű
�� �ι��� second -> ��

- �߰��ϴ� ����� insert()�� ����ϰ� Ű�� ������ ���ÿ� �߰��ؾ� �ϴ� pair / make pair�� ���

- pair : �ΰ��� �ڷ����� �ϳ��� �����ִ� ����ü (���ø� -> � �ڷ����� OK)

- make_pair : pair�� ������ִ� �Լ�
�� pair.first = x; / pair.second = y;
�� pair = make_pair(x, y);

-�ϳ��� Ű�� �������� ���� �����ϰ� �ʹٸ� ��Ƽ���� ����ϴ� �͵� ���

- pair�� Ȯ����� ������ �ۼ��ϰų� �ټ��� ��ȯ���� ������ �ʹٸ� tuple�� ����ؾ� �Ѵ�.

*/
#pragma endregion

class ImageManager : public SingletonBase<ImageManager> // �̱��� : ��ü�� �������� ���� ���ֱ� ����
{
private:
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*>::iterator mapimageIter;
	/*
		- string �� ���� ����
		�ݺ��ڴ� �������� ���� �ִµ� 
		char* �� ���� �ѹ��� Ȯ���ϴ� �۾��� �ʿ��ϴ�.
		�ʰ� ������ �Ǵ� string �� ����Ѵ�.
	*/

private:
	mapImageList _mImageList;


public:
    //���� ó�� ������ ������
    // �̱��� ����Ŭ������ ����� GImage�� �����ϴ� ����
	HRESULT init(void);
	void release(void);
	// �ܵ� ó���� ������
	// �� 1. �����ӿ�ũ �ڵ� ����ġ
	// �� 2. ��ü�� (�̹���) �浹 ���ɼ�


   GImage* addImage(string strKey,int width, int height);
   GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
   GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

   GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
   GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

   GImage* findImage(string strKey);

   bool deleteImage(string strkey);
   bool deleteAll();


    HRESULT initForAlphaBlend(void);    // ���� ���� �ʱ�ȭ �Լ�

    //����

    void render(string strKey,HDC hdc);
    // 0,0 �������� �׸���.
    void render(string strKey, HDC hdc, int destX, int destY);

    //�̹��� Ŭ���� -> ���ϴ� ��ŭ �̹����� �߶� �׸���
    void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight);
    void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sizeX, int sizeY, int sourwidth, int sourheight);
    // �˹� ����
    void alphaRender(string strKey, HDC hdc, BYTE alpha);      // BYTE �ڷ����� 0~255 ũ�⸦ ������ -> ���İ��� �� ����
    void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, BYTE alpha);

    //������ ����
    void frameRender(string strKey, HDC hdc, int destX, int destY);
    void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    void setTransImage(const char* fileName);

    ImageManager() {}
    ~ImageManager() {}
};

