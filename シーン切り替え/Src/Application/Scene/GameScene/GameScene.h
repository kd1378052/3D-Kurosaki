#pragma once

class GameScene
{
public:
	GameScene() {}
	~GameScene() {}

	void Init();
	void Update();
	void DrawSprite();
	void Release();

private:

	Math::Color color;

};
