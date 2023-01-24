
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "jump_stand.h"
#include "player.h"
#include "collision.h"
#include "block.h"
#include "puzzle.h"
#include "MapChip.h"
#include"mouse.h"
#include"sound.h"
#include"cursor.h"

//-------配列にしてほしい↓（マップチップの都合上必要）-------
static JUMPSTAND g_JumpStand[JUMPSTAND_MAX];
//------------------------------------------------------------
static PLAYER* p_Player;
static BLOCK* p_Block;

static ID3D11ShaderResourceView* g_textureBlock;	//画像一枚で一つの変数が必要
//static char* g_textureName_Block= (char*)"data\\texture\\JumpStand.jpg";	//テクスチャファイルパス
static char* g_textureName_Block = (char*)"data\\texture\\jumpstand.png";	//テクスチャファイルパス
static int	  g_TextureNo = 0;	//プレイヤー用テクスチャの識別子

//ジャンプスタンド音
static int g_JumpStandSoundNo = 0;
static char g_JumpStandSoundName[] = "data\\SoundData\\SE\\革靴で歩く右.wav";
//ジャンプスタンド運ぶ（引きずる音）
static int g_JumpStandSoundMoveNo = 0;
static char g_JumpStandSoundMoveName[] = "data\\SoundData\\SE\\引きずる音(要編集).wav";
static int g_JumpStandLandingSoundNo = 0;
static char g_JumpStandLandingSoundName[] = "data\\SoundData\\SE\\物の落下音(無料効果音で遊ぼう！).wav";



