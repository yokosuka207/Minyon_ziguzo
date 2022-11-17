/*==============================================================================

   �}�b�v�`�b�v�w�b�_�[ [MapChip.h]
														 Author : ���؁@��
														 Date   : 2022/11/01
--------------------------------------------------------------------------------
 Update: 
 22/11/01 fusegi
 22/11/02 fusegi
 22/11/04 fusegi
==============================================================================*/

#ifndef _MAPCHIP_H_
#define _MAPCHIP_H_

#include "main.h"
#include "renderer.h"

//**************************************************
//�@�}�N����`
//**************************************************
#define BLOCK_CHIP_ARRAY (16)	// �z��̍ŏ��P��
#define BLOCK_CHIP_SIZE (15)	//�}�b�v�`�b�v�u���b�N�̃T�C�Y
#define BLOCK_CHIP_MAX (12 * 12)//�}�b�v�`�b�v�̒��̃u���b�N�ő吔
#define BLOCK_CHIP_WARP_MAX (2)	//1�X�e�[�W���[�v�̌�
#define BLOCK_CHIP_DIRECTION (4)//�`�b�v�̉�]4������

#define PUZZLE_SIZE (BLOCK_CHIP_ARRAY * BLOCK_CHIP_SIZE)	//180 + 60 
#define PIECE_SIZE (180)
//**************************************************
// �\���̒�`
//**************************************************
enum class MAPCHIP_TYPE{
	TYPE_NONE = 0,	//0
	TYPE_BLOCK,		//1
	TYPE_CHIP,		//2
	TYPE_WARP,		//3
	TYPE_GOAL,		//4

	TYPE_BLANK,		//5	�O���̋�
	TYPE_PUSH,		//6	��
	TYPE_PULL,		//7	��

	TYPE_NUM,		
};

typedef struct {
	int			no;		//���݂̃s�[�X�ԍ�
	D3DXVECTOR2 pos;	//�p�Y���̍��W
	D3DXVECTOR2 OldPos;	//�ړ��poldpos
	D3DXVECTOR2 size;	//�p�Y���̃T�C�Y
	int			chip[BLOCK_CHIP_DIRECTION][BLOCK_CHIP_ARRAY][BLOCK_CHIP_ARRAY];	//�p�Y���̒��̃u���b�N�̌�
	float		TexNo;
	int			direction;	//�p�Y���̕���
	bool		MoveEndFlag;//�����I������u��
	bool		UseFlag;//�p�Y�����o�����Ă��邩�ۂ�

}Piece;

//**************************************************
// �v���g�^�C�v�錾
//**************************************************

//**************************************************
// �O���[�o���ϐ�:
//**************************************************

HRESULT InitMapChip();
void UninitMapChip();
void UpdateMapChip();
void DrawMapChip();

//-----enum�ʂɃZ�b�g-----
void SetMapChip(D3DXVECTOR2 pos, int no);
//-----�t�@�C���ꊇ�Ǘ�-----
void FileLoad(int StageNo);

//-----�s�[�X�̉�]------
void RotateChipData();
void RotateMapChipR(int PieceNo);
void RotateMapChipL(int PieceNo);

Piece* GetPiece();
void SetPieceMapChip(D3DXVECTOR2 pos, int PieceNo);

#endif // !_MAPCHIP_H_
