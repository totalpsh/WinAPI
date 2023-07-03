#pragma once

/*
- �̹����� �ҷ����� ���


*/

class GImage
{

public:

    enum IMAGE_LOAD_KIND
    {
        LOAD_RESOURCE = 0, LOAD_FILE,      // ���ҽ�, ����
        LOAD_EMPTY, LOAD_END            // �� ��Ʈ��, �ε� done

    };

    typedef struct tagImage
    {
        DWORD   resID;
        HDC      hMemDC;
        HBITMAP hBit;
        HBITMAP hOBit;

        float   x;                      // �̹��� x��ǥ
        float   y;                      // �̹��� y��ǥ
        int     width;                  // �̹��� ���� ũ��
        int     height;                 // �̹��� ����ũ��
        int     currentFrameX;          // ���� ������ x
        int     currentFrameY;          // ���� ������ y
        int     maxFrameX;              // �ִ� ������ x ����
        int     maxFrameY;              // �ִ� ������ y ����
        int     frameWidth;             // 1 ������ ���� ũ��
        int     frameHeight;            // 1 ������ ���� ũ��
        BYTE    loadType;               // 


        tagImage()
        {
            resID = 0;                          //long
            hMemDC = nullptr;                   // �޸𸮿� �� �޸�DC
            hBit = nullptr;                     // �޸𸮿� �׸� �Ͱ� ȭ�鿡 �׸� ���� �и� ȭ���� �������� �޸𸮿� �ִ����� �����ϰڴ�!
            hOBit = nullptr;
            x = y = 0;
            width = 0;
            height = 0;
            currentFrameX = 0;
            currentFrameY = 0;
            maxFrameX = 0;
            maxFrameY = 0;
            frameWidth = 0;
            frameHeight = 0;
            width = 0;
            height = 0;
            loadType = LOAD_RESOURCE;          // unsigned char
        }
    }IMAGE_INFO, * LPIMAGE_INFO;
    // ������ �޾ƿͼ� ����ִ°�

private:
    LPIMAGE_INFO   _imageInfo; // �̹��� ���� ����ü
    char* _fileName;  // ���� �н��� �ܺο��� �������°� �����ؼ� �������� ã�� ���� ����
    bool            _isTrans;   // ������ �E���� �ȖE����(ĳ���ͳ� ��Ÿ ������Ʈ) -> � ���� �E���ΰ�?(����Ÿ ����) -> ���ӿ��� ���� �Ⱦ��� �����̴�(255, 0, 255)
    COLORREF      _transColor; // 

    BLENDFUNCTION   _blendFunc;     // ���ĺ��� ���     -> ���İ� ������ �޸� ��뷮 ���ҵ� ����
    LPIMAGE_INFO    _blendImage;    // �˹ٺ��� �̹���


public:

    /*
   COLORREF - �߿��ϴ� �������

   - �������� ���� ������ ǥ���ϱ� ���� ��ȣ���� 32��Ʈ ������
   �� R, G, B ���� 1����Ʈ(8��Ʈ)�̸� 0~255���� ǥ���ϴµ� ����ȭ �Ǿ� �ִ�.

   */
   // �ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
   // ������ �ϳ��� ������� �ִµ�? ���ڰ��� ���� ���� ���� -> �̹����� �޸𸮸� ���� �Դµ� ����ȭ�� ���� �޸𸮸� ���� �� �ִ�?
   // -> �����Ҵ��� �ϰ� �̹��� �ε����ϰ� ������ ������⸦ �ϰ� �׸���
   // �� �̹����� ����ϱ� ���� �޸� ������ ���۵Ǵµ� ��Ÿ�ӿ��� ������ �Ǿ� ���ڰ��� ���� �� �ڽ�Ʈ�� �ٿ� �Լ��� ���Ը� ���δ�
   // �ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�

