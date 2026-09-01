#pragma once

class EnemyYama : public KdGameObject
{
public:
	EnemyYama() {}
	~EnemyYama()			override {}

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;
	void OnHit() override;

	void SetPos(const Math::Vector3& pos)override
	{
		m_pos = pos;
	}
	//ターゲットのセット
	void SetTarget(std::shared_ptr<KdGameObject> _target)
	{
		m_target = _target;
	}
private:
	//モデル
	std::shared_ptr<KdModelData> m_model;

	Math::Vector3 m_pos;

	//ターゲットポインタ　参照カウンタ増やさない
	std::weak_ptr<KdGameObject> m_target;

	float m_angle = 0.0f;

};