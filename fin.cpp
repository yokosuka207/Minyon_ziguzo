
#include "fin.h"
#include "sprite.h"
#include "texture.h"
#include "sound.h"

#include "xkeyboard.h"
#include "xinput.h"
#include "fade.h"
#include "scene.h"
#include "StoryKey.h"

static ID3D11ShaderResourceView* g_FinBGTexture;	//‰æ‘œˆê–‡‚Åˆê‚Â‚Ì•Ï”‚ª•K—v
static char* g_FinBGTextureName = (char*)"data\\texture\\fin.png";
static int g_FinBGTextureNo = 0;

static int g_FinSoundNo = 0;

static FIN g_FinBG;

void InitFin() {
	g_FinBG.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_FinBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_FinBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_FinBG.PaternNo = 0.0f;
	g_FinBG.uv_w = 1.0f / 1.0f;
	g_FinBG.uv_h = 1.0f / 1.0f;
	g_FinBG.NumPatern = 1;

	g_FinBGTextureNo = LoadTexture(g_FinBGTextureName);
	char filename[] = "data\\SoundData\\BGM\\Fin.wav";
	g_FinSoundNo = LoadSound(filename);
	PlaySound(g_FinSoundNo, -1);

	GetStoryKey()->HaveSKey++;
}
void UninitFin() {
	StopSound(g_FinSoundNo);
	if (g_FinBGTexture != NULL) {
		g_FinBGTexture->Release();
		g_FinBGTexture = NULL;
	}
}
void UpdateFin() {
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad B
		Keyboard_IsKeyTrigger(KK_SPACE)) {				// keyboard SPACE
		StartFade(FADE::FADE_ALPHA_OUT);
	}
}
void DrawFin() {
	SetWorldViewProjection2D();
	//”wŒi
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FinBGTextureNo));

		SpriteDrawColorRotation
		(
			g_FinBG.pos.x,
			g_FinBG.pos.y,
			0.0f,
			g_FinBG.size.x,
			g_FinBG.size.y,
			0.0f,
			g_FinBG.color,
			g_FinBG.PaternNo,
			g_FinBG.uv_w,
			g_FinBG.uv_h,
			g_FinBG.NumPatern
		);
	}
}

