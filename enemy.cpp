#include "DxLib.h"
#include "enemy.h"
#include "game.h"

namespace
{
	//キャラクターの移動速度    
	constexpr int kSpeedX = 5;
	constexpr int kSpeedY = 5;
}

Enemy::Enemy()
{
	//キャラクター
	m_handle = 0;
	m_width = 0;
	m_height = 0;

	m_posX = 0;
	m_posY = 0;

	m_vecX = kSpeedX;  
	m_vecY = kSpeedY;

	//弾
	m_bulletHandle = 0;
	m_bulletFlag = 0;
	m_bulletCounter = 0;
	m_bulletX = 0;
	m_bulletY = 0;
	m_bulletW = 0;
	m_bulletH = 0;

}

void Enemy::load()
{
	m_handle = LoadGraph("data/ikirito2.png");
	GetGraphSize(m_handle, &m_width, &m_height);

	m_bulletHandle = LoadGraph("data/");
	GetGraphSize(m_bulletHandle, &m_width, &m_height);
}

void Enemy::unload()

{
	DeleteGraph(m_handle);
}

void Enemy::setPos(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Enemy::update()
{
	m_posX += m_vecX;
	m_posY += m_vecY;
	//m_posY = 100;

	if (m_posX < 0)
	{
		m_posX = 0;
		m_vecX = kSpeedX;
	}
	if (m_posX > Game::kScreenWidth - m_width)
	{
		m_posX = Game::kScreenWidth - m_width;
		m_vecX = -kSpeedX;
	}
	if (m_posY < 0)
	{
		m_posY = 0;
		m_vecY = kSpeedY;
	}
	if (m_posY > Game::kScreenHeight - m_height)
	{
		m_posY = Game::kScreenHeight - m_height;
		m_vecY = -kSpeedY;
	}
}

void Enemy::bullet()
{

}

void Enemy::bulletMove()
{

}

void Enemy::draw()
{
	DrawGraph(m_posX, m_posY, m_handle, true);
}
