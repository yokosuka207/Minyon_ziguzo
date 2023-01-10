
#include "tutorial.h"
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
//#include	"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "scene.h"
#include "fade.h"
//======================
//�}�N����`
//=======================
//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView* g_TutorialTexture = NULL;//�e�N�X�`�����
static	char* g_TutorialTextureName = (char*)"data\\texture\\�W�O�\�[���[���h.jpg";
static int g_TutorialTextureNo = 0;

static FADEPARAM* pFadeParam = GetFadeParam();

typedef	struct
{
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
}TUTORIAL;

TUTORIAL g_Tutorial;

void	InitTutorial() {
	//	�e�N�X�`���̃��[�h
	g_TutorialTextureNo = LoadTexture(g_TutorialTextureName);
	if (g_TutorialTextureNo == -1){
		//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}

	g_Tutorial.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	g_Tutorial.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_Tutorial.Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	g_Tutorial.Rotate = 0.0;
}
void	UninitTutorial() {
	if (g_TutorialTexture){
		g_TutorialTexture->Release();
		g_TutorialTexture = NULL;
	}
}
void	UpdateTutorial() {
	//�L�[���͂̃`�F�b�N
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
		Keyboard_IsKeyTrigger(KK_A))						// Keyboard	A
	{
		//SetScene(SCENE::SCENE_DATASELECT);
		StartFade(FADE::FADE_OUT);
	}
}
void	DrawTutorial() {
	//�Q�c�\�������邽�߂̃}�g���N�X��ݒ�
	SetWorldViewProjection2D();
	//�e�N�X�`���̃Z�b�g
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TutorialTextureNo));

	SpriteDrawColorRotation
	(
		g_Tutorial.Position.x,
		g_Tutorial.Position.y,
		0.0f,
		g_Tutorial.Size.x,
		g_Tutorial.Size.y,
		g_Tutorial.Rotate,
		g_Tutorial.Color,
		0,
		1.0f,
		1.0f,
		1
	);
}
