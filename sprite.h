/*==============================================================================
�X�v���C�g�`��
   �|���S������[sprite.h]
														 Author :�V���Ė�
														 Date   :6/13
--------------------------------------------------------------------------------*/
#pragma once
#ifndef SPRITE_H_
#define SPRITE_H_

//�C���N���[�h
#include"main.h"

//================================
//�}�N����`
//================================




//================================
//�v���g�^�C�v�錾
//�O���̃v���O�����Ɏg���Ăق����֐�
//================================





void	SpriteDrawColorRotation(float, float, int, int, float, D3DXCOLOR, 
	 float PaternNo, float uv_w, float uv_h, int NumPatern);	//�O�p�`�p���_�i�[����
void	SpriteInit();//������
void	SpriteUninit();//�I������
void	SpriteDrawColorBlockRotation(float, float, int, int, float, D3DXCOLOR,
	float, float PaternNo, float uv_w, float uv_h, int NumPatern);	//�O�p�`�p���_�i�[����

#endif // !SPRITTE_H_

