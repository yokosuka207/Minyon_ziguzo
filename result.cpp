#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
//#include	"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include	"scene.h"
#include	"result.h"
#include	"mouse.h"
#include	"time.h"
#include	"score.h"
#include	"fade.h"
#include	"sound.h"
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
static	char* g_ResultBGTextureName = (char*)"data\\texture\\black.png";

//static	char* g_ResultGameEndTextureName = (char*)"data\\texture\\black.png";

// �{�^���̃e�N�X�`��
static	char* g_ResultButtonTextureName[BUTTON_MAX] = { (char*)"data\\texture\\text_exit stage.png" ,
												(char*)"data\\texture\\text_continue game.png" };

static int g_ChangeSceneResultSoundNo = 0;
static char g_ChangeSceneResultSoundName[] = "data\\SoundData\\SE\\�V�[���J��(������).wav";



RESULT	ResultObject;//�^�C�g����ʃI�u�W�F�N�g	�w�i��

int		ResultBGTextureNo;//�e�N�X�`���ԍ�

//int		ResultGameEndTextureNo;//�e�N�X�`���ԍ�
int		ResultButtonTextureNo[BUTTON_MAX];//�e�N�X�`���ԍ�

int ResultSoundNo;	//�^�C�g���T�E���h�ԍ�
int ResultSoundNo2;	//�^�C�g���T�E���h�ԍ�

static Time* pTime = pTime->GetTime();
static TimeParam*	pTimeParam = pTime->GetTimeParam();
static Score* pScore = pScore->GetScore();
static FADEPARAM* pFadeParam = GetFadeParam();
static ANIMEPARAM* pAnimeParam = pScore->GetAnimeParam();

// �{�^��
Button g_ResultButton[BUTTON_MAX];
Button* g_pSelectResultButton = nullptr;
//======================
//������
//======================
void	InitResult()
{
	//	�e�N�X�`���̃��[�h
	ResultBGTextureNo = LoadTexture(g_ResultBGTextureName);
	if (ResultBGTextureNo == -1)
	{//�ǂݍ��݃G���[
		exit(999);	//�����I��
	}
	//ResultGameEndTextureNo = LoadTexture(g_ResultGameEndTextureName);
	//if (ResultGameEndTextureNo == -1)
	//{//�ǂݍ��݃G���[
	//	exit(999);	//�����I��
	//}

	for (int i = 0; i < BUTTON_MAX; i++) {
		ResultButtonTextureNo[i] = LoadTexture(g_ResultButtonTextureName[i]);
		if (ResultButtonTextureNo[i] == -1)
		{//�ǂݍ��݃G���[
			exit(999);	//�����I��
		}
	}

	// �w�i��
	ResultObject.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	ResultObject.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResultObject.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject.Rotate = 0.0f;

	// �{�^���̏������ƃZ�b�g
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_ResultButton[i].Init();
		g_ResultButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 4) * (i * 2 + 1)), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y), 
			D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_ResultButtonTextureName[i]));
	}
	// �I������Ă���{�^���̏�����
	g_pSelectResultButton = &g_ResultButton[0];

	pScore->SetScore(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50), D3DXVECTOR2(50.0f, 50.0f));

	g_ChangeSceneResultSoundNo = LoadSound(g_ChangeSceneResultSoundName);
}
//======================
//�I������
//======================
void	UninitResult()
{
	// �{�^���̏I������
	for (Button& b : g_ResultButton) {
		b.Uninit();
	}

	StopSound(g_ChangeSceneResultSoundNo);
}

