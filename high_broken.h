//=============================================================================
//
//�����Ƃ��납�痎���������u���b�N����
//
//�����/���Ԍ��C�@�����/2022/11/29
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================

#define HIGH_SIZE_W (50)
#define HIGH_SIZE_H (10)
#define HIGH_MAX (10)
#define HIGH_SPEED (2.0f)

struct HIGH
{
	bool UseFlag;//�\���̗��p���t���O
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Postion;//�\�����W(���S���W)
	D3DXVECTOR2 sp;
	float rot;//��]�p�x
	int index;
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
HRESULT InitHigh();
void UninitHigh();
void UpdateHigh();
void DrawHigh();

void SetHigh(D3DXVECTOR2 Pos, D3DXVECTOR2 s,int index);
void DeleteHigh(int PieceNo);

HIGH* GetHigh();//BROKEN�\���̂̐擪�|�C���^���擾

//�����ȂƂ��̖��O�������Ȃ肻���������̂�High�œ��ꂵ�܂����A���͂���