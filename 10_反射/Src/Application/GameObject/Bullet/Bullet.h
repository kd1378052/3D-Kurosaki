#pragma once
class Bullet : public KdGameObject
{
public:
	Bullet() {}
	~Bullet()			override {}

	void Init()		override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()	override;
	void DrawBright()	override;

	void SetPos(const Math::Vector3& pos)override
	{
		m_pos = pos;
	}

	//向きスピード
	void SetParam(Math::Vector3 _pos, Math::Vector3 _dir, float _speed)
	{
		m_pos = _pos;
		m_dir = _dir;
		m_speed = _speed;
	}

private:
	//モデル
	std::shared_ptr<KdModelData> m_model;

	//std::weak_ptr<KdGameObject> m_target;

	Math::Vector3 m_pos;

	Math::Vector3 m_dir;
	float m_speed = 0.5f;

	//寿命
	int m_lifespan = 600;

	//トレイル(＝　き跡)ポリゴン 弾の打った時のエフェクト
	std::shared_ptr<KdTrailPolygon> m_tPoly;
};