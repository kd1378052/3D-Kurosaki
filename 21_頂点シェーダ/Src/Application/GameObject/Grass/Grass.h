#pragma once

class Grass : public KdGameObject
{
public:
	Grass() {}
	~Grass()override {}

	void Init()override;
	void DrawLit()override;


private:
	//モデル
	std::shared_ptr<KdModelData> m_model;

};