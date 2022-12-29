/*==============================================================================

   �t�F�[�h�Ǘ� [fade.cpp]
														 Author : ���؁@��
														 Date   : 2022/12/27
--------------------------------------------------------------------------------

==============================================================================*/

#include "fade.h"
#include "sprite.h"
#include "texture.h"
#include "renderer.h"
#include "scene.h"

static ID3D11ShaderResourceView* g_FadeTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_FadeTextureName = (char*)"data\\texture\\fade_puzzle.png";	//�e�N�X�`���t�@�C���p�X

static FADEPARAM g_FadeParam;

void InitFade() {
	g_FadeParam.TexNo = LoadTexture(g_FadeTextureName);
	g_FadeParam.alpha = 0.0f;
	g_FadeParam.state = FADE::FADE_NONE;
	g_FadeParam.FadeFlag = false;
	g_FadeParam.ExceptFlag = false;

	g_FadeParam.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_FadeParam.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_FadeParam.rot = 0.0f;
	g_FadeParam.PaternNo = 0;
	g_FadeParam.uv_w = 1.0f / 1.0f;
	g_FadeParam.uv_h = 1.0f / 1.0f;
	g_FadeParam.NumPatern = 1;
	StartFade(FADE::FADE_IN);
}
void UninitFade() {
	if (g_FadeTexture != NULL) {
		g_FadeTexture->Release();
		g_FadeTexture = NULL;
	}
}
void UpdateFade() {
	if (g_FadeParam.state == FADE::FADE_OUT) {
		g_FadeParam.alpha += FADE_SPEED;

		if (g_FadeParam.alpha >= 1.0f) {
			g_FadeParam.alpha = 1.0f;
			g_FadeParam.state = FADE::FADE_IN;

			switch (*GetScene()) {
			case SCENE::SCENE_NONE:
				break;
			case SCENE::SCENE_TITLE:
				//�������Ȃ��Ƃ��̓t�F�[�h����
				if (g_FadeParam.ExceptFlag) {
					SetScene(SCENE::SCENE_DATASELECT);
				}
				break;
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
				//continue��
				if (g_FadeParam.ExceptFlag) {
					SetScene(SCENE::SCENE_GAME);
				}
				//�ʏ�
				else {
					SetScene(SCENE::SCENE_TITLE);
				}
				break;
			default:
				break;
			}
			g_FadeParam.FadeFlag = false;
		}
	}

	if (g_FadeParam.state == FADE::FADE_IN) {
		g_FadeParam.alpha -= FADE_SPEED;

		if (g_FadeParam.alpha <= 0.0f) {
			g_FadeParam.alpha = 0.0f;
			g_FadeParam.state = FADE::FADE_NONE;
		}
		g_FadeParam.FadeFlag = false;
	}
}
void DrawFade() {
	SetWorldViewProjection2D();

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FadeParam.TexNo));
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
		}
		if (g_FadeParam.state == FADE::FADE_OUT) {
			g_FadeParam.alpha = 0.0f;
		}
		g_FadeParam.FadeFlag = true;
	}
}
FADEPARAM* GetFadeParam() {
	return &g_FadeParam;
}
