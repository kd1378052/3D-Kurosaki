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
	void DrawLit()		override;
	void Release()		override;

private:

	KdCamera m_camera;
	KdModelData m_model;

	Math::Vector3 m_pos;
	float m_angleY = 0;

};
