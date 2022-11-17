#include "collision.h"
#include"main.h"

#include"player.h"
#include<math.h>
#include"mouse.h"
#include"block.h"
#include"MapChip.h"
#include"joint.h"
/*==============================================================================

   当たり判定管理 [collsion.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

//==================================
//プロトタイプ宣言
//=================================




int punum = 0;	//パズルの配列の添え字の格納


DIRECSION Direcsion = NUM;	//方向の確認
//===============================
//当たり判定処理
//当たり判定を一気に行う
//================================
void UpdateCollision()
{
	//プレーヤー　対　敵キャラ	四角



	//などの必要な判定をここで作る
}
void PieceCollision()
{
	Piece* pPiece = GetPiece();
	JOINT* pJoint = GetJoint();
	bool colFlag = false;//当たって入ったか

	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (pPiece[i].MoveEndFlag)	//動き終わったら
			{
				pPiece[i].MoveEndFlag = false;

				for (int j = 0; j < JOINT_MAX; j++)
				{
					if (pJoint[j].pieNo == i)	//動き終わったピースの中にあったら
					{
						for (int k = 0; k < JOINT_MAX; k++)
						{
							if (pJoint[j].pieNo != pJoint[k].pieNo)//ピース番号が違ったら
							{
								//ジョイントが重なっていたら
								colFlag = CollisionBB(pJoint[j].pos, pJoint[k].pos, pJoint[j].size, pJoint[k].size);

								if (colFlag)
								{
									//凹凸が合っていたら
									if (pJoint[j].type == JOINT_TYPE::TYPE_BUMP&&pJoint[k].type == JOINT_TYPE::TYPE_DIP||
										pJoint[k].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP)
									{
										//ジョイントが右だったら
										if (pPiece[i].pos.x+pPiece[i].size.x/3 < pJoint[j].pos.x)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].pieNo].pos.y)-pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].pieNo].pos.y);

											PositionPlas(temp, i);

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

//---------------------------------
//パズルの当たり判定
//くっつくけるかどうか
//---------------------------------
void PuzzleCollision()
{
	punum = -1;
	bool colFlag = false;//当たって入ったか
	bool pFlag = false;
	PUZZLE* pPuzzle = GetPuzzle();
	PLAYER* pPlayer = GetPlayer();

	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{

			if (pPuzzle[i].MoveEndFlag)
			{
				for (int j = 0; j < PUZZLE_MAX; j++)
				{
					pPuzzle[j].OneOldPosition = pPuzzle[j].Position;

				}

				pPuzzle[i].MoveEndFlag = false;

				if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 2 < pPlayer->Position.y &&
					pPuzzle[i].Position.y + pPuzzle[i].Size.y / 2 > pPlayer->Position.y &&
					pPuzzle[i].Position.x - pPuzzle[i].Size.x / 2 < pPlayer->Position.x &&
					pPuzzle[i].Position.x + pPuzzle[i].Size.x / 2 > pPlayer->Position.x
					)
				{
					pFlag = true;
				}


				for (int j = 0; j < PUZZLE_MAX; j++)
				{
					if (j != i)
					{
						//動かし終わったパズルと今のパズルが重なっているか
						bool hitFlag = CollisionBB(pPuzzle[i].Position, pPuzzle[j].Position, pPuzzle[i].Size, D3DXVECTOR2(pPuzzle[j].Size.x, pPuzzle[j].Size.y));

						if (hitFlag)	//重なっていたら
						{
							//ポジションの差分
							float x = pPuzzle[i].Position.x - pPuzzle[j].Position.x;
							float y = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//絶対値の取得
							x = fabsf(x);
							y = fabsf(y);
							//x = x / 1.5f;
							//パズルが横のほうに有ったら
							if (x >= y)
							{
								//動かしているパズルが右にあったら
								if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
								{
									//パズルのチップの左と右が有っているか
									if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);
										//右が開いているか
										if (hitFlag)
										{
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_WIDHT, pPuzzle[j].Position.y);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												//有っていたらトゥルー
												colFlag = true;

											}
											else
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}

											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;


											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									else
									{
										//パズルのチップの右と左が有っていなかったら

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}
								}
								//動かしているパズルが左にあったら
								if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
								{

									//パズルのチップの右と左が有っているか
									if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);
										//左が開いているか

										if (hitFlag) {
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_WIDHT, pPuzzle[j].Position.y);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												//有っていたらトゥルー
												colFlag = true;

											}
											else
											{
												//合っていなかったら元の戻す

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//パズルのチップの右と左が有っていなかったら
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}
							//パズルが縦のほうに有ったら
							else if (y > x)
							{
								//動かしているパズルが上にあったら

								if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
								{
									//パズルのチップの下と上が有っているか
									if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
									{
										//上が開いているか
										hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

										if (hitFlag)
										{
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_HEIGHT);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												colFlag = true;

											}
											else
											{
												//合っていなかったら元の戻す

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;
											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//パズルのチップの下と上が有っていなかったら

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}
								//動かしているパズルが下にあったら
								if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
								{
									//パズルのチップの上と下が有っているか

									if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
									{
										//下が開いているか
										hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

										if (hitFlag)
										{
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_HEIGHT);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												//合っていたらトゥルー
												colFlag = true;

											}
											else
											{
												//合っていなかったら元の戻す
												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}

											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//パズルのチップの上と下が有っていなかったら元に戻す
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
							//ポジションの差分
							float abx = (pPuzzle[i].Position.x) - pPuzzle[j].Position.x;
							float aby = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//絶対値の取得
							abx = fabsf(abx);
							aby = fabsf(aby);
							//付けたいパズルの近くにいるか
							if ((abx < 20.0f && aby < 200.0f) || (abx < 200.0f && aby < 20.0f))
							{

								//パズルが横のほうに有ったら

								if (abx >= aby)
								{
									//動かしているパズルが右にあったら
									if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
									{
										//パズルのチップの左と右が有っているか

										if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
										{
											//右が開いているか

											hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);

											if (hitFlag)
											{
												//空いていたらポジションを移動する
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_WIDHT, pPuzzle[j].Position.y);
												//四方向のパズルに合うか

												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

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
												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

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
												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

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

												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

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
				if (!colFlag)
				{
					//当たったけど入っていなかったら
					float pPx = pPuzzle[i].Position.x - pPuzzle[i].oldPosition.x;
					float pPy = pPuzzle[i].Position.y - pPuzzle[i].oldPosition.y;
					pPx = fabsf(pPx);
					pPy = fabsf(pPy);
					//前回とほぼ位置が変わっていなかったら
					if (pPx + pPy < 10)
					{
						//pPuzzle[i].Position.x += (20.0f);
						pPuzzle[i].Position.y -= (20.0f);

					}
					pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

					pPuzzle[i].oldPosition = pPuzzle[i].Position;

					pPuzzle[i].Position = pPuzzle[i].oldPosition;

				}
				if (pFlag) {

					MOUSE* pMouse = GetMouse();

					pPlayer->Position = pPuzzle[i].Position - pMouse->PlPos;
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
	{
		return false;
	}

	if (max2.x < min1.x)//判定2
	{
		return false;
	}
	if (max1.y < min2.y)//判定3
	{
		return false;
	}
	if (max2.y < min1.y)//判定4
	{
		return false;
	}

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

					//puzzleの上に別のパズルがあるか
					if (puzzle.Position.y - PUZZLE_HEIGHT - (PUZZLE_HEIGHT / 2) < pPuzzle[i].Position.y &&
						puzzle.Position.y - PUZZLE_HEIGHT + (PUZZLE_HEIGHT / 2) > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_WIDHT / 3 <= pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_WIDHT / 3 >= pPuzzle[i].Position.x)
					{

						punum = i;
						return false;
					}

					break;
				case DOWN:
					//if (puzzle.Position.y + PUZZLE_HEIGHT == pPuzzle[i].Position.y)	return false;
										//puzzleの下に別のパズルがあるか

					if (puzzle.Position.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_WIDHT / 3 <= pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_WIDHT / 3 >= pPuzzle[i].Position.x)
					{
						punum = i;
						return false;
					}

					break;
				case LEFT:
					//if (puzzle.Position.x - PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;
										//puzzleの左に別のパズルがあるか

					if (puzzle.Position.y - PUZZLE_HEIGHT / 3 <= pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_HEIGHT / 3 >= pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 3 < pPuzzle[i].Position.x &&
						puzzle.Position.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 3 > pPuzzle[i].Position.x)
					{
						punum = i;

						return false;
					}

					break;
				case RIGHT:
					//if (puzzle.Position.x + PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;
					//puzzleの右に別のパズルがあるか
					if (puzzle.Position.y - PUZZLE_HEIGHT / 3 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_HEIGHT / 3 > pPuzzle[i].Position.y &&
						puzzle.Position.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 3 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 3 > pPuzzle[i].Position.x)
					{
						punum = i;

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
					//puzzleの上に別のパズルがあるか
					if (puzzle.Position.y - PUZZLE_HEIGHT == pPuzzle[i].Position.y)return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y - PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case DOWN:
					//puzzleの下に別のパズルがあるか
					if (puzzle.Position.y + PUZZLE_HEIGHT == pPuzzle[i].Position.y)	return false;

					if (puzzle.Position.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case LEFT:
					//puzzleの左に別のパズルがあるか
					if (puzzle.Position.x - PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case RIGHT:
					//puzzleの右に別のパズルがあるか
					if (puzzle.Position.x + PUZZLE_WIDHT == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_HEIGHT / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_HEIGHT / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//4方向にパズルがあるかあったらピースの出っ張りが有っているか
//----------------------------------------------
bool fourCollision(PUZZLE puzzle, int index)
{
	PUZZLE* pPuzzle = GetPuzzle();
	punum = -1;

	bool hitFlag;

	hitFlag = PuzzleOpen(puzzle, index, RIGHT);
	//右が開いていなかったら
	if (!hitFlag)
	{
		//パズルのチップの右と左が有っているか
		if ((puzzle.Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeRight == STEAT_NUM && pPuzzle[punum].Puzzle_TypeLeft == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}

	//左が開いていなかったら
	hitFlag = PuzzleOpen(puzzle, index, LEFT);

	if (!hitFlag)
	{
		//パズルのチップの左と右が有っているか
		if ((puzzle.Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeRight == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeRight == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_NUM && pPuzzle[punum].Puzzle_TypeRight == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}
	hitFlag = PuzzleOpen(puzzle, index, UP);


	if (!hitFlag)
	{	//上が開いていなかったら

		//パズルのチップの上と下が有っているか
		if ((puzzle.Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeDown == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeDown == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeUp == STEAT_NUM && pPuzzle[punum].Puzzle_TypeDown == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}

	hitFlag = PuzzleOpen(puzzle, index, DOWN);


	if (!hitFlag)
	{
		//下が開いていなかったら

		//パズルのチップの下と上が有っているか
		if ((puzzle.Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeUp == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeUp == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeDown == STEAT_NUM && pPuzzle[punum].Puzzle_TypeUp == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}


	return true;

}
//--------------------------------------
//ピースの中のものを移動させる
//引数：移動させたい分のポジション、そのピース番号
//--------------------------------------
void PositionPlas(D3DXVECTOR2 num,int pinNo)
{
	BLOCK* pBlock = GetChipBlock();
	JOINT* pJoint = GetJoint();

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (pBlock[i].UseFlag)
		{

			if (pBlock[i].PieceIndex == pinNo)
			{

				pBlock[i].Position += num;

			}

		}

	}
	for (int i = 0; i < JOINT_MAX; i++)
	{
		if (pJoint[i].useFlag)
		{
			if (pJoint[i].pieNo == pinNo)
			{
				pJoint[i].pos += num;
			}

		}

	}

}
