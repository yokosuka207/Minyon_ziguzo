#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include	"scene.h"
#include	"result.h"
#include	"mouse.h"
#include	"time.h"
#include	"score.h"
#include	"fade.h"
#include	"sound.h"
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
static	char* g_ResultBGTextureName = (char*)"data\\texture\\black.png";

//static	char* g_ResultGameEndTextureName = (char*)"data\\texture\\black.png";

// ボタンのテクスチャ
static	char* g_ResultButtonTextureName[BUTTON_MAX] = { (char*)"data\\texture\\text_exit stage.png" ,
												(char*)"data\\texture\\text_continue game.png" };

static int g_ChangeSceneResultSoundNo = 0;
static char g_ChangeSceneResultSoundName[] = "data\\SoundData\\SE\\シーン遷移(魔王魂).wav";



RESULT	ResultObject;//タイトル画面オブジェクト	背景分

int		ResultBGTextureNo;//テクスチャ番号

//int		ResultGameEndTextureNo;//テクスチャ番号
int		ResultButtonTextureNo[BUTTON_MAX];//テクスチャ番号

int ResultSoundNo;	//タイトルサウンド番号
int ResultSoundNo2;	//タイトルサウンド番号

static Time* pTime = pTime->GetTime();
static TimeParam*	pTimeParam = pTime->GetTimeParam();
static Score* pScore = pScore->GetScore();
static FADEPARAM* pFadeParam = GetFadeParam();
static ANIMEPARAM* pAnimeParam = pScore->GetAnimeParam();

// ボタン
Button g_ResultButton[BUTTON_MAX];
Button* g_pSelectResultButton = nullptr;
//======================
//初期化
//======================
void	InitResult()
{
	//	テクスチャのロード
	ResultBGTextureNo = LoadTexture(g_ResultBGTextureName);
	if (ResultBGTextureNo == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}
	//ResultGameEndTextureNo = LoadTexture(g_ResultGameEndTextureName);
	//if (ResultGameEndTextureNo == -1)
	//{//読み込みエラー
	//	exit(999);	//強制終了
	//}

	for (int i = 0; i < BUTTON_MAX; i++) {
		ResultButtonTextureNo[i] = LoadTexture(g_ResultButtonTextureName[i]);
		if (ResultButtonTextureNo[i] == -1)
		{//読み込みエラー
			exit(999);	//強制終了
		}
	}

	// 背景分
	ResultObject.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	ResultObject.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResultObject.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject.Rotate = 0.0f;

	// ボタンの初期化とセット
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_ResultButton[i].Init();
		g_ResultButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 4) * (i * 2 + 1)), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y), 
			D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_ResultButtonTextureName[i]));
	}
	// 選択されているボタンの初期化
	g_pSelectResultButton = &g_ResultButton[0];

	pScore->SetScore(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50), D3DXVECTOR2(50.0f, 50.0f));

	g_ChangeSceneResultSoundNo = LoadSound(g_ChangeSceneResultSoundName);
}
//======================
//終了処理
//======================
void	UninitResult()
{
	// ボタンの終了処理
	for (Button& b : g_ResultButton) {
		b.Uninit();
	}

	StopSound(g_ChangeSceneResultSoundNo);
}

