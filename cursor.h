/*================================================================================

	�J�[�\���w�b�_�[[cursor.h]

												Author: ꎓ� ��o
												 Date : 2022/11/21
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef CURSOR_H_
#define CURSOR_H_

#include "main.h"
#include "renderer.h"

//--------------------------------------------------
// �}�N����`
//--------------------------------------------------
typedef struct
{
	D3DXVECTOR2 size;			// BOX�T�C�Y
	D3DXVECTOR2 pos;			// �\�����W�i���S���W�j
	D3DXVECTOR2 oldPos;			// 1�t���[���O�̍��W
	D3DXVECTOR2 sp;				// �X�s�[�h
	D3DXCOLOR color;			// �F
	float texNo;				// �e�N�X�`���C���f�b�N�X

	bool useFlag;				// �g�p���t���O
}CURSOR;

//--------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------
//[----------��{�֐�----------
HRESULT InitCursor();
void UninitCursor();
void UpdateCursor();
void DrawCursor();
//----------��{�֐�----------]

//----------�J�[�\���Z�b�g�֐�----------
// �����F���S���W, �T�C�Y
void SetCursor(D3DXVECTOR2 pos, D3DXVECTOR2 size);

//----------�J�[�\���Q�b�g�֐�----------
// �Ԓl�F�J�[�\���\���̂̃|�C���^
CURSOR* GetCurso();		// �Q�b�g�֐�

//----------�J�[�\���폜�֐�----------
void DeleteCursor();

#endif // !CURSOR_H_
