#pragma once

class Tank : public KdGameObject
{
public:
	Tank()					 {}
	~Tank()			override {}

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

private:
	//モデル
	std::shared_ptr<KdModelData> m_model;

	float m_angle = 0.0f;
};