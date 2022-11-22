#include "thorn_block.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "puzzle.h"
#include "broken.h"

THORN_BLOCK g_block[THORN_BLOCK_MAX];
static ID3D11ShaderResourceView	*g_textureThornBlock;	//画像一枚で一つの変数が必要
static char *g_textureName_ThornBlock = (char*)"data\\texture\\RED.jpg";	//テクスチャファイルパス

HRESULT InitThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		g_block[i].texno = LoadTexture(g_textureName_ThornBlock);

		g_block[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_block[i].Size = D3DXVECTOR2(THORN_BLOCK_W, THORN_BLOCK_H);
		g_block[i].Rotation = 0.0f;
		g_block[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_block[i].UseFlag = false;

	}

	//SetBlock(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(BLOCK_W, BLOCK_H));

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
}

void DrawThornBlock()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_block[i].UseFlag)
		{

			SetWorldViewProjection2D();


			//四角形の描画
			//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.8f, 0.8f, 0.5f);
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_block[i].texno));

			SpriteDrawColorRotation(g_block[i].Position.x, g_block[i].Position.y,
				g_block[i].Size.x, g_block[i].Size.y, g_block[i].Rotation, g_block[i].Col,
				0, 1.0f, 1.0f, 1);
		}
	}

}

void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, THORN_GRAND_TYPE type, THORN_BLOCK_TYPE btype, int pIndex)
{
	PUZZLE* pPuzzle = GetPuzzle();

	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		if (!g_block[i].UseFlag)
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
						g_block[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_block[i].Rotation = 0.0f;
						g_block[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						break;
					case THORN_GRAND_LEFT:
						g_block[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_block[i].Rotation = 90.0f;
						g_block[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;
					case THORN_GRAND_UP:
						g_block[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_block[i].Rotation = 180.0f;
						g_block[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;
					case THORN_GRAND_RIGHT:
						g_block[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_block[i].Rotation = 270.0f;
						g_block[i].Size = size;
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
						g_block[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_block[i].Rotation = 0.0f;
						g_block[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 0;
						break;
					case THORN_GRAND_LEFT:
						g_block[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_block[i].Rotation = 0.0f;
						g_block[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case THORN_GRAND_UP:
						g_block[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_block[i].Rotation = 0.0f;
						g_block[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case THORN_GRAND_RIGHT:
						g_block[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_block[i].Rotation = 0.0f;
						g_block[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case THORN_TYPE_CENTER:
					g_block[i].Position = D3DXVECTOR2(pos.x, pos.y);
					g_block[i].Rotation = 0.0f;
					g_block[i].Size = size / 2;
					(pPuzzle + pIndex)->blockIndex[0] = i;

					break;
				case THORN_TYPE_T:
					switch (type)
					{
					case THORN_GRAND_DOWN:
						g_block[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_block[i].Rotation = 0.0f;
						g_block[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						g_block[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_block[i + 1].Rotation = 90.0f;
						g_block[i + 1].Size = size;
						g_block[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_block[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_block[i + 2].Rotation = 90.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;

						(pPuzzle + pIndex)->RotNum = 0;

						break;
					case THORN_GRAND_LEFT:
						g_block[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_block[i].Rotation = 90.0f;
						g_block[i].Size = size;

						g_block[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_block[i + 1].Rotation = 0.0f;
						g_block[i + 1].Size = size;
						g_block[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;


						g_block[i + 2].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_block[i + 2].Rotation = 0.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case THORN_GRAND_UP:
						g_block[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_block[i].Rotation = 0.0f;
						g_block[i].Size = size;

						g_block[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_block[i + 1].Rotation = 90.0f;
						g_block[i + 1].Size = size;
						g_block[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_block[i + 2].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_block[i + 2].Rotation = 90.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case THORN_GRAND_RIGHT:
						g_block[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_block[i].Rotation = 90.0f;
						g_block[i].Size = size;


						g_block[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_block[i + 1].Rotation = 0.0f;
						g_block[i + 1].Size = size;
						g_block[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_block[i + 2].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_block[i + 2].Rotation = 00.0f;
						g_block[i + 2].Size = size;
						g_block[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case THORN_TYPE_SQUARE:

					g_block[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_block[i].Rotation = 0.0f;
					g_block[i].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_block[i + 1].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_block[i + 1].Rotation = 0.0f;
					g_block[i + 1].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_block[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;

					g_block[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_block[i + 2].Rotation = 0.0f;
					g_block[i + 2].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_block[i + 2].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[2] = i + 2;

					g_block[i + 3].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_block[i + 3].Rotation = 0.0f;
					g_block[i + 3].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_block[i + 3].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[3] = i + 3;

					break;

				}
			}

			g_block[i].UseFlag = true;
			break;

		}
	}

}

THORN_BLOCK* GetThornBlock()
{
	return &g_block[0];
}
