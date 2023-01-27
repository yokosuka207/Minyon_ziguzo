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
#include "player.h"
#include <math.h>

static ID3D11ShaderResourceView* g_ScoreTexture;	//画像一枚で一つの変数が必要

static char* g_ScoreTextureName = (char*)"data\\texture\\number.png";
static char* g_ScoreRankTextureName[] = {
	(char*)"data\\texture\\number1.png" ,
	(char*)"data\\texture\\number1.png" ,
	(char*)"data\\texture\\number1.png" ,
	(char*)"data\\texture\\number1.png" ,
};

static int g_ScoreTextureNo = 0;
static int g_ScoreRankTextureNo[] = {
	0,0,0,0,
};

static int g_ScoreSoundNo = 0;
static int g_ScoreRankSoundNo = 0;

static Score g_Score;

static SCOREPARAM g_ScoreParam;	//構造体
static SCOREPARAM g_ScoreRankParam;
static ANIMEPARAM g_AnimeParam[SCORE_MAX];
static Time* pTime = pTime->GetTime();
static RESULT* pResult = GetResult();
static int StageNo = 0;

static int score = 0;
static int frame = 0;

void Score::InitScore() {
	g_ScoreTextureNo = LoadTexture(g_ScoreTextureName);
	for (int i = 0; i < 4; i++) {
		g_ScoreRankTextureNo[i] = LoadTexture(g_ScoreRankTextureName[i]);
	}
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

	g_ScoreRankParam.pos = D3DXVECTOR2(SCREEN_WIDTH / 2 + 400.0f, 400.0f);
	g_ScoreRankParam.size = D3DXVECTOR2(100.0f, 100.0f);
	g_ScoreRankParam.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ScoreRankParam.UseFlag = false;

	frame = 0;

	char filename[] = "data\\SoundData\\SE\\タイプライター.wav";
	g_ScoreSoundNo = LoadSound(filename);

	char filename2[] = "data\\SoundData\\SE\\タイプライター.wav";
	g_ScoreRankSoundNo = LoadSound(filename2);
}
void Score::UninitScore() {
	if (g_ScoreTexture != NULL) {
		g_ScoreTexture->Release();
		g_ScoreTexture = NULL;
	}
}
void Score::DrawScore() {
	if (g_ScoreParam.UseFlag) {
		SetWorldViewProjection2D();
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ScoreTextureNo));

		g_ScoreParam.pos.x = SCREEN_WIDTH / 2 - 20.0f;
		if (pResult->type == LOSE) {
			g_ScoreParam.pos.x = SCREEN_WIDTH / 2 + 80.0f;
			g_ScoreParam.pos.y = SCREEN_HEIGHT / 2 + 50.0f;

			g_ScoreRankParam.UseFlag = false;
		}

		score = CulcScore();
		
		frame++;

		for (int i = 0; i < SCORE_MAX; i++) {
			if (!g_AnimeParam[0].AnimeFlag && frame == 10) {
				SetAnimeParam(score / pow(10, 0));
				SetVolume(g_ScoreSoundNo, 0.3f);
				PlaySound(g_ScoreSoundNo, 0);				//0 = 一回だけ再生 sound.h参照
			}
			if (!g_AnimeParam[1].AnimeFlag && frame == 30) {
				SetAnimeParam(score / pow(10, 1));
			}
			if (!g_AnimeParam[2].AnimeFlag && frame == 50) {
				SetAnimeParam(score / pow(10, 2));
			}
			if (!g_AnimeParam[3].AnimeFlag && frame == 80) {
				SetAnimeParam(score / pow(10, 3));
			}
			if (!g_AnimeParam[4].AnimeFlag && frame == 90) {
				SetAnimeParam(score / pow(10, 4));
			}
			if (!g_AnimeParam[5].AnimeFlag && frame == 110) {
				SetAnimeParam(score / pow(10, 5));
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
				g_ScoreParam.pos.x -= 30.0f;
			}
		}
		if (frame == 150) {
			g_ScoreRankParam.UseFlag = true;
			SetVolume(g_ScoreRankSoundNo, 0.3f);
			PlaySound(g_ScoreRankSoundNo, 0);				//0 = 一回だけ再生 sound.h参照
		}

		if (g_ScoreRankParam.UseFlag) {

			switch (g_ScoreParam.rank) {
			case SCORE_RANK::RANK_S:
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ScoreRankTextureNo[0]));
				break;
			case SCORE_RANK::RANK_A:
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ScoreRankTextureNo[1]));
				break;
			case SCORE_RANK::RANK_B:
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ScoreRankTextureNo[2]));
				break;
			case SCORE_RANK::RANK_C:
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ScoreRankTextureNo[3]));
				break;
			}
			
			SpriteDrawColorRotation
			(
				g_ScoreRankParam.pos.x,
				g_ScoreRankParam.pos.y,
				0.0f,
				g_ScoreRankParam.size.x,
				g_ScoreRankParam.size.y,
				0.0f,
				g_ScoreRankParam.color,
				0,
				1.0f / 1.0f,
				1.0f / 1.0f,
				1
			);
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

	PLAYER* pPlayer = GetPlayer();
	switch (pPlayer->hp) {
	case 0:m_score *= 0;
		break;
	case 1:m_score *= 1;
		break;
	case 2:m_score *= 2;
		break;
	case 3:m_score *= 3;
		break;
	default:
		break;
	}

	return m_score;
}
void Score::RankScore(int score) {
	switch (StageNo) {
		//================================================
		//	チュートリアル
		//================================================
	case 0:
		if (score < 40 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 80 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	チュートリアル
		//================================================
	case 1:
		if (score < 40 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 80 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	チュートリアル
		//================================================
	case 2:
		if (score < 40 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 80 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	(初)動くブロックと(初)ジャンプ台
		//================================================
	case 3:
		if (score < 90 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 180 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 270 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	(初)壊れるブロックと(初)紐
		//================================================
	case 4:
		if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 240 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 360 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	(初)スイッチと動くブロック
		//================================================
	case 5:
		if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 240 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 360 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	(初)落ちるブロックとスイッチ
		//================================================
	case 6:
		if (score < 150 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 300 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 450 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	(初)エネミーと紐
		//================================================
	case 7:
		if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 180 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 240 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	(初)ワープ
		//================================================
	case 8:
		if (score < 90 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 150 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	(初)高所落下で壊れるブロックと(初)鍵付き扉とジャンプ台と紐
		//================================================
	case 9:
		if (score < 180 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 360 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 540 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	ジャンプ台と高所落下ブロックとトゲ
		//================================================
	case 10:
		if (score < 120 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 240 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 360 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	ワープと鍵付き扉と高所落下とトゲ
		//================================================
	case 11:
		if (score < 150 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_S;
		}
		else if (score < 225 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_A;
		}
		else if (score < 300 && pResult[0].type == WIN) {
			g_ScoreParam.rank = SCORE_RANK::RANK_B;
		}
		else {
			g_ScoreParam.rank = SCORE_RANK::RANK_C;
		}
		break;
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	チュートリアル終わり
		//================================================
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
		//================================================
		//	ギミックすべて
		//================================================
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
ANIMEPARAM* Score::GetAnimeParam() {
	return g_AnimeParam;
}
