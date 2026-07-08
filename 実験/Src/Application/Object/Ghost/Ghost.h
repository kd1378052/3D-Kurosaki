#pragma once

class Ghost : public KdGameObject
{
public:
	Ghost() { Init(); }
	~Ghost() {}

	void Init()			override;
	void Update()		override;
	void DrawLit()		override;

	//ターゲットのセット
	void SetTarget(std::shared_ptr<KdGameObject> _target) 
	{ 
		m_target = _target;
	}

private:

	//これでポインタになる
	std::shared_ptr<KdSquarePolygon> m_ghost;

	Math::Vector3 m_pos;

	//ターゲットポインタ
	std::weak_ptr<KdGameObject> m_target;

};
