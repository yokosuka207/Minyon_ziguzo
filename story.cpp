
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
static	char* g_StoryTextureNameBlock = (char*)"data\\texture\\ストーリーブロック.png";


static	ID3D11ShaderResourceView* g_StoryTexture1 = NULL;//テクスチャ情報
static	char* g_StoryTextureName1 = (char*)"data\\texture\\日記No.7.png";

static	ID3D11ShaderResourceView* g_StoryTexture2 = NULL;//操作説明情報
static	char* g_StoryTextureName2 = (char*)"data\\texture\\日記No.1.png";

static	ID3D11ShaderResourceView* g_StoryTexture3 = NULL;//テクスチャ情報
static	char* g_StoryTextureName3 = (char*)"data\\texture\\日記No.2.png";

static	ID3D11ShaderResourceView* g_StoryTexture4 = NULL;//テクスチャ情報
static	char* g_StoryTextureName4 = (char*)"data\\texture\\日記No.3.png";

static	ID3D11ShaderResourceView* g_StoryTexture5 = NULL;//テクスチャ情報
static	char* g_StoryTextureName5 = (char*)"data\\texture\\日記No.4.png";

static	ID3D11ShaderResourceView* g_StoryTexture6 = NULL;//テクスチャ情報
static	char* g_StoryTextureName6 = (char*)"data\\texture\\日記No.5.png";

static	ID3D11ShaderResourceView* g_StoryTexture7 = NULL;//テクスチャ情報
static	char* g_StoryTextureName7 = (char*)"data\\texture\\日記No.6.png";

static	ID3D11ShaderResourceView* g_StoryTexture8 = NULL;//テクスチャ情報
static	char* g_StoryTextureName8 = (char*)"data\\texture\\日記No.8.png";


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

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 sp;

	bool	noob;
}S;

STORY	gStory;//タイトル画面オブジェクト
S		s;

STORY_NUMBER StoryNumber = STORY_NUMBER::STORY_NONE;
static int q;

STORYKEY* pSKey;


int i = 3;
int n = 0;

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

	//ストーリー初期化
	
	//gStory.pos = D3DXVECTOR2(30.0f, 210.0f);
	gStory.pos = D3DXVECTOR2(45.0f, 200.0f);//gStory.pos = D3DXVECTOR2(60.0f, 700.0f);
	gStory.size = D3DXVECTOR2(60, 90);
	gStory.color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	gStory.HaveKey = 1;

	gStory.bUse = true;
	gStory.KeyUse = false;


	//ストーリー初期化	
	s.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	s.size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	pSKey = GetStoryKey();

	if (gStory.n == 0) {
		pSKey[0].HaveSKey = 1;
		gStory.n++;
	}
	if (pSKey[0].HaveSKey >= 9) {
		pSKey[0].HaveSKey = 8;
	}
	gStory.HaveKey = pSKey[0].HaveSKey;

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

	if (gStory.KeyUse) 
	{
		if (gStory.HaveKey > 1)
		{
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT) ||		// GamePad	左
				Keyboard_IsKeyTrigger(KK_LEFT))					// Mouse	左
			{
				i = 0;
				n = gStory.HaveKey;
			}
		}

		if(gStory.HaveKey < pSKey[0].HaveSKey) {
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT) ||			// GamePad	右
				Keyboard_IsKeyTrigger(KK_RIGHT))					// Mouse	右
			{
				i = 1;
				n = gStory.HaveKey;
			}
		}

		
		if (i == 0) 
		{
			s.sp.x = 40;

			if (s.pos.x >= SCREEN_WIDTH + s.size.x / 2) {
				s.sp.x = 0;
				s.pos.x = 0 -s.size.x / 2;
				gStory.HaveKey--;
			}
			if (n != gStory.HaveKey){
				if (s.pos.x >= SCREEN_WIDTH / 2) {
					s.sp.x = 0;
					s.pos.x = SCREEN_WIDTH / 2;
					i = 3;
				}
			}

			s.pos += s.sp;
		}
		if (i == 1)
		{
			s.sp.x = 40;

			if (s.pos.x <= -s.size.x / 2) {
				s.sp.x = 0;
				s.pos.x = SCREEN_WIDTH + s.size.x / 2;
				gStory.HaveKey++;
			}
			if (n != gStory.HaveKey) {
				if (s.pos.x <= SCREEN_WIDTH / 2) {
					s.sp.x = 0;
					s.pos.x = SCREEN_WIDTH / 2;
					i = 3;
				}
			}

			s.pos -= s.sp;
		}

		
	}
	

}
//======================
//描画処理
//======================
void DrawStory()
{

	SetWorldViewProjection2D();

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryTextureNoBlock));
	SpriteDrawColorRotation
	(gStory.pos.x, gStory.pos.y, 0.0f,
		gStory.size.x, gStory.size.y, 0, gStory.color, 0, 1.0f, 1.0f, 1);

	if (gStory.KeyUse) 
	{
		switch (gStory.HaveKey) {
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
		(s.pos.x, s.pos.y, 0.0f, s.size.x, s.size.y, 0, gStory.color, 0, 1.0f, 1.0f, 1);

	}
}

STORY* GetStory()
{
	return &gStory;
}

