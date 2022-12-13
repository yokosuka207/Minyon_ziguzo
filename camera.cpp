//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
//#include "keyboard.h"
#include "mouse.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// カメラ行列のパラメーター
#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
//#define	POS_Y_CAM		(200.0f)		// カメラの初期位置(Y座標)
//#define	POS_Z_CAM		(-400.0f)		// カメラの初期位置(Z座標)
#define	POS_Y_CAM		(5.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-900.0f)		// カメラの初期位置(Z座標)

// プロジェクション行列のパラメーター
#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(1.0f)											// ビュー平面のNearZ値	近くが見える限界距離
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値	遠くの見える限界距離

#define	VALUE_MOVE_CAMERA	(1.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAMERA			g_Camera;		// カメラデータ

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);	// カメラの座標
	g_Camera.at = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// カメラの注視点
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// カメラの上ベクトル

	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);
	
	g_Camera.fov = 45.0f;		// 視野角の初期化
}


//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{

	// カメラを初期に戻す
	if (GetKeyboardTrigger(DIK_P))
	{
		UninitCamera();
		InitCamera();
	}

	// 視野角を変更する
	if (GetKeyboardTrigger(DIK_O))
	{// 角度を大きくする
		g_Camera.fov += 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_L))
	{// 角度を小さくする
		g_Camera.fov -= 1.0f;
	}

}


//=============================================================================
// カメラの更新
//=============================================================================
void SetCamera(void) 
{
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);
	// DirectXへカメラ行列をセット
	SetViewMatrix(&g_Camera.mtxView);

	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(g_Camera.fov), VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);
	//D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	// DirectXへプロジェクション行列をセット
		
	// カメラ行列の逆行列を作成

	//float det;
	//D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);

	SetProjectionMatrix(&g_Camera.mtxProjection);

}


//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}


// カメラの視点と注視点をセット
void SetCameraAT(D3DXVECTOR3 pos)
{
	// カメラの注視点をプレイヤーの座標にしてみる
	g_Camera.at = pos;

	// カメラの視点をカメラのY軸回転に対応させている
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
}

