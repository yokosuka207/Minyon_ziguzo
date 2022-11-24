#include "puzzlecip.h"
#include "puzzle.h"
#include"texture.h"
#include"sprite.h"
#include"input.h"
#include"goal.h"
#include"player.h"
//#include"block.h"
#include"mouse.h"
#include "MapChip.h"
#include "SplitStage.h"


PUZZLE_CIP	g_PuzzleCip[CIP_MAX];
//----------マップチップ用配列----------
// 22/11/02
//--------------------------------------
PUZZLE_CIP g_ChipPuzzleChip[BLOCK_CHIP_MAX];

static ID3D11ShaderResourceView	*g_texturePuzzleCip;	//画像一枚で一つの変数が必要
static char *g_textureName_PuzzleCip = (char*)"data\\texture\\blue.png";	//テクスチャファイルパス


void SetPuzzleCipCreate(CREATE_CIP_TYPE ctype,int u, int r, int d, int l, bool gflag);
void CreatePuzzle(int i);
HRESULT InitPuzzleCip()
{
	//マップチップ用初期化
	for (int i = 0; i < PUZZLE_MAX; i++) {
		g_PuzzleCip[i].texno = LoadTexture(g_textureName_PuzzleCip);

		g_ChipPuzzleChip[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_ChipPuzzleChip[i].Size = D3DXVECTOR2(CIP_SIZE_X, CIP_SIZE_Y);
		g_ChipPuzzleChip[i].Type = CIP_NONE;
		g_ChipPuzzleChip[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ChipPuzzleChip[i].Rotation = 0.0f;
		g_ChipPuzzleChip[i].NextPieceIndex = -1;
		g_ChipPuzzleChip[i].GoalFlag = false;
		g_ChipPuzzleChip[i].UseFlag = false;
	}

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
		if (g_ChipPuzzleChip[i].UseFlag)
		{
			SplitStage* pSplitStage = GetSplitStage();

			PLAYER* pPlayer = GetPlayer();
			MOUSE* pMouse = GetMouse();
			PUZZLE* pPuzzle = GetPuzzle();
			if (!pMouse->UseFlag)
			{


						if (g_ChipPuzzleChip[i].Position.x + g_ChipPuzzleChip[i].Size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2
							&& g_ChipPuzzleChip[i].Position.x - g_ChipPuzzleChip[i].Size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2
							&& g_ChipPuzzleChip[i].Position.y + g_ChipPuzzleChip[i].Size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2
							&& g_ChipPuzzleChip[i].Position.y - g_ChipPuzzleChip[i].Size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2)
						{
							SetPieceMapChip(pSplitStage->Split3[2][2], g_ChipPuzzleChip[i].NextPieceIndex);

							g_ChipPuzzleChip[i].UseFlag = false;
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
	//マップチップ描写
	for (int i = 0; i < PUZZLE_MAX; i++) {
		if (g_ChipPuzzleChip[i].UseFlag) {
			SetWorldViewProjection2D();

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ChipPuzzleChip[i].texno));

			SpriteDrawColorRotation(g_ChipPuzzleChip[i].Position.x, g_ChipPuzzleChip[i].Position.y,
				g_ChipPuzzleChip[i].Size.x, g_ChipPuzzleChip[i].Size.y, g_ChipPuzzleChip[i].Rotation, g_ChipPuzzleChip[i].Col,
				0, 1.0f, 1.0f, 1);
		}
	}

}
void SetChipPuzzuleChip(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index) {
	for (int i = 0; i < PUZZLE_MAX; i++) {
		if (!g_ChipPuzzleChip[i].UseFlag) {
			g_ChipPuzzleChip[i].Position = pos;
			g_ChipPuzzleChip[i].Size = size;
			g_ChipPuzzleChip->UseFlag = true;
			break;
		}
	}
}


int SetPuzzleCip(D3DXVECTOR2 pos, D3DXVECTOR2 size, CIP_TYPE type)
{
	for (int i = 0; i < CIP_MAX; i++)
	{
		if (!g_PuzzleCip[i].UseFlag)
		{
			if (type == CIP_NONE)
			{
				return-1;
			}

		//	b++;
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
	//g_PuzzleCip[a].Num_type = ctype;
	//g_PuzzleCip[a].houkou[0] = u;
	//g_PuzzleCip[a].houkou[1] = r;
	//g_PuzzleCip[a].houkou[2] = d;
	//g_PuzzleCip[a].houkou[3] = l;
	//g_PuzzleCip[a].GoalFlag = gflag;
	//a++;

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
