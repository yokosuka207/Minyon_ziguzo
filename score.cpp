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
#include "sound.h"
#include <math.h>

static ID3D11ShaderResourceView* g_ScoreTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_ScoreTextureName = (char*)"data\\texture\\number.png";	//�e�N�X�`���t�@�C���p�X
static int g_ScoreTextureNo = 0;

static Score g_Score;
static SCOREPARAM g_ScoreParam;	//�\����
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
		g_AnimeParam[i].num = 0;
		g_AnimeParam[i].index = -1;
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
			//�t���[�����J������Ɉ�C�ɏo�Ă���
			if (!g_AnimeParam[0].AnimeFlag && frame == 60) {
				SetAnimeParam(score / pow(10, 0), 0);
				//PlaySound(g_ScoreSoundNo, 0);				//0 = ��񂾂��Đ� sound.h�Q��
			}
			if (!g_AnimeParam[1].AnimeFlag && frame == 120) {
				SetAnimeParam(score / pow(10, 1), 1);
				//PlaySound(g_ScoreSoundNo, 0);				//0 = ��񂾂��Đ� sound.h�Q��
			}
			if (!g_AnimeParam[2].AnimeFlag && frame == 180) {
				SetAnimeParam(score / pow(10, 2), 2);
				//PlaySound(g_ScoreSoundNo, 0);				//0 = ��񂾂��Đ� sound.h�Q��
			}
			if (!g_AnimeParam[3].AnimeFlag && frame == 240) {
				SetAnimeParam(score / pow(10, 3), 3);
				//PlaySound(g_ScoreSoundNo, 0);				//0 = ��񂾂��Đ� sound.h�Q��
			}
			if (!g_AnimeParam[4].AnimeFlag && frame == 300) {
				SetAnimeParam(score / pow(10, 4), 4);
				//PlaySound(g_ScoreSoundNo, 0);				//0 = ��񂾂��Đ� sound.h�Q��
			}
			if (!g_AnimeParam[5].AnimeFlag && frame == 360) {
				SetAnimeParam(score / pow(10, 5), 5);
				//PlaySound(g_ScoreSoundNo, 0);				//0 = ��񂾂��Đ� sound.h�Q��
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
	//�X�R�A�Ɍv�����ԍ��v�ƃ|�[�Y�������Ԃ��i�[
	m_TimeScore = pTime->SumTime();
	m_TimeScore -= pTime->PauseElapsedTime();
	//�X�R�A�̒l��b�ɕϊ�
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
void Score::SetAnimeParam(int num,int index) {
	for (int i = 0; i < SCORE_MAX; i++) {
		if (!g_AnimeParam[i].AnimeFlag) {
			g_AnimeParam[i].num = num;
			g_AnimeParam[i].index = i;
			g_AnimeParam[i].AnimeFlag = true;
			break;
		}
	}
}
SCOREPARAM* Score::GetScoreParam() {
	return &g_ScoreParam;
}
Score* Score::GetScore() {
	return &g_Score;
}
