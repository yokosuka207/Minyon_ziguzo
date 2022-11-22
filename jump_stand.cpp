
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "jump_stand.h"
#include "player.h"
#include "collision.h"
#include "block.h"
#include "puzzle.h"

static JUMPSTAND g_JumpStand;
static PLAYER* p_Player;
static BLOCK* p_Block;

static ID3D11ShaderResourceView* g_textureBlock;	//画像一枚で一つの変数が必要
static char* g_textureName_Block= (char*)"data\\texture\\JumpStand.jpg";	//テクスチャファイルパス
static int	  g_TextureNo = 0;	//プレイヤー用テクスチャの識別子

HRESULT InintJumpStand()
{
	p_Player = GetPlayer();

	g_TextureNo = LoadTexture(g_textureName_Block);

	g_JumpStand.pos = D3DXVECTOR2(330.0f, 245.0f);
	g_JumpStand.size = D3DXVECTOR2(JUMPSTAND_SIZE, JUMPSTAND_SIZE);
	
	g_JumpStand.UseJumpStand = true;
	g_JumpStand.JumpStandFlag = false;

	return S_OK;
}

void UninitJumoStand()
{
	if (g_textureBlock)
	{
		g_textureBlock->Release();
		g_textureBlock= NULL;
	}
}

void UpdateJumpStand()
{
	g_JumpStand.oldpos = g_JumpStand.pos;

	if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand.pos.x - g_JumpStand.size.x / 2 &&
		p_Player->oldpos.x + p_Player->size.x / 2 <= g_JumpStand.pos.x - g_JumpStand.size.x / 2 &&
		p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand.pos.y - g_JumpStand.size.y / 2 &&
		p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand.pos.y + g_JumpStand.size.y / 2)
	{
		g_JumpStand.sp = p_Player->sp;
		g_JumpStand.pos.x += g_JumpStand.sp.x;
	}
	//プレイヤー右・壊れるブロック左
	if (p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand.pos.x + g_JumpStand.size.x / 2 &&
		p_Player->oldpos.x - p_Player->size.x / 2 >= g_JumpStand.pos.x + g_JumpStand.size.x / 2 &&
		p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand.pos.y - g_JumpStand.size.y / 2 &&
		p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand.pos.y + g_JumpStand.size.y / 2)
	{
		g_JumpStand.sp = p_Player->sp;
		g_JumpStand.pos.x += g_JumpStand.sp.x;
	}

	if (p_Player->GetJumpStand)
	{
		g_JumpStand.sp = p_Player->sp;
		g_JumpStand.pos.x += g_JumpStand.sp.x;
	}

	else
	{
		g_JumpStand.pos.y++;

		p_Block = GetBlock();

		for (int i = 0; i < BLOCK_MAX; i++)
		{
			if ((p_Block + i)->UseFlag) 
			{
				if (g_JumpStand.pos.x + g_JumpStand.size.x / 2 >= (p_Block + i)->Position.x - (p_Block + i)->Size.x / 2 &&
					g_JumpStand.pos.x - g_JumpStand.size.x / 2 <= (p_Block + i)->Position.x + (p_Block + i)->Size.x / 2 &&
					g_JumpStand.pos.y + g_JumpStand.size.y / 2 >= (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2 &&
					g_JumpStand.pos.y + g_JumpStand.size.y / 2 <= (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2)
				{
					g_JumpStand.pos.y--;
				}
				
			}
		}
	}

	if (g_JumpStand.UseJumpStand) 
	{

		if (Collition_JumpStand())
		{
			g_JumpStand.JumpStandFlag = true;

			g_JumpStand.JumpPower = 17.0f;
			g_JumpStand.JumpGravity = 0.2f;
		}

		if (g_JumpStand.JumpStandFlag)
		{
			if (g_JumpStand.JumpPower > -10.0f)
			{
				g_JumpStand.JumpPower -= g_JumpStand.JumpGravity;
			}
			p_Player->Position.y -= g_JumpStand.JumpPower;

			for (int i = 0; i < BLOCK_MAX; i++)
			{
				p_Player = GetPlayer();
				p_Block = GetBlock();

				if ((p_Block + i)->UseFlag)
				{
					//上
					if (p_Player->Position.x + p_Player->size.x / 2 >= (p_Block + i)->Position.x - (p_Block + i)->Size.x / 2 &&
						p_Player->Position.x - p_Player->size.x / 2 <= (p_Block + i)->Position.x + (p_Block + i)->Size.x / 2 &&
						p_Player->Position.y + p_Player->size.y / 2 >= (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2 &&
						p_Player->oldpos.y + p_Player->size.y / 2 <= (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2)
					{
						p_Player->Position.y = (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2 - p_Player->size.y / 2;
						g_JumpStand.JumpStandFlag = false;
						g_JumpStand.JumpPower = 0.0f;
					}
				}
			}
		}
	}
}

void DrawJumpStand()
{
	if (g_JumpStand.UseJumpStand)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNo));

		SpriteDrawColorRotation(g_JumpStand.pos.x, g_JumpStand.pos.y,
			g_JumpStand.size.x, g_JumpStand.size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0, 1.0f, 1.0f, 1);
	}
}

void SetJumpStand(D3DXVECTOR2 p)
{
	if (!g_JumpStand.UseJumpStand)
	{
		g_JumpStand.pos = p;
		g_JumpStand.size = D3DXVECTOR2(JUMPSTAND_SIZE, JUMPSTAND_SIZE);

		g_JumpStand.UseJumpStand = true;
		g_JumpStand.JumpStandFlag = false;
	}
}

JUMPSTAND* GetJumpStand()
{
	return &g_JumpStand;
}

bool Collition_JumpStand()
{
	p_Player = GetPlayer();
	p_Block= GetBlock();

	//プレイヤー左・壊れるブロック右
	if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand.pos.x - g_JumpStand.size.x / 2 &&
		p_Player->oldpos.x + p_Player->size.x / 2 <= g_JumpStand.pos.x - g_JumpStand.size.x / 2 &&
		p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand.pos.y - g_JumpStand.size.y / 2 &&
		p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand.pos.y + g_JumpStand.size.y / 2)
	{
		p_Player->Position = p_Player->oldpos;
	}
	//プレイヤー右・壊れるブロック左
	if (p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand.pos.x + g_JumpStand.size.x / 2 &&
		p_Player->oldpos.x - p_Player->size.x / 2 >= g_JumpStand.pos.x + g_JumpStand.size.x / 2 &&
		p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand.pos.y - g_JumpStand.size.y / 2 &&
		p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand.pos.y + g_JumpStand.size.y / 2)
	{
		p_Player->Position = p_Player->oldpos;
	}

	//プレイヤー下・壊れるブロック上
	if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand.pos.x - g_JumpStand.size.x / 2 &&
		p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand.pos.x + g_JumpStand.size.x / 2 &&
		p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand.pos.y - g_JumpStand.size.y / 2 &&
		p_Player->oldpos.y + p_Player->size.y / 2 <= g_JumpStand.pos.y - g_JumpStand.size.y / 2)
	{
		return true;
	}

	return false;
}

void DeletejumpStand(int PieceNo) {
	//配列にしないと全部消えることになる
	if (g_JumpStand.UseJumpStand) {
		g_JumpStand.UseJumpStand = false;
	}
}

//bool Player_Push_JumpStand()
//{
//
//}
