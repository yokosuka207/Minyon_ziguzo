//=============================================================================
//
//	時間ヘッダー[time.h]
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

#define TIME_POS_X (SCREEN_WIDTH - 20.0f)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	color;
	bool		UseFlag;
	bool		EndFlag;
}TimeParam;

class Time {
private:
	clock_t m_start;		//計測開始時間
	clock_t m_end;			//計測終了時間
	int		m_ElapsedTime;	//経過時間

	clock_t m_PuaseStart;	//一時停止計測開始時間
	clock_t m_PuaseEnd;		//一時停止計測終了時間
public:
	void InitTime();
	void DrawGameTime();	//ゲーム中に表示される
	void DrawResultTime();	//リザルトで表示される
	void StartTime();
	int EndTime();
	int ElapsedTime();
	void PuaseStartTime();
	void PuaseEndTime();

	void SetTime(D3DXVECTOR2 pos,D3DXVECTOR2 size);
	int GetTime();
	TimeParam* GetTimeParam();
};

#endif // !_TIME_H_
