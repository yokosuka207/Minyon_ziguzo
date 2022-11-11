/*==============================================================================

   �u���b�N�Ǘ� [block.h]
														  Author :�V���Ė�
														 Date   :10/18
--------------------------------------------------------------------------------*/
#pragma once

#ifndef BLOCK_H_
#define BLOCK_H_

#include "main.h"
#include "renderer.h"
#include"puzzlecip.h"

#define	BLOCK_MAX	64
#define BLOCK_H		30	//�u���b�N�̏c�T�C�Y
#define BLOCK_W		30	//�u���b�N�̉��T�C�Y

#define GRAND_H		30	//�u���b�N�̏c�T�C�Y
#define GRAND_W		135	//�u���b�N�̉��T�C�Y

#define SQUAER_H	40	//�l���u���b�N�̏c�T�C�Y
#define SQUAER_W	40	//�l���u���b�N�̉��T�C�Y

typedef enum
{
	GRAND_DOWN=0,
	GRAND_LEFT,
	GRAND_UP,
	GRAND_RIGHT,
	GRAND_NONE,

}GRAND_TYPE;

typedef enum
{
	TYPE_GRAND =0,
	TYPE_HARFGRAND,
	TYPE_CENTER,
	TYPE_T,
	TYPE_SQUARE,
	TYPE_ZYUUZI,
	TYPE_TATE,
	TYPE_BOX,
	TYPE_COVER,
	TYPE_NUM
}BLOCK_TYPE;

typedef struct
{
	D3DXVECTOR2		Position;	//�|�W�V����
	D3DXVECTOR2		Size;	//�T�C�Y
	D3DXCOLOR		Col;	//�F
	float			texno;	//�e�N�X�`���C���f�b�N�X
	float			Rotation;	//�p�x
	bool			UseFlag;	//�g�p�t���O

}BLOCK;

HRESULT InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

void SetBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size);
void SetBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size,GRAND_TYPE type,BLOCK_TYPE btype,int pIndex,CIP_TYPE ctype);
BLOCK* GetBlock();

#endif // !BLOCK_H_
