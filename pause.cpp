
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
#include	"sound.h"

//======================
//�}�N����`
//=======================
#define BUTTON_MAX	3
#define BUTTON_SIZE_X	200
#define BUTTON_SIZE_Y	100
#define BUTTON_DRAWSIZE_X	400
#define BUTTON_DRAWSIZE_Y	400

//======================
//�O���[�o���ϐ�
//======================
//�w�i�e�N�X�`��
static	char* g_PauseTextureName = (char*)"data\\texture\\black.png";
//�R���g���[���[
static	char* g_PauseOperationTextureName = (char*)"data\\texture\\�������.png";
static	char* g_PauseButtonTextureName[BUTTON_MAX] = { (char*)"data\\texture\\text_continue game.png" ,	//countinue
														(char*)"data\\texture\\text_exit stage.png",   //���Z�b�g 
														(char*)"data\\texture\\text_exit stage.png" };//�X�e�[�W�Z���N�g���

//�T�E���h
static int g_ChangeScenePauseSoundNo = 0;
static char g_ChangeScenePauseSoundName[] = "data\\SoundData\\SE\\�V�[���J��(������).wav";

PAUSE	PauseObject[2];//�^�C�g����ʃI�u�W�F�N�g

int		PauseTextureNo = 0;			//�e�N�X�`���ԍ�
int		PauseOperationTextureNo = 0;//�e�N�X�`���ԍ�

static bool		PauseFlag, PauseClick;

Button g_PauseButton[BUTTON_MAX];
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

	PauseFlag = false;
	PauseClick = false;

	// �T�E���h���[�h
	g_ChangeScenePauseSoundNo = LoadSound(g_ChangeScenePauseSoundName);
	
	// �{�^���̏�����
	for (Button& b : g_PauseButton) {
		b.Init();
	}

	// �{�^���̃Z�b�g
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_PauseButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 6) * (i+3) + 50), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y),
			D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_PauseButtonTextureName[i]));
	}

	// �I������Ă���{�^���̃��Z�b�g
	g_pSelectPauseButton = &g_PauseButton[0];
}
//======================
//�I������
//======================
void	UninitPause()
{
	// �{�^���̏I������
	for (Button& b : g_PauseButton) {
		b.Uninit();
	}

	StopSound(g_ChangeScenePauseSoundNo);
}

//======================
//�X�V����
//======================
void	UpdatePause()
{
	if (PauseFlag) 
	{
		// �{�^���̍X�V����
		for (Button& b : g_PauseButton) {
			b.Update();
		}

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
						SetVolume(g_ChangeScenePauseSoundNo, 0.3f);
						PlaySound(g_ChangeScenePauseSoundNo, 0);
						SetScene(SCENE::SCENE_GAME);
						PauseClick = true;
					}
					// 1:Reset ���Z�b�g���ăQ�[���ɖ߂�
					else if(i == 1){
						SetVolume(g_ChangeScenePauseSoundNo, 0.3f);
						PlaySound(g_ChangeScenePauseSoundNo, 0);
						ResetGame();
						SetScene(SCENE::SCENE_GAME);
						PauseClick = true;
					}
					else if(i == 2){
						SetVolume(g_ChangeScenePauseSoundNo, 0.3f);
						PlaySound(g_ChangeScenePauseSoundNo, 0);
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
		for (Button& b : g_PauseButton) {
			b.Draw();
		}

	}
}

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