/*==============================================================================

   フェードヘッダー [fade.h]
														 Author : 伏木　伶
														 Date   : 2022/12/27
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#define FADE_SPEED_ALPHA (0.02f)
#define FADE_SPEED_X (22.0f * 100)	//1422 / 60
#define FADE_SPEED_Y (12.5f * 100)	//800 / 60

enum class FADE {
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_ALPHA_IN,
	FADE_ALPHA_OUT,

	FADE_NUM
};
typedef struct {
	bool	ExceptFlag;	//例外（シーン切り替えの）
	bool	FadeFlag;	//フェードしている間の再発動防止
	float	alpha;		//透明度切り替え
	D3DXVECTOR2	scaling;		//サイズの変化
	FADE	state;		

	int				TexNo1;
	int				TexNo2;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		size;
	int				PaternNo;
	float			uv_w;
	float			uv_h;
	float			rot;
	int				NumPatern;

}FADEPARAM;

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void StartFade(FADE state);
FADEPARAM* GetFadeParam();
#endif // !_FADE_H_
