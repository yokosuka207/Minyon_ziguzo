/*==============================================================================

   ���ʃw�b�_�[ [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1422)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(800)				// �E�C���h�E�̍���

#define SCREEN_LIMIT_UP	(0)	//��̌��E
#define SCREEN_LIMIT_DOWN	(SCREEN_HEIGHT)	//��̌��E
#define SCREEN_LIMIT_RIGHT	(SCREEN_WIDTH)	//��̌��E
#define SCREEN_LIMIT_LEFT	(0)	//��̌��E

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
long GetMousePosX(void);
long GetMousePosY(void);

