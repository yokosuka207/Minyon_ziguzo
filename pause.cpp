
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
#include	"sound.h"

//======================
//マクロ定義
//=======================
#define BUTTON_MAX	3
#define BUTTON_SIZE_X	200
#define BUTTON_SIZE_Y	100
#define BUTTON_DRAWSIZE_X	400
#define BUTTON_DRAWSIZE_Y	400

//======================
//グローバル変数
//======================
//背景テクスチャ
static	char* g_PauseTextureName = (char*)"data\\texture\\black.png";
//コントローラー
static	char* g_PauseOperationTextureName = (char*)"data\\texture\\操作説明.png";
static	char* g_PauseButtonTextureName[BUTTON_MAX] = { (char*)"data\\texture\\text_continue game.png" ,	//countinue
														(char*)"data\\texture\\text_exit stage.png",   //リセット 
														(char*)"data\\texture\\text_exit stage.png" };//ステージセレクト画面

//サウンド
static int g_ChangeScenePauseSoundNo = 0;
static char g_ChangeScenePauseSoundName[] = "data\\SoundData\\SE\\シーン遷移(魔王魂).wav";

PAUSE	PauseObject[2];//タイトル画面オブジェクト

int		PauseTextureNo = 0;			//テクスチャ番号
int		PauseOperationTextureNo = 0;//テクスチャ番号

static bool		PauseFlag, PauseClick;

Button g_PauseButton[BUTTON_MAX];
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

	PauseFlag = false;
	PauseClick = false;

	// サウンドロード
	g_ChangeScenePauseSoundNo = LoadSound(g_ChangeScenePauseSoundName);
	
	// ボタンの初期化
	for (Button& b : g_PauseButton) {
		b.Init();
	}

	// ボタンのセット
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_PauseButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 6) * (i+3) + 50), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y),
			D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_PauseButtonTextureName[i]));
	}

	// 選択されているボタンのリセット
	g_pSelectPauseButton = &g_PauseButton[0];
}
//======================
//終了処理
//======================
void	UninitPause()
{
	// ボタンの終了処理
	for (Button& b : g_PauseButton) {
		b.Uninit();
	}

	StopSound(g_ChangeScenePauseSoundNo);
}

//======================
//更新処理
//======================
void	UpdatePause()
{
	if (PauseFlag) 
	{
		// ボタンの更新処理
		for (Button& b : g_PauseButton) {
			b.Update();
		}

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
						SetVolume(g_ChangeScenePauseSoundNo, 0.3f);
						PlaySound(g_ChangeScenePauseSoundNo, 0);
						SetScene(SCENE::SCENE_GAME);
						PauseClick = true;
					}
					// 1:Reset リセットしてゲームに戻る
					else if(i == 1){
						SetVolume(g_ChangeScenePauseSoundNo, 0.3f);
						PlaySound(g_ChangeScenePauseSoundNo, 0);
						ResetGame();
						SetScene(SCENE::SCENE_GAME);
						PauseClick = true;
					}
					else if(i == 2){
						SetVolume(g_ChangeScenePauseSoundNo, 0.3f);
						PlaySound(g_ChangeScenePauseSoundNo, 0);
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
		for (Button& b : g_PauseButton) {
			b.Draw();
		}

	}
}

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