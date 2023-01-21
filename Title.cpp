
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include	"scene.h"
#include	"fade.h"
#include"mouse.h"
#include"collision.h"
#include"sound.h"

//======================
//マクロ定義
//=======================
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//テクスチャ情報
static	char	*g_TitleTextureName1 = (char*)"data\\texture\\タイトル背景＃２.png";
static	ID3D11ShaderResourceView* g_TitleTextureButton = NULL;//テクスチャ情報
static	char* g_TitleButtonTextureName = (char*)"data\\texture\\start.jpg";

static	ID3D11ShaderResourceView* g_TitleTextureButton2 = NULL;//テクスチャ情報
static	char* g_TitleButtonTextureName2 = (char*)"data\\texture\\GameEnd_end_button.jpg";

//サウンド
static int g_ChangeSceneTitleSoundNo = 0;
static char g_ChangeSceneTitleSoundName[] = "data\\SoundData\\SE\\シーン遷移(魔王魂).wav";



typedef	struct
{
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
}TITLE;
typedef	struct
{
	D3DXVECTOR2		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	int texno;
}TITLE_SWITH;

TITLE	TitleObject;//タイトル画面オブジェクト
TITLE_SWITH g_TitleSwith[2];
int		TitleTextureNo1;//テクスチャ番号

//======================
//初期化
//======================
void	InitTitle()
{
	//	テクスチャのロード
	TitleTextureNo1 = LoadTexture(g_TitleTextureName1);
	if (TitleTextureNo1 == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}

	TitleObject.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	TitleObject.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	TitleObject.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	TitleObject.Rotate = 0.0f;


	g_TitleSwith[0].Position = D3DXVECTOR2(300.0f, 650.0f);
	g_TitleSwith[0].Size = D3DXVECTOR2(200.0f, 150.0f);
	g_TitleSwith[0].texno = LoadTexture(g_TitleButtonTextureName);

	g_TitleSwith[1].Position = D3DXVECTOR2(1100.0f, 650.0f);
	g_TitleSwith[1].Size = D3DXVECTOR2(200.0f, 150.0f);
	g_TitleSwith[1].texno = LoadTexture(g_TitleButtonTextureName2);

	g_ChangeSceneTitleSoundNo = LoadSound(g_ChangeSceneTitleSoundName);
}
//======================
//終了処理
//======================
void	UninitTitle()
{
	if (g_TitleTexture1)
	{
		g_TitleTexture1->Release();
		g_TitleTexture1 = NULL;
		StopSound(g_ChangeSceneTitleSoundNo);
	}
}

//======================
//更新処理
//======================
void	UpdateTitle()
{
	UpdateGameMouse();
	FADEPARAM* pFadeParam = GetFadeParam();
	//キー入力のチェック
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||			// GamePad	B
		Keyboard_IsKeyTrigger(KK_A))						// Keyboard	A
	{
		if (!pFadeParam->FadeFlag)
		{
			//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
			PlaySound(g_ChangeSceneTitleSoundNo, 0);
			//SetScene(SCENE::SCENE_DATASELECT);
			StartFade(FADE::FADE_ALPHA_OUT);
		}
	}
	D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// マウスの座標

	if (CollisionBB(g_TitleSwith[0].Position, MousePos, g_TitleSwith[0].Size, D3DXVECTOR2(3.0f, 3.0f)))
	{
		if (Mouse_IsLeftDown())
		{
			if (!pFadeParam->FadeFlag)
			{
				//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
				PlaySound(g_ChangeSceneTitleSoundNo, 0);
				StartFade(FADE::FADE_ALPHA_OUT);
			}
		}
	}
	if (CollisionBB(g_TitleSwith[1].Position, MousePos, g_TitleSwith[1].Size, D3DXVECTOR2(3.0f, 3.0f)))
	{
		if (Mouse_IsLeftDown())
		{
			DestroyWindow(GetHwnd());
		}
	}





}
//======================
//描画処理
//======================
void	DrawTitle()
{
	//２Ｄ表示をするためのマトリクスを設定
	SetWorldViewProjection2D();
	//テクスチャのセット
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TitleTextureNo1));
	}

	//スプライトの描画
	SpriteDrawColorRotation
	(
		TitleObject.Position.x,
		TitleObject.Position.y,
		0.0f,
		TitleObject.Size.x,
		TitleObject.Size.y,
		TitleObject.Rotate,
		TitleObject.Color,
		0,
		1.0f,
		1.0f,
		1
	);
	for (int i = 0; i < 2; i++)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TitleSwith[i].texno));

		SpriteDrawColorRotation(g_TitleSwith[i].Position.x, g_TitleSwith[i].Position.y,0.0f,
			g_TitleSwith[i].Size.x, g_TitleSwith[i].Size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f, 1);

	}

}



