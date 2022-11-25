#include "scene.h"
#include "main.h"
#include "renderer.h"
#include "game.h"
#include "Title.h"
#include "result.h"
#include "StageSelect.h"

static SCENE g_sceneIndex = SCENE::SCENE_NONE;
static SCENE g_sceneNextIndex = g_sceneIndex;

void InitScene(SCENE no)
{
	g_sceneIndex = g_sceneNextIndex = no;

	switch (g_sceneIndex)
	{

	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_STAGESELECT:
		InitStageSelect();
		SetStageSelect();
		break;
	case SCENE::SCENE_TITLE:
		InitTitle();
		break;
	case SCENE::SCENE_GAME :
		InitGame();
		break;
	case SCENE::SCENE_RESULT:
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
	case SCENE::SCENE_STAGESELECT:
		UninitStageSelect();
		break;
	case SCENE::SCENE_GAME:
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
