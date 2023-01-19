/*================================================================================

	�Z�[�u����[save.cpp]

												Author: ꎓ� ��o
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	2022/12/07	SaitoReito
================================================================================*/
#include <iostream>

#include "save.h"
#include "texture.h"
#include "main.h"
#include "sprite.h"
#include "scene.h"

//#include "input.h"
#include "xinput.h"
#include "xkeyboard.h"

#include "input.h"
#include "fade.h"
#include "mouse.h"
//**************************************************
// �}�N����`
//**************************************************
#define BUTTON_NUM	(3)

//**************************************************
// �O���[�o���ϐ�
//**************************************************
// �e�e�N�X�`���̖��O
static char* g_BGTextureFileName = (char*)"data/texture/black.png";				// �w�i
static char* g_TextureFileName1 = (char*)"data/texture/�Z�[�u�f�[�^�e�L�X�g�P.png";					// �f�[�^�P
static char* g_TextureFileName2 = (char*)"data/texture/�Z�[�u�f�[�^�e�L�X�g�Q.png";					// �f�[�^�Q
static char* g_TextureFileName3 = (char*)"data/texture/�Z�[�u�f�[�^�e�L�X�g�R.png";					// �f�[�^�R

// �Z�[�u�f�[�^��ۑ�����t�@�C����
static char* g_saveFileName1 = (char*)"data/SaveData/Data1.bin";			// �f�[�^�P
static char* g_saveFileName2 = (char*)"data/SaveData/Data2.bin";			// �f�[�^�Q
static char* g_saveFileName3 = (char*)"data/SaveData/Data3.bin";			// �f�[�^�R

// �e�f�[�^�̃{�^�������
Button g_DataButton[BUTTON_NUM];

//==================================================
// ������
//==================================================
void Save::Init()
{
	// �}�E�X�̏�����
	InitGameMouse();
	// �e�{�^���̏�����
	for (auto& b : g_DataButton) {
		b.Init();
	}

	// �e�N�X�`���i���o�[���i�[
	m_BGTexNo = LoadTexture(g_BGTextureFileName);

	m_BGPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_BGSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �Z�[�u�f�[�^�n�̏�����
	m_saveData.clearStageNum = 0;

	// �e�{�^���̃Z�b�g
	int i = 0;
	for (auto& b : g_DataButton) {
		i++;
		switch (i) {
		case 1:
			// �t�@�C������������
			if (ExistFile(g_saveFileName1)) {
				b.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * i), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName1));
				continue;
			}
			break;
		case 2:
			// �t�@�C������������
			if (ExistFile(g_saveFileName2)) {
				b.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * i), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName2));
				continue;
			}
			break;
		case 3:
			// �t�@�C������������
			if (ExistFile(g_saveFileName3)) {
				b.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * i), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName3));
				continue;
			}
			break;
		}
	}
}

//==================================================
// �I������
//==================================================
void Save::Uninit()
{
	// �e�{�^���̏I������
	for (auto& b : g_DataButton) {
		b.Uninit();
	}
}

//==================================================
// �X�V����
//==================================================
void Save::Update()
{
	// �}�E�X�̍X�V
	UpdateGameMouse();
	//[----------�Ƃ肠�����܂��c���Ă����܂�----------
	//[----------����----------
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
		Keyboard_IsKeyTrigger(KK_A)) {						// Keyboard	A
		// �X�e�[�W�Z���N�g�V�[����
		//SetScene(SCENE_STAGESELECT);
		StartFade(FADE::FADE_ALPHA_OUT);
	}
	// Z�{�^������������
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_X) ||			// GamePad	X
		Keyboard_IsKeyTrigger(KK_Z)) {						// Keyboard	Z
		// �S�f�[�^�폜
		DeleteSaveData();
	}
	//----------����----------]
	//----------�Ƃ肠�����܂��c���Ă����܂�----------]

	int dataNo = 0;
	for (auto& b : g_DataButton) {
		dataNo++;
		// �e�{�^���̍X�V
		b.Update();
		// ���������ꂽ��
		if (b.ReleaseButton()) {
			SetDataNo(dataNo);			// �f�[�^�ԍ����Z�b�g
			//DataSave();					// �Z�[�u
			DataLoad();					// ���[�h

			// �{�^���̃e�N�X�`����ς���
			switch (dataNo) {
			case 1:
				b.SetButtonTexNo(LoadTexture(g_TextureFileName1));
				break;
			case 2:
				b.SetButtonTexNo(LoadTexture(g_TextureFileName2));
				break;
			case 3:
				b.SetButtonTexNo(LoadTexture(g_TextureFileName3));
				break;
			}

			FADEPARAM* pFadeParam = GetFadeParam();

			//SetScene(SCENE_STAGESELECT);			// �X�e�[�W�Z���N�g�V�[���ɐ؂�ւ��
			if(!pFadeParam->FadeFlag)
			StartFade(FADE::FADE_ALPHA_OUT);
		}
	}
}

