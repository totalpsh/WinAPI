#include "Stdafx.h"
#include "TempSoundScene.h"

HRESULT TempSoundScene::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("�޸�����ī��", "Resource/Sounds/Dali Van Picasso.mp3");

	return S_OK;
}

void TempSoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("�޸�����ī��");
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("Resource/Sounds/rock man bgm.wav");
	}

}
