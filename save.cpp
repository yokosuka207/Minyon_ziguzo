/*================================================================================

	セーブ処理[save.cpp]

												Author: 齊藤 零登
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	2022/12/07	SaitoReito
================================================================================*/
#include <iostream>

#include "save.h"
#include "texture.h"
#include "main.h"
#include "sprite.h"
#include "scene.h"

//#include "input.h"
#include "xinput.h"
#include "xkeyboard.h"

#include "input.h"
#include "fade.h"
#include "mouse.h"
#include "StageSelect.h"
#include "button.h"

#include "sound.h"

//**************************************************
// マクロ定義
//**************************************************
#define BUTTON_MAX	4
#define DATA_MAX	3

//**************************************************
// グローバル変数
//**************************************************
// 各テクスチャの名前
static char* g_BGTextureFileName = (char*)"data/texture/black.png";				// 背景
static char* g_TextureFileName[] = { (char*)"data/texture/セーブデータテキスト１.png",				// データ１
									(char*)"data/texture/セーブデータテキスト２.png",				// データ２
									(char*)"data/texture/セーブデータテキスト３.png"				// データ３
};

// セーブデータを保存するファイル名
char* g_saveFileName[] = { (char*)"data/SaveData/Data1.bin",			// データ１
							(char*)"data/SaveData/Data2.bin",			// データ２
							(char*)"data/SaveData/Data3.bin" };			// データ３

char* g_DataDeleteTextureName = (char*)"data/texture/Erase.png";
//char* g_SaveTitleTextureName = (char*)"data/texture/Select a File.png";
char* g_SaveTitleTextureName = (char*)"data/texture/Save.png";
int g_SaveTitleTextureNo = -1;

// 各データのボタンを作る
Button g_DataButton[BUTTON_MAX];

//サウンド
static int g_ChangeSceneSaveSoundNo = 0;
static char g_ChangeSceneSaveSoundName[] = "data\\SoundData\\SE\\シーン遷移(魔王魂).wav";

// 全クリしたか
bool g_StageAllClear = false;

//==================================================
// 初期化
//==================================================
void Save::Init()
{
	// マウスの初期化
	InitGameMouse();

	// セーブタイプの初期化
	m_type = SAVE_TYPE::TYPE_NONE;
	// セーブのタイトルのテクスチャ読み込み
	g_SaveTitleTextureNo = LoadTexture(g_SaveTitleTextureName);

	m_pButton = &g_DataButton[0];

	// ボタンのテクスチャ番号読み込み
	int ButtonTexNo[3];
	for (int i = 0; i < DATA_MAX; i++) {
		ButtonTexNo[i] = LoadTexture(g_TextureFileName[i]);
	}

	// 各ボタンの初期化
	for (auto& b : g_DataButton) {
		b.Init();
	}

	// テクスチャナンバーを格納
	m_BGTexNo = LoadTexture(g_BGTextureFileName);

	m_BGPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_BGSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// セーブデータ系の初期化
	m_saveData.clearStageNum = 0;



	FILE* fp;		// ファイルポインタ
	// 各ボタンのセット
	for (int i = 0; i < DATA_MAX; i++) {
		// ファイルがあったら
		g_DataButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * (i+1) + 150),D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), 
			D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2.5), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ButtonTexNo[i]);

		// ファイルを開く
		fopen_s(&fp, g_saveFileName[i], "rb");			// 開く

		// データ読み込む
		if (fp != NULL) {
			fread(&m_saveData, sizeof(SaveData), 1, fp);

			// ファイルを閉じる
			fclose(fp);
		}
		g_DataButton[i].SetNum(m_saveData.clearStageNum);
		if (m_saveData.clearStageNum == STAGE_MAX) {
			g_DataButton[i].SetButtonColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			g_DataButton[i].SetNumColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//g_DataButton[i].SetButtonColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//g_DataButton[i].SetNumColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		}
	}
	// データ削除ボタン
	g_DataButton[3].SetButton(D3DXVECTOR2((SCREEN_WIDTH / 3) * 2.5f, (SCREEN_HEIGHT / 4) * 3.5f), D3DXVECTOR2(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6), 
		D3DXVECTOR2(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_DataDeleteTextureName));

	// サウンドデータのロード
	g_ChangeSceneSaveSoundNo = LoadSound(g_ChangeSceneSaveSoundName);

	// 全クリしてないことにする
	g_StageAllClear = false;
}


