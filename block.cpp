#include "block.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "puzzle.h"
#include "broken.h"
#include "puzzlecip.h"
#include "warp.h"
#include "MapChip.h"

BLOCK g_ThornBlock[BLOCK_MAX];
//----------マップチップ用ブロック配列の追加----------
// 22/11/11
//----------------------------------------------------
BLOCK g_ChipBlock[BLOCK_CHIP_MAX];

static ID3D11ShaderResourceView	*g_textureBlock;	//画像一枚で一つの変数が必要
static char *g_textureName_Block = (char*)"data\\texture\\RED.jpg";	//テクスチャファイルパス


HRESULT InitBlock()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_ThornBlock[i].texno = LoadTexture(g_textureName_Block);

		g_ThornBlock[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_ThornBlock[i].Size = D3DXVECTOR2(BLOCK_W, BLOCK_H);
		g_ThornBlock[i].Rotation = 0.0f;
		g_ThornBlock[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ThornBlock[i].UseFlag = false;

	}

	//SetBlock(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(BLOCK_W, BLOCK_H));

		//----------マップチップ用ブロックの初期化----------
	for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
		g_ChipBlock[i].texno = LoadTexture(g_textureName_Block);

		g_ChipBlock[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_ChipBlock[i].Size = D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE);
		g_ChipBlock[i].Rotation = 0.0f;
		g_ChipBlock[i].PieceIndex = -1;
		g_ChipBlock[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ChipBlock[i].UseFlag = false;

	}


	return S_OK;
}

void UninitBlock()
{
	if (g_textureBlock)
	{
		g_textureBlock->Release();
		g_textureBlock = NULL;
	}

}

void UpdateBlock(){}

void DrawBlock()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_ThornBlock[i].UseFlag)
		{

			SetWorldViewProjection2D();


			//四角形の描画
			//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.8f, 0.8f, 0.5f);
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ThornBlock[i].texno));

			SpriteDrawColorRotation(g_ThornBlock[i].Position.x, g_ThornBlock[i].Position.y,
				g_ThornBlock[i].Size.x, g_ThornBlock[i].Size.y, g_ThornBlock[i].Rotation, g_ThornBlock[i].Col,
				0, 1.0f, 1.0f, 1);
		}
	}
	//----------マップチップ用のブロックの描画----------
	for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
		if (g_ChipBlock[i].UseFlag)
		{
			SetWorldViewProjection2D();
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ChipBlock[i].texno));

			SpriteDrawColorRotation(g_ChipBlock[i].Position.x, g_ChipBlock[i].Position.y,
				g_ChipBlock[i].Size.x, g_ChipBlock[i].Size.y, g_ChipBlock[i].Rotation, g_ChipBlock[i].Col,
				0, 1.0f, 1.0f, 1);
		}
	}
}

//----------マップチップ用ブロックのセッターとゲッター----------
void SetBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index) {
	for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
		if (!g_ChipBlock[i].UseFlag) {
			g_ChipBlock[i].Position = pos;
			g_ChipBlock[i].Size = size;
			g_ChipBlock[i].PieceIndex = index;

			g_ChipBlock[i].UseFlag = true;
			
			break;
		}
	}
}
BLOCK* GetChipBlock() {
	return g_ChipBlock;
}

void deleteBlock(int index){
	for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
		if (g_ChipBlock[i].UseFlag){
			if (g_ChipBlock[i].PieceIndex == index){
				g_ChipBlock[i].UseFlag = false;
			}
		}
	}
}

void SetBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, GRAND_TYPE type, BLOCK_TYPE btype, int pIndex, CIP_TYPE ctype)
{
	PUZZLE* pPuzzle = GetPuzzle();

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (!g_ThornBlock[i].UseFlag)
		{

			if (btype != TYPE_NUM)
			{
				switch (btype)
				{
				case TYPE_GRAND:
					(pPuzzle + pIndex)->CipIndex = SetPuzzleCip(pos, D3DXVECTOR2(CIP_SIZE_X, CIP_SIZE_Y),ctype);
					switch (type)
					{
					case GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 0;

						break;
					case GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation =0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					default:
						break;
					}

					break;

				case TYPE_HARFGRAND:
					switch (type)
					{
					case GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 0;
						break;
					case GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case TYPE_CENTER:
					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = size / 2;
					(pPuzzle + pIndex)->blockIndex[0] = i;

					break;
				case TYPE_T:
					switch (type)
					{
					case GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 90.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						/*g_block[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, pos.y);
						g_block[i + 2].Rotation = 90.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;*/

						(pPuzzle + pIndex)->RotNum = 0;

						break;
					case GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 0.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;


					/*	g_block[i + 2].Position = D3DXVECTOR2(pos.x, pos.y+ PUZZLE_HEIGHT / 2 - BLOCK_H / 2);
						g_block[i + 2].Rotation = 0.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;*/
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 90.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						/*g_block[i + 2].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, pos.y);
						g_block[i + 2].Rotation = 90.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;*/
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;
						

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 0.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						/*g_block[i + 2].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + BLOCK_H / 2);
						g_block[i + 2].Rotation = 00.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;*/
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case TYPE_SQUARE:

					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2+SQUAER_W/2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = D3DXVECTOR2(SQUAER_W,SQUAER_H);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_ThornBlock[i + 1].Rotation = 0.0f;
					g_ThornBlock[i+1].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;

					g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_ThornBlock[i + 2].Rotation = 0.0f;
					g_ThornBlock[i+2].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 2].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[2] = i + 2;

					g_ThornBlock[i + 3].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_ThornBlock[i + 3].Rotation = 0.0f;
					g_ThornBlock[i+3].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 3].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[3] = i + 3;

					break;
				case TYPE_ZYUUZI:


					(pPuzzle + pIndex)->CipIndex = SetPuzzleCip(D3DXVECTOR2(pos.x-PUZZLE_WIDHT/3,pos.y-PUZZLE_HEIGHT/3), D3DXVECTOR2(CIP_SIZE_X, CIP_SIZE_Y), ctype);

					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT-20.0f);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i + 1].Rotation = 0.0f;
					g_ThornBlock[i + 1].Size = D3DXVECTOR2(PUZZLE_WIDHT-20.0f, BLOCK_H);
					g_ThornBlock[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;


					break;
				case TYPE_TATE:
					(pPuzzle + pIndex)->CipIndex = SetPuzzleCip(D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 3, pos.y + PUZZLE_HEIGHT / 3), D3DXVECTOR2(CIP_SIZE_X, CIP_SIZE_Y), ctype);

					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x+PUZZLE_WIDHT/2, pos.y);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i + 1].Rotation = 0.0f;
					g_ThornBlock[i + 1].Size = D3DXVECTOR2(PUZZLE_WIDHT/2, PUZZLE_HEIGHT - 60.0f);
					g_ThornBlock[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;

					break;
				case TYPE_BOX:
					(pPuzzle + pIndex)->WarpIndex[0] = SetWarp(D3DXVECTOR2(pos.x, pos.y - 50.0f), D3DXVECTOR2(20.0f, 20.0f));
					(pPuzzle + pIndex)->WarpIndex[1] = SetWarp(D3DXVECTOR2(pos.x, pos.y + 30.0f), D3DXVECTOR2(20.0f, 20.0f));
					(pPuzzle + pIndex)->CipIndex = SetPuzzleCip(D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 3), D3DXVECTOR2(CIP_SIZE_X, CIP_SIZE_Y), ctype);

					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, pos.y );
					g_ThornBlock[i + 1].Rotation = 0.0f;
					g_ThornBlock[i + 1].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT);
					g_ThornBlock[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;

					g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - BLOCK_H / 2);
					g_ThornBlock[i + 2].Rotation = 0.0f;
					g_ThornBlock[i + 2].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);
					g_ThornBlock[i + 2].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[2] = i + 2;

					g_ThornBlock[i + 3].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, pos.y + PUZZLE_HEIGHT / 4);
					g_ThornBlock[i + 3].Rotation = 0.0f;
					g_ThornBlock[i + 3].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT/2);
					g_ThornBlock[i + 3].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[3] = i + 3;

					break;
				case TYPE_COVER:

					(pPuzzle + pIndex)->CipIndex = SetPuzzleCip(D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 3), D3DXVECTOR2(CIP_SIZE_X, CIP_SIZE_Y), ctype);


					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = D3DXVECTOR2(PUZZLE_WIDHT, BLOCK_H);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - BLOCK_W / 2, pos.y+ PUZZLE_HEIGHT/4);
					g_ThornBlock[i + 1].Rotation = 0.0f;
					g_ThornBlock[i + 1].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT/2);
					g_ThornBlock[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;



					g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + BLOCK_W / 2, pos.y + PUZZLE_HEIGHT /4);
					g_ThornBlock[i + 2].Rotation = 0.0f;
					g_ThornBlock[i + 2].Size = D3DXVECTOR2(BLOCK_W, PUZZLE_HEIGHT/2);
					g_ThornBlock[i + 2].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[2] = i + 2;


					break;
				}
			}

			g_ThornBlock[i].UseFlag = true;
			break;

		}
	}

}

BLOCK * GetBlock()
{
	return &g_ThornBlock[0];
}
