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
#include "StageSelect.h"
#include "result.h"
#include <math.h>

static ID3D11ShaderResourceView* g_ScoreTexture;	//画像一枚で一つの変数が必要
static ID3D11ShaderResourceView* g_ScoreRankTexture;	

static char* g_ScoreTextureName = (char*)"data\\texture\\number.png";	//テクスチャファイルパス
static char* g_ScoreRankTextureName = (char*)"data\\texture\\number.png";

static int g_ScoreTextureNo = 0;
static int g_ScoreRankTextureNo = 0;
static int g_ScoreSoundNo = 0;

static Score g_Score;
static SCOREPARAM g_ScoreParam;	//構造体
static ANIMEPARAM g_AnimeParam[SCORE_MAX];
static Time* pTime = pTime->GetTime();
static RESULT* pResult = GetResult();
static int StageNo = 0;

static int g_ScoreDistance = SCORE_POS_X;
static int score = 0;
static int frame = 0;

void Score::InitScore() {
	g_ScoreTextureNo = LoadTexture(g_ScoreTextureName);
	g_ScoreParam.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_ScoreParam.size = D3DXVECTOR2(0.0f, 0.0f);
	g_ScoreParam.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ScoreParam.UseFlag = false;
	g_ScoreParam.CalcFlag = false;
	g_ScoreParam.rank = SCORE_RANK::RANK_NONE;
	for (int i = 0; i < SCORE_MAX; i++) {
		g_AnimeParam[i].AnimeFlag = false;
		g_AnimeParam[i].num = 0;
		g_AnimeParam[i].index = -1;
	}
	char filename[] = "data\\SoundData\\SE\\meka_ge_type_chin_kaigyo01.wav";
	g_ScoreSoundNo = LoadSound(filename);
}
void Score::UninitScore() {
	if (g_ScoreTexture != NULL) {
		g_ScoreTexture->Release();
		g_ScoreTexture = NULL;
	}
	if (g_ScoreRankTexture != NULL) {
		g_ScoreRankTexture->Release();
		g_ScoreRankTexture = NULL;
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
			if (!g_AnimeParam[5].AnimeFlag && frame == 10) {
				SetAnimeParam(score / pow(10, 0));
				PlaySound(g_ScoreSoundNo, 0);				//0 = 一回だけ再生 sound.h参照
				SetVolume(g_ScoreSoundNo, 0.5f);
			}
			if (!g_AnimeParam[4].AnimeFlag && frame == 30) {
				SetAnimeParam(score / pow(10, 1));
			}
			if (!g_AnimeParam[3].AnimeFlag && frame == 50) {
				SetAnimeParam(score / pow(10, 2));
			}
			if (!g_AnimeParam[2].AnimeFlag && frame == 80) {
				SetAnimeParam(score / pow(10, 3));
			}
			if (!g_AnimeParam[1].AnimeFlag && frame == 90) {
				SetAnimeParam(score / pow(10, 4));
			}
			if (!g_AnimeParam[0].AnimeFlag && frame == 110) {
				SetAnimeParam(score / pow(10, 5));
				frame = 0;
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
					(g_AnimeParam[i].num % 10),
					1.0f / 10.0f,
					1.0f / 1.0f,
					10
				);
				g_ScoreParam.pos.x -= 30;
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

	RankScore(m_TimeScore);

	switch (g_ScoreParam.rank) {
	case (SCORE_RANK::RANK_S):
		m_score = m_TimeScore * 999;
		break;
	case (SCORE_RANK::RANK_A):
		m_score = m_TimeScore * 555;
		break;
	case (SCORE_RANK::RANK_B):
		m_score = m_TimeScore * 222;
		break;
	case (SCORE_RANK::RANK_C):
		m_score = m_TimeScore / 2;
		break;
	default:
		break;
	}
	return m_score;
}
void Score::RankScore(int score) {
	switch (StageNo) {
	case 0:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 1:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 2:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 3:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 4:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 5:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 6:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 7:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 8:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 9:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 10:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 11:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 12:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 13:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 14:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 15:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 16:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 17:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 18:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 19:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 20:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	case 21:
		if (score < 30 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 45 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 60 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
	default:
		break;
	}
}
void Score::SetScore(D3DXVECTOR2 pos,D3DXVECTOR2 size) {
	if (!g_ScoreParam.UseFlag) {
		g_ScoreParam.pos = pos;
		g_ScoreParam.size = size;
		g_ScoreParam.UseFlag = true;
	}
}
void Score::SetAnimeParam(int num) {
	for (int i = 0; i < SCORE_MAX; i++) {
		if (!g_AnimeParam[i].AnimeFlag) {
			g_AnimeParam[i].num = num;
			g_AnimeParam[i].index = i;
			g_AnimeParam[i].AnimeFlag = true;
			break;
		}
	}
}
void Score::SetStageNo(int stage) {
	StageNo = stage;
}
SCOREPARAM* Score::GetScoreParam() {
	return &g_ScoreParam;
}
Score* Score::GetScore() {
	return &g_Score;
}
