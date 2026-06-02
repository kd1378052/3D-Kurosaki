#include "Cannon.h"

void Cannon::Init()
{
	m_cannon = std::make_shared<KdModelData>();
	m_cannon->Load("Asset/Models/NewCannom/a.gltf");

	Math::Matrix transMat = Math::Matrix::CreateTranslation({-1, -2, 0});
	Math::Matrix scaleMat = Math::Matrix::CreateScale(2);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));

	m_mWorld = scaleMat * rotateMat * transMat;

	//当てられる側の処理***********
	{
		//当たり判定をつけたいから実体化する
		m_pCollider = std::make_unique<KdCollider>();
		//モデルの形状で当たり判定　登録
		m_pCollider->RegisterCollisionShape
		(
			"CannonCollision",	// 名前
			m_cannon,			//登録したいモデルの形状
			KdCollider::Type::TypeGround	//当たり判定の種類
		);
	}
}

void Cannon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_cannon, m_mWorld);

}
