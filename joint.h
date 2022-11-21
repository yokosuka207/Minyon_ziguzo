/*================================================================================

	�W���C���g�w�b�_�[[joint.h]

												Author: ꎓ� ��o
												 Date : 2022/11/16
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _JOINT_H_
#define _JOINT_H_

#include "main.h"

//**************************************************
// �}�N����`
//**************************************************
#define JOINT_MAX		64


//**************************************************
// �\���́E�񋓌^
//**************************************************
// �W���C���g�^�C�v�̗񋓌^
enum class JOINT_TYPE
{
	TYPE_BUMP = 0,				// ��
	TYPE_DIP,					// ��
	TYPE_MAX
};

// �W���C���g�\����
typedef struct
{
	D3DXVECTOR2 pos;			// ���S���W
	D3DXVECTOR2 size;			// �T�C�Y
	D3DXCOLOR	color;			// �F
	int pieNo;					// �s�[�X�ԍ�
	JOINT_TYPE type;			// �W���C���g�^�C�v
	float texNo;				// �e�N�X�`���ԍ�
	
	bool useFlag;				// �g�p���t���O
}JOINT;

//**************************************************
// �v���g�^�C�v�錾
//**************************************************
//[----------��{�֐�----------
void InitJoint();
void UninitJoint();
void UpdateJoint();
void DrawJoint();
//----------��{�֐�----------]


//----------�W���C���g�Z�b�g�֐�----------
// �����F���W, �T�C�Y, �s�[�X�ԍ�, �W���C���g�^�C�v
void SetJoint(D3DXVECTOR2 po, D3DXVECTOR2 si, int no, JOINT_TYPE ty);


//----------�W���C���g�Q�b�g�֐�----------
JOINT* GetJoint();


//----------�W���C���g�폜�֐�----------
// �����F�s�[�X�ԍ�
void DeleteJoint(int no);



#endif // !_JOINT_H_
