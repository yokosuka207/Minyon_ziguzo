
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include	"scene.h"
#include	"fade.h"
//======================
//マクロ定義
//=======================
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//テクスチャ情報
static	char	*g_TitleTextureName1 = (char*)"data\\texture\\タイトル背景＃２.png";

typedef	struct
{
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
}TITLE;

TITLE	TitleObject;//タイトル画面オブジェクト

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
	TitleObject.Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	TitleObject.Rotate = 0.0;

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
	}
}

//======================
//更新処理
//======================
void	UpdateTitle()
{
	//キー入力のチェック
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
		Keyboard_IsKeyTrigger(KK_A))						// Keyboard	A
	{
		//SetScene(SCENE::SCENE_DATASELECT);
		StartFade(FADE::FADE_ALPHA_OUT);
		
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


}



