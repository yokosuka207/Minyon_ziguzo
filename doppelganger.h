//=============================================================================
//
//ドッペルゲンガー処理(反プレイヤー)
//
//制作者/菊地空　制作日/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "goal_key.h"

//=============================================================================
//マクロ定義
//=============================================================================

#define DOPPELGANGER_NUM (1)
#define DOPPELGANGER_SIZE_W (10)
#define DOPPELGANGER_SIZE_H (30)

#define DOPPELGANGER_COOLTIME	(120)

#define DOPPELGANGER_HP (5)
#define DOPPELGANGER_UV_W (1.0f / 4)
#define DOPPELGANGER_UV_H (1.0f / 4)

enum class DOPPELGANGER_DIRECTION
{
	UP = 0,
	DOWN,
	RIGHT,
	LEFT
};

struct DOPPELGANGER
{
	
	bool UseFlag;//構造体利用中フラグ
	//bool GetKey;

	bool jump;//ジャンプ中
	//bool getjump;//ジャンプの開始
	bool fall;//落下中
	bool getfall = false;//落下の開始
	
	//bool GetJumpStand;
	bool isGround;	// 地に足をつけている
	bool isSheerFloors;
	bool isSheerFloorsUse;
	bool isMoveBlock;
	bool isHigh;
	bool WarpFlag;

	D3DXVECTOR2 size;//BOXサイズ
	D3DXVECTOR2 Drawsize;//BOXサイズ
	D3DXVECTOR2 Position;//表示座標(中心座標)
	D3DXVECTOR2 oldpos;//1フレーム前の座標
	//D3DXVECTOR2 OneOldpos;//1フレーム前の座標

	D3DXVECTOR2 sp;
	float rot;//回転角度
	float texno;//テクスチャインデックス
	D3DXCOLOR col;//色
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数
	//int hp;
	int frame;
	int CoolTime;//クールタイム
	DOPPELGANGER_DIRECTION dir;			// 反プレイヤーの向き
	int PieceIndex;	//動いでいるピースの番号

};

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitDoppelganger();
void UninitDoppelganger();
void UpdateDoppelganger();
void DrawDoppelganger();
DOPPELGANGER* GetDoppelganger();//DOPPELGANGER構造体の先頭ポインタを取得

void SetDoppelGanger(D3DXVECTOR2 position, D3DXVECTOR2 size, int index);
void DeleteDoppelGanger(int index);