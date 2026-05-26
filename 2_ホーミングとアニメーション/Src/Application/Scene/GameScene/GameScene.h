#pragma once

#include "../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene() {}

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;
	void Release()		override;

private:

	KdTexture m_playerTex;
	KdTexture m_enemyTex;

	Math::Vector2 m_playerPos;
	Math::Vector2 m_enemyPos;

	//アニメーション用
	float m_anime = 0;

};
