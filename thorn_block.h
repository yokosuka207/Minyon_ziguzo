/*==============================================================================

   �g�Q�u���b�N�w�b�_�[ [thorn_block.h]
														 Author		:���Ԍ��C
														 Date		:2022/11/09
														 �ŏI�X�V	:2022/11/224
==============================================================================*/

#pragma once

#include "main.h"
#include "renderer.h"

#define	THORN_BLOCK_MAX	(5)

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
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������

	int FrameWait;
};

typedef enum
{
	THORN_TYPE_GRAND = 0,
	THORN_TYPE_HARFGRAND,
	THORN_TYPE_CENTER,
	THORN_TYPE_T,
	THORN_TYPE_SQUARE,
	THORN_TYPE_NUM
}THORN_BLOCK_TYPE;

typedef struct
{
	D3DXVECTOR2		Position;	//�|�W�V����
	D3DXVECTOR2		Size;	//�T�C�Y
	D3DXCOLOR		Col;	//�F
	float			texno;	//�e�N�X�`���C���f�b�N�X
	float			Rotation;	//�p�x
	int				PieceNo;	
	bool			UseFlag;	//�g�p�t���O

}THORN_BLOCK;
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

HRESULT InitThornBlock();
void UninitThornBlock();
void UpdateThornBlock();
void DrawThornBlock();

void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo);
THORN_BLOCK* GetThornBlock();
int SetThornBlock(D3DXVECTOR2 Pos, D3DXVECTOR2 s);

THORN_BLOCK* GetThornBlock();

