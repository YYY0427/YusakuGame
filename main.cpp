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

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	//window名設定
	SetMainWindowText(Game::kTitleText);
	//画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//ダブルバッファモード
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

		//画面のクリア
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

		//裏画面を表画面を入れ替える
		ScreenFlip();

		//escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		
		//fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	player.unload();
	enemy.unload();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
