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


class Time {
private:
	clock_t m_start;	//計測開始時間
	clock_t m_end;		//計測終了時間
	int m_ElapsedTime;	//経過時間
public:
	void InitTime();
	void DrawGameTime();	//ゲーム中に表示される
	void DrawResultTime();	//リザルトで表示される
	void StartTime();
	int EndTime();
	int GetTime();
};


#endif // !_TIME_H_
