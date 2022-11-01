#include "puzzlecip.h"
#include "puzzle.h"
#include"texture.h"
#include"sprite.h"
#include"input.h"
#include"goal.h"
#include"player.h"
//#include"block.h"
#include"mouse.h"

PUZZLE_CIP	g_PuzzleCip[CIP_MAX];
static ID3D11ShaderResourceView	*g_texturePuzzleCip;	//画像一枚で一つの変数が必要
static char *g_textureName_PuzzleCip = (char*)"data\\texture\\blue.png";	//テクスチャファイルパス


void SetPuzzleCipCreate(CREATE_CIP_TYPE ctype,int u, int r, int d, int l, bool gflag);
void CreatePuzzle(int i);
int a = 0;
int b = 0;
HRESULT InitPuzzleCip()
{
	 a = 0;
	 b = 0;
	for (int i = 0; i < CIP_MAX; i++)
	{
		g_PuzzleCip[i].texno = LoadTexture(g_textureName_PuzzleCip);

		g_PuzzleCip[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_PuzzleCip[i].Size = D3DXVECTOR2(CIP_SIZE_X, CIP_SIZE_Y);
		g_PuzzleCip[i].Type = CIP_NONE;
		g_PuzzleCip[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PuzzleCip[i].Rotation = 0.0f;
		g_PuzzleCip[i].GoalFlag = false;
		g_PuzzleCip[i].UseFlag = false;
		for (int j = 0; j < 4; j++)
		{
			g_PuzzleCip[i].houkou[j] = 0;
		}
	}
	SetPuzzleCipCreate(CREATE_ZYUUZI, 0, 2, 2, 2,false);
	SetPuzzleCipCreate(CREATE_TATE, 0, 0, 1, 2, false);
	SetPuzzleCipCreate(CREATE_BOX, 1, 1, 1, 0, false);
	SetPuzzleCipCreate(CREATE_COVER, 0, 2, 1, 2, true);

	return S_OK;
}

void UninitPuzzleCip()
{
	if (g_texturePuzzleCip)
	{
		g_texturePuzzleCip->Release();
		g_texturePuzzleCip = NULL;
	}

}

void UpdatePuzzleCip()
{
	for (int i = 0; i < CIP_MAX; i++)
	{
		if (g_PuzzleCip[i].UseFlag)
		{
			PLAYER* pPlayer = GetPlayer();
			MOUSE* pMouse = GetMouse();
			PUZZLE* pPuzzle = GetPuzzle();
			if (!pMouse->UseFlag)
			{


						if (g_PuzzleCip[i].Position.x + g_PuzzleCip[i].Size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2
							&& g_PuzzleCip[i].Position.x - g_PuzzleCip[i].Size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2
							&& g_PuzzleCip[i].Position.y + g_PuzzleCip[i].Size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2
							&& g_PuzzleCip[i].Position.y - g_PuzzleCip[i].Size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2)
						{

							switch (g_PuzzleCip[i].Type)
							{
							case CIP_NOMAL:
								CreatePuzzle(i);
								//SetPuzzle(D3DXVECTOR2(0.0f + PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), STEAT_NUM, STEAT_HIKKOMI, STEAT_HIKKOMI, STEAT_HIKKOMI, GRAND_UP, TYPE_NOMAL, CIP_GOAL, TYPE_ZYUUZI,false);
								g_PuzzleCip[i].UseFlag = false;
								break;
							case CIP_GOAL:
								//	SetPuzzle(D3DXVECTOR2(800.0f, 200.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), STEAT_NUM, STEAT_HIKKOMI, STEAT_DEPPARI, STEAT_NUM, GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_GRAND,false);
								g_PuzzleCip[i].UseFlag = false;
								break;
							}
						}

			}
		}
	}
}

void DrawPuzzleCip()
{
	for (int i = 0; i < CIP_MAX; i++)
	{

		if (g_PuzzleCip[i].UseFlag)
		{
			SetWorldViewProjection2D();


			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PuzzleCip[i].texno));

			SpriteDrawColorRotation(g_PuzzleCip[i].Position.x, g_PuzzleCip[i].Position.y,
				g_PuzzleCip[i].Size.x, g_PuzzleCip[i].Size.y, g_PuzzleCip[i].Rotation, g_PuzzleCip[i].Col,
				0, 1.0f, 1.0f, 1);
		}
	}
}