//======================
//�X�V����
//======================
void	UpdateResult()
{
	UpdateGameMouse();

	// �}�E�X��1�t���[���O�̍��W
	static float MouseOldPosX = GetMousePosX();
	static float MouseOldPosY = GetMousePosY();

	FADEPARAM* pFadeParam = GetFadeParam();
	if (ResultObject.type == WIN) 
	{
		//�L�[���͂̃`�F�b�N
		if (Keyboard_IsKeyTrigger(KK_SPACE) ||				// keyboard SPACE
			IsButtonTriggered(0, XINPUT_GAMEPAD_B))			// GamePad B
		{
			//SetVolume(g_ChangeSceneResultSoundNo, 0.5f);
			PlaySound(g_ChangeSceneResultSoundNo, 0);
			// �X�e�[�W�Z���N�g��
			StartFade(FADE::FADE_ALPHA_OUT);
		}
	}
	else if (ResultObject.type == LOSE)
	{
		// �{�^���̍X�V����
		for (Button& b : g_ResultButton) {
			b.Update();
		}
		//[----------�R���g���[���[�ɂ��{�^���̑I��----------
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP)) {		// GamePad �\���L�[ ��
			for (int i = 0; i < BUTTON_MAX; i++) {
				// �I�΂�Ă���{�^������������
				if (g_pSelectResultButton == &g_ResultButton[i]) {
					// ���̃{�^�����Ō�̃{�^���Ȃ�
					if (i == BUTTON_MAX - 1) {
						// 0�Ԗڂ̃{�^����I��
						g_pSelectResultButton = &g_ResultButton[0];
					}
					else {	// �Ō�ȊO�Ȃ�
						// ���̃{�^����I��
						g_pSelectResultButton = &g_ResultButton[i + 1];
					}
					break;
				}
			}
		}
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN)) {		// GamePad �\���L�[ ��
			for (int i = 0; i < BUTTON_MAX; i++) {
				// �I�΂�Ă���{�^������������
				if (g_pSelectResultButton == &g_ResultButton[i]) {
					// ���̃{�^����0�Ԗڂ̃{�^���Ȃ�
					if (i == 0) {
						// �Ō�̃{�^����I��
						g_pSelectResultButton = &g_ResultButton[BUTTON_MAX - 1];
					}
					else {		// 0�ԖڈȊO
						// �ЂƂO�̃{�^����I��
						g_pSelectResultButton = &g_ResultButton[i - 1];
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
				if (g_ResultButton[i].CollisionMouse()) {
					g_pSelectResultButton = &g_ResultButton[i];
				}
			}

			// �I�΂�Ă��邩���Ȃ���
			if (g_pSelectResultButton == &g_ResultButton[i]) {
				// �F��ς���
				g_ResultButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// �{�^���������ꂽ���̏���
				if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad B
					(Mouse_IsLeftTrigger() && g_pSelectResultButton->CollisionMouse())) {		// Mouse ���N���b�N (�������Ă����Ԃ�)
					// 0:Exit Stage �X�e�[�W�Z���N�g�V�[����
					if (i == 0) {
						//SetVolume(g_ChangeSceneResultSoundNo, 0.5f);
						PlaySound(g_ChangeSceneResultSoundNo, 0);
						// �X�e�[�W�Z���N�g��
						StartFade(FADE::FADE_ALPHA_OUT);
					}
					// 1:Continue �Q�[���V�[����
					else {
						//SetVolume(g_ChangeSceneResultSoundNo, 0.5f);
						PlaySound(g_ChangeSceneResultSoundNo, 0);
						pFadeParam->ExceptFlag = true;
						StartFade(FADE::FADE_ALPHA_OUT);
					}
					g_pSelectResultButton->ChangeType();
					break;
				}
			}
			else {
				// �F��ς���
				g_ResultButton[i].SetButtonColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));
			}
		}
		// ���ɔ�����1�t���[���O�̍��W�ɓ����
		MouseOldPosX = GetMousePosX();
		MouseOldPosY = GetMousePosY();

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
	if (ResultObject.type == LOSE)		// �Q�[���I�[�o�[
	{
		// �w�i
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultBGTextureNo));
		//�X�v���C�g�̕`��
		SpriteDrawColorRotation
		(
			ResultObject.Position.x,
			ResultObject.Position.y,
			0.0f,
			ResultObject.Size.x,
			ResultObject.Size.y,
			ResultObject.Rotate,
			ResultObject.Color,
			0,
			1.0f,
			1.0f,
			1
		);

		// �{�^��
		for (Button& b : g_ResultButton) {
			b.Draw();
		}
	}
	else if (ResultObject.type == WIN)		// �N���A
	{

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultBGTextureNo));

		//�X�v���C�g�̕`��
		SpriteDrawColorRotation
		(
			ResultObject.Position.x,
			ResultObject.Position.y,
			0.0f,
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
}

void SetResultType(RESULT_TYPE ty)
{
	ResultObject.type = ty;
}

RESULT* GetResult()
{
	return &ResultObject;
}
