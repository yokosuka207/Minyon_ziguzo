//=============================================================================
//
//	�X�e�[�W�Z���N�g����[StageSelect.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/25
//=============================================================================

#include "texture.h"
#include "sprite.h"
#include "StageSelect.h"
#include "input.h"
#include "cursor.h"
#include "MapChip.h"
#include "scene.h"

//*****************************************************************************
//	�}�N����`
//*****************************************************************************

//*****************************************************************************
//	�O���[�o���ϐ�
//*****************************************************************************
static STAGESELECT g_StageSelect;

static ID3D11Buffer* g_StageSelectVertexBuffer = NULL;	//�|���S���p
static ID3D11ShaderResourceView* g_StageSelectTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_StageSelectTextureName = (char*)"data\\texture\\number.png";	//�e�N�X�`���t�@�C���p�X

//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
HRESULT InitStageSelect() {
	g_StageSelect.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_StageSelect.size = D3DXVECTOR2(0.0f, 0.0f);
	g_StageSelect.UseFlag = false;
	g_StageSelect.StagePieceIndex = 0;
	g_StageSelect.StageUseFlag = false;
	g_StageSelect.texno = LoadTexture(g_StageSelectTextureName);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void UninitStageSelect() {
	if (g_StageSelectTexture) {
		g_StageSelectTexture->Release();
		g_StageSelectTexture = NULL;
	}
}

//-----------------------------------------------------------------------------
//	�X�V����
//-----------------------------------------------------------------------------
void UpdateStageSelect() {

	//�X�e�[�W�I��
	if (GetKeyboardTrigger(DIK_RIGHT)) {
		g_StageSelect.StagePieceIndex++;
		if (g_StageSelect.StagePieceIndex > STAGE_MAX - 1) {
			g_StageSelect.StagePieceIndex = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_LEFT)) {
		g_StageSelect.StagePieceIndex--;
		if (g_StageSelect.StagePieceIndex < 0) {
			g_StageSelect.StagePieceIndex = STAGE_MAX - 1;
		}
	}

	if (GetKeyboardTrigger(DIK_F5)) {
		SetScene(SCENE::SCENE_GAME);
	}
}

//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void DrawStageSelect() {
	{
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelect.texno));

		SpriteDrawColorRotation(
			g_StageSelect.pos.x, g_StageSelect.pos.y,
			g_StageSelect.size.x, g_StageSelect.size.y,
			0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			g_StageSelect.StagePieceIndex,
			1.0f / 10.0f,
			1.0f / 1.0f,
			10
		);
	}
}

//-----------------------------------------------------------------------------
//	�X�e�[�W�Z�b�g�֐�
//-----------------------------------------------------------------------------
void SetStageSelect() {
	g_StageSelect.pos = D3DXVECTOR2(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
	g_StageSelect.size = D3DXVECTOR2(200.0f,200.0f);
}
//-----------------------------------------------------------------------------
//	�X�e�[�W�Z���N�g���O���Œl��ς����悤�ɂ���֐�
//-----------------------------------------------------------------------------
STAGESELECT* GetSelect() {
	return &g_StageSelect;
}