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
#include "button.h"

#include "sound.h"

//**************************************************
// �}�N����`
//**************************************************
#define BUTTON_MAX	4
#define DATA_MAX	3

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
char* g_saveFileName[] = { (char*)"data/SaveData/Data1.bin",			// �f�[�^�P
							(char*)"data/SaveData/Data2.bin",			// �f�[�^�Q
							(char*)"data/SaveData/Data3.bin" };			// �f�[�^�R

char* g_DataDeleteTextureName = (char*)"data/texture/Erase.png";
//char* g_SaveTitleTextureName = (char*)"data/texture/Select a File.png";
char* g_SaveTitleTextureName = (char*)"data/texture/Save.png";
int g_SaveTitleTextureNo = -1;

// �e�f�[�^�̃{�^�������
Button g_DataButton[BUTTON_MAX];

//�T�E���h
static int g_ChangeSceneSaveSoundNo = 0;
static char g_ChangeSceneSaveSoundName[] = "data\\SoundData\\SE\\�V�[���J��(������).wav";

// �S�N��������
bool g_StageAllClear = false;

//==================================================
// ������
//==================================================
void Save::Init()
{
	// �}�E�X�̏�����
	InitGameMouse();

	// �Z�[�u�^�C�v�̏�����
	m_type = SAVE_TYPE::TYPE_NONE;
	// �Z�[�u�̃^�C�g���̃e�N�X�`���ǂݍ���
	g_SaveTitleTextureNo = LoadTexture(g_SaveTitleTextureName);

	m_pButton = &g_DataButton[0];

	// �{�^���̃e�N�X�`���ԍ��ǂݍ���
	int ButtonTexNo[3];
	for (int i = 0; i < DATA_MAX; i++) {
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
	for (int i = 0; i < DATA_MAX; i++) {
		// �t�@�C������������
		g_DataButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * (i+1) + 150),D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), 
			D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2.5), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ButtonTexNo[i]);

		// �t�@�C�����J��
		fopen_s(&fp, g_saveFileName[i], "rb");			// �J��

		// �f�[�^�ǂݍ���
		if (fp != NULL) {
			fread(&m_saveData, sizeof(SaveData), 1, fp);

			// �t�@�C�������
			fclose(fp);
		}
		g_DataButton[i].SetNum(m_saveData.clearStageNum);
		if (m_saveData.clearStageNum == STAGE_MAX) {
			g_DataButton[i].SetButtonColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			g_DataButton[i].SetNumColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//g_DataButton[i].SetButtonColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//g_DataButton[i].SetNumColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		}
	}
	// �f�[�^�폜�{�^��
	g_DataButton[3].SetButton(D3DXVECTOR2((SCREEN_WIDTH / 3) * 2.5f, (SCREEN_HEIGHT / 4) * 3.5f), D3DXVECTOR2(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6), 
		D3DXVECTOR2(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_DataDeleteTextureName));

	// �T�E���h�f�[�^�̃��[�h
	g_ChangeSceneSaveSoundNo = LoadSound(g_ChangeSceneSaveSoundName);

	// �S�N�����ĂȂ����Ƃɂ���
	g_StageAllClear = false;
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
	StopSound(g_ChangeSceneSaveSoundNo);
}