HRESULT InitJumpStand()
{
	p_Player = GetPlayer();
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		g_TextureNo = LoadTexture(g_textureName_Block);

		g_JumpStand[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_JumpStand[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_JumpStand[i].rot = 0.0f;
		g_JumpStand[i].PieceIndex = -1;
		g_JumpStand[i].NowPieceIndex = -1;

		g_JumpStand[i].UseJumpStand = false;
		g_JumpStand[i].JumpStandFlag = false;

		g_JumpStand[i].JumpStandFlag = false;

		g_JumpStand[i].JumpStandNotMove = true;
		g_JumpStand[i].LookFlag = false;

		g_JumpStandSoundNo = LoadSound(g_JumpStandSoundName);
		g_JumpStandSoundMoveNo = LoadSound(g_JumpStandSoundMoveName);
		g_JumpStandLandingSoundNo = LoadSound(g_JumpStandLandingSoundName);
	}
	return S_OK;
}

void UninitJumpStand()
{
	if (g_textureBlock)
	{
		g_textureBlock->Release();
		g_textureBlock = NULL;
	}

	StopSound(g_JumpStandSoundNo);
	StopSound(g_JumpStandSoundMoveNo);
	StopSound(g_JumpStandLandingSoundNo);
}

void UpdateJumpStand()
{
	//BLOCK* pCipBlock = GetChipBlock();
	MOUSE* pMouse = GetMouse();
	p_Player = GetPlayer();
	p_Block = GetChipBlock();

	if (!Mouse_IsLeftDown())
	{


		for (int i = 0; i < JUMPSTAND_MAX; i++)
		{
			if (g_JumpStand[i].UseJumpStand)
			{
				g_JumpStand[i].oldoldpos = g_JumpStand[i].oldpos;
				g_JumpStand[i].oldpos = g_JumpStand[i].pos;

				if (g_JumpStand[i].rot == 90 || g_JumpStand[i].rot == 270) {
					g_JumpStand[i].rot = 180.0f;
				}
				//ジャンプ台右・プレイヤー左
				if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
					p_Player->oldpos.x + p_Player->size.x / 2 <= g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
					p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
					p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
				{
					p_Player->Position.x = g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 - p_Player->size.x / 2;
					//g_JumpStand[i].sp = p_Player->sp;
					//g_JumpStand[i].pos.x += g_JumpStand[i].sp.x;
					//SetVolume(g_JumpStandSoundMoveNo, 0.5f);
					//PlaySound(g_JumpStandSoundMoveNo, 0);
				}
				//プレイヤー右・ジャンプ台左
				if (p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
					p_Player->oldpos.x - p_Player->size.x / 2 >= g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
					p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
					p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
				{
					p_Player->Position.x = g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 + p_Player->size.x / 2;
					//g_JumpStand[i].sp = p_Player->sp;
					//g_JumpStand[i].pos.x += g_JumpStand[i].sp.x;
					//SetVolume(g_JumpStandSoundMoveNo, 0.5f);
					//PlaySound(g_JumpStandSoundMoveNo, 0);
				}


				if (g_JumpStand[i].GetJumpStand)//ジャンプ台を持った時
				{
					g_JumpStand[i].sp = p_Player->sp;
					g_JumpStand[i].pos.x += g_JumpStand[i].sp.x;

					//引きずる音
					if (g_JumpStand[i].oldpos.x != g_JumpStand[i].pos.x && g_JumpStand[i].JumpStandNotMove == true)//動かした瞬間
					{
						//SetVolume(g_JumpStandSoundMoveNo, 0.5f);
						PlaySound(g_JumpStandSoundMoveNo, -1);
						g_JumpStand[i].JumpStandNotMove = false;
					}
				}
				if (g_JumpStand[i].oldpos.x == g_JumpStand[i].pos.x)//動かしてない時
				{
					g_JumpStand[i].JumpStandNotMove = true;
					StopSound(g_JumpStandSoundMoveNo);
				}

				{
					g_JumpStand[i].pos.y--;


					p_Block = GetChipBlock();

					for (int j = 0; j < BLOCK_CHIP_MAX; j++)
					{
						if ((p_Block + j)->UseFlag)
						{
							if (g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2 &&
								g_JumpStand[i].oldpos.y - g_JumpStand[i].size.y / 2 >= (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
							{
								g_JumpStand[i].pos.y = g_JumpStand[i].oldpos.y;
								g_JumpStand[i].NowPieceIndex = p_Block[j].PieceIndex;
								if (!g_JumpStand[i].LookFlag)
								{
									//着地した瞬間だけ音が鳴る,ピースが空き領域に設置されたかどうかをとりたい
									if (g_JumpStand[i].oldoldpos.y != g_JumpStand[i].pos.y)//着地の瞬間
									{
										SetVolume(g_JumpStandLandingSoundNo, 0.5f);
										PlaySound(g_JumpStandLandingSoundNo, 0);
									}
								}
								g_JumpStand[i].LookFlag = false;
							}
							if (g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].oldpos.x + g_JumpStand[i].size.x / 2 <= (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 > (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2 &&
								g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
							{
								g_JumpStand[i].pos.x = g_JumpStand[i].oldpos.x;
							}
							if (g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].oldpos.x - g_JumpStand[i].size.x / 2 >= (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 > (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2 &&
								g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
							{
								g_JumpStand[i].pos.x = g_JumpStand[i].oldpos.x;
							}


						}
					}




					//プレイヤー下・上jumpstand
					if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
						p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
						p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 &&
						p_Player->oldpos.y - p_Player->size.y / 2 >= g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
					{
						g_JumpStand[i].JumpStandFlag = true;

						SetVolume(g_JumpStandSoundNo, 1.5f);
						PlaySound(g_JumpStandSoundNo, 0);

						p_Player->sp.y = 0.0f;
						g_JumpStand[i].JumpPower = 4.8f;
						//p_Player->sp.y = 5.0f;
						g_JumpStand[i].JumpGravity = 0.1f;
						
					}

					if (g_JumpStand[i].JumpStandFlag)
					{
						//p_Player->sp.y = 0.0f;

						if (g_JumpStand[i].JumpPower > -10.0f)
						{
							g_JumpStand[i].JumpPower -= g_JumpStand[i].JumpGravity;
							
						}
						p_Player->Position.y += g_JumpStand[i].JumpPower;
						//p_Player->Position.y -= p_Player->sp.y;


						for (int j = 0; j < BLOCK_CHIP_MAX; j++)
						{

							if ((p_Block + j)->UseFlag)
							{
								//上
								if (p_Player->Position.x + p_Player->size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
									p_Player->Position.x - p_Player->size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
									p_Player->Position.y - p_Player->size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2 &&
									p_Player->oldpos.y - p_Player->size.y / 2 >= (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
								{
									g_JumpStand[i].JumpPower = 0.0f;
									p_Player->sp.y = 0.0f;
									//g_JumpStand[i].JumpGravity = 0.0f;
									p_Player->Position.y = (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2 + p_Player->size.y / 2;
									g_JumpStand[i].JumpStandFlag = false;
								}
								//↓
								if (p_Player->Position.x + p_Player->size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
									p_Player->Position.x - p_Player->size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
									p_Player->Position.y + p_Player->size.y / 2 > (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2 &&
									p_Player->oldpos.y + p_Player->size.y / 2 <= (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2)
								{
									g_JumpStand[i].JumpPower = 0.0f;
									p_Player->sp.y = 0.0f;
									//g_JumpStand[i].JumpGravity = 0.0f;
									p_Player->Position.y = (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2 - p_Player->size.y / 2;
									g_JumpStand[i].JumpStandFlag = false;

								}
							}
						}

					}

				}
			}
		}
	}
}

void DrawJumpStand()
{
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		if (g_JumpStand[i].UseJumpStand)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNo));

			SpriteDrawColorRotation(g_JumpStand[i].pos.x, g_JumpStand[i].pos.y,-0.1f,
				g_JumpStand[i].size.x, g_JumpStand[i].size.y, g_JumpStand[i].rot, D3DXCOLOR(3.0f, 0.0f, 0.0f, 1.0f),
				0, 1.0f, 1.0f, 1);
		}
	}
}

JUMPSTAND* GetJumpStand()
{
	return g_JumpStand;
}

//bool Collition_JumpStand()
//{
//	p_Player = GetPlayer();
//	//p_Block= GetBlock();
//	for (int i = 0; i < JUMPSTAND_MAX; i++)
//	{
//		if (g_JumpStand[i].UseJumpStand)
//		{
//
//
//			//プレイヤー左・壊れるブロック右
//			if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
//				p_Player->oldpos.x + p_Player->size.x / 2 <= g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
//				p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
//				p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
//			{
//				p_Player->Position = p_Player->oldpos;
//			}
//			//プレイヤー右・壊れるブロック左
//			if (p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
//				p_Player->oldpos.x - p_Player->size.x / 2 >= g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
//				p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
//				p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
//			{
//				p_Player->Position = p_Player->oldpos;
//			}
//
//			//プレイヤー下・壊れるブロック上
//			if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
//				p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
//				p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 &&
//				p_Player->oldpos.y - p_Player->size.y / 2 >= g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
//			{
//				return true;
//			}
//
//
//			return false;
//		}
//	}
//}

void SetJumpStand(D3DXVECTOR2 pos, D3DXVECTOR2 size,int direction, int PieceNo) {
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		if (!g_JumpStand[i].UseJumpStand) {
			switch (direction)
			{
			case 0:g_JumpStand[i].rot = (direction + 2) * 90;
				break;
			case 1:g_JumpStand[i].rot = direction * 90;
				break;
			case 2:g_JumpStand[i].rot = (direction - 2) * 90;
				break;
			case 3:g_JumpStand[i].rot = direction * 90;
				break;
			default:
				break;
			}
			g_JumpStand[i].pos = pos;
			//g_JumpStand[i].pos.y += 1.0f;
			g_JumpStand[i].size.x = size.x - 3.0f;
			g_JumpStand[i].size.y = size.y - 3.0f;

			g_JumpStand[i].PieceIndex = PieceNo;
			g_JumpStand[i].NowPieceIndex = PieceNo;
			g_JumpStand[i].UseJumpStand = true;
			break;
		}
	}
}

void DeleteJumpStand(int PieceNo) {
	//配列にしないとマップ上に存在するジャンプ台全部消えることになる
	//今消したいのは PieceNo番目 のピースに存在するジャンプ台のみ
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		if (g_JumpStand[i].UseJumpStand) {
			if (g_JumpStand[i].PieceIndex == PieceNo)
			{
				g_JumpStand[i].UseJumpStand = false;

			}
		}
	}
}

//bool Player_Push_JumpStand()
//{
//
//}
