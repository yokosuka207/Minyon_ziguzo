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
#include "player.h"
#include "StageSelect.h"
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

// �{�^���̃e�N�X�`��
static	char* g_ResultButtonTextureName[BUTTON_MAX] = { (char*)"data\\texture\\text_exit stage.png" ,
												(char*)"data\\texture\\text_continue game.png" };

static	char* g_ResultLifeTextureName = (char*)"data\\texture\\text_life.png";
static	char* g_ResultLifeMaxTextureName = (char*)"data\\texture\\�c�@����.png";
static	char* g_ResultLifeVolumeTextureName = (char*)"data\\texture\\�c�@�Ȃ�.png";
static	char* g_ResultScoreTextureName = (char*)"data\\texture\\text_score.png";
static	char* g_ResultRankTextureName = (char*)"data\\texture\\text_rank.png";
static	char* g_ResultTimeTextureName = (char*)"data\\texture\\text_time.png";
static	char* g_ResultClearTextureName = (char*)"data\\texture\\text_gameclear.png";
static	char* g_ResultOverTextureName = (char*)"data\\texture\\text_gameover.png";

static int g_ResultLifeTextureNo = 0;
static int g_ResultLifeMaxTextureNo = 0;
static int g_ResultLifeVolumeTextureNo = 0;
static int g_ResultScoreTextureNo = 0;
static int g_ResultRankTextureNo = 0;
static int g_ResultTimeTextureNo = 0;
static int g_ResultClearTextureNo = 0;
static int g_ResultOverTextureNo = 0;

static int g_ChangeSceneResultSoundNo = 0;
static char g_ChangeSceneResultSoundName[] = "data\\SoundData\\SE\\�V�[���J��(������).wav";


RESULT	ResultObject;//�^�C�g����ʃI�u�W�F�N�g	�w�i��

RESULT g_Result[RESULT_MAX];

