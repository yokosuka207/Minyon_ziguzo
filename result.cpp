#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
#include	"input.h"
#include	"scene.h"
#include"result.h"
//======================
//�}�N����`
//=======================
//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView	*g_ResultTexture = NULL;//�e�N�X�`�����
static	char	*g_ResultTextureName = (char*)"data\\texture\\���U���g.jpg";
static	ID3D11ShaderResourceView	*g_ResultTexture2 = NULL;//�e�N�X�`�����
static	char	*g_ResultTextureName2 = (char*)"data\\texture\\�X���C�h2.JPG";


RESULT	ResultObject;//�^�C�g����ʃI�u�W�F�N�g

int		ResultTextureNo;//�e�N�X�`���ԍ�
int		ResultTextureNo2;//�e�N�X�`���ԍ�

int ResultSoundNo;	//�^�C�g���T�E���h�ԍ�
int ResultSoundNo2;	//�^�C�g���T�E���h�ԍ�

//======================
//������
//======================
void	InitResult()
{
	//	�e�N�X�`���̃��[�h
	ResultTextureNo = LoadTexture(g_ResultTextureName);
	if (ResultTextureNo == -1)
	{//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}
	//ResultTextureNo2 = LoadTexture(g_ResultTextureName2);
	//if (ResultTextureNo2 == -1)
	//{//�ǂݍ��݃G���[
	//	exit(999);	//�����I��
	//}

	ResultObject.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0);
	ResultObject.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResultObject.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject.Rotate = 0.0f;
	//ResultObject.type = LOSE;

}
//======================
//�I������
//======================
void	UninitResult()
{
	if (g_ResultTexture)
	{
		g_ResultTexture->Release();//�g���I������̂ŉ������
		g_ResultTexture = NULL;
	}


}

//======================
//�X�V����
//======================
void	UpdateResult()
{
	//�L�[���͂̃`�F�b�N
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetScene(SCENE::SCENE_TITLE);


	}


}
//======================
//�`�揈��
//======================
void	DrawResult()
{
	//�Q�c�\�������邽�߂̃}�g���N�X��ݒ�
	SetWorldViewProjection2D();
	//�e�N�X�`���̃Z�b�g
	//if (ResultObject.type ==LOSE)
	{
	//	GetDeviceContext()->PSSetShaderResources(0, 1, Gettexture(ResultTextureNo2));

	}
	//else	if (ResultObject.type == WIN)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultTextureNo));

	}
	
	//�X�v���C�g�̕`��
	SpriteDrawColorRotation
	(
		ResultObject.Position.x,
		ResultObject.Position.y,
		ResultObject.Size.x,
		ResultObject.Size.y,
		ResultObject.Rotate,
		ResultObject.Color,
		0,
		1.0f,
		1.0f,
		1
	);

}

void SetResultType(RESULT_TYPE ty)
{
	ResultObject.type = ty;
}

RESULT * GetResult()
{
	return &ResultObject;
}
