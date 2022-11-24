//=============================================================================
//
//�v���C���[����
//
//�����/��t���l�@�����/2022/06/27
//���̐���ҁF�V���Ė�	����X�V��2022/10/24
//=============================================================================
#pragma once

#include "player.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "block.h"
#include "thorn_block.h"
#include "broken.h"
#include "warp.h"
#include "scene.h"
//#include "piece.h"
#include"puzzlecip.h"
#include"game.h"
#include"puzzle.h"
#include"collision.h"
#include"mouse.h"
#include"jump_stand.h"		//�W�����v��
#include"MapChip.h"
#include"thorn_block.h"
//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static PLAYER g_Player;
static char* g_TextureNameBroken = (char*)"data\\texture\\waking_alpha.png";



//=============================================================================
//����������
//=============================================================================
HRESULT InitPlayer()
{
	//�v���C���[�̏�����
	g_Player.Position = D3DXVECTOR2(300.0f, 300.0f);
	g_Player.OneOldpos = g_Player.oldpos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Player.sp = D3DXVECTOR2(0,8);
	g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
	g_Player.col = D3DXCOLOR(0.0f, 1.0f, 0.0, 1.0f);
	g_Player.rot = 0.0f;
	g_Player.UseFlag = true;
	g_Player.jump = false;
	g_Player.getjump = false;
	g_Player.GetJumpStand = false;		//�W�����v��p
	g_Player.fall = false;
	g_Player.getfall = false;
	g_Player.WarpFlag = false;
	g_Player.texno = LoadTexture(g_TextureNameBroken);

	g_Player.PaternNo = 0;//�p�^�[���ԍ�
	g_Player.uv_w = 1.0f / 4;//���T�C�Y
	g_Player.uv_h = 1.0f / 4;//�c�T�C�Y
	g_Player.NumPatern = 4;//������

	g_Player.hp = 30;
	g_Player.frame = 0;
	g_Player.CoolTime = PLAYER_COOLTIME;

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitPlayer()
{

}

//=============================================================================
//�X�V����
//=============================================================================
void UpdatePlayer()
{
	MOUSE* pMouse = GetMouse();
	if (!pMouse->UseFlag)
	{


		if (g_Player.UseFlag == true)
		{





			//�ړ�
			if (GetKeyboardPress(DIK_RIGHT))//�E�L�[
			{//������Ă���Ƃ��̏���
				g_Player.sp.x = 3.0f;
				g_Player.PaternNo += 0.25f;
			}
			else if (GetKeyboardPress(DIK_LEFT))//���L�[
			{//������Ă���Ƃ��̏���
				g_Player.sp.x = -3.0f;
				g_Player.PaternNo += 0.25f;
			}
			else
			{
				g_Player.sp.x = 0;

			}

			//�W�����v�䏈��
			JUMPSTAND* p_JumpStand = GetJumpStand();
			if (GetKeyboardPress(DIK_B))
			{
				if (CollisionBB(g_Player.Position, p_JumpStand->pos, g_Player.size, p_JumpStand->size * 2)) {
					g_Player.GetJumpStand = true;
				}
			}
			else
			{
				g_Player.GetJumpStand = false;
			}



			//�W�����v
			g_Player.frame++;
			if (g_Player.jump == false && GetKeyboardPress(DIK_SPACE))
			{
				g_Player.jump = true;
				g_Player.getjump = true;
			}
			if (g_Player.jump == true && g_Player.frame < 50)
			{
				if (g_Player.getjump == true)//�������u��
				{
					g_Player.sp.y = -4.2f;
					g_Player.getjump = false;
				}
				else if (g_Player.sp.y <= 0)//����
				{
					g_Player.sp.y += 0.1f;
				}
				else
				{
					//g_Player.sp.y = 0;//��~
				}
			}




			//����
			if (g_Player.fall == false && g_Player.Position.y > g_Player.oldpos.y)
			{
				g_Player.fall = true;
				g_Player.getfall = true;
			}
			if (g_Player.fall == true)
			{
				if (g_Player.getfall == true)//�������u��
				{
					g_Player.sp.y = 0;
					g_Player.getfall = false;
				}
				else if (g_Player.sp.y <= 8)//����,�W�����v�����ꍇ��50�t���[���ォ�痎��
				{
					g_Player.sp.y += 0.2;//����
				}
				else
				{
					g_Player.sp.y = 8;//�ő嗎�����x
				}

				g_Player.jump = true;
			}








			//���f
			g_Player.oldpos = g_Player.Position;
			g_Player.Position += g_Player.sp;








			{
				//�v���C���[�E�u���b�N�@�����蔻��
				/*for (int i = 0; i < BLOCK_MAX; i++)
				{
					BLOCK* block = GetBlock();

					if ((block + i)->UseFlag == true)
					{
						//�v���C���[���E�u���b�N�E
						if (g_Player.Position.x + g_Player.size.x / 2 > (block + i)->Position.x - (block + i)->Size.x / 2 &&
							g_Player.oldpos.x + g_Player.size.x / 2 <= (block + i)->Position.x - (block + i)->Size.x / 2 &&
							g_Player.Position.y + g_Player.size.y / 2 > (block + i)->Position.y - (block + i)->Size.y / 2 &&
							g_Player.Position.y - g_Player.size.y / 2 < (block + i)->Position.y + (block + i)->Size.y / 2)
						{
							g_Player.Position.x = (block + i)->Position.x - (block + i)->Size.x / 2 - g_Player.size.x / 2;
						}
						//�v���C���[�E�E�u���b�N��
						if (g_Player.Position.x - g_Player.size.x / 2 < (block + i)->Position.x + (block + i)->Size.x / 2 &&
							g_Player.oldpos.x - g_Player.size.x / 2 >= (block + i)->Position.x + (block + i)->Size.x / 2 &&
							g_Player.Position.y + g_Player.size.y / 2 > (block + i)->Position.y - (block + i)->Size.y / 2 &&
							g_Player.Position.y - g_Player.size.y / 2 < (block + i)->Position.y + (block + i)->Size.y / 2)
						{
							g_Player.Position.x = (block + i)->Position.x + (block + i)->Size.x / 2 + g_Player.size.x / 2;
						}

						//�v���C���[��E�u���b�N��,���n����
						if (g_Player.Position.x + g_Player.size.x / 2 > (block + i)->Position.x - (block + i)->Size.x / 2 &&
							g_Player.Position.x - g_Player.size.x / 2 < (block + i)->Position.x + (block + i)->Size.x / 2 &&
							g_Player.Position.y + g_Player.size.y / 2 > (block + i)->Position.y - (block + i)->Size.y / 2 &&
							g_Player.oldpos.y + g_Player.size.y / 2 <= (block + i)->Position.y - (block + i)->Size.y / 2)
						{
							g_Player.Position.y = (block + i)->Position.y - (block + i)->Size.y / 2 - g_Player.size.y / 2;
							g_Player.jump = false;
							g_Player.fall = false;
							g_Player.WarpFlag = false;
							g_Player.frame = 0;
						}
						//�v���C���[���E�u���b�N��,��������
						if (g_Player.Position.x + g_Player.size.x / 2 > (block + i)->Position.x - (block + i)->Size.x / 2 &&
							g_Player.Position.x - g_Player.size.x / 2 < (block + i)->Position.x + (block + i)->Size.x / 2 &&
							g_Player.Position.y - g_Player.size.y / 2 < (block + i)->Position.y + (block + i)->Size.y / 2 &&
							g_Player.oldpos.y - g_Player.size.y / 2 >= (block + i)->Position.y + (block + i)->Size.y / 2)
						{
							g_Player.fall = true;
							g_Player.getfall = true;
							g_Player.frame = 50;
						}
					}
				}*/
			}

			//�`�b�v�̃u���b�N�̓����蔻��
			for (int i = 0; i < BLOCK_MAX; i++)
			{
				BLOCK* block = GetBlock();
				BLOCK* cipblock = GetChipBlock();

				if ((cipblock + i)->UseFlag == true)
				{
					//�v���C���[���E�u���b�N�E
					if (g_Player.Position.x + g_Player.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
						g_Player.oldpos.x + g_Player.size.x / 2 <= (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
					{
						g_Player.Position.x = (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 - g_Player.size.x / 2;
					}
					//�v���C���[�E�E�u���b�N��
					if (g_Player.Position.x - g_Player.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
						g_Player.oldpos.x - g_Player.size.x / 2 >= (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 3 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 3 &&
						g_Player.Position.y - g_Player.size.y / 3 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 3)
					{
						g_Player.Position.x = (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 + g_Player.size.x / 2;
					}

					//�v���C���[��E�u���b�N��,���n����
					if (g_Player.Position.x + g_Player.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
						g_Player.oldpos.y + g_Player.size.y / 2 <= (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2)
					{
						g_Player.Position.y = (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 - g_Player.size.y / 2-0.02f;
						g_Player.jump = false; 
						g_Player.fall = false;
						g_Player.WarpFlag = false;
						g_Player.frame = 0;
					}
					//�v���C���[���E�u���b�N��,��������
					if (g_Player.Position.x + g_Player.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 &&
						g_Player.oldpos.y - g_Player.size.y / 2 >= (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
					{
						g_Player.fall = true;
						g_Player.getfall = true;
						g_Player.frame = 50;
					}
				}
			}



			//�v���C���[�E����u���b�N�@�����蔻��
			for (int i = 0; i < BLOCK_MAX; i++)
			{
				BROKEN* broken = GetBroken();
				if ((broken + i)->UseFlag == true)
				{
					//�v���C���[���E����u���b�N�E
					if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.oldpos.x + g_Player.size.x / 2 <= (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2)
					{
						g_Player.Position.x = (broken + i)->Postion.x - (broken + i)->Size.x / 2 - g_Player.size.x / 2;
					}
					//�v���C���[�E�E����u���b�N��
					if (g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.oldpos.x - g_Player.size.x / 2 >= (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2)
					{
						g_Player.Position.x = (broken + i)->Postion.x + (broken + i)->Size.x / 2 + g_Player.size.x / 2;
					}

					//�v���C���[��E����u���b�N��
					if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
						g_Player.oldpos.y + g_Player.size.y / 2 <= (broken + i)->Postion.y - (broken + i)->Size.y / 2)
					{
						g_Player.Position.y = (broken + i)->Postion.y - (broken + i)->Size.y / 2 - g_Player.size.y / 2;
						g_Player.jump = false;
						g_Player.fall = false;
						g_Player.frame = 0;
					}
					//�v���C���[���E����u���b�N��,����
					if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2 &&
						g_Player.oldpos.y - g_Player.size.y / 2 >= (broken + i)->Postion.y + (broken + i)->Size.y / 2)
					{
						(broken + i)->UseFlag = false;
						g_Player.fall = true;
						g_Player.getfall = true;
						g_Player.frame = 50;
					}
				}
			}


			//�v���C���[�E�g�Q�u���b�N�@�����蔻��
			for (int i = 0; i < THORN_BLOCK_MAX; i++)
			{
				THORNBLOCK* thornblock = GetThornBlock();
				if ((thornblock + i)->UseFlag == true)
				{
					//�v���C���[���E�g�Q�u���b�N�E
					if (g_Player.Position.x + g_Player.size.x / 2 > (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
						g_Player.oldpos.x + g_Player.size.x / 2 <= (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2)
					{
						g_Player.Position.x = (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 - g_Player.size.x / 2;
						//g_Player.UseFlag = false;//�Q�[���I�[�o�[�������̓��C�t-1
					}
					//�v���C���[�E�E�g�Q�u���b�N��
					if (g_Player.Position.x - g_Player.size.x / 2 < (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
						g_Player.oldpos.x - g_Player.size.x / 2 >= (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2)
					{
						g_Player.Position.x = (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 + g_Player.size.x / 2;
						//g_Player.UseFlag = false;//�Q�[���I�[�o�[�������̓��C�t-1
					}

					//�v���C���[��E�g�Q�u���b�N��
					if (g_Player.Position.x + g_Player.size.x / 2 > (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 &&
						g_Player.oldpos.y + g_Player.size.y / 2 <= (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2)
					{
						g_Player.Position.y = (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 - g_Player.size.y / 2;
						g_Player.UseFlag = false;//�Q�[���I�[�o�[�������̓��C�t-1
						SetScene(SCENE_RESULT);
					}
					//�v���C���[���E�g�Q�u���b�N��,
					if (g_Player.Position.x + g_Player.size.x / 2 > (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2 &&
						g_Player.oldpos.y - g_Player.size.y / 2 >= (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2)
					{
						g_Player.Position.y = (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2 + g_Player.size.y / 2;
						//g_Player.UseFlag = false;//�Q�[���I�[�o�[�������̓��C�t-1
					}
				}
			}


			g_Player.CoolTime--;

			if (g_Player.CoolTime < 0)
			{
				g_Player.CoolTime = 0;

				//�v���C���[�E���[�v�@�����蔻��
				for (int i = 0; i < BLOCK_MAX; i++)
				{
					WARP* warp = GetWarp();
					if ((warp + i)->UseFlag == true)
					{
						if (g_Player.Position.x + g_Player.size.x / 2 > (warp + i)->Position.x - (warp + i)->Size.x / 2 &&
							g_Player.Position.x - g_Player.size.x / 2 < (warp + i)->Position.x + (warp + i)->Size.x / 2 &&
							g_Player.Position.y + g_Player.size.y / 2 > (warp + i)->Position.y - (warp + i)->Size.y / 2 &&
							g_Player.Position.y - g_Player.size.y / 2 < (warp + i)->Position.y + (warp + i)->Size.y / 2)
						{
							if (i % 2 == 0)
							{
								if (!g_Player.WarpFlag)
								{
									g_Player.Position = (warp + i + 1)->Position;
									g_Player.CoolTime = PLAYER_COOLTIME;
									g_Player.WarpFlag = true;
								}

							}
							else if (i % 2 == 1)
							{
								if (!g_Player.WarpFlag)
								{
									g_Player.Position = (warp + i - 1)->Position;
									g_Player.CoolTime = PLAYER_COOLTIME;

									g_Player.WarpFlag = true;

								}
							}
						}
					}
				}
			}



			if (GetKeyboardTrigger(DIK_R))	//a�L�[�������ꂽ��
			{
				ResetGame();
			}

			//�v���C���[�ƃp�Y���̉�ʊO����

			Piece* pPiece = GetPiece();

			for (int i = 0; i < PUZZLE_MAX; i++)
			{
				if (pPiece[i].UseFlag)
				{
					bool hitflag = CollisionBB(g_Player.Position, pPiece[i].pos, g_Player.size, pPiece[i].size);

					if (hitflag)
					{
						if (g_Player.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, UP);

							if (!hitflag2)
							{
								g_Player.sp.y += 0.2;//����
							}
							else
							{
								g_Player.fall = true;
								g_Player.sp.y = 0;
								//g_Player.getfall = true;
								g_Player.frame = 50;
								//g_Player.sp.y += 0.2;//����
							}
						}
						else if (g_Player.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
						{

							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, RIGHT);

  							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//����
							}
							else
							{
								g_Player.Position.x = g_Player.oldpos.x;
							}


						}
						else if (g_Player.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, LEFT);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//����
							}
							else
							{
 								g_Player.Position.x = g_Player.oldpos.x;
							}


						}

					}
				}


			}


		}
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawPlayer()
{
	if (g_Player.UseFlag == true)
	{
		//�e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.texno));
		//�X�v���C�g��\��
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_Player.Position.x, g_Player.Position.y, g_Player.size.x, g_Player.size.y, g_Player.rot, g_Player.col, g_Player.PaternNo, g_Player.uv_w, g_Player.uv_h, g_Player.NumPatern);
	}
}

//=============================================================================
//�Q�b�g�֐�
//=============================================================================
PLAYER* GetPlayer()
{
	return &g_Player;
}