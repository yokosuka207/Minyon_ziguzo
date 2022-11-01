
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
#include	"input.h"
#include	"scene.h"

//======================
//�}�N����`
//=======================
//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//�e�N�X�`�����
static	char	*g_TitleTextureName1 = (char*)"data\\texture\\�^�C�g��.jpg";

static	ID3D11ShaderResourceView	*g_TitleTexture2 = NULL;//�e�N�X�`�����
static	char	*g_TitleTextureName2 = (char*)"data\\texture\\�W�O�\�[���[���h.jpg";

typedef	struct
{
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
}TITLE;

TITLE	TitleObject;//�^�C�g����ʃI�u�W�F�N�g

int		TitleTextureNo1;//�e�N�X�`���ԍ�
int		TitleTextureNo2;//�e�N�X�`���ԍ�

int TitleNum;
//======================
//������
//======================
void	InitTitle()
{
	TitleNum = 0;
	//	�e�N�X�`���̃��[�h
	TitleTextureNo1 = LoadTexture(g_TitleTextureName1);
	if (TitleTextureNo1 == -1)
	{//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}
	TitleTextureNo2 = LoadTexture(g_TitleTextureName2);
	if (TitleTextureNo2 == -1)
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


	if (g_TitleTexture2)
	{
		g_TitleTexture2->Release();
		g_TitleTexture2 = NULL;
	}

}

//======================
//�X�V����
//======================
void	UpdateTitle()
{
	//�L�[���͂̃`�F�b�N
	if (GetKeyboardTrigger(DIK_A))
	{
		if (TitleNum == 1)
		{
			SetScene(SCENE::SCENE_GAME);

		}
		if (TitleNum == 0)
		{
			TitleNum++;
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
	if (TitleNum == 0)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TitleTextureNo1));
	}
	if (TitleNum == 1)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TitleTextureNo2));
	}

	//�X�v���C�g�̕`��
	SpriteDrawColorRotation
	(
		TitleObject.Position.x,
		TitleObject.Position.y,
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



