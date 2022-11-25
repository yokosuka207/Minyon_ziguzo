//=============================================================================
//
//����u���b�N����
//
//�����/�e�n ��@
//=============================================================================
#include "fallblock.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"
//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static FALLBLOCK g_FallBlock[FALLBLOCK_MAX];

static ID3D11ShaderResourceView	*g_textureBroken;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameBroken = (char*)"data\\texture\\green.png";


HRESULT InitFallBlock()
{
	for (int i = 0; i < FALLBLOCK_MAX; i++)
	{
		g_FallBlock[i].Position = D3DXVECTOR2(200, 300);
		g_FallBlock[i].sp = D3DXVECTOR2(0, 0);
		g_FallBlock[i].Size = D3DXVECTOR2(FALLBLOCK_W,FALLBLOCK_H);
		g_FallBlock[i].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		g_FallBlock[i].texno = LoadTexture(g_TextureNameBroken);
		g_FallBlock[i].PieceIndex = -1;
		g_FallBlock[i].UseFlag = false;

	}

	return S_OK;
}

void UninitFallBlock()
{
	for (int i = 0; i < FALLBLOCK_MAX; i++)
	{

	}
}

void UpdateFallBlock()
{

}

void DrawFallBlock()
{
	for (int i = 0; i < FALLBLOCK_MAX; i++)
	{
		if (g_FallBlock[i].UseFlag)
		{
			SetWorldViewProjection2D();

			//�e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FallBlock[i].texno));
			//�X�v���C�g��\��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_FallBlock[i].Position.x, g_FallBlock[i].Position.y, g_FallBlock[i].Size.x, g_FallBlock[i].Size.y,
				g_FallBlock[i].rot, g_FallBlock[i].col, 0, 1.0f, 1.0f, 1);

		}
	}
}


void SetFallBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size,int PieceNo)
{
	for (int i = 0; i < FALLBLOCK_MAX; i++)
	{
		if (!g_FallBlock[i].UseFlag)
		{
			g_FallBlock[i].Position = pos;
			g_FallBlock[i].Size = size;
			g_FallBlock[i].PieceIndex = PieceNo;
			g_FallBlock[i].UseFlag = true;
			break;
		}
	}
}

void DeleteFallBlock(int PieceNo) {
	for (int i = 0; i < FALLBLOCK_MAX; i++) {
		if (g_FallBlock[i].UseFlag) {
			g_FallBlock[i].UseFlag = false;
		}
	}
}


FALLBLOCK* GetFallBlock()
{
	return g_FallBlock;
}
