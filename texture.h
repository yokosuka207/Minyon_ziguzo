/*==============================================================================

   �e�N�X�`���̊Ǘ�[texture.h]
   ���[�h�̊ȗ���
   �d�������摜�̓��[�h���Ȃ�
														 Author :�V���Ė�
														 Date   :6/13
--------------------------------------------------------------------------------*/

#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include"renderer.h"
#include"main.h"

///============================
//�}�N����`
//-----------------------------


///============================
//�v���g�^�C�v�錾
//-----------------------------
int LoadTexture(char* filename);

void Uninittexture();
//�e�N�X�`���f�[�^�̎擾
ID3D11ShaderResourceView**	GetTexture(int index);	//�|�C���^�ϐ��̃|�C���^




#endif // !TEXTURE_H_
