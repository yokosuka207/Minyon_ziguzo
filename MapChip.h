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
#define PUZZLE_DRAW_SIZE (360)	// �p�Y���̕\���T�C�Y
#define PIECE_SIZE (180)
#define INVENTORY_PUZZLE_SIZE (BLOCK_CHIP_ARRAY * 6.0f)	//16 * 15 (180 + 60) 

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
	TYPE_BROKEN,		//17	�W�����v�ŉ󂷃u���b�N
	TYPE_HIGHBROKEN,	//18	���n�ŉ��鏰
	TYPE_MIRROR,		//19	��
	TYPE_SPWANPOINT,	//20	�X�|�[���|�C���g
	TYPE_MOVEBLOCK,		//21	�����u���b�N
	TYPE_DOPPELGANGER,	//22	�h�b�y���Q���K�[
	TYPE_ENEMY_LEFT,			//23	�G
	TYPE_ENEMY_RIGHT,		//24	�G
	TYPE_START,			//25    �����ʒu
	TYPE_PIACEEXPLAIN,		//26	�s�[�X��]�����u���b�N�@
	TYPE_PIACEEXPLAIN2,		//27	�s�[�X��]�����u���b�N�A
	TYPE_PIACEEXPLAIN3,		//28	�s�[�X��]�����u���b�N�B
	TYPE_BLOCKEXPLAIN,		//29	�u���b�N��]���Ă��������傤�Ԃ���q���g�u���b�N
	TYPE_ENEMYEXPLAIN,		//30	�G�q���g�u���b�N
	TYPE_BROKENEXPLAIN,		//31	����u���b�N�q���g�u���b�N
	TYPE_MOVEEXPLAIN,		//32	���̏�Ƀu���b�N�������q���g�u���b�N
	TYPE_SHEEREXPLAIN,		//33	�u���b�N�������q���g�u���b�N
	TYPE_STORYKEY_1,		//34	�X�g�[���[�L�[1
	///////////////////////TYPE_EXPLAIN,		//35	�q���g�u���b�N
	TYPE_LAMP,			//36	�X��
	TYPE_LAMP_SWITCH,	//37	�X���X�C�b�`
	TYPE_SPWANPOINT_D,	//38	�h�b�y���Q���K�[�̃X�|�[���|�C���g
	TYPE_PIACEEXPLAIN4,		//39	�s�[�X��]�����u���b�N4
	TYPE_PIACEEXPLAIN5,		//40	�s�[�X��]�����u���b�N5
	TYPE_PIACEEXPLAIN6,		//41	�s�[�X��]�����u���b�N6
	TYPE_PIACEEXPLAIN7,		//42	�s�[�X��]�����u���b�N7
	TYPE_STORYKEY_2,		//43	�X�g�[���[2
	TYPE_STORYKEY_3,		//44	�X�g�[���[3
	TYPE_STORYKEY_4,		//45	�X�g�[���[4
	TYPE_STORYKEY_5,		//46	�X�g�[���[5
	TYPE_STORYKEY_6,		//47	�X�g�[���[6

	TYPE_NUM		
};

typedef struct {
	int			no;		//���݂̃s�[�X�ԍ�
	D3DXVECTOR2 pos;	//�p�Y���̍��W
	D3DXVECTOR2 OldPos;	//�ړ��poldpos
	D3DXVECTOR2 OldMovePos;//�����O�̍��W
	D3DXVECTOR2 size;	//�p�Y���̃T�C�Y
	int			chip[BLOCK_CHIP_DIRECTION][BLOCK_CHIP_ARRAY][BLOCK_CHIP_ARRAY];	//�p�Y���̒��̃u���b�N�̌�
	int			startAngle;		// �����p�x
	float		TexNo;
	float		uvH;		// �e�N�X�`����UV�l�@�c
	float		uvW;		// �e�N�X�`����UV�l�@��
	float		PatNo;		// �A�j���[�V�����p�^�[���i���o�[
	int			direction;	//�p�Y���̕���
	int			texDir;		// �e�N�X�`���̕���
	bool		MoveEndFlag;//�����I������u��
	bool		MoveFlag;//�����Ă��邩
	bool		InventoryFlag;	//�C���x���g���̃p�Y����
	bool		UseFlag;//�p�Y�����o�����Ă��邩�ۂ�
	bool		bAnim;	// �A�j���[�V��������
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
void SetField(D3DXVECTOR2 position, D3DXVECTOR2 DrawSize, int no, int Pin, int i, int j);
//-----�t�@�C���ꊇ�Ǘ�----
void FileLoad(int StageNo);

//-----�s�[�X�̉�]------
void RotateChipData();
void RotateMapChipR(int PieceNo);
void RotateMapChipL(int PieceNo);
void DeleteMapChip(int PieceNo);

Piece* GetPiece();
void SetPieceMapChip(D3DXVECTOR2 pos, int PieceNo);
void SetInventoryMapChip(D3DXVECTOR2 pos, int no, int Pin);

// �s�[�X�̃A�j���[�V�����X�^�[�g
void StartPieceAnimation(int PieceNo);

#endif // !_MAPCHIP_H_
