/*==============================================================================

   フェード管理 [fade.cpp]
														 Author : 伏木　伶
														 Date   : 2022/12/27
--------------------------------------------------------------------------------

==============================================================================*/

#include "fade.h"
#include "sprite.h"
#include "texture.h"
#include "renderer.h"
#include "scene.h"
#include "StageSelect.h"
#include "goal.h"


static ID3D11ShaderResourceView* g_FadeTexture;	//画像一枚で一つの変数が必要
static char* g_FadeTextureName = (char*)"data\\texture\\puzzlepiece_item.png";	//テクスチャファイルパス
static char* g_FadeAlphaTextureName = (char*)"data\\texture\\black.png";	//テクスチャファイルパス

static FADEPARAM g_FadeParam;

void InitFade() {
	g_FadeParam.TexNo1 = LoadTexture(g_FadeTextureName);
	g_FadeParam.TexNo2 = LoadTexture(g_FadeAlphaTextureName);

	g_FadeParam.alpha = 0.0f;
	g_FadeParam.scaling = D3DXVECTOR2(SCREEN_WIDTH * 100, SCREEN_HEIGHT * 100);
	g_FadeParam.state = FADE::FADE_NONE;
	g_FadeParam.FadeFlag = false;
	g_FadeParam.ExceptFlag = false;

	g_FadeParam.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_FadeParam.size = D3DXVECTOR2(0.0f, 0.0f);
	g_FadeParam.rot = 0.0f;
	g_FadeParam.PaternNo = 0;
	g_FadeParam.uv_w = 1.0f / 1.0f;
	g_FadeParam.uv_h = 1.0f / 1.0f;
	g_FadeParam.NumPatern = 1;
	StartFade(FADE::FADE_ALPHA_IN);
}
void UninitFade() {
	if (g_FadeTexture != NULL) {
		g_FadeTexture->Release();
		g_FadeTexture = NULL;
	}
}
void UpdateFade() {
	if (g_FadeParam.state == FADE::FADE_OUT) {
		g_FadeParam.size -= D3DXVECTOR2(FADE_SPEED_X, FADE_SPEED_Y);
		if (g_FadeParam.size.x < SCREEN_WIDTH ||
			g_FadeParam.size.y < SCREEN_HEIGHT) {
			g_FadeParam.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
			g_FadeParam.state = FADE::FADE_IN;

			switch (*GetScene()) {
			case SCENE::SCENE_NONE:
				break;
			case SCENE::SCENE_TITLE:
				SetScene(SCENE::SCENE_DATASELECT);
				break;
			//case SCENE::SCENE_TUTORIAL:
			//	SetScene(SCENE::SCENE_DATASELECT);
			//	break;
			case SCENE::SCENE_DATASELECT:
				SetScene(SCENE::SCENE_STAGESELECT);
				break;
			case SCENE::SCENE_STAGESELECT:
				SetScene(SCENE::SCENE_GAME);
				break;
			case SCENE::SCENE_GAME:
				SetScene(SCENE::SCENE_RESULT);
				break;
			case SCENE::SCENE_RESULT:
				//continue時
				if (g_FadeParam.ExceptFlag) {
					SetScene(SCENE::SCENE_GAME);
				}
				//通常
				else {
					SetScene(SCENE::SCENE_STAGESELECT);
				}
				break;
			default:
				break;
			}
			g_FadeParam.FadeFlag = false;
		}
	}

	if (g_FadeParam.state == FADE::FADE_IN) {
		g_FadeParam.size += D3DXVECTOR2(FADE_SPEED_X, FADE_SPEED_Y);

		if (fabsf(g_FadeParam.size.x) >= fabsf(g_FadeParam.scaling.x) &&
			fabsf(g_FadeParam.size.y) >= fabsf(g_FadeParam.scaling.y)) {
			g_FadeParam.size = g_FadeParam.scaling;
			g_FadeParam.state = FADE::FADE_NONE;
			g_FadeParam.FadeFlag = false;
		}
	}

	if (g_FadeParam.state == FADE::FADE_ALPHA_OUT) {
		g_FadeParam.alpha += FADE_SPEED_ALPHA;
		if (g_FadeParam.alpha >= 1.0f) {
			g_FadeParam.alpha = 1.0f;
			g_FadeParam.state = FADE::FADE_ALPHA_IN;
			switch (*GetScene()) {
			case SCENE::SCENE_NONE:
				break;
			case SCENE::SCENE_TITLE:
				SetScene(SCENE::SCENE_DATASELECT);
				break;
			//case SCENE::SCENE_TUTORIAL:
			//	SetScene(SCENE::SCENE_DATASELECT);
			//	break;
			case SCENE::SCENE_DATASELECT:
				SetScene(SCENE::SCENE_STAGESELECT);
				break;
			case SCENE::SCENE_STAGESELECT:
				SetScene(SCENE::SCENE_GAME);
				break;
			case SCENE::SCENE_GAME:
				SetScene(SCENE::SCENE_RESULT);
				break;
			case SCENE::SCENE_RESULT:
				//continue時
				if (g_FadeParam.ExceptFlag) {
					SetScene(SCENE::SCENE_GAME);
				}
				//通常
				else {
					SetScene(SCENE::SCENE_STAGESELECT);
				}
				break;
			default:
				break;
			}
			g_FadeParam.FadeFlag = false;
		}
	}
	if (g_FadeParam.state == FADE::FADE_ALPHA_IN) {
		g_FadeParam.alpha -= FADE_SPEED_ALPHA;
		if (g_FadeParam.alpha <= 0.0f) {
			g_FadeParam.alpha = 0.0f;
			g_FadeParam.state = FADE::FADE_NONE;
			g_FadeParam.FadeFlag = false;
		}
	}
}
void DrawFade() {
	SetWorldViewProjection2D();
	if (g_FadeParam.state == FADE::FADE_IN || g_FadeParam.state == FADE::FADE_OUT || g_FadeParam.state == FADE::FADE_NONE) {
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FadeParam.TexNo1));
	}
	if (g_FadeParam.state == FADE::FADE_ALPHA_IN || g_FadeParam.state == FADE::FADE_ALPHA_OUT) {
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FadeParam.TexNo2));
	}


	SpriteDrawColorRotation(
		g_FadeParam.pos.x,
		g_FadeParam.pos.y,
		0.0f,
		g_FadeParam.size.x,
		g_FadeParam.size.y,
		g_FadeParam.rot,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, g_FadeParam.alpha),
		g_FadeParam.PaternNo,
		g_FadeParam.uv_w,
		g_FadeParam.uv_h,
		g_FadeParam.NumPatern
	);
}
void StartFade(FADE state) {
	if (!g_FadeParam.FadeFlag) {
		g_FadeParam.state = state;
		if (g_FadeParam.state == FADE::FADE_IN) {
			g_FadeParam.alpha = 1.0f;
			g_FadeParam.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		if (g_FadeParam.state == FADE::FADE_OUT) {
			SCENE* scene = GetScene();
			if (*scene == SCENE_STAGESELECT)//ステージセレクト画面のプレイヤーの位置にアイリスイン
			{ 
				PLAYER* player = GetSelectPlayer();
				g_FadeParam.pos = player->Position;
			}
			else//プレイ画面のゴールの位置にアイリスイン
			{ 
				GOAL* goal = GetGoal();
				g_FadeParam.pos = goal->Pos;
			}

			g_FadeParam.alpha = 1.0f;
			g_FadeParam.size = g_FadeParam.scaling;
		}
		if (g_FadeParam.state == FADE::FADE_ALPHA_IN) {
			g_FadeParam.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			g_FadeParam.alpha = 1.0f;
			g_FadeParam.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		if (g_FadeParam.state == FADE::FADE_ALPHA_OUT) {
			g_FadeParam.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			g_FadeParam.alpha = 0.0f;
			g_FadeParam.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		g_FadeParam.FadeFlag = true;
	}
}
FADEPARAM* GetFadeParam() {
	return &g_FadeParam;
}
