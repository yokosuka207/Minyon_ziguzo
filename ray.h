/*================================================================================

	�����w�b�_�[[ray.h]

												Author: ꎓ� ��o
												 Date : 2023/01/09
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _RAY_H_
#define _RAY_H_

#include "main.h"

//**************************************************
// �\����
//**************************************************
typedef struct
{
	D3DXVECTOR2		pos;			// ���W
	D3DXVECTOR2		StartPos;		// �n�_���W
	D3DXVECTOR2		EndPos;			// �I�_���W
	D3DXVECTOR2		size;			// �T�C�Y
	D3DXVECTOR2		dir;			// �������o���x�N�g��
	D3DXCOLOR		col;			// �F
	float			texNo;			// �e�N�X�`���C���f�b�N�X
	float			rot;			// �p�x
	
	int				PieceIndex;		// �s�[�X�̓Y�����i�[
	int				IssuerIndex;	// ���ˑ��u�̔ԍ�
	
	bool			bUse;			// �g�p�t���O

}RAY;

//**************************************************
// �v���g�^�C�v�錾
//**************************************************
void InitRay();
void UninitRay();
void UpdateRay();
void DrawRay();

// �Z�b�g�֐�
void SetRay(D3DXVECTOR2 SPos, D3DXVECTOR2 dir, int INo, int PNo);

// �f���[�g�֐�
void DeleteRayP(int PNo);
void DeleteRay(int INo);

#endif // !_RAY_H_
