/*==============================================================================

   �p�Y���Ǘ� [puzzle.h]
														 Author :�V���Ė�
														 Date   :10/18
--------------------------------------------------------------------------------*/

#pragma once

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include "main.h"
#include "renderer.h"
#include"block.h"
//#include"puzzlecip.h"
#define	PUZZLE_MAX	16

#define PUZZLE_WIDHT	180
#define PUZZLE_HEIGHT	180
#define	NUM_PUZZLE_VERTEX	(64)		//�p�Y���p���_��

typedef enum
{
	STEAT_NUM = 0,
	STEAT_DEPPARI,
	STEAT_HIKKOMI,
}PUZZLE_STEAT;

typedef enum
{
	TYPE_NOMAL =0,
	TYPE_GOAL,
	TYPE_NONE

}PUZZLE_TYPE;



typedef struct
{
	D3DXVECTOR2		Position;	//�|�W�V����
	D3DXVECTOR2		oldPosition;	//1�t���[���O�̃|�W�V����
	D3DXVECTOR2		OneOldPosition;//�ЂƂO�̃p�Y���̈ʒu�ɖ߂�

	D3DXVECTOR2		Size;	//�T�C�Y
	D3DXCOLOR		Col;	//�F
	float			texno;	//�e�N�X�`���C���f�b�N�X
	float			Rotation;	//�p�x
	float			oldRotation;//1�t���[���O�̊p�x

	PUZZLE_STEAT		InitPuzzle_TypeUp;	//�ŏ��̏�������݃^�C�v
	PUZZLE_STEAT		InitPuzzle_TypeDown;	//�ŏ��̉��������݃^�C�v
	PUZZLE_STEAT		InitPuzzle_TypeLeft;	//�ŏ��̍��������݃^�C�v
	PUZZLE_STEAT		InitPuzzle_TypeRight;	//�ŏ��̉E�������݃^�C�v

	PUZZLE_STEAT		Puzzle_TypeUp;	//��������݃^�C�v
	PUZZLE_STEAT		Puzzle_TypeDown;	//���������݃^�C�v
	PUZZLE_STEAT		Puzzle_TypeLeft;	//���������݃^�C�v
	PUZZLE_STEAT		Puzzle_TypeRight;	//�E�������݃^�C�v

	PUZZLE_TYPE			Puzzle_type;	//�p�Y���̃s�[�X�̎��

	BLOCK_TYPE			Block_Type;	//�p�Y�����̃u���b�N�̃^�C�v

	int				blockIndex[4];	//block�̓Y����
	int				CipIndex;	//�`�b�v�̃C���f�b�N�X
	int				BrokenIndex;//����u���b�N�̃C���f�b�N�X
	int				WarpIndex[2];	//���[�v�̃C���f�b�N�X
	int				RotNum;	//��]������
	bool			MoveFlag;	//�����Ă��邩
	bool			MoveEndFlag;	//�����I�������
	bool			UseFlag;	//�g�p�t���O

}PUZZLE;

HRESULT InitPuzzle();
void UninitPuzzle();
void UpdatePuzzle();
void DrawPuzzle();

PUZZLE* GetPuzzle();
void SetPuzzle(D3DXVECTOR2 pos, D3DXVECTOR2 size, PUZZLE_STEAT PTUp, PUZZLE_STEAT PTDown, PUZZLE_STEAT PTLeft, PUZZLE_STEAT PTRigft,
	GRAND_TYPE gtype,PUZZLE_TYPE ptype,CIP_TYPE cType,BLOCK_TYPE btype,bool Wflag);

void	SpriteDrawColorRotationPuzzle(D3DXVECTOR2, D3DXVECTOR2, float, D3DXCOLOR,
	PUZZLE_STEAT, PUZZLE_STEAT, PUZZLE_STEAT, PUZZLE_STEAT);	//�O�p�`�p���_�i�[����
void PuzzleTypeShift(int index);	//90�x�㉺���E�̃p�Y�������ւ���


void PuzzleBlockUpdate(PUZZLE puzzle);//�p�Y���̃u���b�N�̍X�V


#endif // !BLOCK_H_
