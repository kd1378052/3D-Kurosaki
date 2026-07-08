#pragma once

class Back : public KdGameObject
{
public:
	Back() { Init(); }
	~Back(){}

	void Init() override;
	void DrawLit() override;

private:
	//板ポリ　2Dのものは↓これで宣言
	std::shared_ptr<KdSquarePolygon> m_polygon;

};
