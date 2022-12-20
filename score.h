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


typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	color;
	bool		UseFlag;
	bool		CalcFlag;	//�v�Z�������ǂ���

}SCOREPARAM;

class Score{
private:
	int m_score = 0;	//�X�R�A������
	int m_TimeScore = 0;
public:
	void InitScore();
	void UninitScore();
	void DrawScore();
	int CulcScore();	//�X�R�A�̌v�Z
	void SetScore(D3DXVECTOR2 pos, D3DXVECTOR2 size);
	SCOREPARAM* GetScoreParam();
	Score* GetScore();
};

#endif // !_SCORE_H_
