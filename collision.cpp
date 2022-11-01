#include "collision.h"
#include"main.h"

#include"player.h"
#include<math.h>
/*==============================================================================

   �����蔻��Ǘ� [collsion.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

//==================================
//�v���g�^�C�v�錾
//=================================




DIRECSION Direcsion =NUM;
//===============================
//�����蔻�菈��
//�����蔻�����C�ɍs��
//================================
void UpdateCollision()
{
	//�v���[���[�@�΁@�G�L����	�l�p

	//�Ȃǂ̕K�v�Ȕ���������ō��
}
//---------------------------------
//�p�Y���̓����蔻��
//���������邩�ǂ���
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
								//�������Ă���p�Y�����E�ɂ�������
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
								//�������Ă���p�Y�������ɂ�������
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
								//�������Ă���p�Y������ɂ�������

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
								//�������Ă���p�Y�������ɂ�������
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
								//�������Ă���p�Y�����E�ɂ�������
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
								//�������Ă���p�Y�������ɂ�������
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
								//�������Ă���p�Y������ɂ�������

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
								//�������Ă���p�Y�������ɂ�������
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
//�l�p�`���m���������Ă��邩�������Ă��Ȃ����𔻒肷�邾��
//����: �������W�P�A�������W�Q�A�T�C�Y�P�A�T�C�Y�Q
//�߂�l�F true�������Ă���:false�����Ă��Ȃ�
//================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2	min1, min2;	//�l�p�`�̍ŏ����W�i����j
	D3DXVECTOR2 max1, max2;	//�l�p�`�̍ő���W(�E��)

	//�l�p�`�P����
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	//�l�p�`�P�E��
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;
	//�l�p�`�Q����
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	//�l�p�`�Q�E��
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//�Փ˔���
	if (max1.x < min2.x)//����1
	{		return false;	}

	if (max2.x < min1.x)//����2
	{		return false;	}
	if (max1.y < min2.y)//����3
	{		return false;	}
	if (max2.y < min1.y)//����4
	{		return false;	}

	return true;

}
//=================================================
//�~���m���������Ă��邩�������Ă��Ȃ����𔻒肷�邾��
//����: �������W�P�A�������W�Q�A���a�P�A���a�Q
//�߂�l�F true�������Ă���:false�����Ă��Ȃ�
//================================================
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	D3DXVECTOR2 vDisitance = pos1 - pos2;

	float Lenght;
	Lenght = D3DXVec2LengthSq(&vDisitance);	//���[�g���g��Ȃ���
	//Length = D3DXVec2Length(&vDisitance);	//���[�g���g����(���m�Ȓ���)

	//���a�̑��a

	float size = (size1 + size2) * (size1 + size2);
	//float size = (size1+size2);	���[�g��

	//�Փ˔���
	if (size > Lenght)
	{
		return	true;
	}

	return false;
}
//--------------------------------------------
//�p�Y���̈ړ��悪�󂢂Ă��邩
//�����F���̃p�Y���A�ړ��������p�Y���̓Y�����A�ړ��������ꏊ
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
//�v���C���[�̈ړ���Ƀp�Y�������邩
//�����F���̃p�Y���A�ړ��������p�Y���̓Y�����A�ړ��������ꏊ
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
