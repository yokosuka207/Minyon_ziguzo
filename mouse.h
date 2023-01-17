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

	D3DXVECTOR2	PlPos;	//プレイヤーの位置保存
	D3DXVECTOR2	Size;	//プレイヤーの位置保存

	int RotIndex;	//回転した回数

	bool UseFlag;
	bool ScrollFlag;	//スクロールしているかどうか
	bool pFlag;			//プレイヤーがいるかどうか

}MOUSE;

HRESULT InitGameMouse();
void UninitGameMouse();
void UpdateGameMouse();
//void DrawMouse();
MOUSE* GetMouse();

int GetXMousePosX();
int GetXMousePosY();

// マウス入力関数
// 左
bool Mouse_IsLeftDown();
bool Mouse_IsLeftUp();
bool Mouse_IsLeftTrigger();
bool Mouse_IsLeftRelease();
// 右
bool Mouse_IsRightDown();
bool Mouse_IsRightUp();
bool Mouse_IsRightTrigger();
bool Mouse_IsRightRelease();
// ホイール
bool Mouse_IsMiddleDown();
bool Mouse_IsMiddleup();
bool Mouse_IsMiddleTrigger();
bool Mouse_IsMiddleRelease();
/* 
	使い方

　使いたいシーンでInitとUpdate関数を呼んでから
　マウスの入力関数を使う
*/
#endif // !MOUSE_H_


