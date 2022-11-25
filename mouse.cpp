#include "mouse.h"
#include "puzzle.h"
#include"block.h"
#include"texture.h"
#include"sprite.h"
#include"input.h"
#include"player.h"
#include"MapChip.h"
#include"joint.h"
#include"puzzlecip.h"
#include"goal.h"
#include"thorn_block.h"
//#include"puzzlecip.h"
#include"jump_stand.h"

MOUSE Mouse;
bool oneFlag = false;	//�}�E�X�Ńp�Y����������Ă��邩
int MouseIndex = -1;	//�}�E�X�̒͂񂾃p�Y���̔ԍ�����
//bool MouseFlag = false;	//�}�E�X���N���b�N���Ă��邩

long y,x;
//�V���Ė�
HRESULT InitGameMouse()
{
	bool oneFlag = false;
	int MouseIndex = -1;
	Mouse.PosX = GetMousePosX();
	Mouse.PosY = GetMousePosY();
	Mouse.oldPosX = GetMousePosX();
	Mouse.oldPosY = GetMousePosY();
	Mouse.RotIndex = 0;
	Mouse.UseFlag = false;
	Mouse.pFlag = false;
	return S_OK;
}

void UninitGameMouse()
{
}

void UpdateGameMouse()
{
	PUZZLE* pPuzzle = GetPuzzle();
	BLOCK*  pBlock = GetBlock();
	PLAYER* pPlayer=GetPlayer();
	Piece* pPiece = GetPiece();
	BLOCK* pCipBlock = GetChipBlock();
	JOINT* pJoint = GetJoint();
	PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	GOAL* pGoal = GetGoal();
	THORNBLOCK* pThornBlock = GetThornBlock();
	JUMPSTAND* pJumpStand = GetJumpStand();
	Mouse.oldPosX = GetMousePosX();
	Mouse.oldPosY = GetMousePosY();

	y = Mouse.PosY - Mouse.oldPosY;
	x = Mouse.PosX - Mouse.oldPosX;

	Mouse.PosX = GetMousePosX();
	Mouse.PosY = GetMousePosY();

	 Mouse.UseFlag = IsMouseLeftPressed();
	 Mouse.ScrollFlag = IsMouseCenterPressed();

	 if (Mouse.ScrollFlag)
	 {
		 pPlayer->Position.y = pPlayer->Position.y - y;
		 pPlayer->Position.x = pPlayer->Position.x - x;

		 for (int i = 0; i < PUZZLE_MAX; i++)
		 {
			 if (pPuzzle[i].UseFlag)
			 {
				// pPuzzle[i].Position.x -= SCREEN_HEIGHT - Mouse.PosX;
				 pPuzzle[i].Position.y = pPuzzle[i].Position.y-y;
				 pPuzzle[i].Position.x = pPuzzle[i].Position.x - x;

			 }

		 }
	 }


	if (Mouse.UseFlag)
	{

		for (int i = 0; i < PUZZLE_MAX; i++)
		{
				//if (pPuzzle[i].UseFlag)
				//{
				//	pPuzzle[i].MoveEndFlag = false;
				//	if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 3 < Mouse.PosY&&
				//		pPuzzle[i].Position.y + pPuzzle[i].Size.y / 3 > Mouse.PosY&&
				//		pPuzzle[i].Position.x - pPuzzle[i].Size.x / 3 < Mouse.PosX&&
				//		pPuzzle[i].Position.x + pPuzzle[i].Size.x / 3 > Mouse.PosX&&
				//		!oneFlag)
				//	{
				//		if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 2 < pPlayer->Position.y&&
				//			pPuzzle[i].Position.y + pPuzzle[i].Size.y / 2 > pPlayer->Position.y&&
				//			pPuzzle[i].Position.x - pPuzzle[i].Size.x / 2 < pPlayer->Position.x&&
				//			pPuzzle[i].Position.x + pPuzzle[i].Size.x / 2 > pPlayer->Position.x
				//			)
				//		{
				//		}
				//		else
				//		{
				//			oneFlag = true;
				//			MouseIndex = i;
				//			pPuzzle[i].oldPosition = pPuzzle[i].Position;
				//		}
				//	}
				//	else if (oneFlag && i == MouseIndex)
				//	{
				//		pPuzzle[MouseIndex].Position.x = Mouse.PosX;
				//		pPuzzle[MouseIndex].Position.y = Mouse.PosY;
				//		pPuzzle[MouseIndex].MoveFlag = true;
				//		if (GetKeyboardTrigger(DIK_A))	//a�L�[�������ꂽ��
				//		{				//������Ă鎞�̏���
				//			pPuzzle[MouseIndex].Rotation += 90.0f;
				//			pPuzzle[MouseIndex].RotNum++;
				//			if (pPuzzle[MouseIndex].RotNum >=4)
				//			{
				//				pPuzzle[MouseIndex].RotNum = 0;
				//			}
				//			if (pPuzzle[MouseIndex].Block_Type == TYPE_GRAND)
				//			{
				//				for (int j = 0; j < 4; j++)
				//				{
				//					if (pPuzzle[MouseIndex].blockIndex[j] != -1)
				//					{
				//						//pBlock[pPuzzle[MouseIndex].blockIndex[j]].Rotation += 90.0f;
				//					}
				//				}
				//			}
				//			PuzzleTypeShift(MouseIndex);
				//		}
				//	}
				//}

				if (pPiece[i].UseFlag)
				{
					if (pPiece[i].pos.y - pPiece[i].size.y / 3 < Mouse.PosY &&
						pPiece[i].pos.y + pPiece[i].size.y / 3 > Mouse.PosY &&
						pPiece[i].pos.x - pPiece[i].size.x / 3 < Mouse.PosX &&
						pPiece[i].pos.x + pPiece[i].size.x / 3 > Mouse.PosX &&
						!oneFlag)
					{
						//�v���[���[���������s�[�X�̒��ɂ�����
						if (pPiece[i].pos.y - pPiece[i].size.y / 2 < pPlayer->Position.y &&
							pPiece[i].pos.y + pPiece[i].size.y / 2 > pPlayer->Position.y &&
							pPiece[i].pos.x - pPiece[i].size.x / 2 < pPlayer->Position.x &&
							pPiece[i].pos.x + pPiece[i].size.x / 2 > pPlayer->Position.x
							)
						{
							Mouse.pFlag = true;
							pPlayer->OneOldpos = pPlayer->Position;
						}

						Mouse.RotIndex = 0;

						oneFlag = true;
						MouseIndex = i;
						pPiece[i].OldMovePos = pPiece[i].pos;

					}
					else if (oneFlag && i == MouseIndex)
					{
						pPiece[MouseIndex].OldPos = pPiece[MouseIndex].pos;

						pPiece[MouseIndex].pos.x = Mouse.PosX;
						pPiece[MouseIndex].pos.y = Mouse.PosY;
						//pPiece[MouseIndex].MoveFlag = true;
						D3DXVECTOR2 temp = (pPiece[MouseIndex].pos - pPiece[MouseIndex].OldPos);

						for (int i = 0; i < BLOCK_CHIP_MAX; i++)
						{//�u���b�N������
							if (pCipBlock[i].UseFlag)
							{
								if (pCipBlock[i].PieceIndex == MouseIndex)
								{
									pCipBlock[i].Position += temp;
								}

							}

						}
						for (int i = 0; i < JOINT_MAX; i++)
						{//����
							if (pJoint[i].useFlag)
							{
								if (pJoint[i].pieNo == MouseIndex)
								{
									pJoint[i].pos += temp;
								}

							}
						}
						for (int i = 0; i < PUZZLE_MAX; i++)
						{//�s�[�X�`�b�v
							if (pPuzzleCip[i].UseFlag)
							{
								if (pPuzzleCip[i].PieceIndex == MouseIndex)
								{
									pPuzzleCip[i].Position += temp;
								}
							}
						}
						if (pGoal->UseFlag)
						{//�S�[��
							if (pGoal->pieceIndex == MouseIndex)
							{
								pGoal->Pos += temp;
							}
						}
						for (int i = 0; i < THORN_BLOCK_MAX; i++)
						{//�Ƃ�
							if (pThornBlock[i].UseFlag)
							{
								if (pThornBlock[i].PieceIndex == MouseIndex)
								{
									pThornBlock[i].Postion += temp;
								}
							}

						}
						for (int i = 0; i < JUMPSTAND_MAX; i++)
						{//�W�����v�X�^���h
							if (pJumpStand[i].UseJumpStand)
							{
								if (pJumpStand[i].PieceIndex == MouseIndex)
								{
									pJumpStand[i].pos += temp;
								}
							}
						}
						if (!Mouse.pFlag)
						{
							if (GetKeyboardTrigger(DIK_A))	//a�L�[�������ꂽ��
							{
								RotateMapChipR(MouseIndex);
								Mouse.RotIndex += 1;

							}
						}
						else
						{
							pPlayer->Position += temp;
						}
					}



				}

		}

	}

	if (!Mouse.UseFlag)
	{
		if (MouseIndex != -1)
		{
			pPuzzle[MouseIndex].MoveFlag = false;
			pPuzzle[MouseIndex].MoveEndFlag = true;
			pPiece[MouseIndex].MoveEndFlag = true;
			//Mouse.RotIndex = 0;
			Mouse.pFlag = false;

		}

		oneFlag = false;
		MouseIndex = -1;
	}

}

MOUSE * GetMouse()
{
	return &Mouse;
}
