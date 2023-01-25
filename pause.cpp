
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
#define BUTTON_SIZE_X	200
#define BUTTON_SIZE_Y	100
#define BUTTON_DRAWSIZE_X	400
#define BUTTON_DRAWSIZE_Y	400

//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView* g_PauseTexture = NULL;//テクスチャ情報
static	char* g_PauseTextureName = (char*)"data\\texture\\black.png";

static	ID3D11ShaderResourceView* g_PauseOperationTexture = NULL;//操作説明情報
static	char* g_PauseOperationTextureName = (char*)"data\\texture\\操作説明.png";

static	ID3D11ShaderResourceView* g_PauseEndTexture = NULL;//テクスチャ情報
static	char* g_PauseEndTextureName = (char*)"data\\texture\\text_continue game.png";

static	ID3D11ShaderResourceView* g_PauseSelectTexture = NULL;//テクスチャ情報
static	char* g_PauseSelectTextureName = (char*)"data\\texture\\text_exit stage.png";

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

	// ボタンの初期化
	g_PauseButton[0].Init();
	g_PauseButton[1].Init();

	// ボタンのセット
	g_PauseButton[0].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 5) * 3 + 50), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y), 
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PauseEndTextureNo);
	g_PauseButton[1].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 5) * 4 + 50), D3DXVECTOR2(BUTTON_SIZE_X * 1.5f, BUTTON_SIZE_Y), 
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PauseSelectTextureNo);

	// 選択されているボタンのリセット
	g_pSelectPauseButton = &g_PauseButton[0];
}
//======================
//終了処理
//======================
void	UninitPause()
{
	// ボタンの終了処理
	g_PauseButton[0].Uninit();
	g_PauseButton[1].Uninit();

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
		// ボタンの更新処理
		g_PauseButton[0].Update();
		g_PauseButton[1].Update();

		// マウスの1フレーム前の座標
		static float MouseOldPosX = GetMousePosX();
		static float MouseOldPosY = GetMousePosY();

		//[----------コントローラーによるボタンの選択----------
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN)) {		// GamePad 十字キー　下
			for (int i = 0; i < BUTTON_MAX; i++) {
				// 選ばれているボタンを見つけたら
				if (g_pSelectPauseButton == &g_PauseButton[i]) {
					// そのボタンが最後のボタンなら
					if (i == BUTTON_MAX - 1) {
						// 0番目のボタンを選ぶ
						g_pSelectPauseButton = &g_PauseButton[0];
					}
					else {	// 最後以外なら
						// 次のボタンを選ぶ
						g_pSelectPauseButton = &g_PauseButton[i + 1];
					}
					break;
				}
			}
		}
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP)) {		// GamePad 十字キー　上
			for (int i = 0; i < BUTTON_MAX; i++) {
				// 選ばれているボタンを見つけたら
				if (g_pSelectPauseButton == &g_PauseButton[i]) {
					// そのボタンが0番目のボタンなら
					if (i == 0) {
						// 最後のボタンを選ぶ
						g_pSelectPauseButton = &g_PauseButton[BUTTON_MAX - 1];
					}
					else {		// 0番目以外
						// ひとつ前のボタンを選ぶ
						g_pSelectPauseButton = &g_PauseButton[i - 1];
					}
					break;
				}
			}
		}
		//----------コントローラーによるボタンの選択----------]

		//[----------ボタンの処理----------
		for (int i = 0; i < BUTTON_MAX; i++) {
			// マウスが動いていたら
			if (MouseOldPosX != GetMousePosX() ||
				MouseOldPosY != GetMousePosY()) {
				// マウスとボタンが当たっていたらそのボタンを選ぶ
				if (g_PauseButton[i].CollisionMouse()) {
					g_pSelectPauseButton = &g_PauseButton[i];
				}
			}

			// 選ばれているかいないか
			if (g_pSelectPauseButton == &g_PauseButton[i]) {
				// 色を変える
				g_PauseButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// ボタンが押された時の処理
				if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad B
					(Mouse_IsLeftTrigger() && g_pSelectPauseButton->CollisionMouse())) {		// Mouse 左クリック
					// 0:Quit ゲームに戻る
					if (i == 0) {
						SetScene(SCENE::SCENE_GAME);
						PauseClick = true;
					}
					// 1:Exit Stage ステージセレクトに戻る
					else {
						SetScene(SCENE::SCENE_STAGESELECT);
					}
					g_pSelectPauseButton->ChangeType();
					break;
				}
			}
			else {
				// 色を変える
				g_PauseButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
			}
		}
		// 次に備えて1フレーム前の座標に入れる
		MouseOldPosX = GetMousePosX();
		MouseOldPosY = GetMousePosY();
		//----------ボタンの処理----------]

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

		// ボタンの描画処理
		g_PauseButton[0].Draw();
		g_PauseButton[1].Draw();

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