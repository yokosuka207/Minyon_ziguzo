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
#define BLOCK_CHIP_SIZE (15.0f)	//�}�b�v�`�b�v�u���b�N�̃T�C�Y
#define BLOCK_DRAW_SIZE (16.0f)	//�}�b�v�`�b�v�u���b�N�̕\���T�C�Y
#define BLOCK_CHIP_MAX (12 * 12 * 10)//�}�b�v�`�b�v�̒��̃u���b�N�ő吔
#define BLOCK_CHIP_WARP_MAX (2)	//1�X�e�[�W���[�v�̌�
#define BLOCK_CHIP_DIRECTION (4)//�`�b�v�̉�]4������

#define PUZZLE_SIZE (BLOCK_CHIP_ARRAY * BLOCK_CHIP_SIZE)	//16 * 15 (180 + 60) 
#define PIECE_SIZE (180)
//**************************************************
// �\���̒�`
//**************************************************
enum class MAPCHIP_TYPE{
	TYPE_BLANK = 0,		// 0	�O���̋�
	TYPE_PUSH,			// 1	��
	TYPE_PULL,			// 2	��
	TYPE_NONE,			// 3	block�Ȃ�
	TYPE_BLOCK,			// 4	block
	TYPE_CHIP,			// 5	puzzle
	TYPE_WARP,			// 6	warp
	TYPE_GOAL,			// 7	goal
	TYPE_JUMP,			// 8	�W�����v��
	TYPE_SPIKE,			// 9	�g�Q
	TYPE_FALL,			//10	������u���b�N
	TYPE_KEY,			//11	��
	TYPE_DOOR,			//12	���t���h�A
	TYPE_SWITCH,		//13	switch
	TYPE_SWITCHWALL3,	//14	Switch��3
	TYPE_SWITCHWALL4,	//15	Switch��4
	TYPE_SHEET,			//16	�����鏰
	TYPE_BROKEN,		//17	���鏰
	TYPE_HIGHBROKEN,	//18	�W�����v�ŉ��鏰
	TYPE_MIRROR,		//19	��
	TYPE_SPWANPOINT,	//20	�X�|�[���|�C���g

	TYPE_NUM		
};

typedef struct {
	int			no;		//���݂̃s�[�X�ԍ�
	D3DXVECTOR2 pos;	//�p�Y���̍��W
	D3DXVECTOR2 OldPos;	//�ړ��poldpos
	D3DXVECTOR2 OldMovePos;//�����O�̍��W
	D3DXVECTOR2 size;	//�p�Y���̃T�C�Y
	int			chip[BLOCK_CHIP_DIRECTION][BLOCK_CHIP_ARRAY][BLOCK_CHIP_ARRAY];	//�p�Y���̒��̃u���b�N�̌�
	float		TexNo;
	int			direction;	//�p�Y���̕���
	bool		MoveEndFlag;//�����I������u��
	bool		MoveFlag;//�����Ă��邩
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
void SetMapChip(D3DXVECTOR2 pos, int no,int Pin);
//-----�t�@�C���ꊇ�Ǘ�----
void FileLoad(int StageNo);

//-----�s�[�X�̉�]------
void RotateChipData();
void RotateMapChipR(int PieceNo);
void RotateMapChipL(int PieceNo);
void DeleteMapChip(int PieceNo);

Piece* GetPiece();
void SetPieceMapChip(D3DXVECTOR2 pos, int PieceNo);

#endif // !_MAPCHIP_H_
