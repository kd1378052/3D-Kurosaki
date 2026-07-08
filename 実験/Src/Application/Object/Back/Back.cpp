#include "Back.h"

void Back::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Back.png");

	Math::Matrix scalMat = Math::Matrix::CreateScale(300, 100, 1);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(0,0,50);

	//行列合成　順番は　拡大S→回転R→移動T　の順番で行う
	m_mWorld = scalMat * transMat;
}

void Back::DrawLit()
{	
	//表示
	// m_model　は　ポインタだから　*　がいる
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
