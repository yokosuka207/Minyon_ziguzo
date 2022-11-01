//=============================================================================
//
//����u���b�N����
//
//�����/��t���l�@�����/2022/06/27
//=============================================================================
#pragma once

#include "broken.h"
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
static BROKEN g_Broken[BROKEN_MAX];
static ID3D11ShaderResourceView	*g_textureBroken;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameBroken = (char*)"data\\texture\\green.png";

BROKEN InitData[]=
{
	{true,D3DXVECTOR2(BROKEN_SIZE_W,BROKEN_SIZE_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
};


//=============================================================================
//����������
//=============================================================================
HRESULT InitBroken()
{
	srand(time(NULL));

	for (int i = 0; i < BROKEN_MAX; i++)
	{
		g_Broken[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_Broken[i].Size = D3DXVECTOR2(BROKEN_SIZE_W, BROKEN_SIZE_H);
		g_Broken[i].texno = LoadTexture(g_TextureNameBroken);
		g_Broken[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);;
		g_Broken[i].UseFlag = false;
	}
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitBroken()
{
	for (int i = 0; i < BROKEN_MAX; i++)
	{

	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateBroken()
{
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawBroken()
{
	for (int i = 0; i < BROKEN_MAX; i++)
	{
		if (g_Broken[i].UseFlag)
		{
			SetWorldViewProjection2D();

				//�e�N�X�`���̐ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Broken[i].texno));
				//�X�v���C�g��\��
				D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				SpriteDrawColorRotation(g_Broken[i].Postion.x, g_Broken[i].Postion.y, g_Broken[i].Size.x, g_Broken[i].Size.y, 
					g_Broken[i].rot, g_Broken[i].col, 0, 1.0f, 1.0f, 1);
				
		}
	}
}

int SetBroken(D3DXVECTOR2 Pos, D3DXVECTOR2 s)
{
	//PUZZLE* pPuzzle = GetPuzzle();

	for (int i = 0; i < BROKEN_MAX; i++)
	{
		if (!g_Broken[i].UseFlag)
		{

			g_Broken[i].Postion = Pos;
			g_Broken[i].Size = s;
			g_Broken[i].UseFlag = true;
			return i;

		}


	}

}

//=============================================================================
//�Q�b�g�֐�
//=============================================================================
BROKEN* GetBroken()
{
	return g_Broken;
}