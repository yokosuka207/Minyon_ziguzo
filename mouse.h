//-----------------------------------------------
//マウスでやる事管理[mouse.h]
//制作更新日:10/21
//製作者:新保翔麻
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
	bool ScrollFlag;	//スクロールしているかどうか

}MOUSE;

HRESULT InitGameMouse();
void UninitGameMouse();
void UpdateGameMouse();
//void DrawMouse();
MOUSE* GetMouse();

#endif // !MOUSE_H_


