//=============================================================================
//
//	エネミー処理[enemy.cpp]
//															Author:	
//															Date:	
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#include "enemy.h"
#include "renderer.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "bullet.h"
#include "xkeyboard.h"
#include "collision.h"
#include "sound.h"
#include"cursor.h"

static ENEMY g_Enemy[ENEMY_MAX];

static ID3D11ShaderResourceView* g_EnemyTexture;	//画像一枚で一つの変数が必要
static char* g_EnemyTextureName = (char*)"data\\texture\\敵.png";	//テクスチャファイルパス

//エネミーSE
static int g_EnemySoundNo = 0;
static char g_EnemySoundName[] = "data\\SoundData\\SE\\タイプライター.wav";

BULLET* bullet = GetBullet();

HRESULT InitEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_Enemy[i].pos = D3DXVECTOR2(300.0f, 400.0f);
		g_Enemy[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy[i].sp = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Enemy[i].index = -1;
		g_Enemy[i].BulletWait = 110;
		g_Enemy[i].texno = LoadTexture(g_EnemyTextureName);
		g_Enemy[i].dir = ENEMY_DIRECTION::DIRECTION_LEFT;
		g_Enemy[i].UseFlag = false;
		g_Enemy[i].AIFlag = false;
		g_Enemy[i].PaternNo = 0.0f;
		g_Enemy[i].uv_w = -1.0f;
		g_Enemy[i].uv_h = 1.0f;
		g_Enemy[i].NumPatern = 1;
		g_EnemySoundNo = LoadSound(g_EnemySoundName);
	}
	return S_OK;
}

void UninitEnemy() {
	if (g_EnemyTexture != NULL){
		g_EnemyTexture->Release();
		g_EnemyTexture=NULL;
		StopSound(g_EnemySoundNo);
	}
}



void UpdateEnemy() {

	CURSOR* pCursor = GetCurso();		//  カーソル
	if (!pCursor->bHave)
	{


		for (int i = 0; i < ENEMY_MAX; i++) {
			if (g_Enemy[i].UseFlag) {

				switch (g_Enemy[i].dir)
				{
				case ENEMY_DIRECTION::DIRECTION_LEFT:
					g_Enemy[i].uv_w = -1.0f;
					break;
				case ENEMY_DIRECTION::DIRECTION_RIGHT:
					//g_Enemy[i].uv_w = 1.0f;

					break;
				default:
					break;
				}
				if (g_Enemy[i].AIFlag)
				{
					g_Enemy[i].BulletWait++;
					if (g_Enemy[i].BulletWait > 120)
					{
						switch (g_Enemy[i].dir)
						{
						case ENEMY_DIRECTION::DIRECTION_LEFT:
							SetBullet(g_Enemy[i].pos, D3DXVECTOR2(BULLET_SIZE_W, BULLET_SIZE_H), D3DXVECTOR2(-BULLET_SPEED, 0.0f));
							break;
						case ENEMY_DIRECTION::DIRECTION_RIGHT:
							SetBullet(g_Enemy[i].pos, D3DXVECTOR2(BULLET_SIZE_W, BULLET_SIZE_H), D3DXVECTOR2(BULLET_SPEED, 0.0f));

							break;
						case ENEMY_DIRECTION::DIRECTION_UP:
							SetBullet(g_Enemy[i].pos, D3DXVECTOR2(BULLET_SIZE_W, BULLET_SIZE_H), D3DXVECTOR2(0.0f, BULLET_SPEED));

							break;
						case ENEMY_DIRECTION::DIRECTION_DOWN:
							SetBullet(g_Enemy[i].pos, D3DXVECTOR2(BULLET_SIZE_W, BULLET_SIZE_H), D3DXVECTOR2(0.0f, -BULLET_SPEED));

							break;
						default:
							break;
						}



						g_Enemy[i].BulletWait = 0;

					}
				}

			}
		}
	}
}
void DrawEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_Enemy[i].UseFlag) {
			//SetWorldViewProjection2D();
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Enemy[i].texno));
			SpriteDrawColorRotation(
				g_Enemy[i].pos.x,
				g_Enemy[i].pos.y,
				-0.1f,
				g_Enemy[i].size.x,
				g_Enemy[i].size.y,
				g_Enemy[i].rot,
				g_Enemy[i].color,
				g_Enemy[i].PaternNo,
				g_Enemy[i].uv_w,
				g_Enemy[i].uv_h,
				g_Enemy[i].NumPatern
			);
		}
	}
}
void SetEnemy(D3DXVECTOR2 pos, D3DXVECTOR2 size,int direction, int index, ENEMY_DIRECTION d) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!g_Enemy[i].UseFlag) {
			if (d==ENEMY_DIRECTION::DIRECTION_LEFT)
			{
				switch (direction) {
				case 0:g_Enemy[i].rot = direction * 90;
					g_Enemy[i].dir = ENEMY_DIRECTION::DIRECTION_RIGHT;

					break;
				case 1:g_Enemy[i].rot = (direction + 2) * 90;
					g_Enemy[i].dir = ENEMY_DIRECTION::DIRECTION_DOWN;

					break;
				case 2:g_Enemy[i].rot = direction * 90;
					g_Enemy[i].dir = d;
					break;
				case 3:g_Enemy[i].rot = (direction - 2) * 90;
					g_Enemy[i].dir = ENEMY_DIRECTION::DIRECTION_UP;

					break;
				default:
					break;
				}

			}
			if (d == ENEMY_DIRECTION::DIRECTION_RIGHT)
			{
				switch (direction) {
				case 0:g_Enemy[i].rot = direction * 90;
					g_Enemy[i].dir = ENEMY_DIRECTION::DIRECTION_LEFT;

					break;
				case 1:g_Enemy[i].rot = (direction + 2) * 90;
					g_Enemy[i].dir = ENEMY_DIRECTION::DIRECTION_UP;

					break;
				case 2:g_Enemy[i].rot = direction * 90;
					g_Enemy[i].dir = d;
					break;
				case 3:g_Enemy[i].rot = (direction - 2) * 90;
					g_Enemy[i].dir = ENEMY_DIRECTION::DIRECTION_DOWN;


					break;
				default:
					break;
				}

			}

			switch (direction) {
			case 0:g_Enemy[i].rot = direction * 90;
				break;
			case 1:g_Enemy[i].rot = (direction - 2) * 90;
				break;
			case 2:g_Enemy[i].rot = direction * 90;
				break;
			case 3:g_Enemy[i].rot = (direction + 2) * 90;
				break;
			default:
				break;
			}
			g_Enemy[i].pos = pos;
			g_Enemy[i].size = size * 2.0f;
			g_Enemy[i].index = index;
			
			g_Enemy[i].UseFlag = true;
			break;
		}
	}
}
ENEMY* GetEnemy() {
	return g_Enemy;
}
void DeleteEnemy(int index) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_Enemy[i].UseFlag && g_Enemy[i].index == index) {
			g_Enemy[i].UseFlag = false;
		}
	}
}