int SetPuzzleCip(D3DXVECTOR2 pos, D3DXVECTOR2 size, CIP_TYPE type)
{
	for (int i = b; i < CIP_MAX; i++)
	{
		if (!g_PuzzleCip[i].UseFlag)
		{
			if (type == CIP_NONE)
			{
				return-1;
			}

			b++;
			g_PuzzleCip[i].Position = pos;
			g_PuzzleCip[i].Size = size;
			g_PuzzleCip[i].Type = type;
			g_PuzzleCip[i].UseFlag = true;
			return i;
		}
	}
}

PUZZLE_CIP * GetPuzzleCip()
{
	return &g_PuzzleCip[0];
}
//----------------------------
//パズルの値のセット
//引数：チップの作るブロックのタイプ
//		上、右、下、左の引っ込んでいるのか
//	0：何もなし、１：出っ張り、２：引っ込み
//真偽：ゴールかどうか：true.ゴール:false.ゴールじゃない
//----------------------------
void SetPuzzleCipCreate(CREATE_CIP_TYPE ctype, int u, int r, int d, int l, bool gflag)
{
	g_PuzzleCip[a].Num_type = ctype;
	g_PuzzleCip[a].houkou[0] = u;
	g_PuzzleCip[a].houkou[1] = r;
	g_PuzzleCip[a].houkou[2] = d;
	g_PuzzleCip[a].houkou[3] = l;
	g_PuzzleCip[a].GoalFlag = gflag;
	a++;

}

void CreatePuzzle(int i)
{
	PUZZLE_STEAT pst[4];

	for (int j = 0; j < 4; j++)
	{
		switch (g_PuzzleCip[i].houkou[j])
		{
		case 0:
			pst[j] = STEAT_NUM;
			break;
		case 1:
			pst[j] = STEAT_DEPPARI;

			break;
		case 2:
			pst[j] = STEAT_HIKKOMI;
			break;

		default:
			break;
		}
	}
	if (!g_PuzzleCip[i].GoalFlag)
	{


		switch (g_PuzzleCip[i].Num_type)
		{
		case	CREATE_GRAND:

			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_GRAND, false);

			break;

		case	CREATE_HARFGRAND:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_HARFGRAND, false);

			break;

		case	CREATE_CENTER:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_CENTER, false);

			break;

		case	CREATE_T:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_T, false);

			break;

		case	CREATE_SQUARE:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_SQUARE, false);

			break;

		case	CREATE_ZYUUZI:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_ZYUUZI, false);

			break;
		case	CREATE_TATE:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_TATE, false);
			break;

		case	CREATE_BOX:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH- PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_BOX, false);

			break;
		case CREATE_COVER:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH- PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_NOMAL, CIP_NOMAL, TYPE_COVER, false);

			break;
		case	CREATE_GOAL:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH- PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_GRAND, false);

			break;

		case	CREATE_NUM:
			break;


		default:
			break;
		}
	}
	if (g_PuzzleCip[i].GoalFlag)
	{


		switch (g_PuzzleCip[i].Num_type)
		{
		case	CREATE_GRAND:

			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH -PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_GRAND, false);

			break;

		case	CREATE_HARFGRAND:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_HARFGRAND, false);

			break;

		case	CREATE_CENTER:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_CENTER, false);

			break;

		case	CREATE_T:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_T, false);

			break;

		case	CREATE_SQUARE:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_SQUARE, false);

			break;

		case	CREATE_ZYUUZI:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_ZYUUZI, false);

			break;
		case	CREATE_TATE:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_TATE, false);
			break;

		case	CREATE_BOX:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_BOX, false);

			break;
		case CREATE_COVER:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_COVER, false);

			break;

		case	CREATE_GOAL:
			SetPuzzle(D3DXVECTOR2(SCREEN_WIDTH - PUZZLE_WIDHT / 2, 500.0f), D3DXVECTOR2(PUZZLE_WIDHT, PUZZLE_HEIGHT), pst[0], pst[1], pst[2], pst[3], GRAND_DOWN, TYPE_GOAL, CIP_NONE, TYPE_GRAND, false);

			break;

		case	CREATE_NUM:
			break;


		default:
			break;
		}
	}

}
