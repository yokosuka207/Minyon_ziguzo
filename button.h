/*================================================================================

	�{�^���w�b�_�[[button.h]

												Author: ꎓ� ��o
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "main.h"

// �{�^���N���X
class Button
{
private:	
	D3DXVECTOR2 m_pos;										// ���S���W
	D3DXVECTOR2 m_size;										// �T�C�Y
	D3DXCOLOR m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	int m_type = 1;											// ���	1�F�m�[�}���@-1�F������Ă���
	float m_texNo = -1;											// �e�N�X�`���̔ԍ�
public:
	Button() {}
	// �����F�|�W�V����, �T�C�Y, �e�N�X�`���ԍ�
	Button(D3DXVECTOR2 po, D3DXVECTOR2 si, float no) : m_pos(po), m_size(si), m_texNo(no) {}
	~Button() {}

	// ��{�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �e��Q�b�^�[
	D3DXVECTOR2 GetPosition() { return m_pos; }
	D3DXVECTOR2 GetSize() { return m_size; }
	
	// �Z�b�^�[
	void SetButton(D3DXVECTOR2 po, D3DXVECTOR2 si, float no);

	// �^�C�v�ύX
	void ChangeType() { m_type *= -1; }
};

#endif // !_BUTTON_H_
