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
static int g_Time = 0;
static int g_SecondTime = 0;
static int g_MintueTime = 0;
static int distance = (TIME_POS_X);
static TimeParam g_TimeParam;

void Time::InitTime() {
	g_TimeTextureNo = LoadTexture(g_TimeTextureName);
	g_TimeParam.pos = D3DXVECTOR2(0.0f,0.0f);
	g_TimeParam.size = D3DXVECTOR2(0.0f, 0.0f);
	g_TimeParam.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_TimeParam.UseFlag = false;
	g_TimeParam.PauseFlag = false;
	m_start = 0;
	m_end = 0;
	m_puase = 0;
	m_PuaseStart = 0;
	m_PuaseStart = 0;
	m_ElapsedTime = 0;
}
void Time:: DrawGameTime() {
	if (g_TimeParam.UseFlag) {
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

		m_ElapsedTime = ElapsedTime();
		if (g_TimeParam.PauseFlag) {
			m_puase = PauseTime();
		}
		g_Time = m_ElapsedTime / CLOCKS_PER_SEC;//秒表示
		g_SecondTime = g_Time % 60;	//秒
		g_MintueTime = g_Time / 60;	//分
		g_TimeParam.pos.x = distance;
		//1の位(秒)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x,
				g_TimeParam.pos.y,
				g_TimeParam.size.x,
				g_TimeParam.size.y,
				0.0f,
				g_TimeParam.color,
				(g_SecondTime) % 10,
				1.0f / 10.0f,
				1.0f / 1.0f,
				10
			);
			g_TimeParam.pos.x -= 30;
			g_SecondTime /= 10;
		}
		//10の位(秒)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x,
				g_TimeParam.pos.y,
				g_TimeParam.size.x,
				g_TimeParam.size.y,
				0.0f,
				g_TimeParam.color,
				(g_SecondTime) % 10,
				1.0f / 10.0f,
				1.0f / 1.0f,
				10
			);
			g_TimeParam.pos.x -= 30;
		}
		//1の位(分)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x - 5,
				g_TimeParam.pos.y,
				g_TimeParam.size.x,
				g_TimeParam.size.y,
				0.0f,
				g_TimeParam.color,
				(g_MintueTime) % 10,
				1.0f / 10.0f,
				1.0f / 1.0f,
				10
			);
			g_TimeParam.pos.x -= 30;
			g_MintueTime /= 10;
		}
		//10の位(分)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x - 5,
				g_TimeParam.pos.y,
				g_TimeParam.size.x,
				g_TimeParam.size.y,
				0.0f,
				g_TimeParam.color,
				(g_MintueTime) % 10,
				1.0f / 10.0f,
				1.0f / 1.0f,
				10
			);
			g_TimeParam.pos.x -= 30;
		}
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
	return m_end - m_puase - m_start;
}
int Time::ElapsedTime() {
	if(!g_TimeParam.PauseFlag) {
		m_ElapsedTime = clock();
	}
	return m_ElapsedTime - m_start;
}
//ポーズ時の経過時間
int Time::PauseTime() {
	if (g_TimeParam.PauseFlag) {
		m_puase = clock();
	}
	return m_puase - m_PuaseStart;
}
//ポーズの開始時間
void Time::PauseStartTime() {
	m_PuaseStart = clock();
}
//ポーズの終了時間
int Time::PuaseEndTime() {
	m_PuaseEnd = clock();
	return m_PuaseEnd - m_PuaseStart;
}
void Time::SetTime(D3DXVECTOR2 pos, D3DXVECTOR2 size) {
	if (!g_TimeParam.UseFlag) {
		g_TimeParam.pos = pos;
		g_TimeParam.size = size;
		g_TimeParam.UseFlag = true;
	}
}
int Time::GetTime() {
	return m_ElapsedTime;
}
TimeParam* GetTimeParam() {
	return &g_TimeParam;
}

