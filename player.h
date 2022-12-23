//=============================================================================
//
//プレイヤー処理
//
//制作者/稲葉陸斗　制作日/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================

#define PLAYER_SIZE_W (25)
#define PLAYER_SIZE_H (30)

#define PLAYER_COOLTIME	(120)

#define PLAYER_HP (3)

enum class PLAYER_DIRECTION
{
	UP = 0,
	DOWN,
	RIGHT,
	LEFT
};

struct PLAYER
{
	bool UseFlag;//構造体利用中フラグ
	bool jump;//ジャンプ中
	//bool getjump;//ジャンプの開始
	bool fall;//落下中
	bool getfall = false;//落下の開始
	bool WarpFlag = false;//ワープしたか
	bool GetJumpStand;
	bool isGround;	// 地に足をつけている
	bool isSheerFloors;
	bool isSheerFloorsUse;
	bool isHigh;
	bool isMoveBlock;
	int	HaveKey; //鍵所持数
	int GHaveKey;
	//int Hp;

	D3DXVECTOR2 size;//BOXサイズ
	D3DXVECTOR2 Position;//表示座標(中心座標)
	D3DXVECTOR2 oldpos;//1フレーム前の座標
	D3DXVECTOR2 OneOldpos;//1フレーム前の座標

	D3DXVECTOR2 sp;
	float rot;//回転角度
	float texno;//テクスチャインデックス
	D3DXCOLOR col;//色
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数
	int hp;
	int frame;
	int CoolTime;//クールタイム
	PLAYER_DIRECTION dir;			// プレイヤーの向き
	int PieceIndex;	//動いでいるピースの番号

};

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
PLAYER* GetPlayer();//PLAYER構造体の先頭ポインタを取得
