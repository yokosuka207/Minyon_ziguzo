
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include	"xinput.h"
#include	"xkeyboard.h"
#include	"scene.h"
#include	"result.h"
#include	"mouse.h"
#include	"time.h"
#include	 "pause.h"
#include	"game.h"
#include	"button.h"

//======================
//�}�N����`
//=======================
#define BUTTON_MAX	2
#define BUTTON_SIZE_X	200
#define BUTTON_SIZE_Y	100
#define BUTTON_DRAWSIZE_X	400
#define BUTTON_DRAWSIZE_Y	400

//======================
//�O���[�o���ϐ�
//======================
static	ID3D11ShaderResourceView* g_PauseTexture = NULL;//�e�N�X�`�����
static	char* g_PauseTextureName = (char*)"data\\texture\\black.png";

static	ID3D11ShaderResourceView* g_PauseOperationTexture = NULL;//����������
static	char* g_PauseOperationTextureName = (char*)"data\\texture\\�������.png";

static	ID3D11ShaderResourceView* g_PauseEndTexture = NULL;//�e�N�X�`�����
static	char* g_PauseEndTextureName = (char*)"data\\texture\\text_continue game.png";

static	ID3D11ShaderResourceView* g_PauseSelectTexture = NULL;//�e�N�X�`�����
static	char* g_PauseSelectTextureName = (char*)"data\\texture\\text_exit stage.png";

PAUSE	PauseObject[5];//�^�C�g����ʃI�u�W�F�N�g

int		PauseTextureNo = 0;			//�e�N�X�`���ԍ�
int		PauseOperationTextureNo = 0;//�e�N�X�`���ԍ�
int		PauseEndTextureNo = 0;		//�e�N�X�`���ԍ�
int		PauseSelectTextureNo = 0;	//�e�N�X�`���ԍ�

static bool		PauseFlag, PauseClick;

Button g_PauseButton[2];
Button* g_pSelectPauseButton = nullptr;
//======================
//������
//======================
void	InitPause()
{
	//	�e�N�X�`���̃��[�h
	PauseTextureNo = LoadTexture(g_PauseTextureName);
	PauseOperationTextureNo = LoadTexture(g_PauseOperationTextureName);

	//�w�i�e�N�X�`��
	PauseObject[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	PauseObject[0].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	PauseObject[0].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[0].Rotate = 0.0;

	//�R���g���[���[
	PauseObject[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0);
	PauseObject[1].Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	PauseObject[1].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[1].Rotate = 0.0;

	//�Q�[���ɖ߂�I���e�N�X�`��
	PauseObject[2].Position = D3DXVECTOR3(711 , 500.0f, 0);
	PauseObject[2].Size = D3DXVECTOR2(SCREEN_WIDTH / 4 / 3, SCREEN_HEIGHT / 4/ 3);
	PauseObject[2].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[2].Rotate = 0.0f;

	//�Q�[�����Z�b�g�I���e�N�X�`��
	PauseObject[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	PauseObject[3].Size = D3DXVECTOR2(0, 0);
	PauseObject[3].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[3].Rotate = 0.0;

	//�Q�[���I����ʂɖ߂�e�N�X�`��
	PauseObject[4].Position = D3DXVECTOR3(711, 600, 0);
	PauseObject[4].Size = D3DXVECTOR2(SCREEN_WIDTH / 4 / 3, SCREEN_HEIGHT / 4 / 3);
	PauseObject[4].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	PauseObject[4].Rotate = 0.0f;


	PauseFlag = false;
	PauseClick = false;

	// �{�^���̃e�N�X�`���̃��[�h
	PauseEndTextureNo = LoadTexture(g_PauseEndTextureName);
	PauseSelectTextureNo = LoadTexture(g_PauseSelectTextureName);

	// �{�^���̏�����
	g_PauseButton[0].Init();
	g_PauseButton[1].Init();

	// �{�^���̃Z�b�g
	g_PauseButton[0].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 5) * 3 + 50), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y), 
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PauseEndTextureNo);
	g_PauseButton[1].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 5) * 4 + 50), D3DXVECTOR2(BUTTON_SIZE_X * 1.5f, BUTTON_SIZE_Y), 
		D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PauseSelectTextureNo);

	// �I������Ă���{�^���̃��Z�b�g
	g_pSelectPauseButton = &g_PauseButton[0];
}
//======================
//�I������
//======================
void	UninitPause()
{
	// �{�^���̏I������
	g_PauseButton[0].Uninit();
	g_PauseButton[1].Uninit();

	if (g_PauseTexture)
	{
		g_PauseTexture->Release();
		g_PauseTexture = NULL;
	}

	if(g_PauseOperationTexture)
	{
		g_PauseOperationTexture->Release();
		g_PauseOperationTexture = NULL;
	}

	if (g_PauseEndTexture)
	{
		g_PauseEndTexture->Release();
		g_PauseEndTexture = NULL;
	}

	if (g_PauseSelectTexture)
	{
		g_PauseSelectTexture->Release();
		g_PauseSelectTexture = NULL;
	}

}

