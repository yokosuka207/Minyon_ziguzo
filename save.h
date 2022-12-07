/*================================================================================

	�Z�[�u�w�b�_�[[save.h]

												Author: ꎓ� ��o
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	2022/12/07	SaitoReito
================================================================================*/
#pragma once
#ifndef _SAVE_H_
#define _SAVE_H_


#include "button.h"

struct SaveData
{
	int clearStageNum = 0;
};

class Save
{
private:
	float m_BGTexNo = -1;		// �e�N�X�`���ԍ�		0�`2�F�f�[�^�̔ԍ�		3�F�w�i

	D3DXVECTOR2 m_BGPos;
	D3DXVECTOR2 m_BGSize;
	D3DXCOLOR m_BGColor;

	int m_dataNo;			// �Z�[�u�f�[�^�̔ԍ�

	SaveData m_saveData;		// �Z�[�u����f�[�^

public:
	Save() {}
	Save(int no) :m_dataNo(no){}
	~Save() {}

	// ��{�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �Z�[�u
	void DataSave();
	// �Z�[�u�f�[�^�̍폜
	void DeleteSaveData();
	// ���[�h
	void DataLoad();

	// �Q�b�^�[
	int GetDataNo()const { return m_dataNo; }		// �f�[�^�ԍ�
	// �Z�b�^�[
	void SetDataNo(int no) { if (0 < no && no < 4) { m_dataNo = no; } }		// �f�[�^�ԍ�(1�`3)

private:
	// �t�@�C���̗L���`�F�b�N
	bool ExistFile(char* fileName);
};

#endif // !_SAVE_H_
