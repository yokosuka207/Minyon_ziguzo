/*================================================================================

	�����o���I�u�W�F�N�g�w�b�_�[[issuer.h]

												Author: ꎓ� ��o
												 Date : 2023/01/07
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _ISSUER_H_
#define _ISSUER_H_

#include "main.h"

//**************************************************
// �\����
//**************************************************
typedef struct
{
	D3DXVECTOR2		pos;			// ���W
	D3DXVECTOR2		size;			// �T�C�Y
	D3DXVECTOR2		dir;			// �������o���x�N�g��
	D3DXCOLOR		col;			// �F
	float			texNo;			// �e�N�X�`���C���f�b�N�X
	float			rot;			// �p�x
	
	int				PieceIndex;		// �s�[�X�̓Y�����i�[

	bool			bAct;			// �쓮�t���O
	bool			bUse;			// �g�p�t���O

}ISSUER;

//**************************************************
// �v���g�^�C�v�錾
//**************************************************
void InitIssuer();
void UninitIssuer();
void UpdateIssuer();
void DrawIssuer();

// �Z�b�g�֐�
void SetIssuer(D3DXVECTOR2 pos, D3DXVECTOR2 size,float rot, int PNo);

// �f���[�g�֐�
void DeleteIssuer(int PNo);

#endif // !_ISSUER_H_
