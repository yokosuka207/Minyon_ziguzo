/*==============================================================================

   �w�i�Ǘ� [bg.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/
#pragma once

#include "main.h"
#include "renderer.h"
typedef struct
{
	//���̎l������Ύ�芸�����\���ł���
	D3DXVECTOR3		Position;	//�\�����W
	D3DXCOLOR		Color;		//�\���F
	float			Rotation;	//�p�x
	D3DXVECTOR2		Size;		//�|���S���̃T�C�Y
		//float w, h;	//�{�b�N�X�T�C�Y
	float texno;	//�e�N�X�`���C���f�b�N�X

	bool UseFlag;	//�g�p�t���O

}BG;

HRESULT BgInit();
void BgUninit();
void BgUpdate();
void BgDraw();
void SetVertexBG(float PosX, float PosY, int Size_W, int Size_H, float Kakudo, D3DXCOLOR COL, float sokudo);
