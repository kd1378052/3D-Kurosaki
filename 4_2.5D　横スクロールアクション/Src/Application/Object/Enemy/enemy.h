#pragma once

class Enemy : public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() {}

	void Init() override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit() override;

private:
	//板ポリ　2Dのものは↓これで宣言
	std::shared_ptr<KdSquarePolygon> m_enemy;

	float m_anime = 0;
	Math::Vector3 m_pos;

	//ジャンプ
	//重力
	float m_gravity = 0;
};
