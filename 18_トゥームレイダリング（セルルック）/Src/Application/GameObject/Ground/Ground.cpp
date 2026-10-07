#include "Ground.h"

void Ground::Init()
{
	//メモリ確保
	m_model[0] = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model[0]->Load("Asset/Models/Ground/Ground.gltf");
	
	//メモリ確保
	m_model[1] = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model[1]->Load("Asset/Models/map/map.gltf");


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
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model[0], m_mWorld);
	
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model[1], Math::Matrix::Identity);
}