//======================
//更新処理
//======================
void	UpdateResult()
{
	UpdateGameMouse();

	// マウスの1フレーム前の座標
	static float MouseOldPosX = GetMousePosX();
	static float MouseOldPosY = GetMousePosY();

	FADEPARAM* pFadeParam = GetFadeParam();
	if (ResultObject.type == WIN) 
	{
		//キー入力のチェック
		if (Keyboard_IsKeyTrigger(KK_SPACE) ||				// keyboard SPACE
			IsButtonTriggered(0, XINPUT_GAMEPAD_B))			// GamePad B
		{
			//SetVolume(g_ChangeSceneResultSoundNo, 0.5f);
			PlaySound(g_ChangeSceneResultSoundNo, 0);
			// ステージセレクトへ
			StartFade(FADE::FADE_ALPHA_OUT);
		}
	}
	else if (ResultObject.type == LOSE)
	{
		// ボタンの更新処理
		for (Button& b : g_ResultButton) {
			b.Update();
		}
		//[----------コントローラーによるボタンの選択----------
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP)) {		// GamePad 十字キー 上
			for (int i = 0; i < BUTTON_MAX; i++) {
				// 選ばれているボタンを見つけたら
				if (g_pSelectResultButton == &g_ResultButton[i]) {
					// そのボタンが最後のボタンなら
					if (i == BUTTON_MAX - 1) {
						// 0番目のボタンを選ぶ
						g_pSelectResultButton = &g_ResultButton[0];
					}
					else {	// 最後以外なら
						// 次のボタンを選ぶ
						g_pSelectResultButton = &g_ResultButton[i + 1];
					}
					break;
				}
			}
		}
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN)) {		// GamePad 十字キー 下
			for (int i = 0; i < BUTTON_MAX; i++) {
				// 選ばれているボタンを見つけたら
				if (g_pSelectResultButton == &g_ResultButton[i]) {
					// そのボタンが0番目のボタンなら
					if (i == 0) {
						// 最後のボタンを選ぶ
						g_pSelectResultButton = &g_ResultButton[BUTTON_MAX - 1];
					}
					else {		// 0番目以外
						// ひとつ前のボタンを選ぶ
						g_pSelectResultButton = &g_ResultButton[i - 1];
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
				if (g_ResultButton[i].CollisionMouse()) {
					g_pSelectResultButton = &g_ResultButton[i];
				}
			}

			// 選ばれているかいないか
			if (g_pSelectResultButton == &g_ResultButton[i]) {
				// 色を変える
				g_ResultButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// ボタンが押された時の処理
				if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad B
					(Mouse_IsLeftTrigger() && g_pSelectResultButton->CollisionMouse())) {		// Mouse 左クリック (当たっている状態で)
					// 0:Exit Stage ステージセレクトシーンへ
					if (i == 0) {
						//SetVolume(g_ChangeSceneResultSoundNo, 0.5f);
						PlaySound(g_ChangeSceneResultSoundNo, 0);
						// ステージセレクトへ
						StartFade(FADE::FADE_ALPHA_OUT);
					}
					// 1:Continue ゲームシーンへ
					else {
						//SetVolume(g_ChangeSceneResultSoundNo, 0.5f);
						PlaySound(g_ChangeSceneResultSoundNo, 0);
						pFadeParam->ExceptFlag = true;
						StartFade(FADE::FADE_ALPHA_OUT);
					}
					g_pSelectResultButton->ChangeType();
					break;
				}
			}
			else {
				// 色を変える
				g_ResultButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
			}
		}
		// 次に備えて1フレーム前の座標に入れる
		MouseOldPosX = GetMousePosX();
		MouseOldPosY = GetMousePosY();

	}
}
//======================
//描画処理
//======================
void	DrawResult()
{
	//２Ｄ表示をするためのマトリクスを設定
	SetWorldViewProjection2D();

	//テクスチャのセット
	if (ResultObject.type == LOSE)		// ゲームオーバー
	{
		// 背景
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultBGTextureNo));
		//スプライトの描画
		SpriteDrawColorRotation
		(
			ResultObject.Position.x,
			ResultObject.Position.y,
			0.0f,
			ResultObject.Size.x,
			ResultObject.Size.y,
			ResultObject.Rotate,
			ResultObject.Color,
			0,
			1.0f,
			1.0f,
			1
		);

		// ボタン
		for (Button& b : g_ResultButton) {
			b.Draw();
		}
	}
	else if (ResultObject.type == WIN)		// クリア
	{

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultBGTextureNo));

		//スプライトの描画
		SpriteDrawColorRotation
		(
			ResultObject.Position.x,
			ResultObject.Position.y,
			0.0f,
			ResultObject.Size.x,
			ResultObject.Size.y,
			ResultObject.Rotate,
			ResultObject.Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}
}

void SetResultType(RESULT_TYPE ty)
{
	ResultObject.type = ty;
}

RESULT* GetResult()
{
	return &ResultObject;
}
