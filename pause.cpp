
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include	"xinput.h"
#include	"xkeyboard.h"
#include	"scene.h"
#include	"result.h"
#include	"mouse.h"
#include	"time.h"
#include	 "pause.h"
#include	"game.h"
#include	"button.h"

//======================
//マクロ定義
//=======================
#define BUTTON_MAX	2

//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView* g_PauseTexture = NULL;//テクスチャ情報
static	char* g_PauseTextureName = (char*)"data\\texture\\セーブ画面背景.png";

static	ID3D11ShaderResourceView* g_PauseOperationTexture = NULL;//操作説明情報
static	char* g_PauseOperationTextureName = (char*)"data\\texture\\操作説明.png";

static	ID3D11ShaderResourceView* g_PauseEndTexture = NULL;//テクスチャ情報
static	char* g_PauseEndTextureName = (char*)"data\\texture\\Quit.png";

static	ID3D11ShaderResourceView* g_PauseSelectTexture = NULL;//テクスチャ情報
static	char* g_PauseSelectTextureName = (char*)"data\\texture\\Exit Stage.png";

PAUSE	PauseObject[5];//タイトル画面オブジェクト

int		PauseTextureNo = 0;			//テクスチャ番号
int		PauseOperationTextureNo = 0;//テクスチャ番号
int		PauseEndTextureNo = 0;		//テクスチャ番号
int		PauseSelectTextureNo = 0;	//テクスチャ番号

static bool		PauseFlag, PauseClick;

