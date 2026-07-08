#include "Ground.h"

void Ground::Init()
{
	//m_modelを実体化
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");

	Math::Matrix scalMat = Math::Matrix::CreateScale(5, 1, 1);
	
	//↓　全オブジェクトに必要なので親クラスがメンバー変数として宣言
	m_mWorld = scalMat;

	//当てられる側の処理***********
	{
		//当たり判定をつけたいから実体化する
		m_pCollider = std::make_unique<KdCollider>();
		//モデルの形状で当たり判定　登録
		m_pCollider->RegisterCollisionShape
		(
			"GroundCollision",	// 名前
			m_model,			//登録したいモデルの形状
			KdCollider::Type::TypeGround	//当たり判定の種類
		);
	}
	//***********
}

void Ground::DrawLit()
{
	static float d = 0;

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		d += 0.001;
		if (d > 1)
		{
			d = 1;
		}
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		d -= 0.001;
		if (d < 0)
		{
			d = 0;
		}
	}

	//ディゾルブ
	KdShaderManager::Instance().m_StandardShader.SetDissolve(d);

	//表示
	// m_model　は　ポインタだから　*　がいる
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