//==================================================
// �X�V����
//==================================================
void Save::Update()
{
	// �}�E�X�̍X�V
	UpdateGameMouse();

	static float MouseOldPosX = GetMousePosX();
	static float MouseOldPosY = GetMousePosY();

	if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN)) {	// GamePad �\���L�[ ��
		float disSta = 1000000.0f;
		int j = 0;
		for (int i = 0; i < BUTTON_MAX; i++) {
			D3DXVECTOR2 p0 = m_pButton->GetPosition();
			D3DXVECTOR2 p1 = g_DataButton[i].GetPosition();
			// ���܃Z�b�g����Ă���{�^����艺�̈ʒu�ɂ���
			if (p0.y < p1.y) {
				// �Ԃ̋�������ԋ߂��{�^����T��
				float dis = DistanceTwoPoints(p0, p1);
				if (disSta > dis) {
					disSta = dis;
					j = i;
				}
			}
		}
		m_pButton = &g_DataButton[j];
	}
	else if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP)) {	// GamePad �\���L�[ ��
		float disSta = 1000000.0f;
		int j = BUTTON_MAX - 1;
		for (int i = BUTTON_MAX - 1; i >= 0; i--) {
			D3DXVECTOR2 p0 = m_pButton->GetPosition();
			D3DXVECTOR2 p1 = g_DataButton[i].GetPosition();
			// ���܃Z�b�g����Ă���{�^������̈ʒu�ɂ���
			if (p0.y > p1.y) {
				// �Ԃ̋�������ԋ߂��{�^����T��
				float dis = DistanceTwoPoints(p0, p1);
				if (disSta > dis) {
					disSta = dis;
					j = i;
				}
			}
		}
		m_pButton = &g_DataButton[j];
	}
	//----------����----------]

	for (int i = 0; i < BUTTON_MAX; i++) {
		// �e�{�^���̍X�V
		g_DataButton[i].Update();
		// �}�E�X�������Ă�����
		if (MouseOldPosX != GetMousePosX() ||
			MouseOldPosY != GetMousePosY()) {
			if (g_DataButton[i].CollisionMouse()) {
				m_pButton = &g_DataButton[i];
			}
		}

		D3DXCOLOR col = g_DataButton[i].GetCol();
		// ���̃{�^�����I�΂�Ă���
		if (&g_DataButton[i] == m_pButton) {
			g_DataButton[i].SetButtonColor(D3DXCOLOR(col.r, col.g, col.b, 1.0f));
		}
		else {
			g_DataButton[i].SetButtonColor(D3DXCOLOR(col.r, col.g, col.b, 0.4f));
		}

		// �I������Ă���{�^����������
		if (m_pButton == &g_DataButton[i]) {
			// ���̓`�F�b�N
			if (g_DataButton[i].CollisionMouse() && (Mouse_IsLeftTrigger()) ||						// Mouse ��
				IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {		// GamePad B
				// �f�[�^�̃{�^����
				if (i < DATA_MAX) {
					SetDataNo(i);				// �f�[�^�ԍ����Z�b�g
					if (m_type == SAVE_TYPE::TYPE_NONE) {
						DataLoad();					// ���[�h

						// �X�e�[�W�Z���N�g�V�[���ɐ؂�ւ��
						FADEPARAM* pFadeParam = GetFadeParam();
						if (!pFadeParam->FadeFlag)
						{
							//SetVolume(g_ChangeSceneSaveSoundNo, 0.5f);
							PlaySound(g_ChangeSceneSaveSoundNo, 0);
							StartFade(FADE::FADE_ALPHA_OUT);
						}
					}
					else {
						DeleteSaveData();		// �f�[�^�폜
					}
				}
				else {	// �f�[�^�̃{�^���ł͂Ȃ�������
					// �^�C�v�̐؂�ւ�
					if (m_type == SAVE_TYPE::TYPE_NONE) {
						m_type = SAVE_TYPE::TYPE_DELETE;
					}
					else {
						m_type = SAVE_TYPE::TYPE_NONE;
					}
				}
				g_DataButton[i].ChangeType();
				break;
			}
		}
	}

	// ���ɔ�����1�t���[���O�̍��W�ɓ����
	MouseOldPosX = GetMousePosX();
	MouseOldPosY = GetMousePosY();
}


//==================================================
// �`�揈��
//==================================================
void Save::Draw()
{
	//[----------�w�i�̕\��----------
	// �e�N�X�`���̐ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_BGTexNo));

	if (m_type == SAVE_TYPE::TYPE_DELETE) {
		m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
	else {
		m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// �l�p�`�̕`��
	SpriteDrawColorRotation(m_BGPos.x, m_BGPos.y, 0.0f, m_BGSize.x, m_BGSize.y, 0.0f, m_BGColor, 0.0f, 1.0f, 1.0f, 1);
	//----------�w�i�̕\��----------]
	// �Z�[�u�̃^�C�g���̕\��
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SaveTitleTextureNo));
	SpriteDrawColorRotation(SCREEN_WIDTH / 2, 100.0f, 0.0f, 1000, 500, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 1.0f, 1.0f, 1);

	// �e�{�^���̕`��
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_DataButton[i].Draw();
		if (i == DATA_MAX) {
			if (m_type == SAVE_TYPE::TYPE_DELETE) {
				SetBlendState(BLEND_MODE_SUBTRACT);
			}
		}
	}

	// �u�����h���[�h��߂�
	SetBlendState(BLEND_MODE_ALPHABLEND);
}

//==================================================
// �Z�[�u
//==================================================
void Save::DataSave()
{
	// �Z�[�u����f�[�^
	if (g_StageAllClear) {		// �S�N�����Ă���
		m_saveData.clearStageNum = STAGE_MAX;
	}
	else {
		m_saveData.clearStageNum = (GetClearStageNum() - 1);
	}

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
	fopen_s(&fp, g_saveFileName[m_dataNo], "wb");

	if (fp != NULL) {
		// ��������
		fwrite(&m_saveData, sizeof(SaveData), 1, fp);

		// �t�@�C�������
		fclose(fp);
	}
	g_DataButton[m_dataNo].SetNum(m_saveData.clearStageNum);
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

	if (m_saveData.clearStageNum == STAGE_MAX) {
		g_StageAllClear = true;
	}
	SetClearStageNum(m_saveData.clearStageNum);
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

//==================================================
// �S�N����������Ԃ�
//==================================================
bool GetStageAllClear()
{
	return g_StageAllClear;
}

//==================================================
// �S�N��������������
//==================================================
void SetStageAllClear(bool bClear)
{
	g_StageAllClear = bClear;
}
