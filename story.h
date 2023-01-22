#pragma once

#include "main.h"

//====================
//マクロ定義
//=====================

#define STORY_MAX	(8)
#define	STORY_BLOCK_SIZE (30)

typedef	struct
{
	D3DXVECTOR2		pos;	//表示座標
	D3DXVECTOR2		size;	//サイズ
	D3DXVECTOR2		sp;		//移動スピード
	D3DXCOLOR		color;	//色

	bool			bUse;	//ストーリー取得フラグ
	bool			KeyUse;

	int				HaveKey;

	int				n;


}STORY;

typedef enum
{
	STORY_NONE = 0,
	STORY_1,
	STORY_2,
	STORY_3,
	STORY_4,
	STORY_5,
	STORY_6,
	STORY_7,
	STORY_8,

}STORY_NUMBER;


//======================
//プロトタイプ宣言
//======================

void	InitStory();
void	UninitStory();
void	UpdateStory();
void	DrawStory();

STORY* GetStory();
