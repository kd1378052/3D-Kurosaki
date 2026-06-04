#include "Effect.h"
#include "../../Scene/SceneManager.h"

void Effect::Init()
{
	//デバックワイヤー実体化　★
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

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

void Effect::PostUpdate()
{
	//球判定★
	//球判定用　変数
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos();
	sphere.m_sphere.Radius = 0.3f;//半径
	sphere.m_type = KdCollider::TypeDamage;//攻撃判定

	//デバック
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius,kRedColor);
	
	//全オブジェクトと当たり判定を行う
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//球と当たり判定
		//前までの当たり判定は　↓当たったオブジェクトの情報を格納するリスト
		if (obj->Intersects(sphere, nullptr) == true)
		{//当たったかどうかを調べるだけならリストは必要ない
			//当たった
			//★OnHit★　はKdGameObject　に追加した関数
			obj->OnHit();

		}

	}

}

void Effect::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_effect, m_mWorld);
}