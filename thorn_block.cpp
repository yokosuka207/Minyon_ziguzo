#include "thorn_block.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "puzzle.h"
#include "broken.h"
#include "collision.h"
#include "player.h"
#include "game.h"

THORN_BLOCK g_ThornBlock[THORN_BLOCK_MAX];
static ID3D11ShaderResourceView	*g_textureThornBlock;	//画像一枚で一つの変数が必要
static char *g_textureName_ThornBlock = (char*)"data\\texture\\thorn_block.png";	//テクスチャファイルパス

HRESULT InitThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		g_ThornBlock[i].texno = LoadTexture(g_textureName_ThornBlock);

		g_ThornBlock[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_ThornBlock[i].Size = D3DXVECTOR2(THORN_BLOCK_W, THORN_BLOCK_H);
		g_ThornBlock[i].Rotation = 0.0f;
		g_ThornBlock[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ThornBlock[i].PieceNo = -1;
		g_ThornBlock[i].UseFlag = false;

	}

	return S_OK;
}

void UninitThornBlock()
{
	if (g_textureThornBlock)
	{
		g_textureThornBlock->Release();
		g_textureThornBlock = NULL;
	}
}

void UpdateThornBlock()
{
	PLAYER* pPlayer = GetPlayer();
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (CollisionBB(pPlayer->Position, g_ThornBlock[i].Position, pPlayer->size, g_ThornBlock[i].Size)) {
			ResetGame();
		}
	}
}

void DrawThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++){
		if (g_ThornBlock[i].UseFlag){
			SetWorldViewProjection2D();

			//四角形の描画
			//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.8f, 0.8f, 0.5f);
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ThornBlock[i].texno));

			SpriteDrawColorRotation(g_ThornBlock[i].Position.x, g_ThornBlock[i].Position.y,
				g_ThornBlock[i].Size.x, g_ThornBlock[i].Size.y, g_ThornBlock[i].Rotation, g_ThornBlock[i].Col,
				0, 1.0f, 1.0f, 1);
		}
	}

}

void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (!g_ThornBlock[i].UseFlag) {
			g_ThornBlock[i].Position = pos;
			g_ThornBlock[i].Size = size;
			g_ThornBlock[i].PieceNo = PieceNo;
			g_ThornBlock[i].UseFlag = true;
			break;
		}
	}
}


void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, THORN_GRAND_TYPE type, THORN_BLOCK_TYPE btype, int pIndex)
{
	PUZZLE* pPuzzle = GetPuzzle();

	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		if (!g_ThornBlock[i].UseFlag)
		{
			if (btype != THORN_TYPE_NUM)
			{
				switch (btype)
				{
				case THORN_TYPE_GRAND:
					(pPuzzle + pIndex)->BrokenIndex = SetBroken(pos, D3DXVECTOR2(BROKEN_SIZE_W, BROKEN_SIZE_H));
					switch (type)
					{
					case THORN_GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						break;
					case THORN_GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;
					case THORN_GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 180.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;
					case THORN_GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 270.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;

					default:
						break;
					}

					break;

				case THORN_TYPE_HARFGRAND:
					switch (type)
					{
					case THORN_GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 0;
						break;
					case THORN_GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case THORN_GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case THORN_GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case THORN_TYPE_CENTER:
					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = size / 2;
					(pPuzzle + pIndex)->blockIndex[0] = i;

					break;
				case THORN_TYPE_T:
					switch (type)
					{
					case THORN_GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 90.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i + 2].Rotation = 90.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;

						(pPuzzle + pIndex)->RotNum = 0;

						break;
					case THORN_GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 0.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;


						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i + 2].Rotation = 0.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case THORN_GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 90.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i + 2].Rotation = 90.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case THORN_GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;


						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 0.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i + 2].Rotation = 00.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case THORN_TYPE_SQUARE:

					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_ThornBlock[i + 1].Rotation = 0.0f;
					g_ThornBlock[i + 1].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;

					g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_ThornBlock[i + 2].Rotation = 0.0f;
					g_ThornBlock[i + 2].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 2].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[2] = i + 2;

					g_ThornBlock[i + 3].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_ThornBlock[i + 3].Rotation = 0.0f;
					g_ThornBlock[i + 3].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 3].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[3] = i + 3;

					break;

				}
			}

			g_ThornBlock[i].UseFlag = true;
			break;

		}
	}

}

THORN_BLOCK* GetThornBlock()
{
	return &g_ThornBlock[0];
}