    HRESULT init(int width, int height);
    // �̹��� ���ҽ��� �ʱ�ȭ (���� bool�� BOOL�� �ٲ۴ٸ� �Լ� �����ε� ��Ģ�� ��߳��� ������ �߸� �ҷ��� �� �ִ�.)
    // �Լ� �����ε忡 ���ؼ� �ѹ��� ��������.
    HRESULT init(const DWORD resId, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    // �̹��� ���Ϸ� �ʱ�ȭ
    HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

    // �ѹ����� �ٽ� �Ⱥҷ����� �ֵ� -> ���
    HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    // 
    HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    // �÷��̾� ��ġ�� ���̷� Ȱ��
    HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

    HRESULT initForAlphaBlend(void);    // ���� ���� �ʱ�ȭ �Լ�

    // ������ �̹��� ���Ϸ� �ʱ�ȭ



    // ���� �÷�Ű ����
    void setTransColor(bool isTrans, COLORREF transColor);

    //����
    void release(void);

    void render(HDC hdc);
    // 0,0 �������� �׸���.
    void render(HDC hdc, int destX, int destY);

    //�̹��� Ŭ���� -> ���ϴ� ��ŭ �̹����� �߶� �׸���
    void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight);
    void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sizeX, int sizeY, int sourwidth, int sourheight);
    // �˹� ����
    void alphaRender(HDC hdc, BYTE alpha);      // BYTE �ڷ����� 0~255 ũ�⸦ ������ -> ���İ��� �� ����
    void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, BYTE alpha);

    //������ ����
    void frameRender(HDC hdc, int destX, int destY);
    void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    void setTransImage(const char* fileName);

    // ���� ����
    // �� �ݺ� / �̹����� �а� ���� ���
    void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
    void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

    // �ζ��� �Լ�
    inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

    // �̹��� x��ǥ
    inline float getX(void) { return _imageInfo->x; }
    inline void setX(float x) { _imageInfo->x = x; }

    // �̹��� y��ǥ
    inline float getY(void) { return _imageInfo->y; }
    inline void setY(float y) { _imageInfo->y = y; }

    // �̹��� ���� ��ǥ
    inline void setCenter(float x, float y)
    {
        _imageInfo->x = x - (_imageInfo->width / 2);
        _imageInfo->y = y - (_imageInfo->height / 2);
    }

    // �̹��� ���� / ���� ũ��
    inline int getWidth(void) { return _imageInfo->width; }
    inline int getHeight(void) { return _imageInfo->height; }

    // �ٿ�� �ڽ�(�浹�� ��Ʈ)
    inline RECT boundingBox(void)
    {
        RECT rc =
        {
            _imageInfo->x,
            _imageInfo->y,
            _imageInfo->x + _imageInfo->width,
            _imageInfo->y + _imageInfo->height
        };
        return rc;
    }

    // �������� ������ �ٿ�� �ڽ�(�浹�� ��Ʈ)
    inline RECT boundingBoxWithFrame(void)
    {
        RECT rc =
        {
            _imageInfo->x,
            _imageInfo->y,
            _imageInfo->x + _imageInfo->frameWidth,
            _imageInfo->y + _imageInfo->frameHeight
        };
        return rc;
    }

    // ������ X
    inline int getFrameX(void) { return _imageInfo->currentFrameX; }
    inline void setFrameX(int frameX)
    {
        _imageInfo->currentFrameX = frameX;

        if (frameX > _imageInfo->maxFrameX)
        {
            _imageInfo->currentFrameX = _imageInfo->maxFrameX;
        }


    }

    // ������ Y
    inline int getFrameY(void) { return _imageInfo->currentFrameY; }
    inline void setFrameY(int frameY)
    {
        _imageInfo->currentFrameY = frameY;

        if (frameY > _imageInfo->maxFrameX)
        {
            _imageInfo->currentFrameY = _imageInfo->maxFrameY;
        }


    }

    // �̹��� 1������ ���� / ���� ũ��
    inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
    inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

    // �ִ� ������ X / Y ����
    inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
    inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }







    GImage(); // �߻�ü�� ������µ� �����ڿ��� �ʱ�ȭ�� ���־�� �Ѵ�.(private:)
    ~GImage() {} // 1. �켱���� ��� �Լ��� ȣ�� 2. release �Լ����� ó���� �ټ� �ֱ� ����
};