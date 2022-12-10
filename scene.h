#pragma once


typedef enum
{
	SCENE_NONE =0,
	SCENE_TITLE,
	SCENE_DATASELECT,
	SCENE_STAGESELECT,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_PAUSE,
	SCENE_MAX

}SCENE;

void InitScene(SCENE no);//初期化したいシーン
void UninitScene();
void UpdateScene();
void DrawScene();

void SetScene(SCENE no);	//シーン切り替えのリクエスト
void CheckScene();	//しーん切り替え処理