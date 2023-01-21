
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

//======================
//�}�N����`
//=======================
//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//�e�N�X�`�����
static	char	*g_TitleTextureName1 = (char*)"data\\texture\\�^�C�g���w�i���Q.png";
static	ID3D11ShaderResourceView* g_TitleTextureButton = NULL;//�e�N�X�`�����
static	char* g_TitleButtonTextureName = (char*)"data\\texture\\start.jpg";

static	ID3D11ShaderResourceView* g_TitleTextureButton2 = NULL;//�e�N�X�`�����
static	char* g_TitleButtonTextureName2 = (char*)"data\\texture\\GameEnd_end_button.jpg";

//�T�E���h
static int g_ChangeSceneTitleSoundNo = 0;
static char g_ChangeSceneTitleSoundName[] = "data\\SoundData\\SE\\�V�[���J��(������).wav";



typedef	struct
{
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
}TITLE;
typedef	struct
{
	D3DXVECTOR2		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	int texno;
}TITLE_SWITH;

TITLE	TitleObject;//�^�C�g����ʃI�u�W�F�N�g
TITLE_SWITH g_TitleSwith[2];
int		TitleTextureNo1;//�e�N�X�`���ԍ�

//======================
//������
//======================
void	InitTitle()
{
	//	�e�N�X�`���̃��[�h
	TitleTextureNo1 = LoadTexture(g_TitleTextureName1);
	if (TitleTextureNo1 == -1)
	{//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}

	TitleObject.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	TitleObject.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	TitleObject.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	TitleObject.Rotate = 0.0f;


	g_TitleSwith[0].Position = D3DXVECTOR2(300.0f, 650.0f);
	g_TitleSwith[0].Size = D3DXVECTOR2(200.0f, 150.0f);
	g_TitleSwith[0].texno = LoadTexture(g_TitleButtonTextureName);

	g_TitleSwith[1].Position = D3DXVECTOR2(1100.0f, 650.0f);
	g_TitleSwith[1].Size = D3DXVECTOR2(200.0f, 150.0f);
	g_TitleSwith[1].texno = LoadTexture(g_TitleButtonTextureName2);

	g_ChangeSceneTitleSoundNo = LoadSound(g_ChangeSceneTitleSoundName);
}
//======================
//�I������
//======================
void	UninitTitle()
{
	if (g_TitleTexture1)
	{
		g_TitleTexture1->Release();
		g_TitleTexture1 = NULL;
		StopSound(g_ChangeSceneTitleSoundNo);
	}
}

//======================
//�X�V����
//======================
void	UpdateTitle()
{
	UpdateGameMouse();
	FADEPARAM* pFadeParam = GetFadeParam();
	//�L�[���͂̃`�F�b�N
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||			// GamePad	B
		Keyboard_IsKeyTrigger(KK_A))						// Keyboard	A
	{
		if (!pFadeParam->FadeFlag)
		{
			//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
			PlaySound(g_ChangeSceneTitleSoundNo, 0);
			//SetScene(SCENE::SCENE_DATASELECT);
			StartFade(FADE::FADE_ALPHA_OUT);
		}
	}
	D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// �}�E�X�̍��W

	if (CollisionBB(g_TitleSwith[0].Position, MousePos, g_TitleSwith[0].Size, D3DXVECTOR2(3.0f, 3.0f)))
	{
		if (Mouse_IsLeftDown())
		{
			if (!pFadeParam->FadeFlag)
			{
				//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
				PlaySound(g_ChangeSceneTitleSoundNo, 0);
				StartFade(FADE::FADE_ALPHA_OUT);
			}
		}
	}
	if (CollisionBB(g_TitleSwith[1].Position, MousePos, g_TitleSwith[1].Size, D3DXVECTOR2(3.0f, 3.0f)))
	{
		if (Mouse_IsLeftDown())
		{
			DestroyWindow(GetHwnd());
		}
	}





}
//======================
//�`�揈��
//======================
void	DrawTitle()
{
	//�Q�c�\�������邽�߂̃}�g���N�X��ݒ�
	SetWorldViewProjection2D();
	//�e�N�X�`���̃Z�b�g
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TitleTextureNo1));
	}

	//�X�v���C�g�̕`��
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
	for (int i = 0; i < 2; i++)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TitleSwith[i].texno));

		SpriteDrawColorRotation(g_TitleSwith[i].Position.x, g_TitleSwith[i].Position.y,0.0f,
			g_TitleSwith[i].Size.x, g_TitleSwith[i].Size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f, 1);

	}

}



