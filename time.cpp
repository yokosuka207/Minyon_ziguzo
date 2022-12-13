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
static int g_TimeDistance = (TIME_POS_X);
static TimeParam g_TimeParam;

void Time::InitTime() {
	g_TimeTextureNo = LoadTexture(g_TimeTextureName);
	g_TimeParam.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_TimeParam.size = D3DXVECTOR2(0.0f, 0.0f);
	g_TimeParam.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_TimeParam.UseFlag = false;
	g_TimeParam.EndFlag = false;
	m_start = 0;
	m_PuaseStart = 0;
	m_PuaseStart = 0;
	m_ElapsedTime = 0;
	m_PauseElapsed = 0;
}
void Time::UninitTime() {
	if (g_TimeTexture != NULL) {
		g_TimeTexture->Release();
		g_TimeTexture = NULL;
	}
}
void Time:: DrawGameTime() {
	SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	m_ElapsedTime = ElapsedTime();
	g_Time = m_ElapsedTime / CLOCKS_PER_SEC;//秒表示
	g_SecondTime = g_Time % 60;	//秒
	g_MintueTime = g_Time / 60;	//分
	g_TimeParam.pos.x = g_TimeDistance;

	if (g_TimeParam.UseFlag) {
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

//ポーズ時間をどうにかしないと
void Time::DrawResultTime() {
	SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	g_TimeParam.pos.x = SCREEN_WIDTH / 2 + 70;
	g_TimeParam.pos.y = SCREEN_HEIGHT / 2;
	g_TimeParam.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (!g_TimeParam.EndFlag) {
		m_ElapsedTime = ElapsedTime();
		g_TimeParam.EndFlag = true;
	}
	g_Time = m_ElapsedTime / CLOCKS_PER_SEC;//秒表示
	g_SecondTime = g_Time % 60;	//秒
	g_MintueTime = g_Time / 60;	//分

	if (g_TimeParam.UseFlag) {
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
void Time::StartTime() {
	m_start = clock();
}
int Time::ElapsedTime() {
	m_ElapsedTime = clock() - m_start;
	return m_ElapsedTime;
}
//ポーズの開始時間
void Time::PuaseStartTime() {
	m_PuaseStart = clock();
}
//ポーズの終了時間
void Time::PuaseEndTime() {
	m_PuaseEnd = clock();
	//m_PauseElapsed += m_PuaseEnd - m_PuaseStart;
	m_ElapsedTime -= m_PuaseEnd - m_PuaseStart;
}
void Time::SetTime(D3DXVECTOR2 pos, D3DXVECTOR2 size) {
	if (!g_TimeParam.UseFlag) {
		g_TimeParam.pos = pos;
		g_TimeParam.size = size;
		g_TimeParam.UseFlag = true;
	}
}
int* Time::GetTime() {
	return &m_ElapsedTime;
}

void Time::SetElapsedTime(int elapsedtime) {
	m_ElapsedTime = elapsedtime;
}

TimeParam* Time::GetTimeParam() {
	return &g_TimeParam;
}

