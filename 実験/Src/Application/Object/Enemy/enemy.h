#pragma once

class Enemy : public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() {}

	void Init() override;
	void Update() override;
	void PostUpdate() override;
	void DrawLit() override;
	void OnHit() override;
	void OutroUpdate();

	//            ↓コンスト参照
	void SetPos(const Math::Vector3& _pos) override { m_pos = _pos; }
	//　メンバー変数を参照したいから

private:

	std::shared_ptr<KdSquarePolygon> m_enemy;
	float m_anime = 0;
	Math::Vector3 m_pos;
	float m_gravity = 0;

	int m_dir = 1;    //移動方向(1:右, -1:左)
	float m_goal = 0;
	float m_speed = 0.01f;

};