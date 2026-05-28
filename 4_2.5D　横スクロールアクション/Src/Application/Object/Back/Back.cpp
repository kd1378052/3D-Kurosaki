#include "Back.h"

void Back::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Back.png");
}

void Back::DrawLit()
{
	//表示
	// m_model　は　ポインタだから　*　がいる
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
