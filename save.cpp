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

//**************************************************
// マクロ定義
//**************************************************
#define BUTTON_NUM	(3)

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
static char* g_saveFileName[] = { (char*)"data/SaveData/Data1.bin",			// データ１
								(char*)"data/SaveData/Data2.bin",			// データ２
								(char*)"data/SaveData/Data3.bin" };			// データ３

// 各データのボタンを作る
Button g_DataButton[BUTTON_NUM];

//==================================================
// 初期化
//==================================================
void Save::Init()
{
	// マウスの初期化
	InitGameMouse();

	// ボタンのテクスチャ番号読み込み
	int ButtonTexNo[3];
	for (int i = 0; i < BUTTON_NUM; i++) {
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
	for (int i = 0; i < BUTTON_NUM; i++) {
		// ファイルがあったら
		g_DataButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * (i+1)), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TextureFileName[i]));

		// ファイルを開く
		fopen_s(&fp, g_saveFileName[i], "rb");			// 開く

		// データ読み込む
		if (fp != NULL) {
			fread(&m_saveData, sizeof(SaveData), 1, fp);

			// ファイルを閉じる
			fclose(fp);
		}
		g_DataButton[i].SetNum(m_saveData.clearStageNum);
	}
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
}

//==================================================
// 更新処理
//==================================================
void Save::Update()
{
	// マウスの更新
	UpdateGameMouse();
	//[----------とりあえずまだ残しておきます----------
	// Zボタンを押したら
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_X) ||			// GamePad	X
		Keyboard_IsKeyTrigger(KK_Z)) {						// Keyboard	Z
		// 全データ削除
		DeleteSaveData();
	}
	//----------入力----------]
	//----------とりあえずまだ残しておきます----------]
	for (int i = 0; i < BUTTON_NUM; i++) {
		// 各ボタンの更新
		g_DataButton[i].Update();
		// もし押されたら
		if (g_DataButton[i].ReleaseButton()) {
			SetDataNo(i);			// データ番号をセット
			DataLoad();					// ロード

			FADEPARAM* pFadeParam = GetFadeParam();

			//SetScene(SCENE_STAGESELECT);			// ステージセレクトシーンに切り替わる
			if(!pFadeParam->FadeFlag)
			StartFade(FADE::FADE_ALPHA_OUT);
		}
	}
}

//==================================================
// 描画処理
//==================================================
void Save::Draw()
{
	//[----------背景の表示----------
	// テクスチャの設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_BGTexNo));
	// 四角形の描画
	SpriteDrawColorRotation(m_BGPos.x, m_BGPos.y,0.0f, m_BGSize.x, m_BGSize.y, 0.0f, m_BGColor, 0.0f, 1.0f, 1.0f, 1);
	//----------背景の表示----------]

	// 各ボタンの描画
	for (auto& b : g_DataButton) {
		b.Draw();
	}
}

//==================================================
// セーブ
//==================================================
void Save::DataSave()
{
	// ----セーブする各データをm_saveDataに入れたい----
	m_saveData.clearStageNum = (GetClearStageNum() - 1);
	// ------------------------------------------------

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
	for (int i = 0; i < BUTTON_NUM; i++) {
		fopen_s(&fp, g_saveFileName[i], "wb");

		if (fp != NULL) {
			// 書き込む
			fwrite(&m_saveData, sizeof(SaveData), 1, fp);

			// ファイルを閉じる
			fclose(fp);
		}
		g_DataButton[i].SetNum(m_saveData.clearStageNum);
	}
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

	//[----ここでロードした各データを各々の場所に入れたい----
	SetClearStageNum(m_saveData.clearStageNum);
	//------------------------------------------------------]
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
