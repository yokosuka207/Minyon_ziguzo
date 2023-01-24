//=============================================================================
//
//����u���b�N����
//
//�����/�e�n ��@
//=============================================================================
#pragma once
#include "texture.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"
#include "main.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define FALLBLOCK_W (20)
#define FALLBLOCK_H (20)
#define FALLBLOCK_MAX (40)
typedef struct
{

	bool UseFlag;	//�\���̗��p���t���O
	D3DXVECTOR2 Size;	//BOX�T�C�Y
	D3DXVECTOR2 Position;	//�\�����W(���S���W)
	D3DXVECTOR2 oldpos;	//1�t���[���O�̍��W
	D3DXVECTOR2 sp;
	int PieceIndex;
	float rot;	//��]�p�x
	float texno;	//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;	//�F
	float PaternNo;	//�p�^�[���ԍ�
	float uv_w;	//���T�C�Y
	float uv_h;	//�c�T�C�Y
	//bool fall; //����
	//bool getfall;//�����̊J�n
	int NumPatern;	//������

	int FrameWait;
}FALLBLOCK;


//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitFallBlock();
void UninitFallBlock();
void UpdateFallBlock();
void DrawFallBlock();

FALLBLOCK*GetFallBlock();
void SetFallBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size ,int PieceNo);
void DeleteFallBlock(int PieceNo);