RESULT g_ResultLife;

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

	for (int i = 0; i < RESULT_MAX; i++) {
		g_Result[i].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Result[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_Result[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Result[i].UseFlag = false;
	}
	
	g_ResultLife.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f, 0.0f);
	g_ResultLife.Size = D3DXVECTOR2(200.0f, 200.0f);
	g_ResultLife.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ResultLife.UseFlag = false;
	
	g_ResultLifeTextureNo = LoadTexture(g_ResultLifeTextureName);
	g_ResultLifeMaxTextureNo = LoadTexture(g_ResultLifeMaxTextureName);
	g_ResultLifeVolumeTextureNo = LoadTexture(g_ResultLifeVolumeTextureName);
	g_ResultScoreTextureNo = LoadTexture(g_ResultScoreTextureName);
	g_ResultRankTextureNo = LoadTexture(g_ResultRankTextureName);
	g_ResultTimeTextureNo = LoadTexture(g_ResultTimeTextureName);
	g_ResultClearTextureNo = LoadTexture(g_ResultClearTextureName);
	g_ResultOverTextureNo = LoadTexture(g_ResultOverTextureName);

	// �{�^���̏������ƃZ�b�g
	for (int i = 0; i < BUTTON_MAX; i++) {
		g_ResultButton[i].Init();
		g_ResultButton[i].SetButton(D3DXVECTOR2(SCREEN_WIDTH / 3 *(i + 1), (SCREEN_HEIGHT / 5) * 4), D3DXVECTOR2(BUTTON_SIZE_X, BUTTON_SIZE_Y), 
			D3DXVECTOR2(BUTTON_DRAWSIZE_X, BUTTON_DRAWSIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LoadTexture(g_ResultButtonTextureName[i]));
	}
	// �I������Ă���{�^���̏�����
	g_pSelectResultButton = &g_ResultButton[0];

	pScore->SetScore(D3DXVECTOR2(SCORE_POS_X, SCREEN_HEIGHT / 2 + 90.0f), D3DXVECTOR2(50.0f, 50.0f));

	SetResult(D3DXVECTOR3(SCREEN_WIDTH / 2 - 410.0f, 280.0f, 0.0f), D3DXVECTOR2(500.0f, 500.0f));//Life
	SetResult(D3DXVECTOR3(SCREEN_WIDTH / 2 - 390.0f, 500.0f, 0.0f), D3DXVECTOR2(300.0f, 300.0f));//Score
	SetResult(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400.0f, 250.0f, 0.0f), D3DXVECTOR2(500.0f, 500.0f));//Rank
	SetResult(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400.0f, 400.0f, 0.0f), D3DXVECTOR2(500.0f, 500.0f));//Time
	SetResult(D3DXVECTOR3(SCREEN_WIDTH / 2, 70.0f, 0.0f), D3DXVECTOR2(600.0f, 600.0f));//Clear,Over

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
		if (ReturnStageNo() == STAGE_MAX - 1) {
			//�L�[���͂̃`�F�b�N
			if (Keyboard_IsKeyTrigger(KK_SPACE) ||				// keyboard SPACE
				IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT) ||		// GamePad B
				IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT))			// GamePad B
			{
				//SetVolume(g_ChangeSceneResultSoundNo, 0.5f);
				PlaySound(g_ChangeSceneResultSoundNo, 0);
				pFadeParam->FinFlag = true;
				StartFade(FADE::FADE_ALPHA_OUT);

			}
		}
		else {
			// �{�^���̍X�V����
			for (Button& b : g_ResultButton) {
				b.Update();
			}
			//[----------�R���g���[���[�ɂ��{�^���̑I��----------
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT)) {		// GamePad �\���L�[ ��
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
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT)) {		// GamePad �\���L�[ ��
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
	else if (ResultObject.type == LOSE)
	{
		// �{�^���̍X�V����
		for (Button& b : g_ResultButton) {
			b.Update();
		}
		//[----------�R���g���[���[�ɂ��{�^���̑I��----------
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT)) {		// GamePad �\���L�[ ��
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
		if (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT)) {		// GamePad �\���L�[ ��
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
		//�^�C��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultTimeTextureNo));
		g_Result[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 390.0f, 400.0f, 0.0f);
		SpriteDrawColorRotation
		(
			g_Result[3].Position.x,
			g_Result[3].Position.y,
			0.0f,
			g_Result[3].Size.x,
			g_Result[3].Size.y,
			g_Result[3].Rotate,
			g_Result[3].Color,
			0,
			1.0f,
			1.0f,
			1
		);
		//�X�R�A
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultScoreTextureNo));

		SpriteDrawColorRotation
		(
			g_Result[1].Position.x,
			g_Result[1].Position.y,
			0.0f,
			g_Result[1].Size.x,
			g_Result[1].Size.y,
			g_Result[1].Rotate,
			g_Result[1].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		//�����N
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultRankTextureNo));
		SpriteDrawColorRotation
		(
			g_Result[2].Position.x,
			g_Result[2].Position.y,
			0.0f,
			g_Result[2].Size.x,
			g_Result[2].Size.y,
			g_Result[2].Rotate,
			g_Result[2].Color,
			0,
			1.0f,
			1.0f,
			1
		);
		//�Q�[���I�[�o�[
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultOverTextureNo));
		SpriteDrawColorRotation
		(
			g_Result[4].Position.x,
			g_Result[4].Position.y,
			0.0f,
			g_Result[4].Size.x,
			g_Result[4].Size.y,
			g_Result[4].Rotate,
			g_Result[4].Color,
			0,
			1.0f,
			1.0f,
			1
		);

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
		//============================================
		//	Life
		//============================================
		{
			PLAYER* pPlayer = GetPlayer();
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultLifeMaxTextureNo));
			g_ResultLife.Position.x = SCREEN_WIDTH / 2 - 220.0f;

			for (int i = 0; i < PLAYER_HP; i++) {
				if (!g_ResultLife.UseFlag) {
					if (i == pPlayer->hp) {
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultLifeVolumeTextureNo));
					}
					SpriteDrawColorRotation
					(
						g_ResultLife.Position.x,
						g_ResultLife.Position.y,
						0.0f,
						g_ResultLife.Size.x,
						g_ResultLife.Size.y,
						g_ResultLife.Rotate,
						g_ResultLife.Color,
						0,
						1.0f,
						1.0f,
						1
					);
					g_ResultLife.Position.x += 100.0f;
				}
			}
		}
		for (int i = 0; i < RESULT_MAX; i++) {

			if (i == 0) {
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultLifeTextureNo));
			}

			if (i == 1) {
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultScoreTextureNo));
			}

			if (i == 2) {
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultRankTextureNo));
			}

			if (i == 3) {
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultTimeTextureNo));
			}

			if (i == 4) {
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ResultClearTextureNo));
			}


			SpriteDrawColorRotation
			(
				g_Result[i].Position.x,
				g_Result[i].Position.y,
				0.0f,
				g_Result[i].Size.x,
				g_Result[i].Size.y,
				g_Result[i].Rotate,
				g_Result[i].Color,
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
	}
}

void SetResultType(RESULT_TYPE ty)
{
	ResultObject.type = ty;
}

void SetResult(D3DXVECTOR3 pos, D3DXVECTOR2 size) {
	for (int i = 0; i < RESULT_MAX; i++) {
		if (!g_Result[i].UseFlag) {
			g_Result[i].Position = pos;
			g_Result[i].Size = size;
			g_Result[i].UseFlag = true;
			break;
		}
	}
}

RESULT* GetResult()
{
	return &ResultObject;
}
