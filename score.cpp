//=============================================================================
//
//	�X�R�A����[score.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/30
//=============================================================================

#include "score.h"
#include "sprite.h"
#include "texture.h"
#include "time.h"

static ID3D11ShaderResourceView* g_ScoreTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_ScoreTextureName = (char*)"data\\texture\\number.png";	//�e�N�X�`���t�@�C���p�X
static int g_ScoreTextureNo = 0;

static SCORE g_Score;	//�\����

static int distance = SCORE_POS_X;
static int score = 0;

static 	Time g_Time;

void Score::InitScore() {
	g_ScoreTextureNo = LoadTexture(g_ScoreTextureName);
	g_Score.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Score.size = D3DXVECTOR2(0.0f, 0.0f);
	g_Score.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Score.UseFlag = false;
	g_Score.CalcFlag = false;
	m_score = 0;
	m_TimeScore = 0;
}
void Score::UninitScore() {
	if (g_ScoreTexture) {
		g_ScoreTexture->Release();
		g_ScoreTexture = NULL;
	}
}
void Score::DrawScore() {
	if (g_Score.UseFlag) {
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ScoreTextureNo));

		g_Score.pos.x = distance;
		score = CulcScore();

		for (int i = 0; i < SCORE_MAX; i++) {

			SpriteDrawColorRotation
			(
				g_Score.pos.x,
				g_Score.pos.y,
				g_Score.size.x,
				g_Score.size.y,
				0.0f,
				g_Score.color,
				(score % 10),
				1.0f / 10.0f,
				1.0f / 1.0f,
				10
			);
			g_Score.pos.x -= 30;
			score /= 10;
		}
	}
}
int Score::CulcScore() {
	m_TimeScore = g_Time.GetTime();
	
	if (m_TimeScore < 60) {
		m_score = m_TimeScore;
	}
	else {
		m_score = m_TimeScore * 0.5;
	}

	return m_score;
}
void Score::SetScore(D3DXVECTOR2 pos,D3DXVECTOR2 size) {
	if (!g_Score.UseFlag) {
		g_Score.pos = pos;
		g_Score.size = size;
		g_Score.UseFlag = true;
	}
}
SCORE* Score::GetScore() {
	return &g_Score;
}