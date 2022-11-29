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

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR color;
}TimeParam;

class Time {
private:
	clock_t m_start;	//�v���J�n����
	clock_t m_end;		//�v���I������
	int m_ElapsedTime;	//�o�ߎ���
public:
	void InitTime();
	void DrawGameTime();	//�Q�[�����ɕ\�������
	void DrawResultTime();	//���U���g�ŕ\�������
	void StartTime();
	int EndTime();
	int ElapsedTime();
	int GetTime();
};


#endif // !_TIME_H_
