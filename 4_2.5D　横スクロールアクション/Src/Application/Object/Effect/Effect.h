#pragma once

class Effect : public KdGameObject
{
public:
	Effect() { Init(); }
	~Effect() {}

	void Init() override;
	void Update() override;
	void DrawLit() override;

private:

	std::shared_ptr<KdSquarePolygon> m_effect;

	float m_anime = 0;
};