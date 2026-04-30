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

	Math::Color color;

	static const int maxDigits = 10;

	KdTexture m_tex;
	unsigned long m_score = 0;
	int m_digits[maxDigits] = {};//{}初期化
};
