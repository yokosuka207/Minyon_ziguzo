/*==============================================================================
スプライト描画
   ポリゴン分け[sprite.h]
														 Author :新保翔麻
														 Date   :6/13
--------------------------------------------------------------------------------*/

#include"renderer.h"
#include"sprite.h"


///============================
//マクロ定義
//-----------------------------
#define	NUM_TRIANGLE_VERTEX	(4)		//三角形用頂点数
#define	NUM_PUZZLE_VERTEX	(64)		//三角形用頂点数


///============================
//プロトタイプ宣言
//この中だけでいい関数
//-----------------------------


///============================
//グローバル変数
//-----------------------------

static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;	//頂点バッファ


//static float PaternNo = 0;	//パターン番号
//float uv_w = 0.5f;	//横サイズ
//float uv_h = 0.5f;	//縦サイズ
//int NumPatern = 2;	//横枚数

//======================
//初期化
//=========================
void SpriteInit()
{
	{//三角形用の頂点初期化処理
	// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_TRIANGLE_VERTEX;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
		//三角形用頂点格納処理
		//SetVertexTringle(PositionX, PositionY, BOX_W, BOX_H, 0,col);
	}

}
//======================
//終了処理
//======================
void SpriteUninit()
{
	if (g_VertexBufferTriangle)
	{
		g_VertexBufferTriangle->Release();//使い終わったので解放する
		g_VertexBufferTriangle = NULL;
	}

}




//=================================================
//三角形用頂点格納処理
//表示座標X, 表示座標Y,横サイズ,縦サイズ,回転速度,色
//速度,テクスチャのパターン,テクスチャの横サイズ,縦サイズ,横パターンの数
//=================================================
void SpriteDrawColorRotation(float PosX, float PosY,float PosZ, int Size_W, int Size_H, float Kakudo,D3DXCOLOR COL
	,float PaternNo, float uv_w, float uv_h, int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//static float sokudo = 0.0f;

	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(-Size_W/2, -Size_H/2, PosZ);
	vertex[0].Diffuse = COL;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(+Size_W/2, -Size_H/2, PosZ);
	vertex[1].Diffuse = COL;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f  , 0.0f);
	//頂点 V2をセット
	vertex[2].Position = D3DXVECTOR3(-Size_W/2, +Size_H/2,PosZ);
	vertex[2].Diffuse = COL;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f , 1.0f);
	//頂点 V3をセット
	vertex[3].Position = D3DXVECTOR3(+Size_W/2, +Size_H/2, PosZ);
	vertex[3].Diffuse = COL;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f , 1.0f);
	//offset += sokudo / 60.0f;

	//UVアニメーション
	//ほんとは引数にするパラメーター

	//static float PaternNo = 0;	//パターン番号
	//float uv_w = 0.5f;	//横サイズ
	//float uv_h = 0.5f;	//縦サイズ
	//int NumPatern = 2;	//横枚数


	//UV座標の計算
	int no = PaternNo;	//パターン番号を整数値にする
	float u = (no % NumPatern) * uv_w;
	float v = (no / NumPatern) * uv_h;

	//UV座標の書き換え
	vertex[0].TexCoord = D3DXVECTOR2(u, v);	//左上
	vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);//右上
	vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);//左下
	vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);//右下


	PaternNo += 0.01f;
	if (PaternNo >= 4.0f)
	{
		PaternNo -= 4.0f;
	}
	//texcoordをいじれば色々できる
	//度をラジアンへ変換する
	float	rad = D3DXToRadian(Kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{
		//加法定理
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + PosX;	//平行移動（中心をずらす）
		vertex[i].Position.y = y + PosY;
	}

	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//書き込み終了


	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	//三角形の頂点データを格納
	GetDeviceContext()->Draw(NUM_TRIANGLE_VERTEX, 0);

}

