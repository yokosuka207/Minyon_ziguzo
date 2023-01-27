//=============================================================================
//
//	�X�R�A�w�b�_�[[score.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/30
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "renderer.h"

#define SCORE_MAX (6)
#define SCORE_POS_X (SCREEN_WIDTH / 2 + 90)

enum class SCORE_RANK{
	RANK_NONE = 0,
	RANK_S,
	RANK_A,
	RANK_B,
	RANK_C,

	RANK_NUM
};

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	color;
	float		PaternNo;
	bool		UseFlag;
	bool		CalcFlag;	//�v�Z�������ǂ���
	SCORE_RANK	rank;		//�����N
}SCOREPARAM;

typedef struct {
	bool	AnimeFlag;
	int		num;	//�X�R�A�̌����Ƃ̒l
	int		index;	//���Ԗڂɕ`�悳��邩
}ANIMEPARAM;

class Score{
private:
	int m_score = 0;	//�X�R�A������
	int m_TimeScore = 0;

	bool m_Rank_S = false;
	bool m_Rank_A = false;
	bool m_Rank_B = false;
	bool m_Rank_C = false;
public:
	void InitScore();
	void UninitScore();
	void DrawScore();
	int CulcScore();	//�X�R�A�̌v�Z
	void RankScore(int score);	//�����N����
	void SetScore(D3DXVECTOR2 pos, D3DXVECTOR2 size);
	void SetAnimeParam(int num);
	void SetStageNo(int stage);
	SCOREPARAM* GetScoreParam();
	Score* GetScore();
	ANIMEPARAM* GetAnimeParam();
};

#endif // !_SCORE_H_
