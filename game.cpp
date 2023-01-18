#include "game.h"
#include "main.h"
#include "renderer.h"
#include "polygon.h" 

//#include "input.h"	//���͏���
#include "xinput.h"
#include "xkeyboard.h"

#include "bg.h"	//�w�i
#include "player.h"//�v���C���[
#include "collision.h"	//�����蔻��]
#include "block.h"
#include "puzzle.h"
#include "mouse.h"
#include "goal.h"
#include "puzzlecip.h"
#include "broken.h"
#include "warp.h"
#include "MapChip.h"
#include "inventory.h"
#include "joint.h"
#include "cursor.h"
#include "SplitStage.h"
#include "thorn_block.h"
#include "jump_stand.h"
#include "thorn_block.h"
#include "time.h"
#include "score.h"
#include "SheerFloors.h"
#include "high_broken.h"
#include "MoveBlock.h"
#include "switch.h"
#include "SwitchWall.h"
#include"player3D.h"
#include"camera.h"
#include "scene.h"
#include "pause.h"
#include "goal_key.h"
#include "doppelganger.h"
#include "enemy.h"
#include "bullet.h"
#include"noizu.h"
#include "issuer.h"		// �������ˑ��u
#include "ray.h"		// ����
#include "EffectSpark.h"	// �q�o�i�G�t�F�N�g

static Time* pTime = pTime->GetTime();
static Score* pScore = pScore->GetScore();
static PLAYER3D g_Player3D;
static SCENE* p_Scene;
static bool* pause = GetPause();
static bool* pause2 = GetPauseMause();
static TimeParam* pTimeParam = pTime->GetTimeParam();

void InitGame()
{
	p_Scene = GetScene();

	if ((int)p_Scene != SCENE_GAME)
	{
		InitCamera();
		//----------���[��
		//InitPolygon();//�|���S���̏�����
		//-----------------------
		InitSplitStage();
		BgInit();
		InitBlock();
		InitJoint();
		InitGameMouse();
		InitGoal();
		InitGKey();
		InitBroken();
		InitWarp();
		InitJumpStand();
		InitSheerFloors();
		InitPuzzleCip();
		InitPuzzle();
		InitInventory();			// �C���x���g���̏�����
		InitCursor();				// �J�[�\���̏�����
		InitThornBlock();
		InitHigh();
		InitSwitch();
		InitSwitchWall();
		InitMoveBlock();
		InitNoizu();
		InitDoppelganger();
		SetDoppelGanger(D3DXVECTOR2(50, 100),D3DXVECTOR2(DOPPELGANGER_SIZE_W,DOPPELGANGER_SIZE_H),1);
		InitEnemy();
		InitPause();
		InitRay();				// �����̏�����
		InitIssuer();			// �������ˑ��u�̏�����
		InitEffectSpark();		// �q�o�i�G�t�F�N�g
		InitBullet();

	}
	InitMapChip();
	SetCursor(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(100, 100));
	InitPlayer();
	pScore->InitScore();
	g_Player3D.Init();
	if (!pTimeParam->UseFlag) {
		pTime->InitTime();
		pTime->SetTime(D3DXVECTOR2(TIME_POS_X, 30.0f), D3DXVECTOR2(50.0f, 50.0f));
		pTime->StartTime();
	}


}


void UninitGame()
{
	UninitCamera();
	//UninitPolygon();	//�|���S���̏I��
	BgUninit();
	UninitBlock();
	UninitJoint();
	UninitPuzzle();
	UninitGameMouse();
	UninitGoal();
	UninitGKey();
	UninitPuzzleCip();
	UninitBroken();
	UninitPlayer();
	UninitWarp();
	UninitJumpStand();
	//UninitSheerFloors();
	UninitInventory();			// �C���x���g���̏I��
	UninitMapChip();
	UninitCursor();				// �J�[�\���̏I��
	UninitThornBlock();
	UninitMoveBlock();
	UninitHigh();
	UninitSwitch();
	UninitSwitchWall();
	UninitNoizu();
	UninitDoppelganger();
	UninitEnemy();
	UninitBullet();

	UninitPause();
	pScore->UninitScore();
	pTime->UninitTime();
	g_Player3D.Uninit();
	UninitRay();				// �����̏I��
	UninitIssuer();				// �������ˑ��u�̏I��
	UninitEffectSpark();		// �q�o�i�G�t�F�N�g
}

void UpdateGame()
{
	//�|�[�Y����
	if (Keyboard_IsKeyTrigger(KK_TAB)) {
		//�|�[�Y�t���O��off
		if (!(*pause)) {
			(*pause) = true;
			pTime->PauseStartTime();
		}
	}	
	if(*pause2) {
		if ((*pause)) {
			(*pause) = false;
			(*pause2) = false;
			pTime->PauseEndTime();
			pTime->PauseElapsedTime();
		}
	}
	//if (Keyboard_IsKeyTrigger(KK_R)) {
	//	ResetGame();
	//}
	if (!(*pause)) {
		//UpdatePolygon();	//�|���S���̍X�V
		BgUpdate();
		UpdateNoizu();
		//PuzzleCollision();
		UpdatePlayer();
		PieceCollision();
		UpdateCollision();

		UpdateBlock();
		UpdateJoint();
		UpdatePuzzle();
		UpdatePuzzleCip();

		UpdateGoal();
		UpdateGKey();
		UpdateBroken();
		UpdateWarp();
		UpdateJumpStand();
		UpdateSheerFloors();
		UpdateThornBlock();
		UpdateMoveBlock();
		UpdateHigh();
		UpdateSwitch();
		UpdateSwitchWall();

		UpdateDoppelganger();
		UpdateEnemy();
		UpdateBullet();

		UpdateInventory();			// �C���x���g���̍X�V
		UpdateMapChip();
		UpdateGameMouse();
		UpdateCursor();				// �J�[�\���̍X�V
		g_Player3D.Update();
		UpdateCamera();
		UpdateRay();			// �����̍X�V
		UpdateIssuer();			// �������ˑ��u�̍X�V
		UpdateEffectSpark();	// �q�o�i�G�t�F�N�g
	}
	else {
		UpdatePause();
		UpdateGameMouse();
		UpdateCursor();				// �J�[�\���̍X�V
	}
}	


void DrawGame()
{
	if (!(*pause)) {
		SetCamera();

		BgDraw();
		DrawSplitStage();			// ��؂�g�̕`��

		DrawPolygon();		//�|���S���̕`��
		DrawPuzzle();
		DrawMapChip();

		//DrawJoint();				// ������K�����̐���������Ă��I
		DrawBlock();

		DrawPuzzleCip();
		DrawPlayer();
		DrawGKey();
		DrawWarp();
		DrawJumpStand();
		DrawSheerFloors();
		DrawThornBlock();
		DrawMoveBlock();
		DrawHigh();
		DrawSwitch();
		DrawSwitchWall();
		DrawGoal();
		DrawBroken();		
		DrawThornBlock();

		DrawDoppelganger();
		DrawEnemy();
		DrawBullet();
		DrawNoizu();

		//DrawRay();				// �����̕`��
		//DrawIssuer();			// �������ˑ��u�̕`��
		DrawInventory();			// �C���x���g���̕`��
		pTime->DrawGameTime();
		DrawCursor();				// �J�[�\���̕`��
		g_Player3D.Draw();
		DrawEffectSpark();		// �q�o�i�G�t�F�N�g
		SetCamera();
	}
	else {
		BgDraw();
		//DrawCursor();				// �J�[�\���̕`��
		DrawPause();
	}
}

void ResetGame()
{
	InitGame();
}
