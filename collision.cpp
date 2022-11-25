#include "collision.h"
#include "main.h"
		 
#include "player.h"
#include <math.h>
#include "mouse.h"
#include "block.h"
#include "joint.h"
#include "SplitStage.h"
#include "inventory.h"
#include "MapChip.h"
#include "goal.h"
#include "thorn_block.h"
#include "game.h"
/*==============================================================================

   �����蔻��Ǘ� [collsion.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

//==================================
//�v���g�^�C�v�錾
//=================================

bool fourPieceCollision(Piece piece, int index);
bool PieceOpen(Piece piece, int index, DIRECSION direcsion);	//���̕����̃p�Y�����󂢂Ă��邩
bool fourNomalPieceCollision(Piece piece, int index);
void Rotreturn(int index);	//��]��߂�
void SetPosition(Piece p,int i);

int punum = 0;	//�p�Y���̔z��̓Y�����̊i�[


DIRECSION Direcsion = NUM;	//�����̊m�F
//===============================
//�����蔻�菈��
//�����蔻�����C�ɍs��
//================================
void UpdateCollision()
{
	// �Q�b�g
	Piece* pPiece = GetPiece();
	PLAYER* pPlayer = GetPlayer();

	THORNBLOCK* pThornBlock = GetThornBlock();

	//�v���[���[�@�΁@�G�L����	�l�p



	//�Ȃǂ̕K�v�Ȕ���������ō��
	
	//�v���C���[�ƃg�Q�u���b�N�̔���
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (pThornBlock[i].UseFlag) {
			if (CollisionBB(pThornBlock[i].Postion, pPlayer->Position, pThornBlock[i].Size, pPlayer->size)) {
				ResetGame();
			}
		}
	}

	// �s�[�X�ƃC���x���g���͈͂̓����蔻��
	for (int i = 0; i < PUZZLE_MAX; i++) {
		// �s�[�X���C���x���g���ɂ��܂�
		if (pPiece[i].UseFlag && pPiece[i].pos.x < (INVENTORYBG_POS_X + INVENTORYBG_SIZE_X / 2)) {
			SetInventory(pPiece[i].no);
			DeleteMapChip(pPiece[i].no);
		}
	}
}
void PieceCollision()
{
	SplitStage* pSplitStage = GetSplitStage();

	Piece* pPiece = GetPiece();
	JOINT* pJoint = GetJoint();
	PLAYER* pPlayer = GetPlayer();
	bool colFlag = false;//�������ē�������
	bool colFlag2 = false;//�������ē�������
	bool pFlag =false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (pPiece[i].MoveEndFlag)	//�����I�������
			{
				pPiece[i].MoveEndFlag = false;


				if (pPiece[i].pos.y - pPiece[i].size.y / 2 < pPlayer->Position.y &&
					pPiece[i].pos.y + pPiece[i].size.y / 2 > pPlayer->Position.y &&
					pPiece[i].pos.x - pPiece[i].size.x / 2 < pPlayer->Position.x &&
					pPiece[i].pos.x + pPiece[i].size.x / 2 > pPlayer->Position.x
					)
				{
					pFlag = true;
				}
				for (int j = 0; j < JOINT_MAX; j++)
				{
					if (pJoint[j].pieNo == i)	//�����I������s�[�X�̒��ɂ�������
					{
						for (int k = 0; k < JOINT_MAX; k++)
						{
							if (pJoint[j].pieNo != pJoint[k].pieNo)//�s�[�X�ԍ����������
							{

								//�W���C���g���d�Ȃ��Ă�����
								colFlag = CollisionBB(pJoint[j].pos, pJoint[k].pos, pJoint[j].size, pJoint[k].size);

								if (colFlag)
								{

									//���ʂ������Ă�����
									if (pJoint[j].type == JOINT_TYPE::TYPE_BUMP && pJoint[k].type == JOINT_TYPE::TYPE_DIP ||
										pJoint[k].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP)
									{
										colFlag2 = true;

										//�W���C���g���E��������
										if (pPiece[i].pos.x + pPiece[i].size.x / 3 < pJoint[j].pos.x)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].pieNo].pos.y) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].pieNo].pos.y);

											if (fourPieceCollision(pPiece[i], i))
											{
												PositionPlas(temp, i);
												pPiece[i].OldMovePos = pPiece[i].pos;

											}
											else
											{
												Rotreturn(i);						
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].pos;
												PositionPlas(temp, i);
												pPiece[i].pos = pPiece[i].OldMovePos;
												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}


										}
										//�W���C���g������������
										else if (pPiece[i].pos.x - pPiece[i].size.x / 3 > pJoint[j].pos.x)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].pieNo].pos.y) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].pieNo].pos.y);

											if (fourPieceCollision(pPiece[i], i))
											{
												PositionPlas(temp, i);
												pPiece[i].OldMovePos = pPiece[i].pos;

											}
											else
											{
												Rotreturn(i);
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].pos;
												PositionPlas(temp, i);

												pPiece[i].pos = pPiece[i].OldMovePos;
												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}

										}
										//�W���C���g���ゾ������
										else if (pPiece[i].pos.y - pPiece[i].size.y / 3 > pJoint[j].pos.y)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x, pPiece[pJoint[k].pieNo].pos.y + PUZZLE_HEIGHT) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x, pPiece[pJoint[k].pieNo].pos.y + PUZZLE_HEIGHT);

											if (fourPieceCollision(pPiece[i], i))
											{
												PositionPlas(temp, i);
												pPiece[i].OldMovePos = pPiece[i].pos;

											}
											else
											{
												Rotreturn(i);
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
												PositionPlas(temp, i);

												pPiece[i].pos = pPiece[i].OldMovePos;
												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}

										}
										//�W���C���g������������
										else if (pPiece[i].pos.y + pPiece[i].size.y / 3 < pJoint[j].pos.y)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x, pPiece[pJoint[k].pieNo].pos.y - PUZZLE_HEIGHT) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].pieNo].pos.x, pPiece[pJoint[k].pieNo].pos.y - PUZZLE_HEIGHT);

											if (fourPieceCollision(pPiece[i], i))
											{
												PositionPlas(temp, i);
												pPiece[i].OldMovePos = pPiece[i].pos;

											}
											else
											{
												Rotreturn(i);
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].pos;
												PositionPlas(temp, i);

												pPiece[i].pos = pPiece[i].OldMovePos;
												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}

										}

										break;
									}
									break;
								}


							}
						}
					}


				}
				if (!colFlag2)
				{

					if (fourNomalPieceCollision(pPiece[i], i))
					{

					}
					else
					{
						Rotreturn(i);

						colFlag2 = true;
						D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].pos;
						PositionPlas(temp, i);
						pPiece[i].pos = pPiece[i].OldMovePos;
						pPiece[i].OldPos = pPiece[i].pos;
						if (pFlag)
						{
							pPlayer->Position = pPlayer->OneOldpos;
						}

					}


					for (int m = 0; m < 3; m++)
					{
						if (!colFlag2)
						{

							for (int n = 0; n < 3; n++)
							{
								if (pSplitStage->pos.y + SPLIT_SIZE * (m - 1) - pSplitStage->size.y / 2 < pPiece[i].pos.y &&
									pSplitStage->pos.y + SPLIT_SIZE * (m - 1) + pSplitStage->size.y / 2 > pPiece[i].pos.y &&
									pSplitStage->pos.x + SPLIT_SIZE * (n - 1) - pSplitStage->size.x / 2 < pPiece[i].pos.x &&
									pSplitStage->pos.x + SPLIT_SIZE * (n - 1) + pSplitStage->size.x / 2 > pPiece[i].pos.x)
								{
									pPiece[i].pos = pSplitStage->Split3[n][m];

									if (fourNomalPieceCollision(pPiece[i], i))
									{
										D3DXVECTOR2 temp = pPiece[i].pos - pPiece[i].OldPos;

										PositionPlas(temp, i);

									}
									else
									{
										colFlag2 = true;
										D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
										PositionPlas(temp, i);
										pPiece[i].pos = pPiece[i].OldMovePos;
										Rotreturn(i);
										if (pFlag)
										{
											pPlayer->Position = pPlayer->OneOldpos;
										}

									}

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

//---------------------------------
//�p�Y���̓����蔻��
//���������邩�ǂ���
//---------------------------------
void PuzzleCollision()
{
	punum = -1;
	bool colFlag = false;//�������ē�������
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
						//�������I������p�Y���ƍ��̃p�Y�����d�Ȃ��Ă��邩
						bool hitFlag = CollisionBB(pPuzzle[i].Position, pPuzzle[j].Position, pPuzzle[i].Size, D3DXVECTOR2(pPuzzle[j].Size.x, pPuzzle[j].Size.y));

						if (hitFlag)	//�d�Ȃ��Ă�����
						{
							//�|�W�V�����̍���
							float x = pPuzzle[i].Position.x - pPuzzle[j].Position.x;
							float y = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//��Βl�̎擾
							x = fabsf(x);
							y = fabsf(y);
							//x = x / 1.5f;
							//�p�Y�������̂ق��ɗL������
							if (x >= y)
							{
								//�������Ă���p�Y�����E�ɂ�������
								if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
								{
									//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
									if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);
										//�E���J���Ă��邩
										if (hitFlag)
										{
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_WIDHT, pPuzzle[j].Position.y);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												//�L���Ă�����g�D���[
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
											//�J���Ă��Ȃ������猳�ɖ߂�
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									else
									{
										//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��Ȃ�������

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}
								}
								//�������Ă���p�Y�������ɂ�������
								if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
								{

									//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
									if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);
										//�����J���Ă��邩

										if (hitFlag) {
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_WIDHT, pPuzzle[j].Position.y);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												//�L���Ă�����g�D���[
												colFlag = true;

											}
											else
											{
												//�����Ă��Ȃ������猳�̖߂�

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//�J���Ă��Ȃ������猳�ɖ߂�

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��Ȃ�������
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}
							//�p�Y�����c�̂ق��ɗL������
							else if (y > x)
							{
								//�������Ă���p�Y������ɂ�������

								if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
								{
									//�p�Y���̃`�b�v�̉��Əオ�L���Ă��邩
									if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
									{
										//�オ�J���Ă��邩
										hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

										if (hitFlag)
										{
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_HEIGHT);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												colFlag = true;

											}
											else
											{
												//�����Ă��Ȃ������猳�̖߂�

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;
											break;
										}
										else if (!hitFlag)
										{
											//�J���Ă��Ȃ������猳�ɖ߂�
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//�p�Y���̃`�b�v�̉��Əオ�L���Ă��Ȃ�������

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}
								//�������Ă���p�Y�������ɂ�������
								if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
								{
									//�p�Y���̃`�b�v�̏�Ɖ����L���Ă��邩

									if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
									{
										//�����J���Ă��邩
										hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

										if (hitFlag)
										{
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_HEIGHT);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												//�����Ă�����g�D���[
												colFlag = true;

											}
											else
											{
												//�����Ă��Ȃ������猳�̖߂�
												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}

											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//�J���Ă��Ȃ������猳�ɖ߂�

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//�p�Y���̃`�b�v�̏�Ɖ����L���Ă��Ȃ������猳�ɖ߂�
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
							//�|�W�V�����̍���
							float abx = (pPuzzle[i].Position.x) - pPuzzle[j].Position.x;
							float aby = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//��Βl�̎擾
							abx = fabsf(abx);
							aby = fabsf(aby);
							//�t�������p�Y���̋߂��ɂ��邩
							if ((abx < 20.0f && aby < 200.0f) || (abx < 200.0f && aby < 20.0f))
							{

								//�p�Y�������̂ق��ɗL������

								if (abx >= aby)
								{
									//�������Ă���p�Y�����E�ɂ�������
									if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
									{
										//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩

										if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
										{
											//�E���J���Ă��邩

											hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);

											if (hitFlag)
											{
												//�󂢂Ă�����|�W�V�������ړ�����
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_WIDHT, pPuzzle[j].Position.y);
												//�l�����̃p�Y���ɍ�����

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
					//�����������Ǔ����Ă��Ȃ�������
					float pPx = pPuzzle[i].Position.x - pPuzzle[i].oldPosition.x;
					float pPy = pPuzzle[i].Position.y - pPuzzle[i].oldPosition.y;
					pPx = fabsf(pPx);
					pPy = fabsf(pPy);
					//�O��Ƃقڈʒu���ς���Ă��Ȃ�������
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
	{
		return false;
	}
	if (max2.x < min1.x)//����2
	{
		return false;
	}
	if (max1.y < min2.y)//����3
	{
		return false;
	}
	if (max2.y < min1.y)//����4
	{
		return false;
	}
	return true;


	//if (max1.x > min2.x)//����1
	//{
	//	return true;
	//}
	//if (max2.x > min1.x)//����2
	//{
	//	return true;
	//}
	//if (max1.y > min2.y)//����3
	//{
	//	return true;
	//}
	//if (max2.y > min1.y)//����4
	//{
	//	return true;
	//}
	//return false;

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

					//puzzle�̏�ɕʂ̃p�Y�������邩
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
										//puzzle�̉��ɕʂ̃p�Y�������邩

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
										//puzzle�̍��ɕʂ̃p�Y�������邩

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
					//puzzle�̉E�ɕʂ̃p�Y�������邩
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
					//puzzle�̏�ɕʂ̃p�Y�������邩
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
					//puzzle�̉��ɕʂ̃p�Y�������邩
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
					//puzzle�̍��ɕʂ̃p�Y�������邩
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
					//puzzle�̉E�ɕʂ̃p�Y�������邩
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
//4�����Ƀp�Y�������邩��������s�[�X�̏o�����肪�L���Ă��邩
//----------------------------------------------
bool fourCollision(PUZZLE puzzle, int index)
{
	PUZZLE* pPuzzle = GetPuzzle();
	punum = -1;

	bool hitFlag;

	hitFlag = PuzzleOpen(puzzle, index, RIGHT);
	//�E���J���Ă��Ȃ�������
	if (!hitFlag)
	{
		//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
		if ((puzzle.Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeRight == STEAT_NUM && pPuzzle[punum].Puzzle_TypeLeft == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}

	//�����J���Ă��Ȃ�������
	hitFlag = PuzzleOpen(puzzle, index, LEFT);

	if (!hitFlag)
	{
		//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
		if ((puzzle.Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeRight == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeRight == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_NUM && pPuzzle[punum].Puzzle_TypeRight == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}
	hitFlag = PuzzleOpen(puzzle, index, UP);


	if (!hitFlag)
	{	//�オ�J���Ă��Ȃ�������

		//�p�Y���̃`�b�v�̏�Ɖ����L���Ă��邩
		if ((puzzle.Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeDown == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeDown == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeUp == STEAT_NUM && pPuzzle[punum].Puzzle_TypeDown == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}

	hitFlag = PuzzleOpen(puzzle, index, DOWN);


	if (!hitFlag)
	{
		//�����J���Ă��Ȃ�������

		//�p�Y���̃`�b�v�̉��Əオ�L���Ă��邩
		if ((puzzle.Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeUp == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeUp == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeDown == STEAT_NUM && pPuzzle[punum].Puzzle_TypeUp == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}


	return true;

}
//--------------------------------------
//�s�[�X�̒��̂��̂��ړ�������
//�����F�ړ������������̃|�W�V�����A���̃s�[�X�ԍ�
//--------------------------------------
void PositionPlas(D3DXVECTOR2 num,int pinNo)
{
	BLOCK* pBlock = GetChipBlock();
	JOINT* pJoint = GetJoint();
	PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	GOAL* pGoal = GetGoal();
	THORNBLOCK* pThornBlock = GetThornBlock();

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
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzleCip[i].UseFlag)
		{
			if (pPuzzleCip[i].PieceIndex == pinNo)
			{
				pPuzzleCip[i].Position += num;
			}
		}
	}
	if (pGoal->UseFlag)
	{
		if (pGoal->pieceIndex == pinNo)
		{
			pGoal->Pos += num;
		}
	}
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{//�Ƃ�
		if (pThornBlock[i].UseFlag)
		{
			if (pThornBlock[i].PieceIndex == pinNo)
			{
				pThornBlock[i].Postion += num;
			}
		}

	}

}
//--------------------------------------------
//�v���C���[�̈ړ���Ƀs�[�X�����邩
//�����F���̃s�[�X�A�ړ��������s�[�X�̓Y�����A�ړ��������ꏊ
//----------------------------------------------
bool PlayerPieceOpen(Piece p, int index, DIRECSION direcsion)
{
	Piece* pPiece = GetPiece();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					//puzzle�̏�ɕʂ̃p�Y�������邩
					if (p.pos.y - PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)return false;

					if (p.pos.y - PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y - PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 > pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 < pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case DOWN:
					//p�̉��ɕʂ̃p�Y�������邩
					if (p.pos.y + PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)	return false;

					if (p.pos.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case LEFT:
					//p�̍��ɕʂ̃p�Y�������邩
					if (p.pos.x - PUZZLE_WIDHT == pPiece[i].pos.x && p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case RIGHT:
					//p�̉E�ɕʂ̃p�Y�������邩

   					if (p.pos.x + PUZZLE_WIDHT == pPiece[i].pos.x&& p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}


					break;

				}

			}

		}
	}
	return true;

}//--------------------------------------------
//4�����Ƀp�Y�������邩��������s�[�X�̏o�����肪�L���Ă��邩
//----------------------------------------------
bool fourPieceCollision(Piece piece, int index)
{
	JOINT* pJoint = GetJoint();
	Piece* pPiece = GetPiece();
	punum = -1;

	bool hitFlag;
	bool 	JointFlag = false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (i != index)
		{
			if (piece.pos == pPiece[i].pos)
			{
				return false;
			}
		}

	}

	hitFlag = PieceOpen(piece, index, RIGHT);
	//�E���J���Ă��Ȃ�������
	if (!hitFlag)
	{
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == index)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.x + piece.size.x / 3 < pJoint[i].pos.x)	//�W���C���g���s�[�X�̉E��������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo ==punum)
						{
							if (pPiece[punum].pos.x - pPiece[punum].size.x / 3 > pJoint[j].pos.x)
							{
								JointFlag = true;

								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}


	}
	JointFlag = false;

	//�����J���Ă��Ȃ�������
	hitFlag = PieceOpen(piece, index, LEFT);

	if (!hitFlag)
	{
		//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == index)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.x - piece.size.x / 3 > pJoint[i].pos.x)	//�W���C���g���s�[�X�̉E��������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == punum)
						{
							if (pPiece[punum].pos.x + pPiece[punum].size.x / 3 < pJoint[j].pos.x)
							{
								JointFlag = true;

								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}

	}
	hitFlag = PieceOpen(piece, index, UP);
	JointFlag = false;


	if (!hitFlag)
	{	//�オ�J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == index)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.y - piece.size.y / 3 > pJoint[i].pos.y)	//�W���C���g���s�[�X�̏ゾ������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == punum)
						{

							if (pPiece[punum].pos.y + pPiece[punum].size.y / 3 < pJoint[j].pos.y)	//��
							{
								JointFlag = true;

								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
									
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;


		}

	}

	hitFlag = PieceOpen(piece, index, DOWN);
	JointFlag = false;


	if (!hitFlag)
	{
		//�����J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == index)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.y + piece.size.y / 3 < pJoint[i].pos.y)	//�W���C���g���s�[�X�̏ゾ������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == punum)
						{
							if (pPiece[punum].pos.y - pPiece[punum].size.y / 3 > pJoint[j].pos.y)	//��
							{
								JointFlag = true;
								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}
	}


	return true;

}
//--------------------------------------------
//�p�Y���̈ړ��悪�󂢂Ă��邩
//�����F���̃p�Y���A�ړ��������p�Y���̓Y�����A�ړ��������ꏊ
//----------------------------------------------
bool PieceOpen(Piece piece, int index, DIRECSION direcsion)
{
	Piece* pPiece = GetPiece();

	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{

				switch (direcsion)
				{
				case UP:

					//piece�̏�ɕʂ̃p�Y�������邩
					if (piece.pos.y - PUZZLE_HEIGHT - (PUZZLE_HEIGHT / 2) < pPiece[i].pos.y &&
						piece.pos.y - PUZZLE_HEIGHT + (PUZZLE_HEIGHT / 2) > pPiece[i].pos.y &&
						piece.pos.x - PUZZLE_WIDHT / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PUZZLE_WIDHT / 3 >= pPiece[i].pos.x)
					{

						punum = i;
						return false;
					}

					break;
				case DOWN:
					//if (piece.pos.y + PUZZLE_HEIGHT == pPiece[i].pos.y)	return false;
										//piece�̉��ɕʂ̃p�Y�������邩

					if (piece.pos.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						piece.pos.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						piece.pos.x - PUZZLE_WIDHT / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PUZZLE_WIDHT / 3 >= pPiece[i].pos.x)
					{
						punum = i;
						return false;
					}

					break;
				case LEFT:
					//if (piece.pos.x - PUZZLE_WIDHT == pPiece[i].pos.x)	return false;
										//piece�̍��ɕʂ̃p�Y�������邩

					if (piece.pos.y - PUZZLE_HEIGHT / 3 <= pPiece[i].pos.y &&
						piece.pos.y + PUZZLE_HEIGHT / 3 >= pPiece[i].pos.y &&
						piece.pos.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 3 < pPiece[i].pos.x &&
						piece.pos.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 3 > pPiece[i].pos.x)
					{
						punum = i;

						return false;
					}

					break;
				case RIGHT:
					//if (piece.pos.x + PUZZLE_WIDHT == pPiece[i].pos.x)	return false;
					//piece�̉E�ɕʂ̃p�Y�������邩
					if (piece.pos.y - PUZZLE_HEIGHT / 3 < pPiece[i].pos.y &&
						piece.pos.y + PUZZLE_HEIGHT / 3 > pPiece[i].pos.y &&
						piece.pos.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 3 < pPiece[i].pos.x &&
						piece.pos.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 3 > pPiece[i].pos.x)
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
//4�����Ƀp�Y�������邩��������s�[�X�̃m�[�}����
//----------------------------------------------
bool fourNomalPieceCollision(Piece piece, int index)
{
	JOINT* pJoint = GetJoint();
	Piece* pPiece = GetPiece();
	punum = -1;

	bool hitFlag;
	bool 	JointFlag = false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (i != index)
		{
			if (piece.pos == pPiece[i].pos)
			{
				return false;
			}
		}

	}


	hitFlag = PieceOpen(piece, index, RIGHT);
	//�E���J���Ă��Ȃ�������
	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == index)
			{
				if (pJoint[j].pos.x>piece.pos.x+piece.size.x/3)
				{
					return false;
				}
			}
		}

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == punum)	//���̃s�[�X�̃W���C���g��������
			{
				//�W���C���g���Ȃ�������
				if (pPiece[punum].pos.x - pPiece[punum].size.x / 3 > pJoint[i].pos.x)
				{
					//�����Ă��Ȃ�������
					return false;
				}	
			}
		}
	}
	JointFlag = false;

	//�����J���Ă��Ȃ�������
	hitFlag = PieceOpen(piece, index, LEFT);

	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == index)
			{
				if (pJoint[j].pos.x < piece.pos.x - piece.size.x / 3)
				{
					return false;
				}
			}
		}

		//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == punum)
			{				//�W���C���g���Ȃ�������

				if (pPiece[punum].pos.x + pPiece[punum].size.x / 3 < pJoint[i].pos.x)
				{
					//�����Ă��Ȃ�������
					return false;
				}
			}
		}
	}
	hitFlag = PieceOpen(piece, index, UP);
	JointFlag = false;


	if (!hitFlag)
	{	//�オ�J���Ă��Ȃ�������
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == index)
			{
				if (pJoint[j].pos.y < piece.pos.y - piece.size.y / 3)
				{
					return false;
				}
			}
		}

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == punum)
			{
				//�W���C���g���Ȃ�������

				if (pPiece[punum].pos.y + pPiece[punum].size.y / 3 < pJoint[i].pos.y)	//��
				{
					{
						//�����Ă��Ȃ�������
						return false;
					}


				}


			}

		}

	}

	hitFlag = PieceOpen(piece, index, DOWN);
	JointFlag = false;


	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == index)
			{
				if (pJoint[j].pos.y > piece.pos.y + piece.size.y / 3)
				{
					return false;
				}
			}
		}

		//�����J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == punum)
			{
				//�W���C���g���Ȃ�������
				if (pPiece[punum].pos.y - pPiece[punum].size.y / 3 > pJoint[i].pos.y)	//��
				{
					//�����Ă��Ȃ�������
					return false;

				}


			}

		}

	}


	return true;

}
//--------------------------------
//��]�����ɖ߂�
//�����F�p�Y���̓Y����
//--------------------------------
void Rotreturn(int index)
{
	MOUSE* pMouse = GetMouse();

	for (int i = 0; i < pMouse->RotIndex; i++)
	{
		RotateMapChipL(index);

	}

}

