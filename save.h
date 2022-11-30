/*================================================================================

	�Z�[�u�w�b�_�[[save.h]

												Author: ꎓ� ��o
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _SAVE_H_
#define _SAVE_H_


#include "button.h"

class Save
{
private:
	float m_BGTexNo = -1;		// �e�N�X�`���ԍ�		0�`2�F�f�[�^�̔ԍ�		3�F�w�i

	D3DXVECTOR2 m_BGPos;
	D3DXVECTOR2 m_BGSize;
	D3DXCOLOR m_BGColor;

public:
	Save() {}
	~Save() {}

	// ��{�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �Z�[�u
	void Saved(int no);
	// �Z�[�u�f�[�^�̍폜
	void DeleteSaveData(int no);
};

#endif // !_SAVE_H_
