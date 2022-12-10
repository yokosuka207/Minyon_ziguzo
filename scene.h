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

void InitScene(SCENE no);//�������������V�[��
void UninitScene();
void UpdateScene();
void DrawScene();

void SetScene(SCENE no);	//�V�[���؂�ւ��̃��N�G�X�g
void CheckScene();	//���[��؂�ւ�����