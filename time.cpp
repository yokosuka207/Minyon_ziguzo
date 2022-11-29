//=============================================================================
//
//	���ԏ���[time.cpp]
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
//	�}�N����`
//*****************************************************************************
#define TIME_POS_X (SCREEN_WIDTH / 2)
#define TIME_POS_Y (SCREEN_HEIGHT / 2)
#define TIME_SIZE (200.0f)

//*****************************************************************************
//	�O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView* g_TimeTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_TimeTextureName = (char*)"data\\texture\\number.png";	//�e�N�X�`���t�@�C���p�X
static int g_TimeTextureNo = 0;

void Time::InitTime() {
	g_TimeTextureNo = LoadTexture(g_TimeTextureName);
}
void Time:: DrawGameTime() {

	SetWorldViewProjection2D();

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	SpriteDrawColorRotation(
		TIME_POS_X,TIME_POS_Y,TIME_SIZE,TIME_SIZE,
		0.0f,
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		m_ElapsedTime / CLOCKS_PER_SEC,	//���ƕb�ŕ\��3��
		1.0f / 10.0f,
		1.0f / 1.0f,
		10
	);
}
void Time::DrawResultTime() {
	SetWorldViewProjection2D();

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	SpriteDrawColorRotation(
		TIME_POS_X, TIME_POS_Y, TIME_SIZE, TIME_SIZE,
		0.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
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
int Time::GetTime() {
	m_ElapsedTime = clock();
	return m_ElapsedTime;
}
