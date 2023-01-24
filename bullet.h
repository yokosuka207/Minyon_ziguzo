
//=============================================================================
//
//�o���b�g����
//
//�����/SORA�@
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "enemy.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BULLET_MAX (100)
#define BULLET_SPEED (4.0f)
#define BULLET_SIZE_W (ENEMY_SIZE_W)
#define BULLET_SIZE_H (ENEMY_SIZE_H / 3)

struct BULLET
{
	bool use;//�\���̗��p���t���O
	float w, h;//BOX�T�C�Y
	D3DXVECTOR2 pos;//�\�����W(���S���W)
	D3DXVECTOR2 sp;//�ړ����W
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������
	bool hit;
	int Damage; //�e�ɂ��_���[�W
};

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();
BULLET* GetBullet();//BULLET�\���̂̐擪�|�C���^���擾
void SetBullet(D3DXVECTOR2 pos,D3DXVECTOR2 size, D3DXVECTOR2 spd);//�e����
