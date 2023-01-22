#pragma once

#include "main.h"

//====================
//�}�N����`
//=====================

#define STORY_MAX	(8)
#define	STORY_BLOCK_SIZE (30)

typedef	struct
{
	D3DXVECTOR2		pos;	//�\�����W
	D3DXVECTOR2		size;	//�T�C�Y
	D3DXVECTOR2		sp;		//�ړ��X�s�[�h
	D3DXCOLOR		color;	//�F

	bool			bUse;	//�X�g�[���[�擾�t���O
	bool			KeyUse;

	int				HaveKey;

	int				n;


}STORY;

typedef enum
{
	STORY_NONE = 0,
	STORY_1,
	STORY_2,
	STORY_3,
	STORY_4,
	STORY_5,
	STORY_6,
	STORY_7,
	STORY_8,

}STORY_NUMBER;


//======================
//�v���g�^�C�v�錾
//======================

void	InitStory();
void	UninitStory();
void	UpdateStory();
void	DrawStory();

STORY* GetStory();
