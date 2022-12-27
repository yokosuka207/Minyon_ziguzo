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
#include"spawnpoint.h"

MOUSE Mouse;
bool oneFlag = false;	//�}�E�X�Ńp�Y����������Ă��邩
int MouseIndex = -1;	//�}�E�X�̒͂񂾃p�Y���̔ԍ�����
int NoIndex = -1;	//�}�E�X�Œ͂񂾃s�[�X�ԍ�
//bool MouseFlag = false;	//�}�E�X���N���b�N���Ă��邩

long y,x;
//�V���Ė�
HRESULT InitGameMouse()
{
	bool oneFlag = false;
	 MouseIndex = -1;
	 NoIndex = -1;
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
	SpawnPoint* pSpawnPoint = GetSpawnPoint();
	Mouse.oldPosX = GetMousePosX();
	Mouse.oldPosY = GetMousePosY();

	y = Mouse.PosY - Mouse.oldPosY;
	x = Mouse.PosX - Mouse.oldPosX;

	Mouse.PosX = GetMousePosX();
	Mouse.PosY = GetMousePosY();
	Mouse.oldPosX = Mouse.PosX -= SCREEN_WIDTH / 2;
	Mouse.oldPosY = Mouse.PosY -= SCREEN_HEIGHT / 2;

	 Mouse.UseFlag = IsMouseLeftPressed();
	 Mouse.ScrollFlag = IsMouseCenterPressed();



	if (Mouse.UseFlag)
	{

		for (int i = 0; i < PUZZLE_MAX; i++)
		{

				if (pPiece[i].UseFlag)
				{

					if (pPiece[i].pos.y - pPiece[i].size.y / 3 < -Mouse.PosY &&
						pPiece[i].pos.y + pPiece[i].size.y / 3 > -Mouse.PosY &&
						pPiece[i].pos.x - pPiece[i].size.x / 3 <Mouse.PosX &&
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
						pPiece[i].MoveFlag = true;
						MouseIndex = i;
						NoIndex = pPiece[i].no;
						pPiece[i].OldMovePos = pPiece[i].pos;

					}
					else if (oneFlag && i == MouseIndex)
					{
						pPiece[MouseIndex].OldPos = pPiece[MouseIndex].pos;

						pPiece[MouseIndex].pos.x = Mouse.PosX;
						pPiece[MouseIndex].pos.y = -Mouse.PosY;
						//pPiece[MouseIndex].MoveFlag = true;
						D3DXVECTOR2 temp = (pPiece[MouseIndex].pos - pPiece[MouseIndex].OldPos);

						for (int i = 0; i < BLOCK_CHIP_MAX; i++)
						{//�u���b�N������
							if (pCipBlock[i].UseFlag)
							{
								if (pCipBlock[i].PieceIndex == NoIndex)
								{
									pCipBlock[i].Position += temp;
								}

							}

						}
						for (int i = 0; i < JOINT_MAX; i++)
						{//����
							if (pJoint[i].useFlag)
							{
								if (pJoint[i].pieNo == NoIndex)
								{
									pJoint[i].pos += temp;
								}

							}
						}
						for (int i = 0; i < PUZZLE_MAX; i++)
						{//�s�[�X�`�b�v
							if (pPuzzleCip[i].UseFlag)
							{
								if (pPuzzleCip[i].PieceIndex == NoIndex)
								{
									pPuzzleCip[i].Position += temp;
								}
							}
						}
						if (pGoal->UseFlag)
						{//�S�[��
							if (pGoal->pieceIndex == NoIndex)
							{
								pGoal->Pos += temp;
							}
						}
						for (int i = 0; i < THORN_BLOCK_MAX; i++)
						{//�Ƃ�
							if (pThornBlock[i].UseFlag)
							{
								if (pThornBlock[i].PieceIndex == NoIndex)
								{
									pThornBlock[i].Postion += temp;
								}
							}

						}
						for (int i = 0; i < JUMPSTAND_MAX; i++)
						{//�W�����v�X�^���h
							if (pJumpStand[i].UseJumpStand)
							{
								if (pJumpStand[i].PieceIndex == NoIndex)
								{
									pJumpStand[i].pos += temp;
								}
							}
						}
						for (int i = 0; i < SPAWN_POINT_MAX; i++)
						{//�X�|�[���|�C���g
							if (pSpawnPoint[i].UseFlag)
							{
								if (pSpawnPoint[i].PieceIndex == NoIndex)
								{
									pSpawnPoint[i].Position += temp;
								}

							}

						}

						if (!Mouse.pFlag)
						{
							if (GetKeyboardTrigger(DIK_A))	//a�L�[�������ꂽ��
							{
								RotateMapChipR(NoIndex);
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
			pPiece[MouseIndex].MoveFlag = false;

			//Mouse.RotIndex = 0;
			Mouse.pFlag = false;

		}

		oneFlag = false;
		MouseIndex = -1;
		NoIndex = -1;
	}

	for (int i = 0; i < PUZZLE_MAX; i++)
	{

		if (pPiece[i].UseFlag)
		{

			if (pPiece[i].pos.y - pPiece[i].size.y / 3 < -Mouse.PosY &&
				pPiece[i].pos.y + pPiece[i].size.y / 3 > -Mouse.PosY &&
				pPiece[i].pos.x - pPiece[i].size.x / 3 < Mouse.PosX &&
				pPiece[i].pos.x + pPiece[i].size.x / 3 > Mouse.PosX &&
				!oneFlag) {

				if (GetKeyboardTrigger(DIK_Y))
				{
					DeleteMapChip(i);
					SetPieceMapChip(pPiece[i].pos, pPiece[i].no);
				}


			}

		}
	}

}

MOUSE * GetMouse()
{
	return &Mouse;
}

