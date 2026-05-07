#include "GameScene.h"

void GameScene::Init()
{
	m_playerTex.Load("Asset/Textures/player.png");
	m_enemyTex.Load("Asset/Textures/enemy.png");

}

void GameScene::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) m_playerPos.x += 5;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) m_playerPos.x -= 5;
	if (GetAsyncKeyState(VK_UP) & 0x8000 )  m_playerPos.y += 5;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)  m_playerPos.y -= 5;

	//追尾　ホーミング
//★

	//ベクトル計算で弾の一方方向を算出
	//目的地（プレイヤー座標）ー現在地（エネミー座標）
	Math::Vector2 enemyMove = m_playerPos - m_enemyPos;

	//ベクトルの長さを求める
	//enemyMove.Length();
	//ベクトルの正規化　長さを1にする
	enemyMove.Normalize();

	//敵を時機に向かって移動させる
	m_enemyPos += enemyMove * 3;
	//						 ↑スピード
	//★

	//アニメーション処理
	m_anime += 0.3f;//速度
	if (m_anime >= 6)
	{
		m_anime = 0.0f;
	}
}

void GameScene::DrawSprite()
{
	//プレイヤー
	int boostAnime[6] = { 0,64,128,192,128,64 };
	Math::Rectangle rcPlayer = { boostAnime[(int)m_anime],0,64,64};
	KdShaderManager::Instance().m_spriteShader.DrawTex
	(&m_playerTex, m_playerPos.x, m_playerPos.y, 64, 64, &rcPlayer);

	//エネミー
	KdShaderManager::Instance().m_spriteShader.DrawTex
	(&m_enemyTex, m_enemyPos.x, m_enemyPos.y);

}

void GameScene::Release()
{

}
