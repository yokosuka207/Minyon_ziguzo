/*================================================================================

	セーブ処理[save.cpp]

												Author: 齊藤 零登
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#include "save.h"
#include "texture.h"
#include "main.h"
#include "sprite.h"
#include "scene.h"

#include "input.h"

// 各テクスチャの名前
char* g_BGTextureFileName = (char*)"data/texture/JumpStand.jpg";			// 背景
char* g_TextureFileName0 = (char*)"data/texture/GameEnd_haikei.jpg";			// データなし
char* g_TextureFileName1 = (char*)"data/texture/GameEnd_haikei.jpg";			// データ１
char* g_TextureFileName2 = (char*)"data/texture/GameEnd_haikei.jpg";			// データ２
char* g_TextureFileName3 = (char*)"data/texture/GameEnd_haikei.jpg";			// データ３

// 各データのボタンを作る
Button g_Data1;
Button g_Data2;
Button g_Data3;

//==================================================
// 初期化
//==================================================
void Save::Init()
{

	// テクスチャナンバーを格納
	m_BGTexNo = LoadTexture(g_BGTextureFileName);

	m_BGPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_BGSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_Data1.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 1), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), LoadTexture(g_TextureFileName1));
	g_Data2.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), LoadTexture(g_TextureFileName1));
	g_Data3.SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), LoadTexture(g_TextureFileName1));
}

//==================================================
// 終了処理
//==================================================
void Save::Uninit()
{

}

//==================================================
// 更新処理
//==================================================
void Save::Update()
{
	if (GetKeyboardTrigger(DIK_A)) {
		SetScene(SCENE_STAGESELECT);
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
	SpriteDrawColorRotation(m_BGPos.x, m_BGPos.y, m_BGSize.x, m_BGSize.y, 0.0f, m_BGColor, 0.0f, 1.0f, 1.0f, 1);
	//----------背景の表示----------]

	// 各ボタンの描画
	g_Data1.Draw();
	g_Data2.Draw();
	g_Data3.Draw();
}

//==================================================
// セーブ
//==================================================
void Save::Saved(int no)
{

}

//==================================================
// セーブデータ削除
// 引数：セーブデータ番号
//==================================================
void Save::DeleteSaveData(int no)
{

}
