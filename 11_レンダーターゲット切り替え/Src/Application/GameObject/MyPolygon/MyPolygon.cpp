#include "MyPolygon.h"
#include "../../Scene/SceneManager.h"

void MyPolygon::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	
	//座標
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0.0f, 25.0f, 0.0f);
	//拡縮
	Math::Matrix scaleMat = Math::Matrix::CreateScale(50.0f);

	m_mWorld = scaleMat * transMat;

}

void MyPolygon::Update()
{
	//ここで表示をしている
	if (m_poly->GetMaterial() == nullptr)
	{
		m_poly->SetMaterial(SceneManager::Instance().GetRenderTargetTexture());
	}

}

void MyPolygon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
 
}