Button g_PauseButton[2];
Button* g_pSelectPauseButton = nullptr;
//======================
//初期化
//======================
void	InitPause()
{
	//	テクスチャのロード
	PauseTextureNo = LoadTexture(g_PauseTextureName);
	PauseOperationTextureNo = LoadTexture(g_PauseOperationTextureName);

	//背景テクスチャ
	PauseObject[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	PauseObject[0].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	PauseObject[0].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[0].Rotate = 0.0;

	//コントローラー
	PauseObject[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0);
	PauseObject[1].Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	PauseObject[1].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[1].Rotate = 0.0;

	//ゲームに戻る選択テクスチャ
	PauseObject[2].Position = D3DXVECTOR3(711 , 500.0f, 0);
	PauseObject[2].Size = D3DXVECTOR2(SCREEN_WIDTH / 4 / 3, SCREEN_HEIGHT / 4/ 3);
	PauseObject[2].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[2].Rotate = 0.0f;

	//ゲームリセット選択テクスチャ
	PauseObject[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	PauseObject[3].Size = D3DXVECTOR2(0, 0);
	PauseObject[3].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[3].Rotate = 0.0;

	//ゲーム選択画面に戻るテクスチャ
	PauseObject[4].Position = D3DXVECTOR3(711, 600, 0);
	PauseObject[4].Size = D3DXVECTOR2(SCREEN_WIDTH / 4 / 3, SCREEN_HEIGHT / 4 / 3);
	PauseObject[4].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[4].Rotate = 0.0f;


	PauseFlag = false;
	PauseClick = false;

	// ボタンのテクスチャのロード
	PauseEndTextureNo = LoadTexture(g_PauseEndTextureName);
	PauseSelectTextureNo = LoadTexture(g_PauseSelectTextureName);

	// ボタンのセット
	g_PauseButton[0].SetButton(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PauseEndTextureNo);
	g_PauseButton[1].SetButton(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PauseSelectTextureNo);

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

	if(g_PauseOperationTexture)
	{
		g_PauseOperationTexture->Release();
		g_PauseOperationTexture = NULL;
	}

	if (g_PauseEndTexture)
	{
		g_PauseEndTexture->Release();
		g_PauseEndTexture = NULL;
	}

	if (g_PauseSelectTexture)
	{
		g_PauseSelectTexture->Release();
		g_PauseSelectTexture = NULL;
	}

}

//======================
//更新処理
//======================
void	UpdatePause()
{
	if (PauseFlag) 
	{
		//MOUSE* pMouse = GetMouse();
		//D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// マウスの座標

		//D3DXVECTOR2 min1, max1, min2, max2;		// min左上, max右下
		
		////キー入力のチェック

		//min1 = D3DXVECTOR2(PauseObject[2].Position.x - PauseObject[2].Size.x / 2, PauseObject[2].Position.y - PauseObject[2].Size.y / 2);
		//max1 = D3DXVECTOR2(PauseObject[2].Position.x + PauseObject[2].Size.x / 2, PauseObject[2].Position.y + PauseObject[2].Size.y / 2);
		////	ゲームに戻ります
		//if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
		//	Keyboard_IsKeyTrigger(KK_L) ||						// Keyboard	L
		//	Mouse_IsLeftDown())									// Mouse	左
		//{
		//	if (min1.x < MousePos.x && max1.x > MousePos.x && min1.y < MousePos.y && max1.y > MousePos.y)
		//	{
		//		SetScene(SCENE::SCENE_GAME);
		//		PauseClick = true;
		//	}
		//}

		//min2 = D3DXVECTOR2(PauseObject[4].Position.x - PauseObject[4].Size.x / 2, PauseObject[4].Position.y - PauseObject[4].Size.y / 2);
		//max2 = D3DXVECTOR2(PauseObject[4].Position.x + PauseObject[4].Size.x / 2, PauseObject[4].Position.y + PauseObject[4].Size.y / 2);
		////	ゲーム選択画面に戻ります
		//if (IsButtonTriggered(0, XINPUT_GAMEPAD_X) ||			// GamePad	X
		//	Keyboard_IsKeyTrigger(KK_M) ||					// Keyboard	M
		//	Mouse_IsLeftDown())									// Mouse	左
		//{
		//	if (min2.x < MousePos.x && max2.x > MousePos.x && min2.y < MousePos.y && max2.y > MousePos.y)
		//	{
		//		SetScene(SCENE::SCENE_STAGESELECT);
		//	}
		//}

		/*リセットボタン*/
		//if (Keyboard_IsKeyTrigger(KK_R)) {
			//	ResetGame();
			//}
		
		////　ゲームリセットします
			//if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
			//	Keyboard_IsKeyTrigger(KK_TAB) ||					// Keyboard	TAB
			//	Mouse_IsLeftDown())									// Mouse	左
			//{
			//	if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y)
			//	{
			//		//SetScene(SCENE::SCENE_GAME);
			//	}
			//}
			//
			//if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
			//	Keyboard_IsKeyTrigger(KK_TAB) ||					// Keyboard	TAB
			//	Mouse_IsLeftDown())									// Mouse	左
			//{
			//	if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y)
			//	{
			//		//SetScene(SCENE::SCENE_GAME);
			//	}
			//}

	
	
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
		//背景テクスチャ
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

		//コントローラー
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseOperationTextureNo));
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

		////ゲームに戻る選択テクスチャ
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseEndTextureNo));
		//SpriteDrawColorRotation
		//(
		//	PauseObject[2].Position.x,
		//	PauseObject[2].Position.y,
		//	0.0f,		
		//	PauseObject[2].Size.x,
		//	PauseObject[2].Size.y,
		//	PauseObject[2].Rotate,
		//	PauseObject[2].Color,
		//	0,
		//	1.0f,
		//	1.0f,
		//	1
		//);

		//ゲームリセット選択テクスチャ
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseResetTextureNo));
		//SpriteDrawColorRotation
		//(
		//	PauseObject[3].Position.x,
		//	PauseObject[3].Position.y,
		//	0.0f,		
		//	PauseObject[3].Size.x,
		//	PauseObject[3].Size.y,
		//	PauseObject[3].Rotate,
		//	PauseObject[3].Color,
		//	0,
		//	1.0f,
		//	1.0f,
		//	1
		//);

		////ゲーム選択画面に戻るテクスチャ
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseSelectTextureNo));
		//SpriteDrawColorRotation
		//(
		//	PauseObject[4].Position.x,
		//	PauseObject[4].Position.y,
		//	0.0f,		
		//	PauseObject[4].Size.x,
		//	PauseObject[4].Size.y,
		//	PauseObject[4].Rotate,
		//	PauseObject[4].Color,
		//	0,
		//	1.0f,
		//	1.0f,
		//	1
		//);
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
bool* GetPauseMause()
{
	return &PauseClick;
}

void PauseSeletct()
{

}