
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include	"xinput.h"
#include	"xkeyboard.h"
#include	"result.h"
#include	"mouse.h"
#include	"time.h"
#include	"story.h"
#include	"game.h"
#include	"story.h"

#include	"StoryKey.h"

//====================================
//グローバル変数
//====================================

//ストーリーブロック
static	ID3D11ShaderResourceView* g_StoryTextureBlock = NULL;//テクスチャ情報
static	char* g_StoryTextureNameBlock = (char*)"data\\texture\\ステージ選択.jpg";


static	ID3D11ShaderResourceView* g_StoryTexture1 = NULL;//テクスチャ情報
static	char* g_StoryTextureName1 = (char*)"data\\texture\\セーブ画面背景.png";

static	ID3D11ShaderResourceView* g_StoryTexture2 = NULL;//操作説明情報
static	char* g_StoryTextureName2 = (char*)"data\\texture\\操作説明.png";

static	ID3D11ShaderResourceView* g_StoryTexture3 = NULL;//テクスチャ情報
static	char* g_StoryTextureName3 = (char*)"data\\texture\\再開.jpg";

static	ID3D11ShaderResourceView* g_StoryTexture4 = NULL;//テクスチャ情報
static	char* g_StoryTextureName4 = (char*)"data\\texture\\ステージリセット.jpg";

static	ID3D11ShaderResourceView* g_StoryTexture5 = NULL;//テクスチャ情報
static	char* g_StoryTextureName5 = (char*)"data\\texture\\ステージ選択.jpg";

static	ID3D11ShaderResourceView* g_StoryTexture6 = NULL;//テクスチャ情報
static	char* g_StoryTextureName6 = (char*)"data\\texture\\ステージ選択.jpg";

static	ID3D11ShaderResourceView* g_StoryTexture7 = NULL;//テクスチャ情報
static	char* g_StoryTextureName7 = (char*)"data\\texture\\ステージ選択.jpg";

static	ID3D11ShaderResourceView* g_StoryTexture8 = NULL;//テクスチャ情報
static	char* g_StoryTextureName8 = (char*)"data\\texture\\セーブ画面背景.jpg";


//テクスチャ番号
int		StoryTextureNoBlock = 0;
int		StoryTextureNo1 = 0;
int		StoryTextureNo2 = 0;	
int		StoryTextureNo3 = 0;	
int		StoryTextureNo4 = 0;	
int		StoryTextureNo5 = 0;	
int		StoryTextureNo6 = 0;
int		StoryTextureNo7 = 0;
int		StoryTextureNo8 = 0;


STORY	gStory[STORY_MAX];//タイトル画面オブジェクト

STORY_NUMBER StoryNumber = STORY_NUMBER::STORY_NONE;
static int q;

STORYKEY* pSKey;

//======================
//初期化
//======================
void	InitStory()
{
	//テクスチャのロード
	StoryTextureNoBlock = LoadTexture(g_StoryTextureNameBlock);
	StoryTextureNo1 = LoadTexture(g_StoryTextureName1);
	StoryTextureNo2 = LoadTexture(g_StoryTextureName2);
	StoryTextureNo3 = LoadTexture(g_StoryTextureName3);
	StoryTextureNo4 = LoadTexture(g_StoryTextureName4);
	StoryTextureNo5 = LoadTexture(g_StoryTextureName5);
	StoryTextureNo6 = LoadTexture(g_StoryTextureName6);
	StoryTextureNo7 = LoadTexture(g_StoryTextureName7);
	StoryTextureNo8 = LoadTexture(g_StoryTextureName8);

	for (int i = 0; i < STORY_MAX; i++) {
		gStory[i].pos = D3DXVECTOR2(90, 230);
		gStory[i].size = D3DXVECTOR2(STORY_BLOCK_SIZE, STORY_BLOCK_SIZE);
		gStory[i].color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		gStory[0].HaveKey = 1;

		gStory[i].bUse = true;
		gStory[i].KeyUse = false;

		
	}
	pSKey = GetStoryKey();

	if (gStory[0].n == 0) {
		pSKey[0].HaveSKey = 1;
		gStory[0].n++;
	}
	gStory[0].HaveKey = pSKey[0].HaveSKey;
}

//======================
//終了処理
//======================
void UninitStory()
{
	if (g_StoryTextureBlock)
	{
		g_StoryTextureBlock->Release();
		g_StoryTextureBlock = NULL;
	}

	if (g_StoryTexture1)
	{
		g_StoryTexture1->Release();
		g_StoryTexture1 = NULL;
	}
	if (g_StoryTexture2)
	{
		g_StoryTexture2->Release();
		g_StoryTexture2 = NULL;
	}
	if (g_StoryTexture3)
	{
		g_StoryTexture3->Release();
		g_StoryTexture3 = NULL;
	}
	if (g_StoryTexture4)
	{
		g_StoryTexture4->Release();
		g_StoryTexture4 = NULL;
	}

	if (g_StoryTexture5)
	{
		g_StoryTexture5->Release();
		g_StoryTexture5 = NULL;
	}
	if (g_StoryTexture6)
	{
		g_StoryTexture6->Release();
		g_StoryTexture6 = NULL;
	}
	if (g_StoryTexture7)
	{
		g_StoryTexture7->Release();
		g_StoryTexture7 = NULL;
	}
	if (g_StoryTexture8)
	{
		g_StoryTexture8->Release();
		g_StoryTexture8 = NULL;
	}

}

//======================
//更新処理
//======================
void UpdateStory()
{


	
	if (gStory[0].KeyUse >= 1) 
	{

		if (gStory[0].HaveKey > 1)
		{
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad	A
				Keyboard_IsKeyTrigger(KK_LEFT))					// Mouse	左
			{
				gStory[0].HaveKey--;
			}
		}

	if(gStory[0].HaveKey < pSKey[0].HaveSKey) {
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||			// GamePad	A
				Keyboard_IsKeyTrigger(KK_RIGHT))					// Mouse	右
			{
				gStory[0].HaveKey++;
			}
		}

	}
	
	//for (int i = 0; i < STORY_MAX; i++) 
	//{
	//	gStory[i].pos.y += gStory[i].sp.y;
	//}

}
//======================
//描画処理
//======================
void DrawStory()
{

	SetWorldViewProjection2D();

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNoBlock));
	SpriteDrawColorRotation
	(gStory[0].pos.x, gStory[0].pos.y, 0.0f,
		gStory[0].size.x, gStory[0].size.y, 0, gStory[0].color, 0, 1.0f, 1.0f, 1);

	if (gStory[0].KeyUse) 
	{
		switch (gStory[0].HaveKey) {
		case 1:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo1));
			break;
		case 2:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo2));
			break;
		case 3:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo3));
			break;
		case 4:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo4));
			break;
		case 5:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo5));
			break;
		case 6:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo6));
			break;
		case 7:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo7));
			break;
		case 8:
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNo8));
			break;
		default:
			break;
		}

		SpriteDrawColorRotation
		(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, gStory[0].color, 0, 1.0f, 1.0f, 1);
	
	}
}

STORY* GetStory()
{
	return &gStory[0];
}

