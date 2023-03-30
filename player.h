#pragma once
#define SHOT

//プレイヤークラス
class Player
{
public:
	//キャラクター
	Player();

	void load();
	void unload();
	void setPos(int x, int y);

	void update();
	void draw();

	int getLeft();
	int getRight();
	int getTop();
	int getBottom();

	void damegeInit();

	//弾
	void bulletMove();

	int getBulletLeft();
	int getBulletRight();
	int getBulletTop();
	int getBulletBottom();

private:
	//キャラクター
	int m_handle;
	int m_width;
	int m_height;

	int m_posX;
	int m_posY;

	//リアクション
	int m_damegeHandle;
	int m_damegeFlag;
	int m_damegeCounter;

	//弾
	int m_flag;
	int m_shotX;
	int m_shotY;
	int m_bulletHandle;
	int m_bulletHeight;
	int m_bulletWidth;
};