//==================================================
// 終了処理
//==================================================
void Save::Uninit()
{
	// 各ボタンの終了処理
	for (auto& b : g_DataButton) {
		b.Uninit();
	}
	StopSound(g_ChangeSceneSaveSoundNo);
}

//==================================================
// 更新処理
//==================================================
void Save::Update()
{
	// マウスの更新
	UpdateGameMouse();

	static float MouseOldPosX = GetMousePosX();
	static float MouseOldPosY = GetMousePosY();

	if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN)) {	// GamePad 十字キー 下
		float disSta = 1000000.0f;
		int j = 0;
		for (int i = 0; i < BUTTON_MAX; i++) {
			D3DXVECTOR2 p0 = m_pButton->GetPosition();
			D3DXVECTOR2 p1 = g_DataButton[i].GetPosition();
			// いまセットされているボタンより下の位置にいる
			if (p0.y < p1.y) {
				// 間の距離が一番近いボタンを探す
				float dis = DistanceTwoPoints(p0, p1);
				if (disSta > dis) {
					disSta = dis;
					j = i;
				}
			}
		}
		m_pButton = &g_DataButton[j];
	}
	else if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP)) {	// GamePad 十字キー 下
		float disSta = 1000000.0f;
		int j = BUTTON_MAX - 1;
		for (int i = BUTTON_MAX - 1; i >= 0; i--) {
			D3DXVECTOR2 p0 = m_pButton->GetPosition();
			D3DXVECTOR2 p1 = g_DataButton[i].GetPosition();
			// いまセットされているボタンより上の位置にいる
			if (p0.y > p1.y) {
				// 間の距離が一番近いボタンを探す
				float dis = DistanceTwoPoints(p0, p1);
				if (disSta > dis) {
					disSta = dis;
					j = i;
				}
			}
		}
		m_pButton = &g_DataButton[j];
	}
	//----------入力----------]

	for (int i = 0; i < BUTTON_MAX; i++) {
		// 各ボタンの更新
		g_DataButton[i].Update();
		// マウスが動いていたら
		if (MouseOldPosX != GetMousePosX() ||
			MouseOldPosY != GetMousePosY()) {
			if (g_DataButton[i].CollisionMouse()) {
				m_pButton = &g_DataButton[i];
			}
		}

		D3DXCOLOR col = g_DataButton[i].GetCol();
		// そのボタンが選ばれてたら
		if (&g_DataButton[i] == m_pButton) {
			g_DataButton[i].SetButtonColor(D3DXCOLOR(col.r, col.g, col.b, 1.0f));
		}
		else {
			g_DataButton[i].SetButtonColor(D3DXCOLOR(col.r, col.g, col.b, 0.4f));
		}

		// 選択されているボタンだったら
		if (m_pButton == &g_DataButton[i]) {
			// 入力チェック
			if (g_DataButton[i].CollisionMouse() && (Mouse_IsLeftTrigger()) ||						// Mouse 左
				IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {		// GamePad B
				// データのボタンか
				if (i < DATA_MAX) {
					SetDataNo(i);				// データ番号をセット
					if (m_type == SAVE_TYPE::TYPE_NONE) {
						DataLoad();					// ロード

						// ステージセレクトシーンに切り替わる
						FADEPARAM* pFadeParam = GetFadeParam();
						if (!pFadeParam->FadeFlag)
						{
							//SetVolume(g_ChangeSceneSaveSoundNo, 0.5f);
							PlaySound(g_ChangeSceneSaveSoundNo, 0);
							StartFade(FADE::FADE_ALPHA_OUT);
						}
					}
					else {
						DeleteSaveData();		// データ削除
					}
				}
				else {	// データのボタンではなかったら
					// タイプの切り替え
					if (m_type == SAVE_TYPE::TYPE_NONE) {
						m_type = SAVE_TYPE::TYPE_DELETE;
					}
					else {
						m_type = SAVE_TYPE::TYPE_NONE;
					}
				}
				g_DataButton[i].ChangeType();
				break;
			}
		}
	}

	// 次に備えて1フレーム前の座標に入れる
	MouseOldPosX = GetMousePosX();
	MouseOldPosY = GetMousePosY();
}


