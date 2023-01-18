#include "scene.h"
#include "main.h"
#include "renderer.h"
#include "game.h"
#include "Title.h"
#include "result.h"
#include "StageSelect.h"
#include "save.h"
#include "time.h"
#include "pause.h"
#include "score.h"
#include "tutorial.h"
#include "fade.h"
#include "noizu.h"
#include "sound.h"

#define SOUND_FADE_OUT_VOLUME (0.02f)

static SCENE g_sceneIndex = SCENE::SCENE_NONE;
static SCENE g_sceneNextIndex = g_sceneIndex;

static Time* pTime = pTime->GetTime();
static Score* pScore = pScore->GetScore();
static FADEPARAM* pFade = GetFadeParam();
static clock_t Elapsedtime = 0;
static clock_t PauseElapsed = 0;
static int	StageNo = 0;
static Save g_SaveScene;				// セーブクラスのインスタンス

//===================================================================
// サウンド関連
//===================================================================
static int g_TitleSoundNo = 0;
static char TitleSoundName[] = "data\\SoundData\\BGM\\タイトル.wav";

static int g_StageSelectSoundNo = 0;
//static char* StageSelectName[4] = {
//	(char*)"data\\SoundData\\BGM\\ステージセレクト①.wav",
//	(char*)"data\\SoundData\\BGM\\ステージセレクト②.wav",
//	(char*)"data\\SoundData\\BGM\\ステージセレクト③.wav",
//	(char*)"data\\SoundData\\BGM\\ステージセレクト④.wav",
//};
//fuck
static char StageSelectName[] = "data\\SoundData\\BGM\\ステージセレクト④.wav";
static int g_GameSoundNo = 0;
static char GameSoundName[] = "data\\SoundData\\BGM\\環境音.wav";

static int g_ResultSoundNo = 0;
//static char ResultSoundName[] = "data\\SoundData\\BGM\\.wav";

static float g_SoundFadeOutVolume = 0.0f;

void InitScene(SCENE no){
	g_sceneIndex = g_sceneNextIndex = no;
	switch (g_sceneIndex){
	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:
		InitTitle();
		InitNoizu();
		g_TitleSoundNo = LoadSound(TitleSoundName);
		PlaySound(g_TitleSoundNo, -1);	//-1はloop
		SetVolume(g_TitleSoundNo, 1.0f);//通常はvolume 1.0f
		break;
	case SCENE::SCENE_TUTORIAL:
		InitTutorial();
		InitNoizu();

		break;
	case SCENE::SCENE_DATASELECT:
		g_SaveScene.Init();
		InitNoizu();

		break;
	case SCENE::SCENE_STAGESELECT:
		InitStageSelect();
		//g_StageSelectSoundNo = LoadSound(StageSelectName[Irand(3)]);
		g_StageSelectSoundNo = LoadSound(StageSelectName);
		PlaySound(g_StageSelectSoundNo, -1);
		SetVolume(g_StageSelectSoundNo, 0.4f);
		//SetStageSelect();
		break;
	case SCENE::SCENE_GAME :
		pFade->ExceptFlag = false;
		pTime->StartTime();
		InitGame();
		g_GameSoundNo = LoadSound(GameSoundName);
		PlaySound(g_GameSoundNo, -1);
		SetVolume(g_GameSoundNo, 1.0f);
		break;
	case SCENE::SCENE_RESULT:
		InitResult();
		InitNoizu();

		break;
	default:
		break;
	}
}

void UninitScene(){
	switch (g_sceneIndex){
	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:
		UninitTitle();
		UninitNoizu();
		break;
	case SCENE::SCENE_TUTORIAL:
		UninitTutorial();
		UninitNoizu();

		break;
	case SCENE::SCENE_DATASELECT:
		g_SaveScene.Uninit();
		UninitNoizu();
		StopSound(g_TitleSoundNo);
		g_SoundFadeOutVolume = 0.0f;
		break;
	case SCENE::SCENE_STAGESELECT:
		UninitStageSelect();
		UninitNoizu();
		StopSound(g_StageSelectSoundNo);
		g_SoundFadeOutVolume = 0.0f;
		break;
	case SCENE::SCENE_GAME:
		Elapsedtime = pTime->SumTime();
		PauseElapsed = pTime->PauseElapsedTime();
		StageNo = ReturnStageNo();
		UninitGame();
		break;
	case SCENE::SCENE_RESULT:
		UninitResult();
		UninitNoizu();

		break;
	default:
		break;
	}
}

void UpdateScene(){
	switch (g_sceneIndex){
	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:
		UpdateTitle();
		UpdateNoizu();
		break;
	case SCENE::SCENE_TUTORIAL:
		UpdateTutorial();
		UpdateNoizu();

		break;
	case SCENE::SCENE_DATASELECT:
		g_SaveScene.Update();
		UpdateNoizu();
		if (pFade->FadeFlag) {
			SetVolume(g_TitleSoundNo, 1.0f - g_SoundFadeOutVolume);
			g_SoundFadeOutVolume += SOUND_FADE_OUT_VOLUME;
			if (g_SoundFadeOutVolume > 1.0f) {
				g_SoundFadeOutVolume = 1.0f;
			}
		}

		break;
	case SCENE::SCENE_STAGESELECT:
		UpdateStageSelect();
		UpdateNoizu();
		if (pFade->FadeFlag) {
			SetVolume(g_StageSelectSoundNo, 0.4f - g_SoundFadeOutVolume);
			g_SoundFadeOutVolume += SOUND_FADE_OUT_VOLUME / 2;
			if (g_SoundFadeOutVolume > 0.4f) {
				g_SoundFadeOutVolume = 0.4f;
			}
		}

		break;
	case SCENE::SCENE_GAME:
		UpdateGame();
		if (pFade->FadeFlag) {
			SetVolume(g_GameSoundNo, 1.0f - g_SoundFadeOutVolume);
			g_SoundFadeOutVolume += SOUND_FADE_OUT_VOLUME;
			if (g_SoundFadeOutVolume > 1.0f) {
				g_SoundFadeOutVolume = 1.0f;
			}
		}
		break;
	case SCENE::SCENE_RESULT:
		UpdateResult();
		UpdateNoizu();

		break;
	default:
		break;
	}
}

void DrawScene(){
	switch (g_sceneIndex){
	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:

		DrawTitle();
		DrawNoizu();

		break;
	case SCENE::SCENE_TUTORIAL:
		DrawTutorial();
		DrawNoizu();


		break;
	case SCENE::SCENE_DATASELECT:

		g_SaveScene.Draw();
		DrawNoizu();

		break;
	case SCENE::SCENE_STAGESELECT:

		DrawStageSelect();
		DrawNoizu();

		break;
	case SCENE::SCENE_GAME:
		DrawGame();
		break;
	case SCENE::SCENE_RESULT:

		DrawResult();
		pTime->DrawResultTime(Elapsedtime,PauseElapsed);
		pScore->DrawScore();
		pScore->SetStageNo(StageNo);
		DrawNoizu();

		break;
	default:
		break;
	}
}

void SetScene(SCENE no){
	g_sceneNextIndex = no;
}

void CheckScene(){
	if (g_sceneIndex != g_sceneNextIndex){
		UninitScene();
		InitScene(g_sceneNextIndex);
	}
}

SCENE* GetScene(){
	return &g_sceneIndex;
}
