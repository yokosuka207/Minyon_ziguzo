#include "collision.h"
#include"main.h"

#include"player.h"
#include<math.h>
/*==============================================================================

   当たり判定管理 [collsion.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

//==================================
//プロトタイプ宣言
//=================================




DIRECSION Direcsion =NUM;
//===============================
//当たり判定処理
//当たり判定を一気に行う
//================================
void UpdateCollision()
{
	//プレーヤー　対　敵キャラ	四角

	//などの必要な判定をここで作る
}
//---------------------------------
//パズルの当たり判定
//くっつくけるかどうか
//---------------------------------
void PuzzleCollision()
{
	PUZZLE* pPuzzle = GetPuzzle();
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{
			if (pPuzzle[i].MoveEndFlag)
			{
				pPuzzle[i].MoveEndFlag = false;

				for (int j = 0; j < PUZZLE_MAX; j++)
				{
					if (j != i)
					{

						bool hitFlag = CollisionBB(pPuzzle[i].Position, pPuzzle[j].Position, pPuzzle[i].Size,D3DXVECTOR2(pPuzzle[j].Size.x,pPuzzle[j].Size.y));

						if (hitFlag)
						{

							float x = pPuzzle[i].Position.x - pPuzzle[j].Position.x;
							float y = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							x = fabsf(x);
							y = fabsf(y);
							//x = x / 1.5f;

							if (x >= y)
							{
								//動かしているパズルが右にあったら
								if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
								{

									if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);

										if (hitFlag)
										{
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_WIDHT, pPuzzle[j].Position.y);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}
								}
								//動かしているパズルが左にあったら
								if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
								{

									if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);

										if (hitFlag) {
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_WIDHT, pPuzzle[j].Position.y);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}
							else if (y > x)
							{
								//動かしているパズルが上にあったら

								if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
								{

									if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

										if (hitFlag)
										{
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_HEIGHT);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;
											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}
								//動かしているパズルが下にあったら
								if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
								{

									if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

										if (hitFlag)
										{
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_HEIGHT);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}


							//hitFlag = CollisionBB(pPuzzle[i].Position,D3DXVECTOR2( pPuzzle[j].Position.x
							//	pPuzzle[i].Size, pPuzzle[j].Size);
						}
						else
						{
						float x = (pPuzzle[i].Position.x) - pPuzzle[j].Position.x;
						float y = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

						float	abx = fabsf(x);
						float	aby = fabsf(y);

						if ((abx < 20.0f && aby < 200.0f)|| (abx < 200.0f && aby < 20.0f))
						{


							if (abx >= aby)
							{
								//動かしているパズルが右にあったら
								if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
								{

									if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);

										if (hitFlag)
										{
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_WIDHT, pPuzzle[j].Position.y);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}
								}
								//動かしているパズルが左にあったら
								if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
								{

									if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);

										if (hitFlag) {
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_WIDHT, pPuzzle[j].Position.y);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}
							else if (aby > abx)
							{
								//動かしているパズルが上にあったら

								if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
								{

									if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

										if (hitFlag)
										{
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_HEIGHT);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;
											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}
								//動かしているパズルが下にあったら
								if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
								{

									if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

										if (hitFlag)
										{
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_HEIGHT);
											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}

						}

					 }
					}
				}
			}
		}

	}


}
//===========================================
//四角形同士が当たっているかあたっていないかを判定するだけ
//引数: 中央座標１、中央座標２、サイズ１、サイズ２
//戻り値： true当たっている:false当っていない
//================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2	min1, min2;	//四角形の最小座標（左上）
	D3DXVECTOR2 max1, max2;	//四角形の最大座標(右下)

	//四角形１左上
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	//四角形１右下
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;
	//四角形２左上
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	//四角形２右下
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//衝突判定
	if (max1.x < min2.x)//判定1
	{		return false;	}

	if (max2.x < min1.x)//判定2
	{		return false;	}
	if (max1.y < min2.y)//判定3
	{		return false;	}
	if (max2.y < min1.y)//判定4
	{		return false;	}

	return true;

}
//=================================================
//円同士が当たっているかあたっていないかを判定するだけ
//引数: 中央座標１、中央座標２、半径１、半径２
//戻り値： true当たっている:false当っていない
//================================================
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	D3DXVECTOR2 vDisitance = pos1 - pos2;

	float Lenght;
	Lenght = D3DXVec2LengthSq(&vDisitance);	//ルートを使わない版
	//Length = D3DXVec2Length(&vDisitance);	//ルートを使う版(正確な長さ)

	//半径の総和

	float size = (size1 + size2) * (size1 + size2);
	//float size = (size1+size2);	ルート版

	//衝突判定
	if (size > Lenght)
	{
		return	true;
	}

	return false;
}
//--------------------------------------------
//パズルの移動先が空いているか
//引数：元のパズル、移動したいパズルの添え字、移動したい場所
//----------------------------------------------
bool PuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion)
{
	PUZZLE* pPuzzle = GetPuzzle();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					//if (puzzle.Position.y - PUZZLE_HEIGHT == pPuzzle[i].Position.y)return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT - PUZZLE_HEIGHT / 3 < pPuzzle[i].Position.y&&
						puzzle.Position.y - PUZZLE_HEIGHT + PUZZLE_HEIGHT / 3 > pPuzzle[i].Position.y&&
						puzzle.Position.x - PUZZLE_WIDHT / 3 > pPuzzle[i].Position.x&&
						puzzle.Position.x + PUZZLE_WIDHT / 3 < pPuzzle[i].Position.x)
					{
						return false;
					}

					break;
				case DOWN:
					//if (puzzle.Position.y + PUZZLE_HEIGHT == pPuzzle[i].Position.y)	return false;

					if (puzzle.Position.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 3 < pPuzzle[i].Position.y&&
						puzzle.Position.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 3 > pPuzzle[i].Position.y&&
						puzzle.Position.x - PUZZLE_WIDHT / 3 < pPuzzle[i].Position.x&&
						puzzle.Position.x + PUZZLE_WIDHT / 3 > pPuzzle[i].Position.x)
					{
						return false;
					}

					break;
				case LEFT:
					//if (puzzle.Position.x - PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT / 3 < pPuzzle[i].Position.y&&
						puzzle.Position.y + PUZZLE_HEIGHT / 3 > pPuzzle[i].Position.y&&
						puzzle.Position.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 3 < pPuzzle[i].Position.x&&
						puzzle.Position.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 3 > pPuzzle[i].Position.x)
					{
						return false;
					}

					break;
				case RIGHT:
					//if (puzzle.Position.x + PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT / 3 < pPuzzle[i].Position.y&&
						puzzle.Position.y + PUZZLE_HEIGHT / 3 > pPuzzle[i].Position.y&&
						puzzle.Position.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 3 < pPuzzle[i].Position.x&&
						puzzle.Position.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 3> pPuzzle[i].Position.x)
					{
						return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//プレイヤーの移動先にパズルがあるか
//引数：元のパズル、移動したいパズルの添え字、移動したい場所
//----------------------------------------------
bool PlayerPuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion)
{
	PUZZLE* pPuzzle = GetPuzzle();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					if (puzzle.Position.y - PUZZLE_HEIGHT == pPuzzle[i].Position.y)return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y&&
						puzzle.Position.y - PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y&&
						puzzle.Position.x - PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x&&
						puzzle.Position.x + PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x)
					{
						return false;
					}

					break;
				case DOWN:
					if (puzzle.Position.y + PUZZLE_HEIGHT == pPuzzle[i].Position.y)	return false;

					if (puzzle.Position.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y&&
						puzzle.Position.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y&&
						puzzle.Position.x - PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x&&
						puzzle.Position.x + PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x)
					{
						return false;
					}

					break;
				case LEFT:
					if (puzzle.Position.x - PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y&&
						puzzle.Position.y + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y&&
						puzzle.Position.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x&&
						puzzle.Position.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x)
					{
						return false;
					}

					break;
				case RIGHT:
					if (puzzle.Position.x + PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y&&
						puzzle.Position.y + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y&&
						puzzle.Position.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x&&
						puzzle.Position.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x)
					{
						return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
