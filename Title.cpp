
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include	"scene.h"
#include	"fade.h"
//======================
//�}�N����`
//=======================
//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//�e�N�X�`�����
static	char	*g_TitleTextureName1 = (char*)"data\\texture\\�^�C�g���w�i���Q.png";

typedef	struct
{
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
}TITLE;

TITLE	TitleObject;//�^�C�g����ʃI�u�W�F�N�g

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
	TitleObject.Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	TitleObject.Rotate = 0.0;

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
	}
}

//======================
//�X�V����
//======================
void	UpdateTitle()
{
	//�L�[���͂̃`�F�b�N
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) ||			// GamePad	A
		Keyboard_IsKeyTrigger(KK_A))						// Keyboard	A
	{
		//SetScene(SCENE::SCENE_DATASELECT);
		StartFade(FADE::FADE_ALPHA_OUT);
		
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


}



