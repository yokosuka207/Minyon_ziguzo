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
	clock_t m_start;		//�v���J�n����
	clock_t m_end;			//�v���I������
	clock_t	m_ElapsedTime;	//�o�ߎ���

	clock_t m_PuaseStart;	//�ꎞ��~�v���J�n����
	clock_t m_PuaseEnd;		//�ꎞ��~�v���I������
	clock_t m_PauseElapsed;	//�ꎞ��~���ԍ��v
public:
	void InitTime();
	void UninitTime();
	void DrawGameTime();	//�Q�[�����ɕ\�������
	void DrawResultTime();	//���U���g�ŕ\�������
	void StartTime();
	int EndTime();
	int	 ElapsedTime();
	void PuaseStartTime();
	void PuaseEndTime();

	void SetTime(D3DXVECTOR2 pos,D3DXVECTOR2 size);
	clock_t GetTime();
	void SetElapsedTime(clock_t elapsedtime);
	TimeParam* GetTimeParam();
	Time* GetTimeClass();
};

#endif // !_TIME_H_
