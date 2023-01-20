/*================================================================================

	�{�^���w�b�_�[[button.h]

												Author: ꎓ� ��o
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	2022/12/07	SaitoReito
================================================================================*/
#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "main.h"

#define BUTTON_MAX (10)

enum class BUTTON_TYPE
{
	TYPE_NORMAL = 0,					// ������Ă��Ȃ�
	TYPE_PRESSED,						// ������Ă���
	TYPE_MAX
};

// �{�^���N���X
class Button
{
private:	
	D3DXVECTOR2 m_pos;										// ���S���W
	D3DXVECTOR2 m_drawPos;									// �\�����W
	D3DXVECTOR2 m_size;										// �T�C�Y
	D3DXCOLOR m_color;	// �F
	BUTTON_TYPE m_type = BUTTON_TYPE::TYPE_NORMAL;			// ���
	float m_texNo = -1;										// �e�N�X�`���̔ԍ�
	int m_num = -1;											// �N���A�X�e�[�W���\���p
	float m_numTexNo = -1;									// �����̃e�N�X�`��
	float m_frameTexNo = -1;								// �g�̃e�N�X�`��
	bool m_bSelect = false;									// �I������Ă��邩
public:
	Button() {}
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
	// �����F�|�W�V����, �T�C�Y, �e�N�X�`���ԍ�
	void SetButton(D3DXVECTOR2 po, D3DXVECTOR2 si, D3DXCOLOR co, float no);
	void SetButtonTexNo(float no) { m_texNo = no; }			// �e�N�X�`���؂�ւ�
	void SetNum(int num) { m_num = num; }		// �����̃Z�b�g
	void SetNumTexNo(float no) { m_numTexNo = no; }	// �����̃e�N�X�`���̃Z�b�g
	void SetIsSelect(bool bSelect) { m_bSelect = bSelect; }		// �I�΂�Ă��邩�̃Z�b�g

	// �}�E�X�Ƃ̓����蔻��
	bool CollisionMouse();
	// �{�^���������ꂽ
	bool ReleaseButton();
private:
	// �^�C�v�ύX
	void ChangeType(BUTTON_TYPE type) { m_type = type; }
};

#endif // !_BUTTON_H_
