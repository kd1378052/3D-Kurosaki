#include "Ground.h"

void Ground::Init()
{
	//メモリ確保
	m_model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model->Load("Asset/Models/Ground/Ground.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(100.0f);
	//座標行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	
	// 行列合成 (S * R * T)
	m_mWorld = scaleMat * transMat;

}

void Ground::DrawLit()
{
	//地面描画
	//地面には陰影がつくべきなのでDrawLit（）で描画する
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