//==================================================
// �`�揈��
//==================================================
void Save::Draw()
{
	//[----------�w�i�̕\��----------
	// �e�N�X�`���̐ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_BGTexNo));
	// �l�p�`�̕`��
	SpriteDrawColorRotation(m_BGPos.x, m_BGPos.y,0.0f, m_BGSize.x, m_BGSize.y, 0.0f, m_BGColor, 0.0f, 1.0f, 1.0f, 1);
	//----------�w�i�̕\��----------]

	// �e�{�^���̕`��
	for (auto& b : g_DataButton) {
		b.Draw();
	}
}

//==================================================
// �Z�[�u
//==================================================
void Save::DataSave()
{
	// ----�Z�[�u����e�f�[�^��m_saveData�ɓ��ꂽ��----
	m_saveData.clearStageNum = 0;				// ��
	// ------------------------------------------------

	FILE* fp;		// �t�@�C���|�C���^

	// �t�@�C�����J��
	switch (m_dataNo) {
	case 1:
		fopen_s(&fp, g_saveFileName1, "wb");
		break;
	case 2:
		fopen_s(&fp, g_saveFileName2, "wb");
		break;
	case 3:
		fopen_s(&fp, g_saveFileName3, "wb");
		break;
	}

	if (fp != NULL) {
		// ��������
		fwrite(&m_saveData, sizeof(SaveData), 1, fp);

		// �t�@�C�������
		fclose(fp);
	}
}

//==================================================
// �Z�[�u�f�[�^�폜
// �����F�Z�[�u�f�[�^�ԍ�
//==================================================
void Save::DeleteSaveData()
{
	// �t�@�C�����폜
	//switch (m_dataNo) {
	//case 1:
	//	remove(g_saveFileName1);
	//	break;
	//case 2:
	//	remove(g_saveFileName2);
	//	break;
	//case 3:
	//	remove(g_saveFileName3);
	//	break;
	//}
	remove(g_saveFileName1);
	remove(g_saveFileName2);
	remove(g_saveFileName3);

}

//==================================================
// ���[�h
// �����F�Z�[�u�f�[�^�ԍ�
//==================================================
void Save::DataLoad()
{
	FILE* fp;		// �t�@�C���|�C���^

	// �t�@�C�����J��
	switch (m_dataNo) {
	case 1:
		// �t�@�C�����Ȃ��Ȃ���
		if (!ExistFile(g_saveFileName1)) {
			DataSave();
		}
		fopen_s(&fp, g_saveFileName1, "rb");			// �J��
		break;
	case 2:
		// �t�@�C�����Ȃ��Ȃ���
		if (!ExistFile(g_saveFileName2)) {
			DataSave();
		}
		fopen_s(&fp, g_saveFileName2, "rb");			// �J��
		break;
	case 3:
		// �t�@�C�����Ȃ��Ȃ���
		if (!ExistFile(g_saveFileName3)) {
			DataSave();
		}
		fopen_s(&fp, g_saveFileName3, "rb");			// �J��
		break;
	}

	// �f�[�^�ǂݍ���
	if (fp != NULL) {
		fread(&m_saveData, sizeof(SaveData), 1, fp);

		// �t�@�C�������
		fclose(fp);
	}

	//[----�����Ń��[�h�����e�f�[�^���e�X�̏ꏊ�ɓ��ꂽ��----
	//
	//------------------------------------------------------]
}

//==================================================
// �t�@�C�������݂��Ă��邩
// �����F�t�@�C���p�X
// �Ԓl�Fbool(true�F���݂��Ă���)
//==================================================
bool Save::ExistFile(char* fileName) 
{
	FILE* fp;		// �t�@�C���|�C���^

	// �t�@�C�����Ȃ�������false��Ԃ�
	if (fopen_s(&fp, fileName, "rb") != 0) {
		return false;
	}

	fclose(fp);				// ����

	// �t�@�C������������true��Ԃ�
	return true;
}
