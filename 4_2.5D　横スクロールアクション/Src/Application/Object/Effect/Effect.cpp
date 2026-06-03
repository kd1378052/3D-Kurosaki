#include "Effect.h"

void Effect::Init()
{
	m_effect = std::make_shared<KdSquarePolygon>();
	m_effect->SetMaterial("Asset/Textures/effect.png");

	m_effect->SetSplit(4, 4);


	Math::Matrix transmat = Math::Matrix::CreateTranslation(-20, 2, 0);

	// 行列合成（基本的な合成はSRT）
	m_mWorld = transmat;
}

void Effect::Update()
{
	//0～11のアニメーション
	m_effect->SetUVRect(m_anime);
	m_anime += 0.5;
	if (m_anime >= 12)
	{
		// アニメーションが終わったら領域を消したい
		// Expired 期限
		m_isExpired = true;
	}

}

void Effect::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_effect, m_mWorld);
}