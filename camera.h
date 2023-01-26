//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct CAMERA
{
	D3DXVECTOR3			pos;			// カメラの視点(位置)
	D3DXVECTOR3			at;				// カメラの注視点
	D3DXVECTOR3			up;				// カメラの上方向ベクトル
	D3DXMATRIX			mtxView;		// ビューマトリックス	カメラの行列
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス
	// ここまで最低限必要な要素 ルックアットカメラ

	float				fov;			// 視野角

	D3DXVECTOR3			rot;			// カメラの回転
	float				len;			// カメラの視点と注視点の距離

	D3DXMATRIX			mtxInvView;		// ビューマトリックス	カメラの逆行列
	bool zoomFlag;
	bool MoveFlag;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
void SetCameraAT(D3DXVECTOR3 pos);
