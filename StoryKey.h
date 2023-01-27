//=============================================================================
//�S�[���p��
//
//�����/���Ԍ��C�@
//=============================================================================

#pragma once

#include "main.h"

//==============================================================
//�}�N����`
//==============================================================
//#define STORYKEY_SIZE	(1)
#define STORYKEY_MAX	(8)


typedef struct
{
	D3DXVECTOR2 pos;		//�\���ʒu
	D3DXVECTOR2 size;		//�T�C�Y
	D3DXCOLOR	col;		//�F

	float	rot;				//��]
	int		no;				//�}�b�v�`�b�v�ԍ�

	bool	bUse;			//�g�p���t���O

	int		HaveSKey;			//��������

}STORYKEY;

//==============================================================
//�v���g�^�C�v�錾
//==============================================================

HRESULT InitStoryKey();
void UninitStoryKey();
void UpdateStoryKey();
void DrawStoryKey();

void SetStoryKey(D3DXVECTOR2 p, D3DXVECTOR2 s, int no, int direction, int tex);
STORYKEY* GetStoryKey();
void DeleteStoryKey(int no);
