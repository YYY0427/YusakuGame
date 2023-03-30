#include "DxLib.h"
#include "player.h"
#include "enemy.h"
#include "game.h"

bool isCoLLision(Player player, Enemy enemy)
{
	if (player.getLeft() > enemy.getRight())		return false;
	if (player.getRight() < enemy.getLeft())		return false;
	if (player.getTop() > enemy.getBottom())		return false;
	if (player.getBottom() < enemy.getTop())		return false;

	return true;
}

bool bulletCoLLision(Player player, Enemy enemy)
{
	if (player.getBulletLeft() > enemy.getRight())		return false;
	if (player.getBulletRight() < enemy.getLeft())		return false;
	if (player.getBulletTop() > enemy.getBottom())		return false;
	if (player.getBulletBottom() < enemy.getTop())		return false;

	return true;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	//window���ݒ�
	SetMainWindowText(Game::kTitleText);
	//��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	Player player;
	Enemy enemy;

	player.load();
	enemy.load();

	player.setPos(0, 360);
	enemy.setPos(640, 0);

	int startHandle = LoadGraph("data/start.png");
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();
		DrawExtendGraph(0, 0, 1280, 720, startHandle, FALSE);
		//DrawGraph(0, 0, startHandle, false);

		if (CheckHitKey(KEY_INPUT_RETURN))	break;

		ScreenFlip();
	}

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		//��ʂ̃N���A
		ClearDrawScreen();

		player.update();
		enemy.update();

		player.bulletMove();

		player.draw();
		enemy.draw();

		if (bulletCoLLision(player, enemy))
		{
			break;
		}
		
		if (isCoLLision(player, enemy))
		{
			//player.damegeInit();

			Sleep(2000);

			int handle = LoadGraph("data/gameover.jpg");
			while (ProcessMessage() == 0)
			{
				ClearDrawScreen();
				DrawExtendGraph(0, 0, 1280, 720, handle, FALSE);

				if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

				ScreenFlip();
			}
			DeleteGraph(handle);
			break;
		}

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		//esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		
		//fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	player.unload();
	enemy.unload();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
