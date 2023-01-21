//=============================================================================
//
//何かを開ける鍵
//
//制作者/菊地 空　
//=============================================================================

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
#define KEY_MAX (3)

typedef struct {

	bool GetKey; //鍵を取ったかどうかの判定
	bool OpenKey; //鍵を開けるかどうかの判定
	bool UseFlag;
	D3DXVECTOR2 Size;//BOXサイズ
	D3DXVECTOR2 Position;//表示座標(中心座標)
	D3DXCOLOR col;//色
	D3DXVECTOR2 oldpos;
	float		rot;//回転角度
	int index;
	float texno;//テクスチャインデックス
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数
	
}KEY;
//=============================================================================
//プロトタイプ宣言
//=============================================================================

HRESULT InitKey();
void UninitKey();
void UpdateKey();
void DrawKey();

void SetKey(D3DXVECTOR2 pos, D3DXVECTOR2 size,int direction, int index);
void DeleteKey(int PieceNo);

KEY *GetKey();
