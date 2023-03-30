#pragma once

class Enemy
{
public:
	Enemy();

	void load();
	void unload();
	void setPos(int x, int y);
	void update();
	void draw();
	void bulletMove();
	void bullet();

	int getLeft()	const { return m_posX; }
	int getRight()	const { return m_posX + m_width; }
	int getTop()	const { return m_posY; }
	int getBottom()	const { return m_posY + m_height; }
private:
	//弾
	int m_bulletHandle;
	int m_bulletFlag;
	int m_bulletCounter;
	int m_bulletX, m_bulletY;
	int m_bulletW, m_bulletH;

	//キャラクター
	int m_handle;
	int m_width, m_height;
	int m_posX, m_posY;
	int m_vecX, m_vecY;
};

class Enemy2 : public Enemy
{
public:

private:

};