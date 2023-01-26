
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
//�}�N����`
//=======================
#define BUTTON_MAX	2
#define BUTTON_SIZE_X	200
#define BUTTON_SIZE_Y	100
#define BUTTON_DRAWSIZE_X	300
#define BUTTON_DRAWSIZE_Y	300
// 
//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//�e�N�X�`�����
static	char* g_TitleTextureName1 = (char*)"data\\texture\\�^�C�g���w�i.png";
//static	char* g_TitleTextureName1 = (char*)"data\\texture\\�^�C�g���w�i2.png";
//static	char* g_TitleTextureName1 = (char*)"data\\texture\\�^�C�g���w�i3.png";
static	ID3D11ShaderResourceView* g_TitleTextureButton = NULL;//�e�N�X�`�����
static	char* g_TitleStartButtonTextureName = (char*)"data\\texture\\text_start.png";

static	ID3D11ShaderResourceView* g_TitleTextureButton2 = NULL;//�e�N�X�`�����
static	char* g_TitleQuitButtonTextureName = (char*)"data\\texture\\text_quit.png";

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
//TITLE_SWITH g_TitleSwith[2];
int		TitleTextureNo1;//�e�N�X�`���ԍ�

// �{�^���n�O���[�o���ϐ�
Button g_TitleButton[2];
Button* g_pSelectTitleButton = nullptr;

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


	//g_TitleSwith[0].Position = D3DXVECTOR2(300.0f, 650.0f);
	//g_TitleSwith[0].Size = D3DXVECTOR2(200.0f, 150.0f);
	//g_TitleSwith[0].texno = LoadTexture(g_TitleStartButtonTextureName);

	//g_TitleSwith[1].Position = D3DXVECTOR2(1100.0f, 650.0f);
	//g_TitleSwith[1].Size = D3DXVECTOR2(200.0f, 150.0f);
	//g_TitleSwith[1].texno = LoadTexture(g_TitleQuitButtonTextureName);

	g_ChangeSceneTitleSoundNo = LoadSound(g_ChangeSceneTitleSoundName);

	// �{�^���̏�����
	g_TitleButton[0].Init();
	g_TitleButton[1].Init();

	// �{�^���̃Z�b�g
	g_TitleButton[0].SetButton(D3DXVECTOR2((SCREEN_WIDTH / 3) * 1, (SCREEN_HEIGHT / 5) * 4), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y),
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TitleStartButtonTextureName));
	g_TitleButton[1].SetButton(D3DXVECTOR2((SCREEN_WIDTH / 3) * 2, (SCREEN_HEIGHT / 5) * 4), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y),
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_TitleQuitButtonTextureName));

	// �I������Ă���{�^���̃��Z�b�g
	g_pSelectTitleButton = &g_TitleButton[0];
}
//======================
//�I������
//======================
void	UninitTitle()
{
	// �{�^���̏I������
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
//�X�V����
//======================
void	UpdateTitle()
{
	// �{�^���̍X�V����
	g_TitleButton[0].Update();
	g_TitleButton[1].Update();

	UpdateGameMouse();
	// �}�E�X��1�t���[���O�̍��W
	static float MouseOldPosX = GetMousePosX();
	static float MouseOldPosY = GetMousePosY();

	FADEPARAM* pFadeParam = GetFadeParam();

	//[----------�R���g���[���[�ɂ��{�^���̑I��----------
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT)) {		// GamePad �\���L�[ ��
		for (int i = 0; i < BUTTON_MAX; i++) {
			// �I�΂�Ă���{�^������������
			if (g_pSelectTitleButton == &g_TitleButton[i]) {
				// ���̃{�^�����Ō�̃{�^���Ȃ�
				if (i == BUTTON_MAX - 1) {
					// 0�Ԗڂ̃{�^����I��
					g_pSelectTitleButton = &g_TitleButton[0];
				}
				else {	// �Ō�ȊO�Ȃ�
					// ���̃{�^����I��
					g_pSelectTitleButton = &g_TitleButton[i + 1];
				}
				break;
			}
		}
	}
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT)) {		// GamePad �\���L�[ �E
		for (int i = 0; i < BUTTON_MAX; i++) {
			// �I�΂�Ă���{�^������������
			if (g_pSelectTitleButton == &g_TitleButton[i]) {
				// ���̃{�^����0�Ԗڂ̃{�^���Ȃ�
				if (i == 0) {
					// �Ō�̃{�^����I��
					g_pSelectTitleButton = &g_TitleButton[BUTTON_MAX - 1];
				}
				else {		// 0�ԖڈȊO
					// �ЂƂO�̃{�^����I��
					g_pSelectTitleButton = &g_TitleButton[i - 1];
				}
				break;
			}
		}
	}
	//----------�R���g���[���[�ɂ��{�^���̑I��----------]

	//[----------�{�^���̏���----------
	for (int i = 0; i < BUTTON_MAX; i++) {
		// �}�E�X�������Ă�����
		if (MouseOldPosX != GetMousePosX() ||
			MouseOldPosY != GetMousePosY()) {
			// �}�E�X�ƃ{�^�����������Ă����炻�̃{�^����I��
			if (g_TitleButton[i].CollisionMouse()) {
				g_pSelectTitleButton = &g_TitleButton[i];
			}
		}

		// �I�΂�Ă��邩���Ȃ���
		if (g_pSelectTitleButton == &g_TitleButton[i]) {
			// �F��ς���
			g_TitleButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// �{�^���������ꂽ���̏���
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad B
				(Mouse_IsLeftTrigger() && g_pSelectTitleButton->CollisionMouse())) {		// Mouse ���N���b�N (�������Ă����Ԃ�)
				// 0:Start �Z�[�u�V�[����
				if (i == 0) {
					//SetVolume(g_ChangeSceneTitleSoundNo, 0.5f);
					PlaySound(g_ChangeSceneTitleSoundNo, 0);
					// �Z�[�u�f�[�^�I����
					StartFade(FADE::FADE_ALPHA_OUT);
				}
				// 1:Quit �Q�[�������I��
				else {
					GameEnd();
				}
				g_pSelectTitleButton->ChangeType();
				break;
			}
		}
		else {
			// �F��ς���
			g_TitleButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
		}
	}

	// ���ɔ�����1�t���[���O�̍��W�ɓ����
	MouseOldPosX = GetMousePosX();
	MouseOldPosY = GetMousePosY();
	//----------�{�^���̏���----------]
	////�L�[���͂̃`�F�b�N
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
	//D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// �}�E�X�̍��W

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
	// �{�^���̏I������
	g_TitleButton[0].Draw();
	g_TitleButton[1].Draw();
	//for (int i = 0; i < 2; i++)
	//{
	//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TitleSwith[i].texno));

	//	SpriteDrawColorRotation(g_TitleSwith[i].Position.x, g_TitleSwith[i].Position.y,0.0f,
	//		g_TitleSwith[i].Size.x, g_TitleSwith[i].Size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f, 1);

	//}

}



