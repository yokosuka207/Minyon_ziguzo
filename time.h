//=============================================================================
//
//	���ԃw�b�_�[[time.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/29
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "renderer.h"
#include <time.h>

#define TIME_POS_X (SCREEN_WIDTH - 20)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	color;
	bool		UseFlag;
	bool		EndFlag;
}TimeParam;

class Time {
private:
	clock_t m_start = 0;		//�v���J�n����
	clock_t m_end = 0;			//�v���I������
	clock_t	m_ElapsedTime = 0;	//�o�ߎ���

	clock_t m_PauseStart = 0;	//�ꎞ��~�v���J�n����
	clock_t m_PauseEnd = 0;		//�ꎞ��~�v���I������
	clock_t m_PauseElapsed = 0;	//�ꎞ��~���ԍ��v
public:
	void InitTime();
	void UninitTime();
	void DrawGameTime();	//�Q�[�����ɕ\�������
	void DrawResultTime(clock_t elapsedtime,clock_t pause);	//���U���g�ŕ\�������
	void StartTime();
	clock_t EndTime();
	clock_t	ElapsedTime();
	void PauseStartTime();
	void PauseEndTime();
	clock_t PauseElapsedTime();
	void SetTime(D3DXVECTOR2 pos,D3DXVECTOR2 size);
	TimeParam* GetTimeParam();
};

#endif // !_TIME_H_
