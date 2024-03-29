//=============================================================================
//
//	ステージセレクトヘッダー[StageSelect.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/25
//=============================================================================
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_

#include "main.h"
#include "renderer.h"
#include "player.h"

#define STAGE_MAX (21)

#define SELECT_MAX (2)//2桁

enum class STAGE_SELECT_TYPE
{
	TYPE_NG,
	TYPE_OK

};


typedef struct
{
	D3DXVECTOR2		pos;		// 表示座標
	D3DXVECTOR2		size;		// 表示サイズ
	D3DXCOLOR		color;		// カラー
	float			texno;		// テクスチャインデックス番号
}STAGESELECT_BG;
typedef struct
{
	D3DXVECTOR2		pos;		// 表示座標
	D3DXVECTOR2		size;		// 表示サイズ
	D3DXCOLOR		color;		// カラー
	float			texno;		// テクスチャインデックス番号

}STAGESELECT_STAIRS;

typedef struct
{
	D3DXVECTOR2		pos;		// 表示座標
	D3DXVECTOR2		size;		// 表示サイズ
	D3DXCOLOR		color;		// カラー
	float			texno;		// テクスチャインデックス番号

}STAGESELECT_BLOCK;



typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	float		texno;
	int			StagePieceIndex;//ステージピースが何番目なのか
	bool		StageUseFlag;	//ステージに入れるかどうか
	STAGE_SELECT_TYPE type;		//ステージに入れるかどうか
	bool		UseFlag;		//ステージピース(仮名称)
}STAGESELECT;

HRESULT InitStageSelect();
void UninitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();
void SetStageSelect(int a);
STAGESELECT* GetSelect();
STAGESELECT* GetSelectNumber();
PLAYER* GetSelectPlayer();

int ReturnStageNo();

int GetClearStageNum();
void SetClearStageNum(int num);

#endif // !_STAGESELECT_H_

