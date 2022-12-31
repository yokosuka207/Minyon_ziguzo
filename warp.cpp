//=============================================================================
//
//���[�v����
//
//�����/��t���l�@�����/2022/06/27
//=============================================================================
#pragma once

#include "warp.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "time.h"
#include "scene.h"

//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static WARP g_Warp[WARP_MAX];
static ID3D11ShaderResourceView	*g_textureWarp;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameWarp= (char*)"data\\texture\\warp.png";

WARP InitData[]=
{
	{true,D3DXVECTOR2(WARP_SIZE_W,WARP_SIZE_H),D3DXVECTOR2(800,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(0,1,0,1),1,8,16,8,60 * 0},
	{true,D3DXVECTOR2(WARP_SIZE_W,WARP_SIZE_H),D3DXVECTOR2(800,400),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(0,1,0,1),1,8,16,8,60 * 0},
};


//=============================================================================
//����������
//=============================================================================
HRESULT InitWarp()
{
	srand(time(NULL));

	for (int i = 0; i < WARP_MAX; i++)
	{
		//g_Warp[i] = InitData[i];
		g_Warp[i].Position = D3DXVECTOR2(0.0f,0.0f);
		g_Warp[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_Warp[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Warp[i].texno = LoadTexture(g_TextureNameWarp);
		
		g_Warp[i].UseFlag = false;
	}
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitWarp()
{
	for (int i = 0; i < WARP_MAX; i++)
	{

	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWarp()
{
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawWarp()
{
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (g_Warp[i].UseFlag)
		{
			SetWorldViewProjection2D();

				//�e�N�X�`���̐ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Warp[i].texno));
				//�X�v���C�g��\��
				//D3DXCOLOR col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				SpriteDrawColorRotation(g_Warp[i].Position.x, g_Warp[i].Position.y, g_Warp[i].Size.x, g_Warp[i].Size.y,
					g_Warp[i].rot, g_Warp[i].col, 0, 1.0f, 1.0f, 1);
			
		}
	}
}
//---------------------------------------------------
//�s�[�X�̃Z�b�g���[�v
//�����F�|�W�V�����A�T�C�Y�A�s�[�X�̔ԍ�
//--------------------------------------------------
void cipSetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index)
{
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (!g_Warp[i].UseFlag)
		{

			g_Warp[i].Position = pos;
			g_Warp[i].Size = size;
			g_Warp[i].PieceIndex = index;
			g_Warp[i].UseFlag = true;
			break;

		}


	}

}


int SetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (!g_Warp[i].UseFlag)
		{

			g_Warp[i].Position = pos;
			g_Warp[i].Size = size;
			g_Warp[i].UseFlag = true;
			return i;

		}


	}

}

//=============================================================================
//�Q�b�g�֐�
//=============================================================================
WARP* GetWarp()
{
	return g_Warp;
}