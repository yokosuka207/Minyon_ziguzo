//=============================================================================
//
//�����Ƃ��납�痎���������u���b�N����
//
//�����/���Ԍ��C�@�����/2022/11/29
//=============================================================================
#pragma once

#include "high_broken.h"
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
static HIGH g_High[HIGH_MAX];
static ID3D11ShaderResourceView* g_textureHigh;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameHigh = (char*)"data\\texture\\green.png";

HIGH InitData[] =
{
	{true,D3DXVECTOR2(HIGH_SIZE_W,HIGH_SIZE_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
};


//=============================================================================
//����������
//=============================================================================
HRESULT InitHigh()
{
	srand(time(NULL));

	for (int i = 0; i < HIGH_MAX; i++)
	{
		g_High[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_High[i].Size = D3DXVECTOR2(HIGH_SIZE_W, HIGH_SIZE_H);
		g_High[i].texno = LoadTexture(g_TextureNameHigh);
		g_High[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);;
		g_High[i].UseFlag = false;
	}
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitHigh()
{
	for (int i = 0; i < HIGH_MAX; i++)
	{

	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateHigh()
{
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawHigh()
{
	for (int i = 0; i < HIGH_MAX; i++)
	{
		if (g_High[i].UseFlag)
		{
			SetWorldViewProjection2D();

			//�e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_High[i].texno));
			//�X�v���C�g��\��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_High[i].Postion.x, g_High[i].Postion.y, g_High[i].Size.x, g_High[i].Size.y,
				g_High[i].rot, g_High[i].col, 0, 1.0f, 1.0f, 1);

		}
	}
}

int SetHigh(D3DXVECTOR2 Pos, D3DXVECTOR2 s)
{
	//PUZZLE* pPuzzle = GetPuzzle();

	for (int i = 0; i < HIGH_MAX; i++)
	{
		if (!g_High[i].UseFlag)
		{

			g_High[i].Postion = Pos;
			g_High[i].Size = s;
			g_High[i].UseFlag = true;
			return i;

		}


	}

}

//=============================================================================
//�Q�b�g�֐�
//=============================================================================
HIGH* GetHigh()
{
	return g_High;
}