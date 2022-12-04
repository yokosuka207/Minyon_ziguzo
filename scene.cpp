#include "scene.h"
#include "main.h"
#include "renderer.h"
#include "game.h"
#include "Title.h"
#include "result.h"
#include "StageSelect.h"
#include "save.h"
#include "time.h"

static SCENE g_sceneIndex = SCENE::SCENE_NONE;
static SCENE g_sceneNextIndex = g_sceneIndex;

static Time g_Time;
static int ElapsedTime;

Save g_SaveScene;				// セーブクラスのインスタンス

void InitScene(SCENE no)
{
	g_sceneIndex = g_sceneNextIndex = no;

	switch (g_sceneIndex)
	{

	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:
		InitTitle();
		break;
	case SCENE::SCENE_DATASELECT:
		g_SaveScene.Init();
		break;
	case SCENE::SCENE_STAGESELECT:
		InitStageSelect();
		SetStageSelect();
		break;
	case SCENE::SCENE_GAME :
		InitGame();
		break;
	case SCENE::SCENE_RESULT:
		g_Time.SetElapsedTime(ElapsedTime);
		InitResult();
		break;


	default:
		break;
	}

}

void UninitScene()
{
	switch (g_sceneIndex)
	{

	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE::SCENE_DATASELECT:
		g_SaveScene.Uninit();
		break;
	case SCENE::SCENE_STAGESELECT:
		UninitStageSelect();
		break;
	case SCENE::SCENE_GAME:
		ElapsedTime = g_Time.GetTime();
		UninitGame();
		break;
	case SCENE::SCENE_RESULT:
		UninitResult();
		break;


	default:
		break;
	}

}

void UpdateScene()
{
	switch (g_sceneIndex)
	{

	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE::SCENE_DATASELECT:
		g_SaveScene.Update();
		break;
	case SCENE::SCENE_STAGESELECT:
		UpdateStageSelect();
		break;
	case SCENE::SCENE_GAME:
		UpdateGame();
		break;
	case SCENE::SCENE_RESULT:
		UpdateResult();
		break;


	default:
		break;
	}

}

void DrawScene()
{
	switch (g_sceneIndex)
	{

	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE::SCENE_DATASELECT:
		g_SaveScene.Draw();
		break;
	case SCENE::SCENE_STAGESELECT:
		DrawStageSelect();
		break;
	case SCENE::SCENE_GAME:
		DrawGame();
		break;
	case SCENE::SCENE_RESULT:
		DrawResult();
		break;


	default:
		break;
	}

}

void SetScene(SCENE no)
{
	g_sceneNextIndex = no;
}

void CheckScene()
{
	if (g_sceneIndex != g_sceneNextIndex)
	{
		UninitScene();

		InitScene(g_sceneNextIndex);
	}
}
