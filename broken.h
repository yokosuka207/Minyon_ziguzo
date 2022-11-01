//=============================================================================
//
//����u���b�N����
//
//�����/��t���l�@�����/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================

#define BROKEN_SIZE_W (50)
#define BROKEN_SIZE_H (10)
#define BROKEN_MAX (10)
#define BROKEN_SPEED (2.0f)

struct BROKEN
{
	bool UseFlag;//�\���̗��p���t���O
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Postion;//�\�����W(���S���W)
	D3DXVECTOR2 sp;
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
HRESULT InitBroken();
void UninitBroken();
void UpdateBroken();
void DrawBroken();

int SetBroken(D3DXVECTOR2 Pos, D3DXVECTOR2 s);

BROKEN* GetBroken();//BROKEN�\���̂̐擪�|�C���^���擾