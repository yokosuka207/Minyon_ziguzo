
//=============================================================================
//
//�o���b�g����
//
//�����/SORA�@
//=============================================================================
#pragma once

#include "bullet.h"
#include "player.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include"collision.h"
#include "sound.h"
#include"block.h"

//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static BULLET g_Bullet[BULLET_MAX];
static char* g_TextureName = (char*)"data\\texture\\�e.png";

//�e���ˉ�SE
static int g_BulletSoundNo = 0;
static char g_BulletSoundName[] = "data\\SoundData\\SE\\�e��(On-Jin).wav";

//=============================================================================
//����������
//=============================================================================
HRESULT InitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//�o���b�g�̏�����
		g_Bullet[i].pos = D3DXVECTOR2(0, 0);
		g_Bullet[i].sp = D3DXVECTOR2(-BULLET_SPEED, 0.0f);
		//g_Bullet[i].sp = D3DXVECTOR2(BULLET_SPEED, 0);
		g_Bullet[i].w = BULLET_SIZE_W;
		g_Bullet[i].h = BULLET_SIZE_H;
		g_Bullet[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].use = false;
		g_Bullet[i].texno = LoadTexture(g_TextureName);

		g_Bullet[i].PaternNo = 0;//�p�^�[���ԍ�
		g_Bullet[i].uv_w = 1;//���T�C�Y
		g_Bullet[i].uv_h = 1;//�c�T�C�Y
		g_Bullet[i].NumPatern = 1;//������
		g_Bullet[i].hit = false;
		g_Bullet[i].Damage = 1;

		g_BulletSoundNo = LoadSound(g_BulletSoundName);
	}

	
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		StopSound(g_BulletSoundNo);
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateBullet()
{
	BLOCK* pBlock = GetChipBlock();


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)
		{
			g_Bullet[i].pos.x += g_Bullet[i].sp.x;

			for (int j = 0; j < BLOCK_CHIP_MAX; j++)
			{
				if (!pBlock[j].UseFlag)continue;

				if (CollisionBB(g_Bullet[i].pos,pBlock[j].Position, D3DXVECTOR2(g_Bullet[i].w,g_Bullet[i].h),pBlock[j].Size))
				{
					g_Bullet[i].use = false;
				}

			}


		}
		if (g_Bullet[i].pos.y < SCREEN_LIMIT_UP - (g_Bullet[i].h / 2.0f))
		{
			g_Bullet[i].use = false;
		}
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)
		{
			//�e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Bullet[i].texno));
			//�X�v���C�g��\��
			D3DXCOLOR col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			//�����̈����Ԉ���Ă邩��
			SpriteDrawColorRotation(g_Bullet[i].pos.x, g_Bullet[i].pos.y, 0.0f, g_Bullet[i].w, g_Bullet[i].h, g_Bullet[i].rot, g_Bullet[i].col, g_Bullet[i].PaternNo, g_Bullet[i].uv_w, g_Bullet[i].uv_h, g_Bullet[i].NumPatern);
		}
	}
}

//=============================================================================
//�Z�b�g�֐�
//=============================================================================
void SetBullet(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == false)
		{
			g_Bullet[i].pos = pos;
			g_Bullet[i].h = BULLET_SIZE_H;
			g_Bullet[i].w = BULLET_SIZE_W;
			g_Bullet[i].use = true;
			//SetVolume(g_BulletSoundNo, 0.5f);
			PlaySound(g_BulletSoundNo, 0);
			return;
		}
	}
}

//=============================================================================
//�Q�b�g�֐�
//=============================================================================
BULLET* GetBullet()
{
	return g_Bullet;
}