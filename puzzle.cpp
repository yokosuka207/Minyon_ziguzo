#include "puzzle.h"
#include"texture.h"
#include"sprite.h"
#include"input.h"
#include"goal.h"
#include"puzzlecip.h"
#include"broken.h"
#include"warp.h"
//p

PUZZLE g_Puzzle[PUZZLE_MAX];

static ID3D11ShaderResourceView	*g_texturePuzzle;	//画像一枚で一つの変数が必要
static char *g_textureName_Puzzle = (char*)"data\\texture\\black&white.jpg";	//テクスチャファイルパス
static	ID3D11Buffer		*g_VertexBufferP = NULL;	//頂点バッファ

HRESULT InitPuzzle()
{	// 頂点バッファ生成
	{//三角形用の頂点初期化処理
// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_PUZZLE_VERTEX;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferP);
	}


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		g_Puzzle[i].texno = LoadTexture(g_textureName_Puzzle);

		g_Puzzle[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_Puzzle[i].oldPosition = g_Puzzle[i].Position;
		g_Puzzle[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_Puzzle[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Puzzle[i].Rotation = 0.0f;
		g_Puzzle[i].InitPuzzle_TypeUp = STEAT_NUM;
		g_Puzzle[i].InitPuzzle_TypeDown = STEAT_NUM;
		g_Puzzle[i].InitPuzzle_TypeLeft = STEAT_NUM;
		g_Puzzle[i].InitPuzzle_TypeRight = STEAT_NUM;
		g_Puzzle[i].Puzzle_type = TYPE_NONE;
		for (int j = 0; j < 4; j++)
		{
			g_Puzzle[i].blockIndex[j] = -1;
		}
		g_Puzzle[i].CipIndex = -1;
		g_Puzzle[i].BrokenIndex = -1;
		g_Puzzle[i].WarpIndex[0] = -1;
		g_Puzzle[i].WarpIndex[1] = -1;
		g_Puzzle[i].RotNum = 0;
		g_Puzzle[i].MoveFlag = false;
		g_Puzzle[i].MoveEndFlag = false;
		g_Puzzle[i].UseFlag = false;
	}
	SetPuzzle(D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), 
		STEAT_NUM, STEAT_DEPPARI, STEAT_NUM, STEAT_DEPPARI,GRAND_DOWN,TYPE_NOMAL,CIP_NONE,TYPE_GRAND,false);
	SetPuzzle(D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT),
		STEAT_NUM, STEAT_NUM, STEAT_HIKKOMI, STEAT_HIKKOMI,GRAND_RIGHT,TYPE_NOMAL, CIP_NOMAL,TYPE_GRAND,false);

	/*SetPuzzle(D3DXVECTOR2(200.0f, 400.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT),
		STEAT_DEPPARI, STEAT_DEPPARI, STEAT_NUM, STEAT_DEPPARI, GRAND_UP, TYPE_NOMAL, CIP_NONE,TYPE_HARFGRAND,true);
	SetPuzzle(D3DXVECTOR2(600.0f, 400.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT),
		STEAT_DEPPARI, STEAT_HIKKOMI, STEAT_NUM, STEAT_HIKKOMI, GRAND_UP, TYPE_NOMAL, CIP_NONE, TYPE_CENTER,false);
	SetPuzzle(D3DXVECTOR2(600.0f, 100.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT),
		STEAT_HIKKOMI, STEAT_DEPPARI, STEAT_HIKKOMI, STEAT_HIKKOMI, GRAND_LEFT, TYPE_NOMAL, CIP_NONE, TYPE_HARFGRAND,true);*/

	return S_OK;
}

void UninitPuzzle()
{
	if (g_texturePuzzle)
	{
		g_texturePuzzle->Release();
		g_texturePuzzle = NULL;
	}
	if (g_VertexBufferP)
	{
		g_VertexBufferP->Release();//使い終わったので解放する
		g_VertexBufferP = NULL;

	}

}

void UpdatePuzzle()
{
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (g_Puzzle[i].UseFlag)
		{

			PuzzleBlockUpdate(g_Puzzle[i]);

			if (g_Puzzle[i].BrokenIndex != -1)
			{
				BROKEN* pBroken = GetBroken();
				pBroken[g_Puzzle[i].BrokenIndex].Postion = D3DXVECTOR2(g_Puzzle[i].Position.x, g_Puzzle[i].Position.y);
			}

		}
	}

}

