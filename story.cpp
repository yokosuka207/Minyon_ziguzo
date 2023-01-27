
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
//�O���[�o���ϐ�
//====================================

//�X�g�[���[�u���b�N
static	ID3D11ShaderResourceView* g_StoryTextureBlock = NULL;//�e�N�X�`�����
static	char* g_StoryTextureNameBlock = (char*)"data\\texture\\�X�g�[���[�u���b�N.png";


static	ID3D11ShaderResourceView* g_StoryTexture1 = NULL;//�e�N�X�`�����
static	char* g_StoryTextureName1 = (char*)"data\\texture\\���LNo.7.png";

static	ID3D11ShaderResourceView* g_StoryTexture2 = NULL;//����������
static	char* g_StoryTextureName2 = (char*)"data\\texture\\���LNo.1.png";

static	ID3D11ShaderResourceView* g_StoryTexture3 = NULL;//�e�N�X�`�����
static	char* g_StoryTextureName3 = (char*)"data\\texture\\���LNo.2.png";

static	ID3D11ShaderResourceView* g_StoryTexture4 = NULL;//�e�N�X�`�����
static	char* g_StoryTextureName4 = (char*)"data\\texture\\���LNo.3.png";

static	ID3D11ShaderResourceView* g_StoryTexture5 = NULL;//�e�N�X�`�����
static	char* g_StoryTextureName5 = (char*)"data\\texture\\���LNo.4.png";

static	ID3D11ShaderResourceView* g_StoryTexture6 = NULL;//�e�N�X�`�����
static	char* g_StoryTextureName6 = (char*)"data\\texture\\���LNo.5.png";

static	ID3D11ShaderResourceView* g_StoryTexture7 = NULL;//�e�N�X�`�����
static	char* g_StoryTextureName7 = (char*)"data\\texture\\���LNo.6.png";

static	ID3D11ShaderResourceView* g_StoryTexture8 = NULL;//�e�N�X�`�����
static	char* g_StoryTextureName8 = (char*)"data\\texture\\���LNo.8.png";


//�e�N�X�`���ԍ�
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

STORY	gStory;//�^�C�g����ʃI�u�W�F�N�g
S		s;

STORY_NUMBER StoryNumber = STORY_NUMBER::STORY_NONE;
static int q;

STORYKEY* pSKey;


int i = 3;
int n = 0;

//======================
//������
//======================
void	InitStory()
{
	//�e�N�X�`���̃��[�h
	StoryTextureNoBlock = LoadTexture(g_StoryTextureNameBlock);
	StoryTextureNo1 = LoadTexture(g_StoryTextureName1);
	StoryTextureNo2 = LoadTexture(g_StoryTextureName2);
	StoryTextureNo3 = LoadTexture(g_StoryTextureName3);
	StoryTextureNo4 = LoadTexture(g_StoryTextureName4);
	StoryTextureNo5 = LoadTexture(g_StoryTextureName5);
	StoryTextureNo6 = LoadTexture(g_StoryTextureName6);
	StoryTextureNo7 = LoadTexture(g_StoryTextureName7);
	StoryTextureNo8 = LoadTexture(g_StoryTextureName8);

	//�X�g�[���[������
	
	//gStory.pos = D3DXVECTOR2(30.0f, 210.0f);
	gStory.pos = D3DXVECTOR2(45.0f, 200.0f);//gStory.pos = D3DXVECTOR2(60.0f, 700.0f);
	gStory.size = D3DXVECTOR2(60, 90);
	gStory.color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	gStory.HaveKey = 1;

	gStory.bUse = true;
	gStory.KeyUse = false;


	//�X�g�[���[������	
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
//�I������
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
//�X�V����
//======================
void UpdateStory()
{

	if (gStory.KeyUse) 
	{
		if (gStory.HaveKey > 1)
		{
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT) ||		// GamePad	��
				Keyboard_IsKeyTrigger(KK_LEFT))					// Mouse	��
			{
				i = 0;
				n = gStory.HaveKey;
			}
		}

		if(gStory.HaveKey < pSKey[0].HaveSKey) {
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT) ||			// GamePad	�E
				Keyboard_IsKeyTrigger(KK_RIGHT))					// Mouse	�E
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
//�`�揈��
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

