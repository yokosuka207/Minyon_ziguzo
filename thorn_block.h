/*==============================================================================

   �g�Q�u���b�N�w�b�_�[ [thorn_block.h]
														 Author :���Ԍ��C
														 Date   :2022/11/09

==============================================================================*/

#pragma once

#ifndef THORN_BLOCK_H_
#define THORN_BLOCK_H_

#include "main.h"
#include "renderer.h"

#define	THORN_BLOCK_MAX	64
#define THORN_BLOCK_H		30	//�u���b�N�̏c�T�C�Y
#define THORN_BLOCK_W		30	//�u���b�N�̉��T�C�Y

#define THORN_GRAND_H		30	//�u���b�N�̏c�T�C�Y
#define THORN_GRAND_W		135	//�u���b�N�̉��T�C�Y

#define THORN_SQUAER_H	40	//�l���u���b�N�̏c�T�C�Y
#define THORN_SQUAER_W	40	//�l���u���b�N�̉��T�C�Y

typedef enum
{
	THORN_GRAND_DOWN = 0,
	THORN_GRAND_LEFT,
	THORN_GRAND_UP,
	THORN_GRAND_RIGHT,
	THORN_GRAND_NONE,

}THORN_GRAND_TYPE;

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
	bool			UseFlag;	//�g�p�t���O

}THORN_BLOCK;

HRESULT InitThornBlock();
void UninitThornBlock();
void UpdateThornBlock();
void DrawThornBlock();

void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, THORN_GRAND_TYPE type, THORN_BLOCK_TYPE btype, int pIndex);
THORN_BLOCK* GetThornBlock();

#endif // !THORN_BLOCK_H_
