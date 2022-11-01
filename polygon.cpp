/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :5/30
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include"sprite.h"
#include"texture.h"
#include"input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX_LINESTRIP (64)	//ラインストリップ頂点最大数
//#define	NUM_TRIANGLE_VERTEX	(4)		//三角形用頂点数

#define	BOX_W	(100)	//四角形の横のサイズ
#define	BOX_H	(100)	//四角形の縦のサイズ



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void	SetVertexLineStrip(int);							//ラインストリップ頂点格納処理
//void	SetVertexTringle(float, float, int, int, float,D3DXCOLOR,float);	//三角形用頂点格納処理
void	SetVertexLine(float, float, float, float);			//直線用頂点格納処理
void	SetVertexCircle(float, float, float, int, D3DXCOLOR);	//多角形の表示


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static	ID3D11Buffer		*g_VertexBufferLineStrip = NULL;//ラインストリップ用
//static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;	//四角形用
static	ID3D11Buffer		*g_VertexBufferLine = NULL;		//直線用

static	ID3D11Buffer		*g_VertexBufferCircle = NULL;	//多角形用



float	PositionX = 0;//画面中央座標
float	PositionY = 0;
float	Kakudo = 0; //四角形の回転角度

float	StartPositionX = 0;				//直線のスタート座標
float	StartPositionY = 0;
float	EndPositionX = SCREEN_WIDTH;	//直線の終了座標
float	EndPositionY = SCREEN_HEIGHT;


//テクスチャの保存変数


D3DXVECTOR3	Goal = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);	//画面中央
D3DXVECTOR3	Speed;
D3DXVECTOR3	Start;


//キャラクター構造体

//背景構造体
//typedef struct
//{
//	//この四つがあれば取り敢えず表示できる
//	D3DXVECTOR3		Position;	//表示座標
//	D3DXCOLOR		Color;		//表示色
//	float			Rotation;	//角度
//	D3DXVECTOR2		Size;		//ポリゴンのサイズ
//
//}BG;
//BG *Bg;	//背景構造体のポインタ変数


