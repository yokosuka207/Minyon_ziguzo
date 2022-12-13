/*==============================================================================

   背景管理 [bg.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

#include"bg.h"
#include"texture.h"
#include"sprite.h"
//変更

static	ID3D11Buffer		*g_VertexBufferBG = NULL;	//背景ポリゴン用
static ID3D11ShaderResourceView	*g_texture;	//画像一枚で一つの変数が必要
//static char *g_textureName = (char*)"data\\texture\\R.png";	//テクスチャファイルパス
//static char *g_textureName = (char*)"data\\texture\\game-pipora-min_1.png";	//テクスチャファイルパス
static char *g_textureName = (char*)"data\\texture\\runningman003.png";	//テクスチャファイルパス

static ID3D11ShaderResourceView	*g_texture_under;	//画像一枚で一つの変数が必要
static char *g_texture_under_Name = (char*)"data\\texture\\gray.jpg";	//テクスチャファイルパス
static int g_TextureNoBG = 0;

BG *Bg;	//背景構造体のポインタ変数

HRESULT BgInit()
{
	//SpriteInit();

	g_TextureNoBG = LoadTexture(g_texture_under_Name);
	if (g_TextureNoBG == -1)
	{//ロードエラー
		exit(999);	//強制終了する
	}
	Bg = new BG;	//動的インスタンス化
	Bg->Position = D3DXVECTOR3(0.0f, 0.0f, 0);
	Bg->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	Bg->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Bg->Rotation = 0.0f;

	return S_OK;

}

void BgUninit()
{
	if (g_VertexBufferBG)
	{
		g_VertexBufferBG->Release();//使い終わったので解放する
		g_VertexBufferBG = NULL;
	}
	if (g_texture_under)
	{
		g_texture_under->Release();
		g_texture_under = NULL;
	}

	if (Bg)
	{
		delete Bg;
		Bg = NULL;
	}


}

void BgUpdate()
{
}

void BgDraw()
{
	//SetWorldViewProjection2D();

	{	//背景ポリゴン表示

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNoBG));

		D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		SpriteDrawColorRotation(
			Bg->Position.x, Bg->Position.y,0.5f, Bg->Size.x, Bg->Size.y
			, Bg->Rotation, Bg->Color, 0, 1.0f, 1.0f, 1);
	}

}
//=================================================
//背景ポリゴン頂点格納処理
//表示座標X, 表示座標Y,横サイズ,縦サイズ,回転速度,色
//=================================================


void SetVertexBG(float PosX, float PosY, int Size_W, int Size_H, float Kakudo, D3DXCOLOR COL, float sokudo)
{
	//D3D11_MAPPED_SUBRESOURCE msr;
	////頂点バッファへの書き込み許可をもらう
	//GetDeviceContext()->Map(g_VertexBufferBG, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	////頂点構造体の型にポインター型を変換をする
	//VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	////static float sokudo = 0.0f;
	////頂点 V0をセット
	//vertex[0].Position = D3DXVECTOR3(-Size_W / 2, -Size_H / 2, 0.0f);
	//vertex[0].Diffuse = COL;
	//vertex[0].TexCoord = D3DXVECTOR2(0.0f + sokudo, 0.0f);
	////頂点 V1をセット
	//vertex[1].Position = D3DXVECTOR3(+Size_W / 2, -Size_H / 2, 0.0f);
	//vertex[1].Diffuse = COL;
	//vertex[1].TexCoord = D3DXVECTOR2(1.0f + sokudo, 0.0f);
	////頂点 V2をセット
	//vertex[2].Position = D3DXVECTOR3(-Size_W / 2, +Size_H / 2, 0.0f);
	//vertex[2].Diffuse = COL;
	//vertex[2].TexCoord = D3DXVECTOR2(0.0f + sokudo, 1.0f);
	////頂点 V3をセット
	//vertex[3].Position = D3DXVECTOR3(+Size_W / 2, +Size_H / 2, 0.0f);
	//vertex[3].Diffuse = COL;
	//vertex[3].TexCoord = D3DXVECTOR2(1.0f + sokudo, 1.0f);
	////offset += sokudo / 60.0f;




	////texcoordをいじれば色々できる
	////度をラジアンへ変換する
	//float	rad = D3DXToRadian(Kakudo);
	//float	x, y;

	//for (int i = 0; i < 4; i++)
	//{
	//	//加法定理		
	//	x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
	//	y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

	//	vertex[i].Position.x = x + PosX;	//平行移動（中心をずらす）
	//	vertex[i].Position.y = y + PosY;
	//}

	////UVアニメーション
	//GetDeviceContext()->Unmap(g_VertexBufferBG, 0);//書き込み終了
}
