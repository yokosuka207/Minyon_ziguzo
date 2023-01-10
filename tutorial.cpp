
#include "tutorial.h"
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
//#include	"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "scene.h"
#include "fade.h"
//======================
//マクロ定義
//=======================
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView* g_TutorialTexture = NULL;//テクスチャ情報
static	char* g_TutorialTextureName = (char*)"data\\texture\\ジグソーワールド.jpg";
static int g_TutorialTextureNo = 0;

static FADEPARAM* pFadeParam = GetFadeParam();

typedef	struct
{
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
}TUTORIAL;

TUTORIAL g_Tutorial;

void	InitTutorial() {
	//	テクスチャのロード
	g_TutorialTextureNo = LoadTexture(g_TutorialTextureName);
	if (g_TutorialTextureNo == -1){
		//読み込みエラー
		exit(999);	//強制終了
	}

	g_Tutorial.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	g_Tutorial.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_Tutorial.Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	g_Tutorial.Rotate = 0.0;
}
void	UninitTutorial() {
	if (g_TutorialTexture){
		g_TutorialTexture->Release();
		g_TutorialTexture = NULL;
	}
}
void	UpdateTutorial() {
	//キー入力のチェック
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
		Keyboard_IsKeyTrigger(KK_A))						// Keyboard	A
	{
		//SetScene(SCENE::SCENE_DATASELECT);
		StartFade(FADE::FADE_OUT);
	}
}
void	DrawTutorial() {
	//２Ｄ表示をするためのマトリクスを設定
	SetWorldViewProjection2D();
	//テクスチャのセット
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TutorialTextureNo));

	SpriteDrawColorRotation
	(
		g_Tutorial.Position.x,
		g_Tutorial.Position.y,
		0.0f,
		g_Tutorial.Size.x,
		g_Tutorial.Size.y,
		g_Tutorial.Rotate,
		g_Tutorial.Color,
		0,
		1.0f,
		1.0f,
		1
	);
}
