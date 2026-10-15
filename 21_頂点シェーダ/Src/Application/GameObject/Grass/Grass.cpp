#include "Grass.h"

void Grass::Init()
{
	//メモリ確保
	m_model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Grass/Grass.gltf");

	Math::Matrix transMat = Math::Matrix::CreateTranslation(rand()%200 - 100, 0, rand()%200 - 100);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(rand()% 3 + 1);
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rand() % 180));

	// 行列合成　←こいつは絶対Updateの最後!!!!!
	m_mWorld = scaleMat * rotMat * transMat;
}

void Grass::DrawLit()
{
	//裏面カリング解除
	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);
	//黒崎授業12
	//風の影響を受ける
	KdShaderManager::Instance().m_StandardShader.SetWindEnable(true);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);

	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullBack);

}
