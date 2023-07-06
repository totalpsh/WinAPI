#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init(void)
{
    // ! do nothing
    return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias";
    string finalQuery = first + fileName + end + key;


    const char* str = finalQuery.c_str();

    //mciSendString() : ��ġ�� Ư�� ��ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ��ɾ�, ��ȯ���� �˷��� ��ɾ�, ��ȯ�� ����, �ڵ� �ݹ� 
    mciSendString(str, NULL, 0, NULL);

}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type waveaudio alias";
    string finalQuery = first + fileName + end + key;


    const char* str = finalQuery.c_str();

    //mciSendString() : ��ġ�� Ư�� ��ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ��ɾ�, ��ȯ���� �˷��� ��ɾ�, ��ȯ�� ����, �ڵ� �ݹ� 
    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
    /*
    // PlaySound("���� �̸�.wav"),
    // ���ϸ� ����ϸ� NULL !=  �ش� �ν��Ͻ� �ڵ�
    // fdwSound (�ɼ� | �ɼ� | �ɼ�)

    SND_ASYNC : ����ϸ鼭 ���� �ڵ带 ����
    �� �񵿱� �÷���

    SND_LOOP: �ݺ� ���

    SND_NODEFAULT: ������ ��ο� �Τ��� ��� ������� ������� �ʴ´�.
    */
    PlaySound(fileName, NULL, SND_ASYNC); // ������ ���� �ѹ��� ���� �����ִ� ���ڰ�

}

void TempSoundManager::playSoundWithKey(string key)
{
    string first = "play";

    string finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);

}

void TempSoundManager::stopMp3WithKey(string key)
{
    string first = "stop "; // 

    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}
