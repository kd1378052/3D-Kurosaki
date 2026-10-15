#pragma once

class Ground : public KdGameObject
{
public:
	Ground() {}
	~Ground()override {}

	void Init()override;
	void DrawLit()override;

private:
	//モデル
	std::shared_ptr<KdModelData> m_model;

};