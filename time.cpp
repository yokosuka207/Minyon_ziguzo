//=============================================================================
//
//	時間処理[time.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/29
//=============================================================================

#include "time.h"
#include "sprite.h"
#include "texture.h"
#include <iostream>
#include <Windows.h>
#include <vector>
//*****************************************************************************
//	マクロ定義
//*****************************************************************************

//*****************************************************************************
//	グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView* g_TimeTexture;	//画像一枚で一つの変数が必要
static char* g_TimeTextureName = (char*)"data\\texture\\number.png";	//テクスチャファイルパス
static int g_TimeTextureNo = 0;
static int g_time = 0;
static int distance = (SCREEN_WIDTH / 2);
static TimeParam g_TimeParam;

void Time::InitTime() {
	g_TimeTextureNo = LoadTexture(g_TimeTextureName);
	g_TimeParam.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_TimeParam.size = D3DXVECTOR2(50.0f, 50.0f);
	g_TimeParam.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
void Time:: DrawGameTime() {

	SetWorldViewProjection2D();

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	m_ElapsedTime = ElapsedTime();
	g_time = m_ElapsedTime / CLOCKS_PER_SEC;//秒表示
	g_TimeParam.pos.x = distance;

	for (int i = 0; i < 2; i++) {
		SpriteDrawColorRotation(
			g_TimeParam.pos.x,
			g_TimeParam.pos.y,
			g_TimeParam.size.x,
			g_TimeParam.size.y,
			0.0f,
			g_TimeParam.color,
			(g_time % 60) % 10,
			1.0f / 10.0f,
			1.0f / 1.0f,
			10
		);
		g_TimeParam.pos.x -= 30;
		g_time /= 10;
	}

	for (int i = 0; i < 2; i++) {
		SpriteDrawColorRotation(
			g_TimeParam.pos.x - 5,
			g_TimeParam.pos.y,
			g_TimeParam.size.x,
			g_TimeParam.size.y,
			0.0f,
			g_TimeParam.color,
			(g_time / 60) % 10,
			1.0f / 10.0f,
			1.0f / 1.0f,
			10
		);
		g_TimeParam.pos.x -= 30;
		g_time /= 10;
	}
}
void Time::DrawResultTime() {
	SetWorldViewProjection2D();

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	SpriteDrawColorRotation(
		g_TimeParam.pos.x,
		g_TimeParam.pos.y,
		g_TimeParam.size.x,
		g_TimeParam.size.y,
		0.0f,
		g_TimeParam.color,
		EndTime(),
		1.0f / 10.0f,
		1.0f / 1.0f,
		10
	);
}
void Time::StartTime() {
	m_start = clock();
}
int Time:: EndTime() {
	m_end = clock();
	return m_end - m_start;
}
int Time::ElapsedTime() {
	m_ElapsedTime = clock();
	return m_ElapsedTime;
}
int Time::GetTime() {
	return m_ElapsedTime;
}
