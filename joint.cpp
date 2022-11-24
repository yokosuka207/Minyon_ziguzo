/*================================================================================

	凹凸処理[joint.cpp]

												Author: 齊藤 零登
												 Date : 2022/11/16
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#include "joint.h"
#include "texture.h"
#include "sprite.h"
#include"MapChip.h"

//**************************************************
// マクロ定義
//**************************************************

//**************************************************
// プロトタイプ宣言
//**************************************************

//**************************************************
// グローバル変数
//**************************************************
JOINT g_Joint[JOINT_MAX];

// テクスチャの名前
static char* g_JointTextureName = (char*)"data\\texture\\white.jpg";


//==================================================
// 凹凸初期化
//==================================================
void InitJoint()
{
	// テクスチャ番号をもらう
	float texNo = LoadTexture(g_JointTextureName);

	// 各凹凸の各パラメータの初期化
	for (int i = 0; i < JOINT_MAX; i++) {
		g_Joint[i].pos = D3DXVECTOR2(0.0f, 0.0f);			
		g_Joint[i].size = D3DXVECTOR2(0.0f, 0.0f);	
		g_Joint[i].color = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		g_Joint[i].pieNo = -1;								
		g_Joint[i].type = JOINT_TYPE::TYPE_BUMP;	
		g_Joint[i].texNo = texNo;

		g_Joint[i].useFlag = false;							
	}
}


//==================================================
// 凹凸終了処理
//==================================================
void UninitJoint()
{

}


//==================================================
// 凹凸更新処理
//==================================================
void UpdateJoint()
{

}


//==================================================
// 凹凸描画処理
//==================================================
void DrawJoint()
{
	// 凹凸の描画
	for (int i = 0; i < JOINT_MAX; i++){
		if (g_Joint[i].useFlag) {
			// テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Joint[i].texNo));
			// 四角形の描画
			SpriteDrawColorRotation(g_Joint[i].pos.x, g_Joint[i].pos.y, g_Joint[i].size.x, g_Joint[i].size.y, 0.0f, g_Joint[i].color, 0, 1.0f, 1.0f, 1);
		}
	}
}


//==================================================
// 凹凸セット関数
//==================================================
void SetJoint(D3DXVECTOR2 po, D3DXVECTOR2 si, int no, JOINT_TYPE ty)
{
	for (int i = 0; i < JOINT_MAX; i++) {
		// 未使用なら引数の各値を代入
		if (!g_Joint[i].useFlag) {
			g_Joint[i].pos = po;
			g_Joint[i].size = si;
			g_Joint[i].pieNo = no;
			g_Joint[i].type = ty;

			g_Joint[i].useFlag = true;

			break;
		}
	}
}


//==================================================
// 凹凸ゲット関数
//==================================================
JOINT* GetJoint()
{
	return g_Joint;
}


//==================================================
// 凹凸デリート関数
//==================================================
void DeleteJoint(int no)
{
	for (int i = 0; i < JOINT_MAX; i++) {
		// 使用中で引数と同じ番号なら未使用にする
		if (g_Joint[i].useFlag && g_Joint[i].pieNo == no) {
			g_Joint[i].useFlag = false;
		}
	}
}

