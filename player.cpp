#include "DxLib.h"
#include "player.h"
#include "game.h"

#define SHOT 6

namespace
{
	//キャラクターの移動速度
	constexpr int kSpeedX = 10;
	constexpr int kSpeedY = 10;

	//当たり判定の大きさ
	constexpr int kColWidth = 1;
	constexpr int kColHeight = 1;

	//弾の当たり判定の大きさ
	constexpr int kBulletWidth = 1;
	constexpr int kBulletHeight = 1;
}

Player::Player()
{
	//キャラクター
	m_handle = 0;
	m_width = 0;
	m_height = 0;

	m_posX = 0;
	m_posY = 0;

	//リアクション
	m_damegeHandle = 0;
	m_damegeFlag = 0;
	m_damegeCounter = 0;

	//弾
	m_flag = 0;
	m_shotX = 0;
	m_shotY = 0;
	m_bulletHandle = 0;
	m_bulletHeight = 0;
	m_bulletWidth = 0;
}

void Player::load()
{
	m_handle = LoadGraph("data/etou.png");
	m_bulletHandle = LoadGraph("data/eto.png");
	m_damegeHandle = LoadGraph("data/damegeEto.png");
	GetGraphSize(m_bulletHandle, &m_bulletWidth, &m_bulletHeight);
	GetGraphSize(m_handle, &m_width, &m_height);
}

void Player::unload()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_bulletHandle);
}

void Player::setPos(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Player::update()
{
	if (m_damegeFlag == 1)
	{
		DrawGraph(m_posX, m_posY, m_damegeHandle, true);
		m_damegeCounter++;
		if (m_damegeCounter == 30)
		{
			m_damegeFlag == 0;
		}
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			m_posX -= kSpeedX;
			if (m_posX < 0)
			{
				m_posX = 0;
			}
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			m_posX += kSpeedX;
			if (m_posX > Game::kScreenWidth - m_width)
			{
				m_posX = Game::kScreenWidth - m_width;
			}
		}
		if (CheckHitKey(KEY_INPUT_UP))
		{
			m_posY -= kSpeedY;
			if (m_posY < 0)
			{
				m_posY = 0;
			}
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			m_posY += kSpeedY;
			if (m_posY > Game::kScreenHeight - m_height)
			{
				m_posY = Game::kScreenHeight - m_height;
			}
		}
		if (CheckHitKey(KEY_INPUT_W) == 1 && m_flag == 0)
		{
			m_shotX = (m_width - m_bulletWidth) / 2 + m_posX;
			m_shotY = (m_height - m_bulletHeight) / 2 + m_posY;

			m_flag = 1;
		}
		if (CheckHitKey(KEY_INPUT_D) == 1 && m_flag == 0 )
		{
			m_shotX = (m_width - m_bulletWidth) / 2 + m_posX;
			m_shotY = (m_height - m_bulletHeight) / 2 + m_posY;

			m_flag = 2;
		}
		if (CheckHitKey(KEY_INPUT_A) == 1 && m_flag == 0)
		{
			m_shotX = (m_width - m_bulletWidth) / 2 + m_posX;
			m_shotY = (m_height - m_bulletHeight) / 2 + m_posY;

			m_flag = 3;
		}
		if (CheckHitKey(KEY_INPUT_S) == 1 && m_flag == 0)
		{
			m_shotX = (m_width - m_bulletWidth) / 2 + m_posX;
			m_shotY = (m_height - m_bulletHeight) / 2 + m_posY;

			m_flag = 4;
		}
	}
}

void Player::damegeInit()
{
	m_damegeFlag = 1;

	m_damegeCounter = 0;
}

void Player::draw()
{
	DrawGraph(m_posX, m_posY, m_handle, true);
}

void Player::bulletMove()
{
	if (m_flag == 1)
	{
		m_shotY -= 16;

		if (m_shotY < -80)
		{
			m_flag = 0;
		}

		DrawGraph(m_shotX, m_shotY, m_bulletHandle, false);
	}

	if (m_flag == 2)
	{
		m_shotX += 16;

		if (m_shotX > Game::kScreenWidth + 80)
		{
			m_flag = 0;
		}

		DrawGraph(m_shotX, m_shotY, m_bulletHandle, false);
	}

	if (m_flag == 3)
	{
		m_shotX -= 16;

		if (m_shotX <  -80)
		{
			m_flag = 0;
		}

		DrawGraph(m_shotX, m_shotY, m_bulletHandle, false);
	}

	if (m_flag == 4)
	{
		m_shotY += 16;

		if (m_shotY > Game::kScreenHeight + 80)
		{
			m_flag = 0;
		}

		DrawGraph(m_shotX, m_shotY, m_bulletHandle, false);
	}
}

int Player::getLeft()
{
	int result = m_posX;
	int tempX = m_width - kColWidth;
	result = m_posX + tempX / 2;
	return result;
}

int Player::getRight()
{
	int result = m_posX;
	int tempX = m_width - kColWidth;
	result = m_posX + m_width - tempX / 2;
	return result;
}

int Player::getTop()
{
	int result = m_posY;
	int tempY = m_height - kColHeight;
	result = m_posY + tempY / 2;
	return result;
}

int Player::getBottom()
{
	int result = m_posY;
	int tempY = m_height - kColHeight;
	result = m_posY + m_height - tempY / 2;
	return result;
}

int Player::getBulletLeft()
{
	int result = m_shotX;
	int tempX = m_bulletWidth - kBulletWidth;
	result = m_shotX + tempX / 2;
	return result;
}

int Player::getBulletRight()
{
	int result = m_shotX;
	int tempX = m_bulletWidth - kBulletWidth;
	result = m_shotX + m_bulletWidth - tempX / 2;
	return result;
}

int Player::getBulletTop()
{
	int result = m_shotY;
	int tempY = m_bulletHeight - kBulletHeight;
	result = m_shotY + tempY / 2;
	return result;
}

int Player::getBulletBottom()
{
	int result = m_shotY;
	int tempY = m_bulletHeight - kBulletHeight;
	result = m_shotY + m_bulletHeight - tempY / 2;
	return result;
}
