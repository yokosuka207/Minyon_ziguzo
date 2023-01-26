
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
#include "button.h"

//======================
//マクロ定義
//=======================
#define BUTTON_MAX	2
#define BUTTON_SIZE_X	200
#define BUTTON_SIZE_Y	100
#define BUTTON_DRAWSIZE_X	300
#define BUTTON_DRAWSIZE_Y	300
// 
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//テクスチャ情報
static	char* g_TitleTextureName1 = (char*)"data\\texture\\タイトル背景.png";
//static	char* g_TitleTextureName1 = (char*)"data\\texture\\タイトル背景2.png";
//static	char* g_TitleTextureName1 = (char*)"data\\texture\\タイトル背景3.png";
static	ID3D11ShaderResourceView* g_TitleTextureButton = NULL;//テクスチャ情報
static	char* g_TitleStartButtonTextureName = (char*)"data\\texture\\text_start.png";

static	ID3D11ShaderResourceView* g_TitleTextureButton2 = NULL;//テクスチャ情報
static	char* g_TitleQuitButtonTextureName = (char*)"data\\texture\\text_quit.png";

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
//TITLE_SWITH g_TitleSwith[2];
int		TitleTextureNo1;//テクスチャ番号

// ボタン系グローバル変数
Button g_TitleButton[2];
Button* g_pSelectTitleButton = nullptr;

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


	//g_TitleSwith[0].Position = D3DXVECTOR2(300.0f, 650.0f);
	//g_TitleSwith[0].Size = D3DXVECTOR2(200.0f, 150.0f);
	//g_TitleSwith[0].texno = LoadTexture(g_TitleStartButtonTextureName);

	//g_TitleSwith[1].Position = D3DXVECTOR2(1100.0f, 650.0f);
	//g_TitleSwith[1].Size = D3DXVECTOR2(200.0f, 150.0f);
	//g_TitleSwith[1].texno = LoadTexture(g_TitleQuitButtonTextureName);

	g_ChangeSceneTitleSoundNo = LoadSound(g_ChangeSceneTitleSoundName);

	// ボタンの初期化
	g_TitleButton[0].Init();
	g_TitleButton[1].Init();

	// ボタンのセット
	g_TitleButton[0].SetButton(D3DXVECTOR2((SCREEN_WIDTH / 3) * 1, (SCREEN_HEIGHT / 5) * 4), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y),
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TitleStartButtonTextureName));
	g_TitleButton[1].SetButton(D3DXVECTOR2((SCREEN_WIDTH / 3) * 2, (SCREEN_HEIGHT / 5) * 4), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y),
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TitleQuitButtonTextureName));

	// 選択されているボタンのリセット
	g_pSelectTitleButton = &g_TitleButton[0];
}
//======================
//終了処理
//======================
void	UninitTitle()
{
	// ボタンの終了処理
	g_TitleButton[0].Uninit();
	g_TitleButton[1].Uninit();


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
	// ボタンの更新処理
	g_TitleButton[0].Update();
	g_TitleButton[1].Update();

	UpdateGameMouse();
	// マウスの1フレーム前の座標
	static float MouseOldPosX = GetMousePosX();
	static float MouseOldPosY = GetMousePosY();

	FADEPARAM* pFadeParam = GetFadeParam();

	//[----------コントローラーによるボタンの選択----------
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT)) {		// GamePad 十字キー 左
		for (int i = 0; i < BUTTON_MAX; i++) {
			// 選ばれているボタンを見つけたら
			if (g_pSelectTitleButton == &g_TitleButton[i]) {
				// そのボタンが最後のボタンなら
				if (i == BUTTON_MAX - 1) {
					// 0番目のボタンを選ぶ
					g_pSelectTitleButton = &g_TitleButton[0];
				}
				else {	// 最後以外なら
					// 次のボタンを選ぶ
					g_pSelectTitleButton = &g_TitleButton[i + 1];
				}
				break;
			}
		}
	}
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT)) {		// GamePad 十字キー 右
		for (int i = 0; i < BUTTON_MAX; i++) {
			// 選ばれているボタンを見つけたら
			if (g_pSelectTitleButton == &g_TitleButton[i]) {
				// そのボタンが0番目のボタンなら
				if (i == 0) {
					// 最後のボタンを選ぶ
					g_pSelectTitleButton = &g_TitleButton[BUTTON_MAX - 1];
				}
				else {		// 0番目以外
					// ひとつ前のボタンを選ぶ
					g_pSelectTitleButton = &g_TitleButton[i - 1];
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
			if (g_TitleButton[i].CollisionMouse()) {
				g_pSelectTitleButton = &g_TitleButton[i];
			}
		}

		// 選ばれているかいないか
		if (g_pSelectTitleButton == &g_TitleButton[i]) {
			// 色を変える
			g_TitleButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// ボタンが押された時の処理
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad B
				(Mouse_IsLeftTrigger() && g_pSelectTitleButton->CollisionMouse())) {		// Mouse 左クリック (当たっている状態で)
				// 0:Start セーブシーンへ
				if (i == 0) {
					//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
					PlaySound(g_ChangeSceneTitleSoundNo, 0);
					// セーブデータ選択へ
					StartFade(FADE::FADE_ALPHA_OUT);
				}
				// 1:Quit ゲーム強制終了
				else {
					GameEnd();
				}
				g_pSelectTitleButton->ChangeType();
				break;
			}
		}
		else {
			// 色を変える
			g_TitleButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		}
	}

	// 次に備えて1フレーム前の座標に入れる
	MouseOldPosX = GetMousePosX();
	MouseOldPosY = GetMousePosY();
	//----------ボタンの処理----------]
	////キー入力のチェック
	//if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||			// GamePad	B
	//	Keyboard_IsKeyTrigger(KK_A))						// Keyboard	A
	//{
	//	if (!pFadeParam->FadeFlag)
	//	{
	//		//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
	//		PlaySound(g_ChangeSceneTitleSoundNo, 0);
	//		//SetScene(SCENE::SCENE_DATASELECT);
	//		StartFade(FADE::FADE_ALPHA_OUT);
	//	}
	//}
	//D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// マウスの座標

	////if (CollisionBB(g_TitleSwith[0].Position, MousePos, g_TitleSwith[0].Size, D3DXVECTOR2(3.0f, 3.0f)))
	//{
	//	if (Mouse_IsLeftDown())
	//	{
	//		if (!pFadeParam->FadeFlag)
	//		{
	//			//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
	//			PlaySound(g_ChangeSceneTitleSoundNo, 0);
	//			StartFade(FADE::FADE_ALPHA_OUT);
	//		}
	//	}
	//}
	//if (CollisionBB(g_TitleSwith[1].Position, MousePos, g_TitleSwith[1].Size, D3DXVECTOR2(3.0f, 3.0f)))
	//{
	//	if (Mouse_IsLeftDown())
	//	{
	//		DestroyWindow(GetHwnd());
	//	}
	//}
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
	// ボタンの終了処理
	g_TitleButton[0].Draw();
	g_TitleButton[1].Draw();
	//for (int i = 0; i < 2; i++)
	//{
	//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TitleSwith[i].texno));

	//	SpriteDrawColorRotation(g_TitleSwith[i].Position.x, g_TitleSwith[i].Position.y,0.0f,
	//		g_TitleSwith[i].Size.x, g_TitleSwith[i].Size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f, 1);

	//}

}



