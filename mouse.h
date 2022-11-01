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

	bool UseFlag;
	bool ScrollFlag;	//�X�N���[�����Ă��邩�ǂ���

}MOUSE;

HRESULT InitGameMouse();
void UninitGameMouse();
void UpdateGameMouse();
//void DrawMouse();
MOUSE* GetMouse();

#endif // !MOUSE_H_


