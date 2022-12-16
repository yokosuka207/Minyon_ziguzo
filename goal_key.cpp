//=============================================================================
//�S�[���p��
//
//�����/���Ԍ��C�@
//=============================================================================

#include "goal_key.h"
#include "goal.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include "puzzle.h"

//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static GKEY g_GKey[GKEY_MAX];
static ID3D11ShaderResourceView* g_textureGKey;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameGKey = (char*)"data\\texture\\key-1.png";

HRESULT InitGKey()
{
	g_GKey->size = D3DXVECTOR2(GKEY_W, GKEY_H);
	g_GKey->pos = D3DXVECTOR2(600, 550);
	g_GKey->texno = LoadTexture(g_TextureNameGKey);
	g_GKey->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_GKey->UseFlag = true;
	g_GKey->GetGKey = false;
	return S_OK;
}

void UninitGKey()
{

}

void UpdateGKey()
{

}

void DrawGKey()
{
	if (g_GKey->UseFlag)
	{
		SetWorldViewProjection2D();

		//�e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_GKey->texno));
		//�X�v���C�g��\��
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_GKey->pos.x, g_GKey->pos.y, g_GKey->size.x, g_GKey->size.y,
			g_GKey->rot, g_GKey->col, 0, 1.0f, 1.0f, 1);
	}
}

void SetGKey(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_GKey->pos = pos;
	g_GKey->size = size;
	g_GKey->UseFlag = true;
}

void DeleteGKey()
{
	g_GKey->UseFlag = false;
}

GKEY* GetGKey()
{
	return g_GKey;
}