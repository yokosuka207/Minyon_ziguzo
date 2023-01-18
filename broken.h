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
#define BROKEN_MAX (20)
#define BROKEN_SPEED (2.0f)

struct BROKEN
{
	bool UseFlag;//�\���̗��p���t���O
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Postion;//�\�����W(���S���W)
	D3DXVECTOR2 sp;
	float rot;//��]�p�x
	int index;	//�s�[�X�̔ԍ�
	int Number;	//�s�[�X�̉��Ԗڂ̃u���b�N��
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������

	int FrameWait;

	bool breakFlag;	//��ꂽ���ǂ���
};

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitBroken();
void UninitBroken();
void UpdateBroken();
void DrawBroken();

void SetBroken(D3DXVECTOR2 Pos, D3DXVECTOR2 s,int index,int number);
void DeleteBroken(int PieceNo);
BROKEN* GetBroken();//BROKEN�\���̂̐擪�|�C���^���擾