//テクスチャの番号の箱
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon(void)
{

	//乱数の初期化
	srand(timeGetTime());
	//ポリゴンの表示をランダムにする
	PositionX = SCREEN_WIDTH/2;
	PositionY = SCREEN_HEIGHT/2;

	Start.x = PositionX;
	Start.y = PositionY;
	Start.z = 0.0f;

	//目的地までのベクトルを作る
	Speed = Goal - Start;
	//正規化して長さを1にする(ポインタ)
	D3DXVec3Normalize(&Speed, &Speed);
	//ベクトルを任意に長さにする
	//x.y.zに３がかけられる
	Speed *= 1.0f;

	ID3D11Device *pDevice = GetDevice();

	//テクスチャロード
	{
		//D3DX11CreateShaderResourceViewFromFile(
		//	pDevice,	//DirectX本体の情報
		//	g_textureName,	//テクスチャのファイル名
		//	NULL, NULL, &g_texture,	//ロードしたテクスチャの情報
		//	NULL
		//);

		//D3DX11CreateShaderResourceViewFromFile(
		//	pDevice,	//DirectX本体の情報
		//	g_texture_under_Name,	//テクスチャのファイル名
		//	NULL, NULL, &g_texture_under,	//ロードしたテクスチャの情報
		//	NULL
		//);
		

	}

	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX_LINESTRIP;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLineStrip);
		// 頂点バッファ更新
		SetVertexLineStrip(4);
	}
	/*{//三角形用の頂点初期化処理
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
	}*/
	{//直線用
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 2;			//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLine);
		//直線用頂点格納処理
		SetVertexLine(StartPositionX, StartPositionY, EndPositionX, EndPositionY );
	}
	{//多角形用
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 64;	//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferCircle);

		//多角形用頂点格納処理
		D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		SetVertexCircle(300.0f, 500.0f, 100.0f, 32, col);

	}
	
	//{//背景ポリゴン用の頂点初期化処理
	//// 頂点バッファ生成
	//	D3D11_BUFFER_DESC bd;
	//	ZeroMemory(&bd, sizeof(bd));
	//	bd.Usage = D3D11_USAGE_DYNAMIC;
	//	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_TRIANGLE_VERTEX;//頂点1個＊頂点数のサイズで作る
	//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferBG);
	//	//三角形用頂点格納処理
	//	//D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	//SetVertexBG(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, col, 0.0f);
	//}

	//スプライトの初期化
	//SpriteInit();


	//背景の初期化

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	// 頂点バッファの解放
	if (g_VertexBufferLineStrip)
	{
		g_VertexBufferLineStrip->Release();//使い終わったので解放する
		g_VertexBufferLineStrip = NULL;
	}

	//if (g_VertexBufferTriangle)
	//{
	//	g_VertexBufferTriangle->Release();//使い終わったので解放する
	//	g_VertexBufferTriangle = NULL;
	//}

	if (g_VertexBufferLine)
	{
		g_VertexBufferLine->Release();//使い終わったので解放する
		g_VertexBufferLine = NULL;
	}

	if (g_VertexBufferCircle)
	{
		g_VertexBufferCircle->Release();//使い終わったので解放する
		g_VertexBufferCircle = NULL;
	}
	//スプライトの終了処理
	SpriteUninit();

	//BG構造体の解放
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	//中心に向かう移動
	Start += Speed;

	PositionX = Start.x;
	PositionY = Start.y;

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	//{
	//	// 表示したいポリゴンの頂点バッファを設定
	//	UINT stride = sizeof(VERTEX_3D);
	//	UINT offset = 0;
	//	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferLineStrip, &stride, &offset);
	//	// プリミティブトポロジ設定
	//	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);// LINELIST);
	// マテリアル設定
		/*MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SetMaterial(material);*/
		//SetVertexLineStrip(4);
		//// ポリゴン描画
		//GetDeviceContext()->Draw(4, 0);
	//背景ポリゴン表示
	//{
	//	//背景ポリゴン表示
	//		UINT stride = sizeof(VERTEX_3D);
	//		UINT offset = 0;
	//		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferBG, &stride, &offset);
	//		// プリミティブトポロジ設定
	//		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//		
	//		//色を与える
	//		D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	SetVertexBG(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f,col,0.0f);
	//	//		Kakudo += 3.0f;
	//			//テクスチャの設定(Drewの直前に書く)
	//			//数字は変えない
	//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_texture_under);
	//	//GetDeviceContext()->PSSetShaderResources(0, 1, NULL);これでテクスチャを使わない
	//	// ポリゴン描画
	//	GetDeviceContext()->Draw(NUM_TRIANGLE_VERTEX, 0);
	//}

	//四角形の描画

	{		//SetBlendState(BLEND_MODE::BLEND_MODE_SUBTRACT);

		//四角形の描画
		// 表示したいポリゴンの頂点バッファを設定
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		//// プリミティブトポロジ設定
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		////三角形の頂点データを格納
			//色を与える
				//Kakudo += 3.0f;
				//textuer_sokudo += 1.0f / 60.0f;
				//テクスチャの設定(Drewの直前に書く)
				//数字は変えない
		//GetDeviceContext()->PSSetShaderResources(0, 1, NULL);これでテクスチャを使わない


		 //SetSamplerState(FILTER_MODE::FILTER_MODE_POINT, ADDRESS_MODE ::ADDRESS_MODE_MIRROR);
		// ポリゴン描画
	//	GetDeviceContext()->Draw(NUM_TRIANGLE_VERTEX, 0);
		//SetBlendState(BLEND_MODE::BLEND_MODE_ALPHABLEND);

	}

	//	// ２Ｄ表示をするためのマトリクスを設定

	{//直線の描画
		// 表示したいポリゴンの頂点バッファを設定
	//	UINT stride = sizeof(VERTEX_3D);
	//	UINT offset = 0;
	//	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferLine, &stride, &offset);
	//	// プリミティブトポロジ設定
	//	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//	//直線の頂点データを格納
	//	SetVertexLine(StartPositionX, StartPositionY, EndPositionX, EndPositionY);
	//	// ポリゴン描画
	//	GetDeviceContext()->Draw(2, 0);
	}
	{//多角形の描画
		//// 表示したいポリゴンの頂点バッファを設定
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferCircle, &stride, &offset);
		//// プリミティブトポロジ設定
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		////多角形の頂点データを格納
		//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//SetVertexCircle(300.0f, 300.0f, 100.0f, 16, col);
		//// ポリゴン描画
		//GetDeviceContext()->Draw(16+1, 0);
	}

	
}


//=============================================================================
// 頂点データ設定
//=============================================================================
void SetVertexLineStrip(int	NumVertex)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferLineStrip, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//一本目の直線の頂点をセット
	vertex[0].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH-100.0f, SCREEN_HEIGHT-100.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//二本目の直線の頂点をセット
	vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 50.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);


	GetDeviceContext()->Unmap(g_VertexBufferLineStrip, 0);
}

