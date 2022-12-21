//=============================================================================
//
//	スコア処理[score.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/30
//=============================================================================

#include "score.h"
#include "sprite.h"
#include "texture.h"
#include "time.h"
#include "sound.h"

static ID3D11ShaderResourceView* g_ScoreTexture;	//画像一枚で一つの変数が必要
static char* g_ScoreTextureName = (char*)"data\\texture\\number.png";	//テクスチャファイルパス
static int g_ScoreTextureNo = 0;

static Score g_Score;
static SCOREPARAM g_ScoreParam;	//構造体
static ANIMEPARAM g_AnimeParam[SCORE_MAX];
static Time* pTime = pTime->GetTime();

static int g_ScoreDistance = SCORE_POS_X;
static int score = 0;
static int frame = 0;
static int g_ScoreSoundNo = 0;
void Score::InitScore() {
	g_ScoreTextureNo = LoadTexture(g_ScoreTextureName);
	g_ScoreParam.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_ScoreParam.size = D3DXVECTOR2(0.0f, 0.0f);
	g_ScoreParam.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ScoreParam.UseFlag = false;
	g_ScoreParam.CalcFlag = false;
	for (int i = 0; i < SCORE_MAX; i++) {
		g_AnimeParam[i].AnimeFlag = false;
	}
	//char filename[] = "data\\SoundData\\.wav";
	//char filename[] = "data\\SE\\bomb000.wav";
	//g_ScoreSoundNo = LoadSound(filename);

}
void Score::UninitScore() {
	if (g_ScoreTexture) {
		g_ScoreTexture->Release();
		g_ScoreTexture = NULL;
	}
}
void Score::DrawScore() {
	if (g_ScoreParam.UseFlag) {
		SetWorldViewProjection2D();
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ScoreTextureNo));

		g_ScoreParam.pos.x = g_ScoreDistance;
		score = CulcScore();
		
		frame++;
		for (int i = 0; i < SCORE_MAX; i++) {
			if (!g_AnimeParam[i].AnimeFlag && frame % 60 == 0) {
				g_AnimeParam[i].AnimeFlag = true;
				//PlaySound(g_ScoreSoundNo, 0);	//0 = 一回だけ再生 sound.h参照
			}
			if (g_AnimeParam[i].AnimeFlag) {
				SpriteDrawColorRotation
				(
					g_ScoreParam.pos.x,
					g_ScoreParam.pos.y,
					0.0f,
					g_ScoreParam.size.x,
					g_ScoreParam.size.y,
					0.0f,
					g_ScoreParam.color,
					(score % 10),
					1.0f / 10.0f,
					1.0f / 1.0f,
					10
				);
				g_ScoreParam.pos.x -= 30;
				//score /= 10;
			}
		}
	}
}
int Score::CulcScore() {
	//スコアに計測時間合計とポーズした時間を格納
	m_TimeScore = pTime->SumTime();
	m_TimeScore -= pTime->PauseElapsedTime();
	//スコアの値を秒に変換
	m_TimeScore /= CLOCKS_PER_SEC;
	if (m_TimeScore < 60) {
		m_score = m_TimeScore;
	}
	else {
		m_score = m_TimeScore;
	}

	return m_score;
}
void Score::SetScore(D3DXVECTOR2 pos,D3DXVECTOR2 size) {
	if (!g_ScoreParam.UseFlag) {
		g_ScoreParam.pos = pos;
		g_ScoreParam.size = size;
		g_ScoreParam.UseFlag = true;
	}
}
SCOREPARAM* Score::GetScoreParam() {
	return &g_ScoreParam;
}
Score* Score::GetScore() {
	return &g_Score;
}