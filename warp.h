//=============================================================================
//
//���[�v����
//
//�����/��t���l�@�����/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================

#define WARP_SIZE_W (20)
#define WARP_SIZE_H (20)
#define WARP_MAX (2)
#define WARP_SPEED (2.0f)

//���[�v �A�j���[�V����
#define WARP_UV_W (1.0f / 4)
#define WARP_UV_H (1.0f / 4)

struct WARP
{
	bool UseFlag;//�\���̗��p���t���O
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Position;//�\�����W(���S���W)
	D3DXVECTOR2 sp;
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������


	int		PieceIndex; //�s�[�X�̓Y�����i�[

	int FrameWait;
};

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitWarp();
void UninitWarp();
void UpdateWarp();
void DrawWarp();

void cipSetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index);


int SetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size);

WARP* GetWarp();//WARP�\���̂̐擪�|�C���^���擾