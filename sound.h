
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);					//�T�E���h������(windows�̃n���h��)
void UninitSound(void);						//�T�E���h�̏I��

int LoadSound(char* pFilename);				//�T�E���h�̓ǂݍ���("�t�@�C���l�[��")
void PlaySound(int index, int loopCount);	//�T�E���h�̍Đ�(�Đ���������,���L�Q��)
											//loopCount = 0 :���Đ�
											//loopCount < 0 :���[�v
											//loopCount = 1 :2��Đ�
void StopSound(int index);					//�T�E���h�̒�~(��~�����)
void StopSoundAll(void);					//���ׂẴT�E���h�̒�~
void SetVolume(int index, float vol);		//���ʂ̐ݒ�(�ݒ肵������,����)
