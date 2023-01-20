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
#include "StageSelect.h"

//**************************************************
// �}�N����`
//**************************************************
#define BUTTON_NUM	(3)

//**************************************************
// �O���[�o���ϐ�
//**************************************************
// �e�e�N�X�`���̖��O
static char* g_BGTextureFileName = (char*)"data/texture/black.png";				// �w�i
static char* g_TextureFileName[] = { (char*)"data/texture/�Z�[�u�f�[�^�e�L�X�g�P.png",				// �f�[�^�P
									(char*)"data/texture/�Z�[�u�f�[�^�e�L�X�g�Q.png",				// �f�[�^�Q
									(char*)"data/texture/�Z�[�u�f�[�^�e�L�X�g�R.png"				// �f�[�^�R
};

// �Z�[�u�f�[�^��ۑ�����t�@�C����
static char* g_saveFileName[] = { (char*)"data/SaveData/Data1.bin",			// �f�[�^�P
								(char*)"data/SaveData/Data2.bin",			// �f�[�^�Q
								(char*)"data/SaveData/Data3.bin" };			// �f�[�^�R

// �e�f�[�^�̃{�^�������
Button g_DataButton[BUTTON_NUM];

//==================================================
// ������
//==================================================
void Save::Init()
{
	// �}�E�X�̏�����
	InitGameMouse();

	// �{�^���̃e�N�X�`���ԍ��ǂݍ���
	int ButtonTexNo[3];
	for (int i = 0; i < BUTTON_NUM; i++) {
		ButtonTexNo[i] = LoadTexture(g_TextureFileName[i]);
	}

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



	FILE* fp;		// �t�@�C���|�C���^
	// �e�{�^���̃Z�b�g
	for (int i = 0; i < BUTTON_NUM; i++) {
		// �t�@�C������������
		g_DataButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * (i+1)), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName[i]));

		// �t�@�C�����J��
		fopen_s(&fp, g_saveFileName[i], "rb");			// �J��

		// �f�[�^�ǂݍ���
		if (fp != NULL) {
			fread(&m_saveData, sizeof(SaveData), 1, fp);

			// �t�@�C�������
			fclose(fp);
		}
		g_DataButton[i].SetNum(m_saveData.clearStageNum);
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
	// Z�{�^������������
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_X) ||			// GamePad	X
		Keyboard_IsKeyTrigger(KK_Z)) {						// Keyboard	Z
		// �S�f�[�^�폜
		DeleteSaveData();
	}
	//----------����----------]
	//----------�Ƃ肠�����܂��c���Ă����܂�----------]
	for (int i = 0; i < BUTTON_NUM; i++) {
		// �e�{�^���̍X�V
		g_DataButton[i].Update();
		// ���������ꂽ��
		if (g_DataButton[i].ReleaseButton()) {
			SetDataNo(i);			// �f�[�^�ԍ����Z�b�g
			DataLoad();					// ���[�h

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
	m_saveData.clearStageNum = (GetClearStageNum() - 1);
	// ------------------------------------------------

	FILE* fp;		// �t�@�C���|�C���^

	// �t�@�C�����J��
	fopen_s(&fp, g_saveFileName[m_dataNo], "wb");

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
	m_saveData.clearStageNum = 0;

	FILE* fp;		// �t�@�C���|�C���^

	// �t�@�C�����J��
	for (int i = 0; i < BUTTON_NUM; i++) {
		fopen_s(&fp, g_saveFileName[i], "wb");

		if (fp != NULL) {
			// ��������
			fwrite(&m_saveData, sizeof(SaveData), 1, fp);

			// �t�@�C�������
			fclose(fp);
		}
		g_DataButton[i].SetNum(m_saveData.clearStageNum);
	}
}

//==================================================
// ���[�h
// �����F�Z�[�u�f�[�^�ԍ�
//==================================================
void Save::DataLoad()
{
	FILE* fp;		// �t�@�C���|�C���^

	// �t�@�C�����J��
	fopen_s(&fp, g_saveFileName[m_dataNo], "rb");			// �J��

	// �f�[�^�ǂݍ���
	if (fp != NULL) {
		fread(&m_saveData, sizeof(SaveData), 1, fp);

		// �t�@�C�������
		fclose(fp);
	}

	//[----�����Ń��[�h�����e�f�[�^���e�X�̏ꏊ�ɓ��ꂽ��----
	SetClearStageNum(m_saveData.clearStageNum);
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