////=================================================
////三角形用頂点格納処理
////表示座標X, 表示座標Y,横サイズ,縦サイズ,回転速度,色
////=================================================
//void SetVertexTringle(float PosX, float PosY, int Size_W, int Size_H, float Kakudo,D3DXCOLOR COL,float sokudo)
//{
//	D3D11_MAPPED_SUBRESOURCE msr;
//	//頂点バッファへの書き込み許可をもらう
//	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
//	//頂点構造体の型にポインター型を変換をする
//	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;
//
//	//static float sokudo = 0.0f;
//
//	//頂点 V0をセット
//	vertex[0].Position = D3DXVECTOR3(-Size_W/2, -Size_H/2, 0.0f);
//	vertex[0].Diffuse = COL;
//	vertex[0].TexCoord = D3DXVECTOR2(0.0f+sokudo, 0.0f);
//	//頂点 V1をセット
//	vertex[1].Position = D3DXVECTOR3(+Size_W/2, -Size_H/2, 0.0f);
//	vertex[1].Diffuse = COL;
//	vertex[1].TexCoord = D3DXVECTOR2(3.0f + sokudo, 0.0f);
//	//頂点 V2をセット
//	vertex[2].Position = D3DXVECTOR3(-Size_W/2, +Size_H/2,0.0f);
//	vertex[2].Diffuse = COL;
//	vertex[2].TexCoord = D3DXVECTOR2(0.0f + sokudo, 3.0f);
//	//頂点 V3をセット
//	vertex[3].Position = D3DXVECTOR3(+Size_W/2, +Size_H/2, 0.0f);
//	vertex[3].Diffuse = COL;
//	vertex[3].TexCoord = D3DXVECTOR2(3.0f + sokudo, 3.0f);
//	//offset += sokudo / 60.0f;
//
//	//UVアニメーション
//	static float PaternNo = 0;	//パターン番号
//	float uv_w = 0.5f;	//横サイズ
//	float uv_h = 0.5f;	//縦サイズ
//	int NumPatern = 2;	//横枚数
//
//
//	//UV座標の計算
//	int no = PaternNo;	//パターン番号を整数値にする
//	float u = (no % NumPatern) * uv_w;
//	float v = (no / NumPatern) * uv_h;
//
//	//UV座標の書き換え
//	//vertex[0].TexCoord = D3DXVECTOR2(u, v);	//左上
//	//vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);//右上
//	//vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);//左下
//	//vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);//右下
//
//
//	PaternNo += 0.01f;
//	if (PaternNo >= 4.0f)
//	{
//		PaternNo -= 4.0f;
//	}
//	//texcoordをいじれば色々できる
//	//度をラジアンへ変換する
//	float	rad = D3DXToRadian(Kakudo);
//	float	x, y;
//
//	for (int i = 0; i < 4; i++)
//	{
//		//加法定理		
//		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
//		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);
//
//		vertex[i].Position.x = x + PosX;	//平行移動（中心をずらす）
//		vertex[i].Position.y = y + PosY;
//	}
//
//	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//書き込み終了
//}

//===============================
//直線の頂点を格納
//in
//  開始座標X, 開始座標Y, 終了座標X, 終了座標Y
//
void	SetVertexLine(float StartX, float StartY, float EndX, float EndY)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferLine, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(StartX, StartY, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(EndX, EndY, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	GetDeviceContext()->Unmap(g_VertexBufferLine, 0);//書き込み終了

}

//==============================
//ラインで多角形の表示
//in
//　表示座標X, 表示座標Y, 半径, 頂点数, 色
//==========================================
void	SetVertexCircle(float PosX, float PosY, float Rad, int NumVertex, D3DXCOLOR col)
{

	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferCircle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float	kakudo = 0;
	for (int i = 0; i < NumVertex; i++)
	{
		vertex[i].Position.x = cosf(D3DXToRadian(kakudo)) * Rad + PosX;
		vertex[i].Position.y = sinf(D3DXToRadian(kakudo)) * Rad + PosY;
		vertex[i].Position.z = 0.0f;
		vertex[i].Diffuse = col;
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		kakudo += (360.0f / NumVertex);
	}
	//最後の頂点に最初の頂点をコピーして図形を閉じる
	vertex[NumVertex].Position = vertex[0].Position;
	vertex[NumVertex].Diffuse = vertex[0].Diffuse;
	vertex[NumVertex].TexCoord = vertex[0].TexCoord;

	GetDeviceContext()->Unmap(g_VertexBufferCircle, 0);//書き込み終了



}

