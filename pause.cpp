
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
#include	"input.h"
#include	"scene.h"
#include	"result.h"
#include	"mouse.h"
#include	"time.h"
#include	 "pause.h"

//======================
//マクロ定義
//=======================
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView* g_PauseTexture = NULL;//テクスチャ情報
static	char* g_PauseTextureName = (char*)"data\\texture\\ポーズ.png";

static	ID3D11ShaderResourceView* g_PauseEndTexture = NULL;//テクスチャ情報
static	char* g_PauseEndTextureName = (char*)"data\\texture\\再開.jpg";

PAUSE	PauseObject[4];//タイトル画面オブジェクト

int		PauseTextureNo = 0;//テクスチャ番号
int		PauseEndTextureNo = 0;//テクスチャ番号

static bool		PauseFlag;
static Time		g_Time;
//======================
//初期化
//======================
void	InitPause()
{
	//	テクスチャのロード
	PauseTextureNo = LoadTexture(g_PauseTextureName);
	//if (PauseTextureNo == -1)
	//{//読み込みエラー
	//	exit(999);	//強制終了
	//}
	PauseEndTextureNo = LoadTexture(g_PauseEndTextureName);
	//if (PauseEndTextureNo == -1)
	//{//読み込みエラー
	//	exit(999);	//強制終了
	//}

	PauseObject[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	PauseObject[0].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	PauseObject[0].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[0].Rotate = 0.0;

	PauseObject[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	PauseObject[1].Size = D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
	PauseObject[1].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[1].Rotate = 0.0;


	PauseFlag = false;
}
//======================
//終了処理
//======================
void	UninitPause()
{
	if (g_PauseTexture)
	{
		g_PauseTexture->Release();
		g_PauseTexture = NULL;
	}


	if (g_PauseEndTexture)
	{
		g_PauseTexture->Release();
		g_PauseTexture = NULL;
	}

}

//======================
//更新処理
//======================
void	UpdatePause()
{
	if (PauseFlag) {
		MOUSE* pMouse = GetMouse();
		D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// マウスの座標

		D3DXVECTOR2 min, max;		// min左上, max右下
		min = D3DXVECTOR2(PauseObject[1].Position.x - PauseObject[1].Size.x / 2, PauseObject[1].Position.y - PauseObject[1].Size.y / 2);
		max = D3DXVECTOR2(PauseObject[1].Position.x + PauseObject[1].Size.x / 2, PauseObject[1].Position.y + PauseObject[1].Size.y / 2);

		//キー入力のチェック

		if (IsMouseLeftPressed())
		{
			if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y)
			{
				//g_Time.PuaseEndTime();
				//SetScene(SCENE::SCENE_GAME);
				PauseFlag = false;
			}
		}
	}
}
//======================
//描画処理
//======================
void	DrawPause()
{
	//２Ｄ表示をするためのマトリクスを設定
	SetWorldViewProjection2D();
	//テクスチャのセット


	//スプライトの描画
	
	//シーン画面
	if (PauseFlag)
	{


		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseTextureNo));
		SpriteDrawColorRotation
		(
			PauseObject[0].Position.x,
			PauseObject[0].Position.y,
			-0.0f,
			PauseObject[0].Size.x,
			PauseObject[0].Size.y,
			PauseObject[0].Rotate,
			PauseObject[0].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		//再開ボタン
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseEndTextureNo));
		SpriteDrawColorRotation
		(
			PauseObject[1].Position.x,
			PauseObject[1].Position.y,
			0.0f,
			PauseObject[1].Size.x,
			PauseObject[1].Size.y,
			PauseObject[1].Rotate,
			PauseObject[1].Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}
}


//void SetPause(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col)
//{
//	PauseObject[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
//	PauseObject[0].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
//	PauseObject[0].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
//	PauseObject[0].Rotate = 0.0;
//
//	PauseObject[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
//	PauseObject[1].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
//	PauseObject[1].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
//	PauseObject[1].Rotate = 0.0;
//}
bool* GetPause() {
	return &PauseFlag;
}