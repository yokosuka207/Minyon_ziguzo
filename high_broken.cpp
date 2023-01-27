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
static HIGH_ANIME g_HighAnime[HIGH_ANIME_MAX];

static ID3D11ShaderResourceView* g_textureHigh;	//�摜�ꖇ�ň�̕ϐ����K�v
static ID3D11ShaderResourceView* g_textureHighAnime;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameHigh = (char*)"data\\texture\\high_broken.png";
static char* g_TextureNameHighAnime = (char*)"data\\texture\\explosion.png";

static int g_HighAnimeNo = 0;

HIGH InitData[] =
{
	{true,D3DXVECTOR2(HIGH_SIZE_W,HIGH_SIZE_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
};

static int HighBrokenIndex;
//=============================================================================
//����������
//=============================================================================
HRESULT InitHigh()
{
	HighBrokenIndex = 0;
	srand(time(NULL));

	for (int i = 0; i < HIGH_MAX; i++)
	{
		g_High[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_High[i].Size = D3DXVECTOR2(HIGH_SIZE_W, HIGH_SIZE_H);
		g_High[i].index = -1;
		g_High[i].Number = -1;
		g_High[i].texno = LoadTexture(g_TextureNameHigh);
		g_High[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_High[i].UseFlag = false;
		g_High[i].breakFlag = false;
	}
	for (int i = 0; i < HIGH_ANIME_MAX; i++) {
		g_HighAnime[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_HighAnime[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_HighAnime[i].index = -1;
		g_HighAnime[i].PaternNo = 0.0f;
		g_HighAnime[i].uv_w = 1.0f / 4.0f;
		g_HighAnime[i].uv_h = 1.0f / 4.0f;
		g_HighAnime[i].NumPatern = 4;
		g_HighAnime[i].UseFlag = false;
	}
	g_HighAnimeNo = LoadTexture(g_TextureNameHighAnime);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitHigh()
{
	if (g_textureHigh != NULL) {
		g_textureHigh->Release();
		g_textureHigh = NULL;
	}
	if (g_textureHighAnime != NULL) {
		g_textureHighAnime->Release();
		g_textureHighAnime = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateHigh(){
		
	
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
			//SetWorldViewProjection2D();

			//�e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_High[i].texno));
			//�X�v���C�g��\��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_High[i].Postion.x, g_High[i].Postion.y,-0.1f, g_High[i].Size.x, g_High[i].Size.y,
				g_High[i].rot, g_High[i].col, 0, 1.0f, 1.0f, 1);

		}
	}
	for (int i = 0; i < HIGH_ANIME_MAX; i++) {
		if (g_HighAnime[i].UseFlag) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_HighAnimeNo));
			SpriteDrawColorRotation(
				g_HighAnime[i].Postion.x,
				g_HighAnime[i].Postion.y,
				-0.1f,
				g_HighAnime[i].Size.x,
				-g_HighAnime[i].Size.y,
				0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				g_HighAnime[i].PaternNo,
				g_HighAnime[i].uv_w,
				g_HighAnime[i].uv_h,
				g_HighAnime[i].NumPatern
			);
			g_HighAnime[i].PaternNo += 0.5f;
			if (g_HighAnime[i].PaternNo > 16.0f) {
				g_HighAnime[i].PaternNo = 0.0f;
			}
			if (g_HighAnime[i].PaternNo == 16.0f) {
				g_HighAnime[i].UseFlag = false;
			}
		}
	}
}

void SetHigh(D3DXVECTOR2 Pos, D3DXVECTOR2 s,int index, int number){
	bool MatchFlag = false;

	for (int i = 0; i < HIGH_MAX; i++)
	{
		if (!g_High[i].UseFlag)
		{
			if (g_High[i].index == index)
			{
				if (g_High[i].Number == number)
				{
					MatchFlag = true;
					if (!g_High[i].breakFlag)
					{
						g_High[i].Postion = Pos;
						g_High[i].Size = s;
						g_High[i].index = index;
						g_High[i].Number = number;
						g_High[i].UseFlag = true;
						break;

					}
					else {

						break;

					}
				}
			}

		}


	}

	if (!MatchFlag)
	{
		for (int i = HighBrokenIndex; i < HIGH_MAX; i++) {
			if (!g_High[i].UseFlag) {
				g_High[i].Postion = Pos;
				g_High[i].Size = s;
				g_High[i].index = index;
				g_High[i].Number = number;
				g_High[i].UseFlag = true;
				HighBrokenIndex++;
				if (HighBrokenIndex== HIGH_MAX)
				{
					HighBrokenIndex = 0;

				}
				break;
			}
		}
	}
}
void DeleteHigh(int PieceNo) {
	for (int i = 0; i < HIGH_MAX; i++) {
		if (g_High[i].index == PieceNo) {
			if (g_High[i].UseFlag) {
				g_High[i].UseFlag = false;
			}
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
void SetHighAnime(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index) {
	for (int i = 0; i < HIGH_ANIME_MAX; i++) {
		if (!g_HighAnime[i].UseFlag) {
			g_HighAnime[i].Postion = pos;
			g_HighAnime[i].Size = size;
			g_HighAnime[i].index = index;
			g_HighAnime[i].UseFlag = true;
			break;
		}
	}
}
