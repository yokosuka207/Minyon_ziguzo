#pragma once

#include "main.h"

//====================
//�}�N����`
//=====================
typedef	struct
{
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
}PAUSE;


//======================
//�v���g�^�C�v�錾
//======================

void	InitPause();
void	UninitPause();
void	UpdatePause();
void	DrawPause();
//void	SetPause(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col);