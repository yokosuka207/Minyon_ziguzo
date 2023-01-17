//-----------------------------------------------
//�}�E�X�ł�鎖�Ǘ�[mouse.h]
//����X�V��:10/21
//�����:�V���Ė�
//-----------------------------------------------
#pragma once

#ifndef MOUSE_H_
#define	MOUSE_H_

#include"main.h"

typedef struct
{
	long	PosX;
	long	PosY;
	long	oldPosX;
	long	oldPosY;

	D3DXVECTOR2	PlPos;	//�v���C���[�̈ʒu�ۑ�
	D3DXVECTOR2	Size;	//�v���C���[�̈ʒu�ۑ�

	int RotIndex;	//��]������

	bool UseFlag;
	bool ScrollFlag;	//�X�N���[�����Ă��邩�ǂ���
	bool pFlag;			//�v���C���[�����邩�ǂ���

}MOUSE;

HRESULT InitGameMouse();
void UninitGameMouse();
void UpdateGameMouse();
//void DrawMouse();
MOUSE* GetMouse();

int GetXMousePosX();
int GetXMousePosY();

// �}�E�X���͊֐�
// ��
bool Mouse_IsLeftDown();
bool Mouse_IsLeftUp();
bool Mouse_IsLeftTrigger();
bool Mouse_IsLeftRelease();
// �E
bool Mouse_IsRightDown();
bool Mouse_IsRightUp();
bool Mouse_IsRightTrigger();
bool Mouse_IsRightRelease();
// �z�C�[��
bool Mouse_IsMiddleDown();
bool Mouse_IsMiddleup();
bool Mouse_IsMiddleTrigger();
bool Mouse_IsMiddleRelease();
/* 
	�g����

�@�g�������V�[����Init��Update�֐����Ă�ł���
�@�}�E�X�̓��͊֐����g��
*/
#endif // !MOUSE_H_


