/*==============================================================================

   共通ヘッダー [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1422)				// ウインドウの幅
#define SCREEN_HEIGHT	(800)				// ウインドウの高さ

#define SCREEN_LIMIT_UP	(0)	//上の限界
#define SCREEN_LIMIT_DOWN	(SCREEN_HEIGHT)	//上の限界
#define SCREEN_LIMIT_RIGHT	(SCREEN_WIDTH)	//上の限界
#define SCREEN_LIMIT_LEFT	(0)	//上の限界

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
long GetMousePosX(void);
long GetMousePosY(void);

