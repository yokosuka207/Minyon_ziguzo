#pragma once

#define JUMPSTAND_SIZE	(20)
#define JUMPSTAND_MAX (8)
typedef struct 
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 size;	//大きさ
	D3DXVECTOR2 oldpos;
	D3DXVECTOR2 oldoldpos;
	D3DXVECTOR2 sp;		//スピード

	float		rot;
	int			PieceIndex;
	int			NowPieceIndex;	//今のピースのインデックス

	float JumpGravity;	//重力
	float JumpPower;	//飛ぶ力

	bool UseJumpStand;	//ジャンプスタンドフラグ
	bool JumpStandFlag;		//ジャンプスタンドのジャンプ中フラグ

	bool GetJumpStand;
	bool JumpStandNotMove;
	bool LookFlag;

	//ドッペルゲンガーver
	D3DXVECTOR2 spD;
	float JumpPowerD;
	bool JumpStandFlagD;		//ジャンプスタンドのジャンプ中フラグ


}JUMPSTAND;

HRESULT InitJumpStand();
void UninitJumpStand();
void UpdateJumpStand();
void DrawJumpStand();
void SetJumpStand(D3DXVECTOR2 p);
void SetJumpStand(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int PieceNo);
void DeleteJumpStand(int PieceNo);

JUMPSTAND* GetJumpStand();

bool Collition_JumpStand();