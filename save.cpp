/*================================================================================

	�Z�[�u����[save.cpp]

												Author: ꎓ� ��o
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#include "save.h"
#include "texture.h"
#include "main.h"
#include "sprite.h"
#include "scene.h"

#include "input.h"

// �e�e�N�X�`���̖��O
char* g_BGTextureFileName = (char*)"data/texture/JumpStand.jpg";			// �w�i
char* g_TextureFileName0 = (char*)"data/texture/GameEnd_haikei.jpg";			// �f�[�^�Ȃ�
char* g_TextureFileName1 = (char*)"data/texture/GameEnd_haikei.jpg";			// �f�[�^�P
char* g_TextureFileName2 = (char*)"data/texture/GameEnd_haikei.jpg";			// �f�[�^�Q
char* g_TextureFileName3 = (char*)"data/texture/GameEnd_haikei.jpg";			// �f�[�^�R

// �e�f�[�^�̃{�^�������
Button g_DataButton1;
Button g_DataButton2;
Button g_DataButton3;

//==================================================
// ������
//==================================================
void Save::Init()
{
	g_DataButton1.Init();
	g_DataButton2.Init();
	g_DataButton3.Init();

	// �e�N�X�`���i���o�[���i�[
	m_BGTexNo = LoadTexture(g_BGTextureFileName);

	m_BGPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_BGSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_DataButton1.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 1), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName1));
	g_DataButton2.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName1));
	g_DataButton3.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName1));
}

//==================================================
// �I������
//==================================================
void Save::Uninit()
{
	g_DataButton1.Uninit();
	g_DataButton2.Uninit();
	g_DataButton3.Uninit();
}

//==================================================
// �X�V����
//==================================================
void Save::Update()
{
	if (GetKeyboardTrigger(DIK_A)) {
		SetScene(SCENE_STAGESELECT);
	}

	g_DataButton1.Update();
	g_DataButton2.Update();
	g_DataButton3.Update();
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
	SpriteDrawColorRotation(m_BGPos.x, m_BGPos.y, m_BGSize.x, m_BGSize.y, 0.0f, m_BGColor, 0.0f, 1.0f, 1.0f, 1);
	//----------�w�i�̕\��----------]

	// �e�{�^���̕`��
	g_DataButton1.Draw();
	g_DataButton2.Draw();
	g_DataButton3.Draw();
}

//==================================================
// �Z�[�u
//==================================================
void Save::Saved(int no)
{

}

//==================================================
// �Z�[�u�f�[�^�폜
// �����F�Z�[�u�f�[�^�ԍ�
//==================================================
void Save::DeleteSaveData(int no)
{

}