//==================================================
// 描画処理
//==================================================
void Save::Draw()
{
	//[----------背景の表示----------
	// テクスチャの設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_BGTexNo));

	if (m_type == SAVE_TYPE::TYPE_DELETE) {
		m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
	else {
		m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// 四角形の描画
	SpriteDrawColorRotation(m_BGPos.x, m_BGPos.y, 0.0f, m_BGSize.x, m_BGSize.y, 0.0f, m_BGColor, 0.0f, 1.0f, 1.0f, 1);
	//----------背景の表示----------]
	// セーブのタイトルの表示
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SaveTitleTextureNo));
	SpriteDrawColorRotation(SCREEN_WIDTH / 2, 100.0f, 0.0f, 1000, 500, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 1.0f, 1.0f, 1);

	// 各ボタンの描画
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_DataButton[i].Draw();
		if (i == DATA_MAX) {
			if (m_type == SAVE_TYPE::TYPE_DELETE) {
				SetBlendState(BLEND_MODE_SUBTRACT);
			}
		}
	}

	// ブレンドモードを戻す
	SetBlendState(BLEND_MODE_ALPHABLEND);
}

//==================================================
// セーブ
//==================================================
void Save::DataSave()
{
	// セーブするデータ
	if (g_StageAllClear) {		// 全クリしてたら
		m_saveData.clearStageNum = STAGE_MAX;
	}
	else {
		m_saveData.clearStageNum = (GetClearStageNum() - 1);
	}

	FILE* fp;		// ファイルポインタ

	// ファイルを開く
	fopen_s(&fp, g_saveFileName[m_dataNo], "wb");

	if (fp != NULL) {
		// 書き込む
		fwrite(&m_saveData, sizeof(SaveData), 1, fp);

		// ファイルを閉じる
		fclose(fp);
	}
}

//==================================================
// セーブデータ削除
// 引数：セーブデータ番号
//==================================================
void Save::DeleteSaveData()
{
	m_saveData.clearStageNum = 0;

	FILE* fp;		// ファイルポインタ

	// ファイルを開く
	fopen_s(&fp, g_saveFileName[m_dataNo], "wb");

	if (fp != NULL) {
		// 書き込む
		fwrite(&m_saveData, sizeof(SaveData), 1, fp);

		// ファイルを閉じる
		fclose(fp);
	}
	g_DataButton[m_dataNo].SetNum(m_saveData.clearStageNum);
}

//==================================================
// ロード
// 引数：セーブデータ番号
//==================================================
void Save::DataLoad()
{
	FILE* fp;		// ファイルポインタ

	// ファイルを開く
	fopen_s(&fp, g_saveFileName[m_dataNo], "rb");			// 開く

	// データ読み込む
	if (fp != NULL) {
		fread(&m_saveData, sizeof(SaveData), 1, fp);

		// ファイルを閉じる
		fclose(fp);
	}

	if (m_saveData.clearStageNum == STAGE_MAX) {
		g_StageAllClear = true;
	}
	SetClearStageNum(m_saveData.clearStageNum);
}


//==================================================
// ファイルが存在しているか
// 引数：ファイルパス
// 返値：bool(true：存在している)
//==================================================
bool Save::ExistFile(char* fileName) 
{
	FILE* fp;		// ファイルポインタ

	// ファイルがなかったらfalseを返す
	if (fopen_s(&fp, fileName, "rb") != 0) {
		return false;
	}

	fclose(fp);				// 閉じる

	// ファイルがあったらtrueを返す
	return true;
}

//==================================================
// 全クリしたかを返す
//==================================================
bool GetStageAllClear()
{
	return g_StageAllClear;
}

//==================================================
// 全クリしたかを入れる
//==================================================
void SetStageAllClear(bool bClear)
{
	g_StageAllClear = bClear;
}
