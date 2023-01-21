//=============================================================================
//
//何かを開ける鍵
//
//制作者/菊地 空　
//=============================================================================
#include "Key.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"
//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static KEY g_Key[KEY_MAX];
static ID3D11ShaderResourceView	*g_KeyTexture;	//画像一枚で一つの変数が必要

static char* g_KeyTextureName = (char*)"data\\texture\\鍵.png";
static int g_KeyTextureNo = 0;


HRESULT InitKey()
{
	for (int i = 0; i < KEY_MAX; i++) {
		g_Key[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_Key[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_Key[i].rot = 0.0f;
		g_Key[i].index = -1;
		g_KeyTextureNo= LoadTexture(g_KeyTextureName);
		g_Key[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Key[i].GetKey = false;
		g_Key[i].UseFlag = false;
		//g_Key.OpenKey = false;
		
	}
	return S_OK;
}

void UninitKey(){
	if (g_KeyTexture != NULL) {
		g_KeyTexture->Release();
		g_KeyTexture = NULL;
	}
}

void UpdateKey()
{
	for (int i = 0; i < KEY_MAX; i++){
		if (g_Key[i].rot == 90 || g_Key[i].rot == 270) {
			g_Key[i].rot = 0.0f;
		}
	}	
}

void DrawKey()
{
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_KeyTextureNo));

	for (int i = 0; i < KEY_MAX; i++){
		if (g_Key[i].UseFlag){
			//SetWorldViewProjection2D();

			//テクスチャの設定
			//スプライトを表示
			SpriteDrawColorRotation(
				g_Key[i].Position.x,
				g_Key[i].Position.y,
				-0.1f,
				g_Key[i].Size.x,
				-g_Key[i].Size.y,
				g_Key[i].rot,
				g_Key[i].col,
				0,
				1.0f,
				1.0f,
				1);
		}
	}
}

void SetKey(D3DXVECTOR2 pos, D3DXVECTOR2 size,int direction, int index){
	for (int i = 0; i < KEY_MAX; i++) {
		if (!g_Key[i].UseFlag){
			switch (direction) {
			case 0:g_Key[i].rot = (direction + 2) * 90;
				break;
			case 1:g_Key[i].rot = direction * 90;
				break;
			case 2:g_Key[i].rot = (direction - 2) * 90;
				break;
			case 3:g_Key[i].rot = direction * 90;
				break;
			default:
				break;
			}
			g_Key[i].Position = pos;
			g_Key[i].Size = size;
			g_Key[i].index = index;
			g_Key[i].UseFlag = true;
		}
	}
}

void DeleteKey(int PieceNo) {
	for (int i = 0; i < KEY_MAX; i++) {
		if (g_Key[i].index == PieceNo) {
			if (g_Key[i].UseFlag) {
				g_Key[i].UseFlag = false;
			}
		}
	}
}

KEY *GetKey(){
	return g_Key;
}