void DrawPuzzle()
{
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (g_Puzzle[i].UseFlag)
		{

			SetWorldViewProjection2D();
			//四角形の描画
			//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.8f, 0.8f, 0.5f);
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Puzzle[i].texno));

			/*
			SpriteDrawColorRotation(g_Puzzle[i].Position.x, g_Puzzle[i].Position.y,
				g_Puzzle[i].Size.x, g_Puzzle[i].Size.y, g_Puzzle[i].Rotation, g_Puzzle[i].Col, 0,
				0, 1.0f, 1.0f, 1);
				//*/

			///*
			SpriteDrawColorRotationPuzzle(g_Puzzle[i].Position,g_Puzzle[i].Size, g_Puzzle[i].Rotation, g_Puzzle[i].Col, 
				g_Puzzle[i].InitPuzzle_TypeUp, g_Puzzle[i].InitPuzzle_TypeRight, g_Puzzle[i].InitPuzzle_TypeDown, g_Puzzle[i].InitPuzzle_TypeLeft);
			//*/

		}
	}

}

//--------------------------------------------
//パズルのセット関数
//引数：ポジション.サイズ.上下左右のpuzzleモードの選択
//	地面の上下左右の設置.パズルのチップのタイプ
//--------------------------------------------
void SetPuzzle(D3DXVECTOR2 pos, D3DXVECTOR2 size,
	PUZZLE_STEAT PTUp, PUZZLE_STEAT PTRigft,PUZZLE_STEAT PTDown, PUZZLE_STEAT PTLeft,
	GRAND_TYPE gtype, PUZZLE_TYPE ptype,CIP_TYPE ctype, BLOCK_TYPE btype, bool Wflag)
{
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (!g_Puzzle[i].UseFlag)
		{
			

				g_Puzzle[i].Position = pos;
				g_Puzzle[i].oldPosition = g_Puzzle[i].Position;
				g_Puzzle[i].Size = size;
				g_Puzzle[i].InitPuzzle_TypeUp = g_Puzzle[i].Puzzle_TypeUp = PTUp;
				g_Puzzle[i].InitPuzzle_TypeDown = g_Puzzle[i].Puzzle_TypeDown = PTDown;
				g_Puzzle[i].InitPuzzle_TypeLeft = g_Puzzle[i].Puzzle_TypeLeft = PTLeft;
				g_Puzzle[i].InitPuzzle_TypeRight = g_Puzzle[i].Puzzle_TypeRight = PTRigft;
				g_Puzzle[i].Block_Type = btype;
				for (int j = 0; j < 4; j++)
				{
					g_Puzzle[i].blockIndex[j] = -1;
				}
					if (gtype != GRAND_NONE)
					{
						//g_Puzzle[i].blockIndex = SetBlock(D3DXVECTOR2(g_Puzzle[i].Position.x, g_Puzzle[i].Position.y), D3DXVECTOR2(GRAND_W, GRAND_H), gtype);
						SetBlock(D3DXVECTOR2(g_Puzzle[i].Position.x, g_Puzzle[i].Position.y), D3DXVECTOR2(GRAND_W, GRAND_H), gtype,btype,i,ctype);

					}
				
				if (ptype == TYPE_GOAL)
				{
					SetGoal(D3DXVECTOR2(g_Puzzle[i].Position.x, g_Puzzle[i].Position.y),D3DXVECTOR2(GOAL_SIEZX,GOAL_SIZEY));
				}

				//g_Puzzle[i].CipIndex = SetPuzzleCip(D3DXVECTOR2(g_Puzzle[i].Position.x, g_Puzzle[i].Position.y), D3DXVECTOR2(GOAL_SIEZX, GOAL_SIZEY), ctype);
				
				//g_Puzzle[i].BrokenIndex = SetBroken(g_Puzzle[i].Position, D3DXVECTOR2(BROKEN_SIZE_W, BROKEN_SIZE_H));

				g_Puzzle[i].Puzzle_type = ptype;
				if (Wflag)
				{
					g_Puzzle[i].WarpIndex[0] = SetWarp(D3DXVECTOR2(pos.x, pos.y - 30.0f),D3DXVECTOR2(WARP_SIZE_W,WARP_SIZE_H));
				}
				g_Puzzle[i].MoveEndFlag = false;

				g_Puzzle[i].UseFlag = true;
				break;
			
		}
	}

}

PUZZLE * GetPuzzle()
{
	return &g_Puzzle[0];
}


//=================================================
//パズル用頂点格納処理
//ポジション,サイズ,角度,色
//上下左右のpuzzleモードの選択
//=================================================

