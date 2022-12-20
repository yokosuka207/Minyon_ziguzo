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
#include "pause.h"
#include <iostream>
#include <Windows.h>
#include <vector>
//*****************************************************************************
//	�}�N����`
//*****************************************************************************

//*****************************************************************************
//	�O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView* g_TimeTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_TimeTextureName = (char*)"data\\texture\\number.png";	//�e�N�X�`���t�@�C���p�X
static int g_TimeTextureNo = 0;
static int g_Time = 0;
static int g_SecondTime = 0;
static int g_MintueTime = 0;
static int g_TimeDistance = (TIME_POS_X);
static TimeParam g_TimeParam;
static Time g_TimeClass;
static bool* pause = GetPause();

void Time::InitTime() {
	g_TimeTextureNo = LoadTexture(g_TimeTextureName);
	g_TimeParam.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_TimeParam.size = D3DXVECTOR2(0.0f, 0.0f);
	g_TimeParam.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_TimeParam.UseFlag = false;
	g_TimeParam.EndFlag = false;
}
void Time::UninitTime() {
	if (g_TimeTexture != NULL) {
		g_TimeTexture->Release();
		g_TimeTexture = NULL;
	}
}

//�v��Ȃ�
void Time:: DrawGameTime() {
	SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	m_ElapsedTime = ElapsedTime();
	m_ElapsedTime -= m_PauseElapsed;
	
	g_Time = m_ElapsedTime / CLOCKS_PER_SEC;//�b�\��
	g_SecondTime = g_Time % 60;	//�b
	g_MintueTime = g_Time / 60;	//��
	g_TimeParam.pos.x = g_TimeDistance;

	if (g_TimeParam.UseFlag) {
		//1�̈�(�b)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x,
				g_TimeParam.pos.y,
				0.0f,
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
		//10�̈�(�b)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x,
				g_TimeParam.pos.y,
				0.0f,
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
		//1�̈�(��)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x - 5,
				g_TimeParam.pos.y,
				0.0f,
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
		//10�̈�(��)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x - 5,
				g_TimeParam.pos.y,
				0.0f,
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

//�|�[�Y���Ԃ��ǂ��ɂ����Ȃ���
void Time::DrawResultTime(clock_t elapsedtime, clock_t pause) {
	SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TimeTextureNo));

	g_TimeParam.pos.x = SCREEN_WIDTH / 2 + 70;
	g_TimeParam.pos.y = SCREEN_HEIGHT / 2;
	g_TimeParam.size = D3DXVECTOR2(50.0f, 50.0f);
	g_TimeParam.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (g_TimeParam.EndFlag) {
		m_ElapsedTime = elapsedtime;
		m_PauseElapsed = pause;
		m_ElapsedTime -= m_PauseElapsed;
		g_TimeParam.EndFlag = false;
	}
	g_Time = m_ElapsedTime / CLOCKS_PER_SEC;//�b�\��
	g_SecondTime = g_Time % 60;	//�b
	g_MintueTime = g_Time / 60;	//��

	if (g_TimeParam.UseFlag) {
		//1�̈�(�b)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x,
				g_TimeParam.pos.y,
				0.0f,
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
		//10�̈�(�b)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x,
				g_TimeParam.pos.y,
				0.0f,
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
		//1�̈�(��)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x - 5,
				g_TimeParam.pos.y,
				0.0f,
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
		//10�̈�(��)
		{
			SpriteDrawColorRotation(
				g_TimeParam.pos.x - 5,
				g_TimeParam.pos.y,
				0.0f,
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
//�v���J�n
void Time::StartTime() {
	m_start = clock();
}
//�v���I��
void Time::EndTime() {
	m_end = clock();
	SumTime();
}
//�v�����ԍ��v
clock_t Time::SumTime() {
	m_ElapsedTime = m_end - m_start;
	return m_ElapsedTime;
}
//�o�ߎ���
clock_t Time::ElapsedTime() {
	m_ElapsedTime = clock() - m_start;
	return m_ElapsedTime;
}
//�|�[�Y�̊J�n����
void Time::PauseStartTime() {
	m_PauseStart = clock();
}
//�|�[�Y�̏I������
void Time::PauseEndTime() {
	m_PauseEnd = clock();
}
//�|�[�Y�̍��v����
clock_t Time::PauseElapsedTime() {
	m_PauseElapsed += m_PauseEnd - m_PauseStart;
	return m_PauseElapsed;
}
//���Ԃ̕\�����W
void Time::SetTime(D3DXVECTOR2 pos, D3DXVECTOR2 size) {
	if (!g_TimeParam.UseFlag) {
		g_TimeParam.pos = pos;
		g_TimeParam.size = size;
		g_TimeParam.UseFlag = true;
	}
}
TimeParam* Time::GetTimeParam() {
	return &g_TimeParam;
}
Time* Time::GetTime() {
	return &g_TimeClass;
}