#pragma once

#define JUMPSTAND_SIZE	(20)

typedef struct 
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 size;	//大きさ
	D3DXVECTOR2 oldpos;	
	D3DXVECTOR2 sp;		//スピード

	float JumpGravity;	//重力
	float JumpPower;	//飛ぶ力

	bool UseJumpStand;	//ジャンプスタンドフラグ
	bool JumpStandFlag;		//ジャンプスタンドのジャンプ中フラグ

}JUMPSTAND;

HRESULT InintJumpStand();
void UninitJumoStand();
void UpdateJumpStand();
void DrawJumpStand();
void SetJumpStand(D3DXVECTOR2 p);
JUMPSTAND* GetJumpStand();

bool Collition_JumpStand();