#include "texture.h"
/*==============================================================================

   テクスチャの管理[texture.cpp]
														 Author :新保翔麻
														 Date   :6/13
--------------------------------------------------------------------------------*/
///============================
//マクロ定義
//-----------------------------
#define		MAX_TEXTURE_NUM		(110)//テクスチャの読み込み最大枚数

///============================
//プロトタイプ宣言
//-----------------------------


///============================
//グローバル変数
//-----------------------------
//ロードしたテクスチャの情報配列
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM];
//ロードしたテクスチャの枚数
static UINT g_TextureIndex = 0;
//ロードしたテクスチャファイルのバッファ
static char g_TextureNameBroken[MAX_TEXTURE_NUM][256];

///--------------------------------
//テクスチャのロード
//引数：ファイル名
//戻り値：テクスチャインデックス
//---------------------------------
int LoadTexture(char * filename)
{
	//すでに読み込まれた同名のテクスチャがある場合はその番号を返す
	for (int i = 0; i < g_TextureIndex; i++)
	{
		//if (strcmp(&g_TextureName[i][0], filename))こっちでもいい

		//名前が同じだったら
		if (strcmp(g_TextureNameBroken[i], filename) == 0)
		{
			return i;
		}
	}
	//読み込み最大数を超えていたらエラー

	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return -1;//エラーとしてマイナスイチを返す
	}
	//テクスチャのロード

	HRESULT		hr = D3DX11CreateShaderResourceViewFromFile
	(
	GetDevice(),filename,NULL,NULL,&g_pTexture[g_TextureIndex],NULL
	);
	if (hr !=  S_OK)	//うまくいくとS＿OKとなるので違う勝った場合
	{
		return -1;
	}
	//テクスチャ名の登録	名前の箱	最大文字数	コピーしたい名前
	strcpy_s(g_TextureNameBroken[g_TextureIndex], 256, filename);

	int retIndex = g_TextureIndex;	//保存

	g_TextureIndex++;	//インクリメント

	return retIndex;	//読み込んだテクスチャの番号を返す
}
//--------------------------------------
//テクスチャの解放
//--------------------------------------
void Uninittexture()
{
	for (int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] !=NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}
//----------------------------------------
//テクスチャの取得
//引数：テクスチャインデックス
//戻り値：テクスチャ情報のポインタ
//---------------------------------------
ID3D11ShaderResourceView ** GetTexture(int index)
{
	//不正値のチェック
	if (index <0)	//０未満
	{
		return NULL;
	}
	if (index >= g_TextureIndex)	//読み込み数オーバー
	{
		return NULL;

	}

	return &g_pTexture[index];	//indexが表す配列のポインタ
}
