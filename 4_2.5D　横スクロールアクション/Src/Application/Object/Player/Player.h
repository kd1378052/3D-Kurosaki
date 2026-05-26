#pragma once

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player() {}

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

private:

	//これでポインタになる
	std::shared_ptr<KdSquarePolygon> m_polygon;

	float m_anime = 0;
	Math::Vector3 m_pos;

};
