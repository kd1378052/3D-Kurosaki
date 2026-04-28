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

};
