//=============================================================================
//
//鍵で開く何か
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
#define OPEN_KEY_MAX (3)
#define STAGE_OPEN_KEY_MAX (3)

typedef struct {
	bool		UseFlag;//構造体利用中フラグ
	bool		KeyOpen;
	bool		DrawFlag;
	D3DXVECTOR2 Size;//BOXサイズ
	D3DXVECTOR2 Position;//表示座標(中心座標)
	float		rot;//回転角度
	float		texno;//テクスチャインデックス
	D3DXCOLOR	col;//色
	int			index;
	float		PaternNo;//パターン番号
	float		uv_w;//横サイズ
	float		uv_h;//縦サイズ
	int			NumPatern;//横枚数
}OPENKEY;

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitOpenKey();
void UninitOpenKey();
void UpdateOpenKey();
void DrawOpenKey();
OPENKEY *GetOpenKey();
void SetOpenKey(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int index);
void DeleteOpenKey(int PieceNo);


//=============================================================================
//グローバル変数
//=============================================================================
