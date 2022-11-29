#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
#include	"input.h"
#include	"scene.h"
#include	"result.h"
#include	"mouse.h"
//======================
//�}�N����`
//=======================
//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView* g_ResultTexture = NULL;//�e�N�X�`�����
static	char* g_ResultTextureName = (char*)"data\\texture\\���U���g.jpg";

static	ID3D11ShaderResourceView* g_ResultGameEndTexture = NULL;//�e�N�X�`�����
static	char* g_ResultGameEndTextureName = (char*)"data\\texture\\GameEnd_haikei.jpg";

static	ID3D11ShaderResourceView* g_ResultTextureButton = NULL;//�e�N�X�`�����
static	char* g_ResultButtonTextureName = (char*)"data\\texture\\GameEnd_contie_button.jpg";

static	ID3D11ShaderResourceView* g_ResultTextureButton2 = NULL;//�e�N�X�`�����
static	char* g_ResultButtonTextureName2 = (char*)"data\\texture\\GameEnd_end_button.jpg";


RESULT	ResultObject[3];//�^�C�g����ʃI�u�W�F�N�g	�e�N�X�`���������̔z��

int		ResultTextureNo;//�e�N�X�`���ԍ�

int		ResultGameEndTextureNo;//�e�N�X�`���ԍ�
int		ResultButtonTextureNo;//�e�N�X�`���ԍ�
int		ResultButtonTextureNo2;//�e�N�X�`���ԍ�

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
	ResultGameEndTextureNo = LoadTexture(g_ResultGameEndTextureName);
	if (ResultGameEndTextureNo == -1)
	{//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}
	ResultButtonTextureNo = LoadTexture(g_ResultButtonTextureName);
	if (ResultButtonTextureNo == -1)
	{//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}
	ResultButtonTextureNo2 = LoadTexture(g_ResultButtonTextureName2);
	if (ResultButtonTextureNo2 == -1)
	{//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}

	ResultObject[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	ResultObject[0].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResultObject[0].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject[0].Rotate = 0.0f;
	//ResultObject[0].type = LOSE;

	ResultObject[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0);
	ResultObject[1].Size = D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8);
	ResultObject[1].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject[1].Rotate = 0.0f;

	ResultObject[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 0);
	ResultObject[2].Size = D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8);
	ResultObject[2].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject[2].Rotate = 0.0f;

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

	if (g_ResultGameEndTexture)
	{
		g_ResultGameEndTexture->Release();//�g���I������̂ŉ������
		g_ResultGameEndTexture = NULL;
	}

	if (g_ResultTextureButton)
	{
		g_ResultTextureButton->Release();//�g���I������̂ŉ������
		g_ResultTextureButton = NULL;
	}

	if (g_ResultTextureButton2)
	{
		g_ResultTextureButton2->Release();//�g���I������̂ŉ������
		g_ResultTextureButton2 = NULL;
	}

}

//======================
//�X�V����
//======================
void	UpdateResult()
{
	if (ResultObject[0].type == WIN) 
	{
		//�L�[���͂̃`�F�b�N
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			SetScene(SCENE::SCENE_TITLE);
		}
	}
	else if (ResultObject[0].type == LOSE)
	{
		MOUSE* pMouse = GetMouse();
		D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// �}�E�X�̍��W

		// �����蔻��p���W
		D3DXVECTOR2 min, max, min2, max2;		// min����, max�E��
		min = D3DXVECTOR2(ResultObject[1].Position.x - ResultObject[1].Size.x / 2, ResultObject[1].Position.y - ResultObject[1].Size.y / 2);
		max = D3DXVECTOR2(ResultObject[1].Position.x + ResultObject[1].Size.x / 2, ResultObject[1].Position.y + ResultObject[1].Size.y / 2);
		min2 = D3DXVECTOR2(ResultObject[2].Position.x - ResultObject[2].Size.x / 2, ResultObject[2].Position.x - ResultObject[2].Size.x / 2);
		max2 = D3DXVECTOR2(ResultObject[2].Position.x + ResultObject[2].Size.x / 2, ResultObject[2].Position.x + ResultObject[2].Size.x / 2);

		// �}�E�X��continy�{�^���̓����蔻��
		if (IsMouseLeftPressed())
		{
			if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y) 
			{
				SetScene(SCENE::SCENE_GAME);
			}
		}
		
		// �}�E�X�ƏI���{�^���̓����蔻��
		if (IsMouseLeftPressed())
		{
			if (min2.x < MousePos.x && max2.x > MousePos.x && min2.y < MousePos.y && max2.y > MousePos.y)
			{
				SetScene(SCENE::SCENE_TITLE);
			}
		}
		
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
	if (ResultObject[0].type == LOSE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultGameEndTextureNo));
		//�X�v���C�g�̕`��
		SpriteDrawColorRotation
		(
			ResultObject[0].Position.x,
			ResultObject[0].Position.y,
			ResultObject[0].Size.x,
			ResultObject[0].Size.y,
			ResultObject[0].Rotate,
			ResultObject[0].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultButtonTextureNo));
		SpriteDrawColorRotation
		(//countinuButton
			ResultObject[1].Position.x,
			ResultObject[1].Position.y,
			ResultObject[1].Size.x,
			ResultObject[1].Size.y,
			ResultObject[1].Rotate,
			ResultObject[1].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultButtonTextureNo2));
		SpriteDrawColorRotation
		(//endButton
			ResultObject[2].Position.x,
			ResultObject[2].Position.y,
			ResultObject[2].Size.x,
			ResultObject[2].Size.y,
			ResultObject[2].Rotate,
			ResultObject[2].Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}
	else if (ResultObject[0].type == WIN)
	{

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultTextureNo));

		//�X�v���C�g�̕`��
		SpriteDrawColorRotation
		(
			ResultObject[0].Position.x,
			ResultObject[0].Position.y,
			ResultObject[0].Size.x,
			ResultObject[0].Size.y,
			ResultObject[0].Rotate,
			ResultObject[0].Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

}

void SetResultType(RESULT_TYPE ty)
{
	ResultObject[0].type = ty;
}

RESULT* GetResult()
{
	return &ResultObject[0];
}
