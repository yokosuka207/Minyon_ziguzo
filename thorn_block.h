/*==============================================================================

   �g�Q�u���b�N�w�b�_�[ [thorn_block.h]
														 Author		:���Ԍ��C
														 Date		:2022/11/09
														 �ŏI�X�V	:2022/11/224
==============================================================================*/

#pragma once

#include "main.h"
#include "renderer.h"


//=============================================================================
//�}�N����`
//=============================================================================


#define	THORN_BLOCK_MAX	64
#define THORN_BLOCK_H		30	//�u���b�N�̏c�T�C�Y
#define THORN_BLOCK_W		30	//�u���b�N�̉��T�C�Y

struct THORNBLOCK
{
	bool UseFlag;//�\���̗��p���t���O
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Postion;//�\�����W(���S���W)
	D3DXVECTOR2 sp;
	int			PieceIndex;
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������

	int FrameWait;
};

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

HRESULT InitThornBlock();
void UninitThornBlock();
void UpdateThornBlock();
void DrawThornBlock();

int SetThornBlock(D3DXVECTOR2 Pos, D3DXVECTOR2 s);
void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo);

THORNBLOCK* GetThornBlock();

