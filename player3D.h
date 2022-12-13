//-----------------------------
//	player.h[プレイヤー管理]
//-----------------------------
#pragma once

#include<d3dx9.h>
#include"renderer.h"
//#include"model.h"

//--------------------
//マクロ定義
//--------------------
#define		ROTAION_SPEED	(2.0f)	//回転速度
#define		MOVE_SPEED		(1.0f)	//動く速度



//--------------------
//構造体宣言
//--------------------
struct PLAYER3D
{
	bool UseFlag;//使用中フラグ

	//DX11_MODEL Model;	//モデル構造体

	//アップデートで更新させる
	D3DXVECTOR3	Position;	//表示座標
	D3DXVECTOR3 Rotation;	//回転角度
	D3DXVECTOR3 Scaling;	//大きさ

	D3DXVECTOR3 MoveSpeed;	//移動するスピード
		
	//表示するときに作成される情報
	D3DXMATRIX	WorldMatrix;//表示用最終行列
	D3DXMATRIX	RotationMatrix;//回転行列
	D3DXMATRIX	TranslationMatrix;//平行移動行列
	D3DXMATRIX	ScalingMatrix;//大きさ行列

	//メンバ変数のアクセス
	void SetPosition(D3DXVECTOR3 vec) { Position = vec; };
	void SetRotation(D3DXVECTOR3 rot) { Rotation = rot; };
	void SetScaling(D3DXVECTOR3 scl) { Scaling = scl; };
	void SetMoveSpeed(D3DXVECTOR3 spd) { MoveSpeed = spd; };


	D3DXVECTOR3 GetPosition() { return Position; };
	D3DXVECTOR3 GetRotation() { return Rotation; };
	D3DXVECTOR3 GetScaling() { return Scaling; };
	D3DXVECTOR3 GetMoveSpeed() { return MoveSpeed; };

	//基本関数
	void Init();	//初期化
	void Uninit();	//終了処理
	void Update();	//更新処理
	void Draw();	//表示

	void SetUse(bool use) { UseFlag = use; };
	bool GetUseFlag() { return UseFlag; };//使用中かどうか
};


//--------------------
//プロトタイプ宣言
//--------------------

