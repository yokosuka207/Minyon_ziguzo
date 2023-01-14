//--------------------------------------
//�p�Y���̃`�b�v[puzzlecip.h]
//����X�V��10/21
//����ҁF�V���Ė�
//--------------------------------------
#pragma once

#ifndef PUZZLE_CIP_H_
#define PUZZLE_CIP_H_

#include"main.h"

#define CIP_MAX	(20)
#define	CIP_SIZE_X	(20)
#define	CIP_SIZE_Y	(20)
#define CIP_UV_W (1.0f / 4)
#define CIP_UV_H (1.0f / 4)

typedef enum
{
	CIP_NOMAL =0,	//���ʂ̃p�Y���`�b�v
	CIP_GOAL,		//�S�[���`�b�v
	CIP_NONE		//�����Ȃ�
}CIP_TYPE;

typedef enum
{
	CREATE_GRAND = 0,
	CREATE_HARFGRAND,
	CREATE_CENTER,
	CREATE_T,
	CREATE_SQUARE,
	CREATE_ZYUUZI,
	CREATE_TATE,
	CREATE_BOX,
	CREATE_COVER,
	CREATE_GOAL,
	CREATE_NUM


}CREATE_CIP_TYPE;


typedef struct
{
	D3DXVECTOR2	Position;	//�`�b�v�̈ʒu
	D3DXVECTOR2	Size;	//�傫��
	D3DXVECTOR2	DrawSize;	//�傫��
	D3DXCOLOR		Col;	//�F
	float			texno;	//�e�N�X�`���C���f�b�N�X
	float			Rotation;	//�p�x

	int				NextPieceIndex;	//���s�[�X�̔ԍ�
	int				PieceIndex;//�\���s�[�X�ԍ�
	CIP_TYPE	Type;	//�`�b�v�̎��
	CREATE_CIP_TYPE		Num_type;//���̃^�C�v
	int houkou[4];	//�����p�Y���o�����Ă��邩�Ђ�����ł��邩
	//CREATE_CIP_TYPE		Next_Type;//���̃`�b�v�̃^�C�v
	bool GoalFlag;	//�S�[���̃`�b�v��
	bool UseFlag;	//�g�p�t���O
	bool GetFlag;	//���ꂽ���ǂ���
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������


}PUZZLE_CIP;

HRESULT InitPuzzleCip();
void UninitPuzzleCip();
void UpdatePuzzleCip();
void DrawPuzzleCip();
void SetChipPuzzuleChip(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index);

void DeleteChipPiece(int index);

int SetPuzzleCip(D3DXVECTOR2 pos,D3DXVECTOR2 size,CIP_TYPE type);
PUZZLE_CIP* GetPuzzleCip();


#endif // !PUZZLE_CIP_H_