//======================
//�X�V����
//======================
void	UpdatePause()
{
	if (PauseFlag) 
	{
		// �{�^���̍X�V����
		g_PauseButton[0].Update();
		g_PauseButton[1].Update();

		// �}�E�X��1�t���[���O�̍��W
		static float MouseOldPosX = GetMousePosX();
		static float MouseOldPosY = GetMousePosY();

		//[----------�R���g���[���[�ɂ��{�^���̑I��----------
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN)) {		// GamePad �\���L�[�@��
			for (int i = 0; i < BUTTON_MAX; i++) {
				// �I�΂�Ă���{�^������������
				if (g_pSelectPauseButton == &g_PauseButton[i]) {
					// ���̃{�^�����Ō�̃{�^���Ȃ�
					if (i == BUTTON_MAX - 1) {
						// 0�Ԗڂ̃{�^����I��
						g_pSelectPauseButton = &g_PauseButton[0];
					}
					else {	// �Ō�ȊO�Ȃ�
						// ���̃{�^����I��
						g_pSelectPauseButton = &g_PauseButton[i + 1];
					}
					break;
				}
			}
		}
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP)) {		// GamePad �\���L�[�@��
			for (int i = 0; i < BUTTON_MAX; i++) {
				// �I�΂�Ă���{�^������������
				if (g_pSelectPauseButton == &g_PauseButton[i]) {
					// ���̃{�^����0�Ԗڂ̃{�^���Ȃ�
					if (i == 0) {
						// �Ō�̃{�^����I��
						g_pSelectPauseButton = &g_PauseButton[BUTTON_MAX - 1];
					}
					else {		// 0�ԖڈȊO
						// �ЂƂO�̃{�^����I��
						g_pSelectPauseButton = &g_PauseButton[i - 1];
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
				if (g_PauseButton[i].CollisionMouse()) {
					g_pSelectPauseButton = &g_PauseButton[i];
				}
			}

			// �I�΂�Ă��邩���Ȃ���
			if (g_pSelectPauseButton == &g_PauseButton[i]) {
				// �F��ς���
				g_PauseButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// �{�^���������ꂽ���̏���
				if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad B
					(Mouse_IsLeftTrigger() && g_pSelectPauseButton->CollisionMouse())) {		// Mouse ���N���b�N
					// 0:Quit �Q�[���ɖ߂�
					if (i == 0) {
						SetScene(SCENE::SCENE_GAME);
						PauseClick = true;
					}
					// 1:Exit Stage �X�e�[�W�Z���N�g�ɖ߂�
					else {
						SetScene(SCENE::SCENE_STAGESELECT);
					}
					g_pSelectPauseButton->ChangeType();
					break;
				}
			}
			else {
				// �F��ς���
				g_PauseButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
			}
		}
		// ���ɔ�����1�t���[���O�̍��W�ɓ����
		MouseOldPosX = GetMousePosX();
		MouseOldPosY = GetMousePosY();
		//----------�{�^���̏���----------]

	}
}
//======================
//�`�揈��
//======================
void	DrawPause()
{
	//�Q�c�\�������邽�߂̃}�g���N�X��ݒ�
	SetWorldViewProjection2D();
	//�e�N�X�`���̃Z�b�g


	//�X�v���C�g�̕`��
	

	//�V�[�����
	if (PauseFlag)
	{
		//�w�i�e�N�X�`��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseTextureNo));
		SpriteDrawColorRotation
		(
			PauseObject[0].Position.x,
			PauseObject[0].Position.y,
			-0.0f,
			PauseObject[0].Size.x,
			PauseObject[0].Size.y,
			PauseObject[0].Rotate,
			PauseObject[0].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		//�R���g���[���[
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseOperationTextureNo));
		SpriteDrawColorRotation
		(
			PauseObject[1].Position.x,
			PauseObject[1].Position.y,
			0.0f,
			PauseObject[1].Size.x,
			PauseObject[1].Size.y,
			PauseObject[1].Rotate,
			PauseObject[1].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		// �{�^���̕`�揈��
		g_PauseButton[0].Draw();
		g_PauseButton[1].Draw();

		////�Q�[���ɖ߂�I���e�N�X�`��
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseEndTextureNo));
		//SpriteDrawColorRotation
		//(
		//	PauseObject[2].Position.x,
		//	PauseObject[2].Position.y,
		//	0.0f,		
		//	PauseObject[2].Size.x,
		//	PauseObject[2].Size.y,
		//	PauseObject[2].Rotate,
		//	PauseObject[2].Color,
		//	0,
		//	1.0f,
		//	1.0f,
		//	1
		//);

		//�Q�[�����Z�b�g�I���e�N�X�`��
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseResetTextureNo));
		//SpriteDrawColorRotation
		//(
		//	PauseObject[3].Position.x,
		//	PauseObject[3].Position.y,
		//	0.0f,		
		//	PauseObject[3].Size.x,
		//	PauseObject[3].Size.y,
		//	PauseObject[3].Rotate,
		//	PauseObject[3].Color,
		//	0,
		//	1.0f,
		//	1.0f,
		//	1
		//);

		////�Q�[���I����ʂɖ߂�e�N�X�`��
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(PauseSelectTextureNo));
		//SpriteDrawColorRotation
		//(
		//	PauseObject[4].Position.x,
		//	PauseObject[4].Position.y,
		//	0.0f,		
		//	PauseObject[4].Size.x,
		//	PauseObject[4].Size.y,
		//	PauseObject[4].Rotate,
		//	PauseObject[4].Color,
		//	0,
		//	1.0f,
		//	1.0f,
		//	1
		//);
	}
}

//void SetPause(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col)
//{
//	PauseObject[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
//	PauseObject[0].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
//	PauseObject[0].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
//	PauseObject[0].Rotate = 0.0;
//
//	PauseObject[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
//	PauseObject[1].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
//	PauseObject[1].Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
//	PauseObject[1].Rotate = 0.0;
//}

bool* GetPause() {
	return &PauseFlag;
}
bool* GetPauseMause()
{
	return &PauseClick;
}

void PauseSeletct()
{

}