void SpriteDrawColorRotationPuzzle(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, float Kakudo, D3DXCOLOR col,
	PUZZLE_STEAT Up, PUZZLE_STEAT Right, PUZZLE_STEAT Down, PUZZLE_STEAT Left)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferP, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	/////////////////////////////////////////////////////////////////////////////////

	vertex[0].Position = D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.5f, 0.0f);
	
	vertex[1].Position = D3DXVECTOR3(Size.x / 2,-Size.y / 2, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
	vertex[2].Position = D3DXVECTOR3(- Size.x / 2, Size.y / 2, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	
	vertex[3].Position = D3DXVECTOR3(Size.x / 2,- Size.y / 2, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
	vertex[4].Position = D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);
	vertex[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[4].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	
	vertex[5].Position = D3DXVECTOR3(- Size.x / 2, Size.y / 2, 0.0f);
	vertex[5].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[5].TexCoord = D3DXVECTOR2(0.5f, 1.0f);
	//////////////////////////////////////////////////////////////////
	switch (Up)
	{
	case STEAT_DEPPARI:
		vertex[6].Position = D3DXVECTOR3(-BLOCK_W/2, -Size.y / 2 - BLOCK_H, 0.0f);
		vertex[6].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[6].TexCoord = D3DXVECTOR2(0.5f, 0.0f);
	
		vertex[7].Position = D3DXVECTOR3(BLOCK_W/2, -Size.y / 2 - BLOCK_H, 0.0f);
		vertex[7].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[7].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
		vertex[8].Position = D3DXVECTOR3(-BLOCK_W/2, -Size.y / 2 , 0.0f);
		vertex[8].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[8].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	
		vertex[9].Position = D3DXVECTOR3(BLOCK_W/2, -Size.y / 2 - BLOCK_H, 0.0f);
		vertex[9].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[9].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
		vertex[10].Position = D3DXVECTOR3(BLOCK_W/2, -Size.y / 2, 0.0f);
		vertex[10].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[10].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	
		vertex[11].Position = D3DXVECTOR3(-BLOCK_H / 2, -Size.y / 2, 0.0f);
		vertex[11].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[11].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	
		break;
	case STEAT_HIKKOMI:
		vertex[6].Position = D3DXVECTOR3(BLOCK_W / 2, -Size.y / 2 + BLOCK_H, 0.0f);
		vertex[6].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[6].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[7].Position = D3DXVECTOR3(-BLOCK_W / 2, -Size.y / 2 + BLOCK_H, 0.0f);
		vertex[7].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[7].TexCoord = D3DXVECTOR2(0.5f, 0.0f);

		vertex[8].Position = D3DXVECTOR3(-BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[8].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[8].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[9].Position = D3DXVECTOR3(BLOCK_W / 2, -Size.y / 2 + BLOCK_H, 0.0f);
		vertex[9].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[9].TexCoord = D3DXVECTOR2(0.5f, 0.0f);

		vertex[10].Position = D3DXVECTOR3(-BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[10].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[10].TexCoord = D3DXVECTOR2(0.5f, 0.5f);

		vertex[11].Position = D3DXVECTOR3(BLOCK_H / 2, -Size.y / 2, 0.0f);
		vertex[11].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[11].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	
		break;
	case STEAT_NUM:
		vertex[6].Position = D3DXVECTOR3(-BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[6].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[6].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[7].Position = D3DXVECTOR3(BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[7].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[7].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[8].Position = D3DXVECTOR3(-BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[8].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[8].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[9].Position = D3DXVECTOR3(BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[9].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[9].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[10].Position = D3DXVECTOR3(BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[10].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[10].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[11].Position = D3DXVECTOR3(-BLOCK_W / 2, -Size.y / 2, 0.0f);
		vertex[11].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[11].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		break;
	default:
		break;
	}
	///////////////////////////////////////////////////////////////////////////////
	switch (Right)
	{
	case STEAT_DEPPARI:
		vertex[12].Position = D3DXVECTOR3(Size.x / 2 + BLOCK_W, -BLOCK_H / 2, 0.0f);
		vertex[12].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[12].TexCoord = D3DXVECTOR2(0.5f, 0.0f);
	
		vertex[13].Position = D3DXVECTOR3(Size.x / 2 + BLOCK_W,BLOCK_H / 2, 0.0f);
		vertex[13].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[13].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
		vertex[14].Position = D3DXVECTOR3(Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[14].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[14].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	
		vertex[15].Position = D3DXVECTOR3(Size.x / 2 + BLOCK_W, BLOCK_H / 2, 0.0f);
		vertex[15].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[15].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
		vertex[16].Position = D3DXVECTOR3(Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[16].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[16].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	
		vertex[17].Position = D3DXVECTOR3(Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[17].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[17].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	
		break;
	case STEAT_HIKKOMI:
		vertex[12].Position = D3DXVECTOR3(Size.x / 2 - BLOCK_W, -BLOCK_H / 2, 0.0f);
		vertex[12].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[12].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[13].Position = D3DXVECTOR3(Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[13].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[13].TexCoord = D3DXVECTOR2(0.5f, 0.0f);

		vertex[14].Position = D3DXVECTOR3(Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[14].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[14].TexCoord = D3DXVECTOR2(0.5f, 0.5f);

		vertex[15].Position = D3DXVECTOR3(Size.x / 2 - BLOCK_W, -BLOCK_H / 2, 0.0f);
		vertex[15].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[15].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[16].Position = D3DXVECTOR3(Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[16].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[16].TexCoord = D3DXVECTOR2(0.5f, 0.5f);

		vertex[17].Position = D3DXVECTOR3(Size.x / 2 - BLOCK_W, BLOCK_H / 2, 0.0f);
		vertex[17].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[17].TexCoord = D3DXVECTOR2(0.5f, 0.0f);

		break;
	case STEAT_NUM:
	
		vertex[12].Position = D3DXVECTOR3(Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[12].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[12].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[13].Position = D3DXVECTOR3(Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[13].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[13].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[14].Position = D3DXVECTOR3(Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[14].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[14].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[15].Position = D3DXVECTOR3(Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[15].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[15].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[16].Position = D3DXVECTOR3(Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[16].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[16].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[17].Position = D3DXVECTOR3(Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[17].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[17].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		break;
	default:
		break;
	}
	//////////////////////////////////////////////////////////////////////////////////////
	switch (Down)
	{
	case STEAT_DEPPARI:
		vertex[18].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[18].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[18].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
		vertex[19].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2 + BLOCK_H, 0.0f);
		vertex[19].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[19].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	
		vertex[20].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2 + BLOCK_H, 0.0f);
		vertex[20].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[20].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	
		vertex[21].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[21].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[21].TexCoord = D3DXVECTOR2(0.6f, 0.0f);
	
		vertex[22].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2 + BLOCK_H, 0.0f);
		vertex[22].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[22].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
		vertex[23].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[23].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[23].TexCoord = D3DXVECTOR2(0.6f, 0.5f);
	
		break;
	case STEAT_HIKKOMI:
		vertex[18].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2 - BLOCK_H, 0.0f);
		vertex[18].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[18].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[19].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2 - BLOCK_H, 0.0f);
		vertex[19].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[19].TexCoord = D3DXVECTOR2(0.5f, 0.0f);

		vertex[20].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[20].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[20].TexCoord = D3DXVECTOR2(0.5f, 0.5f);

		vertex[21].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2 - BLOCK_H, 0.0f);
		vertex[21].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[21].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[22].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[22].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[22].TexCoord = D3DXVECTOR2(0.5f, 0.0f);

		vertex[23].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[23].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[23].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
		break;
	case STEAT_NUM:
		vertex[18].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[18].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[18].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[19].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[19].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[19].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[20].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[20].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[20].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[21].Position = D3DXVECTOR3(BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[21].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[21].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[22].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[22].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[22].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[23].Position = D3DXVECTOR3(-BLOCK_W / 2, Size.y / 2, 0.0f);
		vertex[23].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[23].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		break;
	default:
		break;
	}
	switch (Left)
	{
	case STEAT_DEPPARI:
		vertex[24].Position = D3DXVECTOR3(-Size.x / 2+2.0f, BLOCK_H / 2, 0.0f);
		vertex[24].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[24].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	
		vertex[25].Position = D3DXVECTOR3(-Size.x / 2 - BLOCK_W, BLOCK_H / 2, 0.0f);
		vertex[25].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[25].TexCoord = D3DXVECTOR2(0.5f, 0.5f);
	
		vertex[26].Position = D3DXVECTOR3(-Size.x / 2 - BLOCK_W, -BLOCK_H / 2, 0.0f);
		vertex[26].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[26].TexCoord = D3DXVECTOR2(0.5f, 0.0f);
	
		vertex[27].Position = D3DXVECTOR3(-Size.x / 2 - BLOCK_W, -BLOCK_H / 2, 0.0f);
		vertex[27].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[27].TexCoord = D3DXVECTOR2(0.5f, 0.0f);
	
		vertex[28].Position = D3DXVECTOR3(-Size.x / 2 + 2.0f, -BLOCK_H / 2, 0.0f);
		vertex[28].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[28].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
		vertex[29].Position = D3DXVECTOR3(-Size.x / 2 + 2.0f, BLOCK_H / 2, 0.0f);
		vertex[29].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[29].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	
		break;
	case STEAT_HIKKOMI:
		vertex[24].Position = D3DXVECTOR3(-Size.x / 2 + BLOCK_W, BLOCK_H / 2, 0.0f);
		vertex[24].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[24].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[25].Position = D3DXVECTOR3(-Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[25].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[25].TexCoord = D3DXVECTOR2(0.5f, 0.5f);

		vertex[26].Position = D3DXVECTOR3(-Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[26].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[26].TexCoord = D3DXVECTOR2(0.0f, 0.5f);

		vertex[27].Position = D3DXVECTOR3(-Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[27].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[27].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[28].Position = D3DXVECTOR3(-Size.x / 2 + BLOCK_W, -BLOCK_H / 2, 0.0f);
		vertex[28].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[28].TexCoord = D3DXVECTOR2(0.5f, 0.5f);

		vertex[29].Position = D3DXVECTOR3(-Size.x / 2+ BLOCK_W, BLOCK_H / 2, 0.0f);
		vertex[29].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[29].TexCoord = D3DXVECTOR2(0.0f, 0.5f);

		break;
	case STEAT_NUM:
	
		vertex[24].Position = D3DXVECTOR3(-Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[24].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[24].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[25].Position = D3DXVECTOR3(-Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[25].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[25].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[26].Position = D3DXVECTOR3(-Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[26].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[26].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[27].Position = D3DXVECTOR3(-Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[27].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[27].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[28].Position = D3DXVECTOR3(-Size.x / 2, -BLOCK_H / 2, 0.0f);
		vertex[28].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[28].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[29].Position = D3DXVECTOR3(-Size.x / 2, BLOCK_H / 2, 0.0f);
		vertex[29].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[29].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		break;
	default:
		break;
	}


	//UV座標の計算
	//int no = PaternNo;	//パターン番号を整数値にする
	//float u = (no % NumPatern) * uv_w;
	//float v = (no / NumPatern) * uv_h;
	//UV座標の書き換え
	//vertex[0].TexCoord = D3DXVECTOR2(u, v);	//左上
	//vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);//右上
	//vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);//左下
	//vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);//右下


	//PaternNo += 0.01f;
	//if (PaternNo >= 4.0f)
	//{
	//	PaternNo -= 4.0f;
	//}
	//texcoordをいじれば色々できる
	//度をラジアンへ変換する
	//float k = 360.0f / Kakudo;
	float	rad = D3DXToRadian(Kakudo);
	float	x, y;

	for (int i = 0; i < 30; i++)
	{

		//加法定理
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x+Pos.x;	//平行移動（中心をずらす）
		vertex[i].Position.y = y+Pos.y;

	}

	GetDeviceContext()->Unmap(g_VertexBufferP, 0);//書き込み終了


	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferP, &stride, &offset);
		// プリミティブトポロジ設定
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	}
	//三角形の頂点データを格納
	GetDeviceContext()->Draw(30, 0);

}

//---------------------------------------------
//回転していたら上下左右のパズルを入れ替える
//引数：配列の添え字
//---------------------------------------------
void PuzzleTypeShift(int index)
{
	PUZZLE_STEAT Up, Down, Left, Right;	//保存


	for (int i = 0; i < PUZZLE_MAX; i++)
	{

		if (i == index)
		{
			Down = g_Puzzle[i].Puzzle_TypeDown;
			Left = g_Puzzle[i].Puzzle_TypeLeft;
			Right = g_Puzzle[i].Puzzle_TypeRight;
			Up = g_Puzzle[i].Puzzle_TypeUp;

			g_Puzzle[i].Puzzle_TypeRight = Up;
			g_Puzzle[i].Puzzle_TypeUp = Left;
			g_Puzzle[i].Puzzle_TypeDown = Right;
			g_Puzzle[i].Puzzle_TypeLeft = Down;

		}

	}


}
//--------------------------------------------
//パズル内のブロックの更新
//引数：パズルの実体
//--------------------------------------------
void PuzzleBlockUpdate(PUZZLE puzzle)
{
	BLOCK* pBlock = GetBlock();
	PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	WARP* pWarp = GetWarp();
	GOAL* pGoal = GetGoal();



	switch (puzzle.Block_Type)
	{
	case TYPE_GRAND:

			puzzle.MoveEndFlag = false;
			puzzle.oldRotation = puzzle.Rotation;
			if (puzzle.blockIndex[0] != -1)
			{

				if (puzzle.RotNum == 1)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x - puzzle.Size.x / 2 + BLOCK_W / 2, puzzle.Position.y);
					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(GRAND_H, GRAND_W);
				}
				if (puzzle.RotNum == 2)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - puzzle.Size.y / 2 + BLOCK_H / 2);
					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(GRAND_W, GRAND_H);

				}
				if (puzzle.RotNum == 3)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + puzzle.Size.x / 2 - BLOCK_W / 2, puzzle.Position.y);
					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(GRAND_H, GRAND_W);

				}
				if (puzzle.RotNum == 0)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + puzzle.Size.y / 2 - BLOCK_H / 2);
					//puzzle.Rotation = 0.0f;
					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(GRAND_W, GRAND_H);

					pBlock[puzzle.blockIndex[0]].Rotation = 0.0f;
				}

			}
		
			if (puzzle.CipIndex != -1)
			{

				pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
			}

			if (puzzle.Puzzle_type == TYPE_GOAL)
			{

				if (pGoal->UseFlag)
				{
					pGoal->Pos = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
				}

			}

		break;
	case TYPE_HARFGRAND:
		puzzle.MoveEndFlag = false;
		puzzle.oldRotation = puzzle.Rotation;
		if (puzzle.blockIndex[0] != -1)
		{

			if (puzzle.RotNum == 1)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x - puzzle.Size.x / 2 + BLOCK_W / 2, puzzle.Position.y);
			}
			if (puzzle.RotNum == 2)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - puzzle.Size.y / 2 + BLOCK_H / 2);
			}
			if (puzzle.RotNum == 3)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + puzzle.Size.x / 2 - BLOCK_W / 2, puzzle.Position.y);
			}
			if (puzzle.RotNum == 0)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + puzzle.Size.y / 2 - BLOCK_H / 2);
				//puzzle.Rotation = 0.0f;
				//puzzle.RotNum = 0;
				pBlock[puzzle.blockIndex[0]].Rotation = 0.0f;
			}

		}
		break;

	case TYPE_CENTER:
		puzzle.MoveEndFlag = false;
		puzzle.oldRotation = puzzle.Rotation;

		pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);

		break;

	case TYPE_T:
			if (puzzle.blockIndex[0] != -1)
			{

				if (puzzle.RotNum == 1)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x - puzzle.Size.x / 2 + BLOCK_W / 2, puzzle.Position.y);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);

					pBlock[puzzle.blockIndex[0]].Rotation = 90.0f;
					pBlock[puzzle.blockIndex[1]].Rotation = 0.0f;
					pBlock[puzzle.blockIndex[2]].Rotation = 0.0f;
				}
				if (puzzle.RotNum == 2)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, puzzle.Position.y);

					pBlock[puzzle.blockIndex[0]].Rotation = 0.0f;
					pBlock[puzzle.blockIndex[1]].Rotation = 90.0f;
					pBlock[puzzle.blockIndex[2]].Rotation = 90.0f;
				}
				if (puzzle.RotNum == 3)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, puzzle.Position.y);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);

					pBlock[puzzle.blockIndex[0]].Rotation = 90.0f;
					pBlock[puzzle.blockIndex[1]].Rotation = 0.0f;
					pBlock[puzzle.blockIndex[2]].Rotation = 0.0f;
				}
				if (puzzle.RotNum == 0)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, puzzle.Position.y);

					pBlock[puzzle.blockIndex[0]].Rotation = 0.0f;
					pBlock[puzzle.blockIndex[1]].Rotation = 90.0f;
					pBlock[puzzle.blockIndex[2]].Rotation = 90.0f;
					//puzzle.RotNum= 0;
				}

			}
		

		break;

	case TYPE_SQUARE:
		pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, puzzle.Position.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);

		pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, puzzle.Position.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);

		pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, puzzle.Position.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);

		pBlock[puzzle.blockIndex[3]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, puzzle.Position.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);

		break;

	case TYPE_ZYUUZI:
		pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);

		pBlock[puzzle.blockIndex[1]].Position= D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);

		if (puzzle.CipIndex != -1)
		{
			if (puzzle.RotNum == 1)
			{
				pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 3, puzzle.Position.y - PUZZLE_HEIGHT / 3);

			}
			if (puzzle.RotNum == 2)
			{
				pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 3, puzzle.Position.y - PUZZLE_HEIGHT / 3);

			}
			if (puzzle.RotNum == 3)
			{
				pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 3, puzzle.Position.y + PUZZLE_HEIGHT / 3);

			}
			if (puzzle.RotNum == 0)
			{
				pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 3, puzzle.Position.y + PUZZLE_HEIGHT / 3);

			}

		}
		break;
	case TYPE_TATE:
		if (puzzle.blockIndex[0] != -1)
		{

			if (puzzle.RotNum == 1)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y+PUZZLE_HEIGHT/2-BLOCK_H/2);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - 40.0f);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(PUZZLE_WIDHT,BLOCK_H);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT-70.0f, PUZZLE_HEIGHT / 3);
				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x+PUZZLE_WIDHT/4, puzzle.Position.y+ PUZZLE_HEIGHT / 4);
				}

			}
			if (puzzle.RotNum == 2)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + BLOCK_H / 2, puzzle.Position.y);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x+40.0f, puzzle.Position.y+30.0f);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT / 3, PUZZLE_HEIGHT - 70.0f);
				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 4, puzzle.Position.y + PUZZLE_HEIGHT / 4);
				}

			}
			if (puzzle.RotNum == 3)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + 40.0f);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT - 70.0f, PUZZLE_HEIGHT /3);
				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 4, puzzle.Position.y - PUZZLE_HEIGHT / 4);
				}

			}
			if (puzzle.RotNum == 0)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 + BLOCK_H / 2, puzzle.Position.y);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x-40.0f, puzzle.Position.y+30.0f);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT / 3, PUZZLE_HEIGHT - 70.0f);
				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 4, puzzle.Position.y + PUZZLE_HEIGHT / 4);
				}

			}

		}



		break;

	case TYPE_BOX:


		if (puzzle.blockIndex[0] != -1)
		{

			if (puzzle.RotNum == 1)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x-PUZZLE_WIDHT/4, puzzle.Position.y-PUZZLE_HEIGHT/2+BLOCK_W/2);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
				pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x , puzzle.Position.y + PUZZLE_HEIGHT/2 - BLOCK_W/2);
				pBlock[puzzle.blockIndex[3]].Position = D3DXVECTOR2(puzzle.Position.x -PUZZLE_WIDHT/2+BLOCK_W/2, puzzle.Position.y);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(PUZZLE_WIDHT/2, BLOCK_H);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);

				pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);
				pBlock[puzzle.blockIndex[3]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 4, puzzle.Position.y + PUZZLE_HEIGHT / 4);
				}
				if (puzzle.WarpIndex[0] != -1)
				{
					pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x - 40.0f, puzzle.Position.y );
				}
				if (puzzle.WarpIndex[1] != -1)
				{

					pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x + 30.0f, puzzle.Position.y);

				}


			}
			if (puzzle.RotNum == 2)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, puzzle.Position.y - PUZZLE_HEIGHT / 4);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
				pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, puzzle.Position.y);
				pBlock[puzzle.blockIndex[3]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT/2);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);

				pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
				pBlock[puzzle.blockIndex[3]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);
				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 4, puzzle.Position.y - PUZZLE_HEIGHT / 4);
				}
				if (puzzle.WarpIndex[0] != -1)
				{
					pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + 50.0f);
				}
				if (puzzle.WarpIndex[1] != -1)
				{

					pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - 30.0f);

				}

			}
			if (puzzle.RotNum == 3)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 4, puzzle.Position.y - PUZZLE_HEIGHT / 2 + BLOCK_W / 2);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
				pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + PUZZLE_HEIGHT / 2 - BLOCK_W / 2);
				pBlock[puzzle.blockIndex[3]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, puzzle.Position.y);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(PUZZLE_WIDHT/2, BLOCK_H);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);

				pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);
				pBlock[puzzle.blockIndex[3]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 4, puzzle.Position.y - PUZZLE_HEIGHT / 4);
				}
				if (puzzle.WarpIndex[0] != -1)
				{
					pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + 40.0f, puzzle.Position.y );
				}
				if (puzzle.WarpIndex[1] != -1)
				{

					pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x - 40.0f, puzzle.Position.y);

				}

			}
			if (puzzle.RotNum == 0)
			{
				pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, puzzle.Position.y);
				pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
				pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, puzzle.Position.y + PUZZLE_HEIGHT / 4);
				pBlock[puzzle.blockIndex[3]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);

				pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
				pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);

				pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT/2);
				pBlock[puzzle.blockIndex[3]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);

				if (puzzle.CipIndex != -1)
				{

					pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 4, puzzle.Position.y + PUZZLE_HEIGHT / 4);
				}
				if (puzzle.WarpIndex[0] != -1)
				{
					pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - 50.0f);
				}
				if (puzzle.WarpIndex[1] != -1)
				{

					pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + 30.0f);

				}

			}

		}

		break;

		case TYPE_COVER:
			if (puzzle.blockIndex[0] != -1)
			{

				if (puzzle.RotNum == 1)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 4, puzzle.Position.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 4, puzzle.Position.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);

					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(PUZZLE_WIDHT/2, BLOCK_H);
					pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);

					pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(PUZZLE_WIDHT/2, BLOCK_H);
					if (puzzle.CipIndex != -1)
					{

						pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 3, puzzle.Position.y);
					}
					if (puzzle.WarpIndex[0] != -1)
					{
						pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + 50.0f);
					}
					if (puzzle.WarpIndex[1] != -1)
					{

						pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - 40.0f);

					}
					if (puzzle.Puzzle_type == TYPE_GOAL)
					{

						if (pGoal->UseFlag)
						{
							pGoal->Pos = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 3, puzzle.Position.y);
						}

					}

				}

				if (puzzle.RotNum == 2)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, puzzle.Position.y - PUZZLE_HEIGHT / 4);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, puzzle.Position.y - PUZZLE_HEIGHT / 4);

					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT / 2);
					pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);

					pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT / 2);

					if (puzzle.CipIndex != -1)
					{

						pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - PUZZLE_HEIGHT / 3);
					}
					if (puzzle.WarpIndex[0] != -1)
					{
						pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - 30.0f);
					}
					if (puzzle.WarpIndex[1] != -1)
					{

						pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + 50.0f);

					}
					if (puzzle.Puzzle_type == TYPE_GOAL)
					{

						if (pGoal->UseFlag)
						{
							pGoal->Pos = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - PUZZLE_HEIGHT / 3);
						}

					}


				}
				if (puzzle.RotNum == 3)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 4, puzzle.Position.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 4, puzzle.Position.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);

					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(PUZZLE_WIDHT/2, BLOCK_H);
					pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);

					pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(PUZZLE_WIDHT/2, BLOCK_H);
					if (puzzle.CipIndex != -1)
					{

						pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 3, puzzle.Position.y);
					}
					if (puzzle.WarpIndex[0] != -1)
					{
						pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + 50.0f);
					}
					if (puzzle.WarpIndex[1] != -1)
					{

						pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - 40.0f);

					}
					if (puzzle.Puzzle_type == TYPE_GOAL)
					{

						if (pGoal->UseFlag)
						{
							pGoal->Pos = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 3, puzzle.Position.y);
						}

					}

				}
				if (puzzle.RotNum == 0)
				{
					pBlock[puzzle.blockIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, puzzle.Position.y+PUZZLE_HEIGHT/4);
					pBlock[puzzle.blockIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y);
					pBlock[puzzle.blockIndex[2]].Position = D3DXVECTOR2(puzzle.Position.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, puzzle.Position.y + PUZZLE_HEIGHT / 4);

					pBlock[puzzle.blockIndex[0]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT/2);
					pBlock[puzzle.blockIndex[1]].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);

					pBlock[puzzle.blockIndex[2]].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT/2);

					if (puzzle.CipIndex != -1)
					{

						pPuzzleCip[puzzle.CipIndex].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + PUZZLE_HEIGHT / 3);
					}
					if (puzzle.WarpIndex[0] != -1)
					{
						pWarp[puzzle.WarpIndex[0]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y - 30.0f);
					}
					if (puzzle.WarpIndex[1] != -1)
					{

						pWarp[puzzle.WarpIndex[1]].Position = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + 50.0f);

					}
					if (puzzle.Puzzle_type == TYPE_GOAL)
					{

						if (pGoal->UseFlag)
						{
							pGoal->Pos = D3DXVECTOR2(puzzle.Position.x, puzzle.Position.y + PUZZLE_HEIGHT / 3);
						}

					}


				}

			}

			break;
	case TYPE_NUM:
		break;

	default:
		break;
	}

}

