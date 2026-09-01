#include "Bullet.h"
#include"../../Scene/SceneManager.h"

void Bullet::Init()
{
	//メモリ確保
	m_model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model->Load("Asset/Models/Bullet/Bullet.gltf");

	//デバックワイヤー実体化　★
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//トレイルポリゴン初期化
	m_tPoly = std::make_shared<KdTrailPolygon>();
	m_tPoly->SetMaterial("Asset/Textures/jet.png");
	//板ポリをカメラに向ける　ビルボード処理
	m_tPoly->SetPattern(KdTrailPolygon::Trail_Pattern::eBillboard);

}

void Bullet::Update()
{
	//マイフレーム寿命を削る
	m_lifespan--;
	if (m_lifespan <= 0)
	{
		m_isExpired = true;
	}

	//移動
	m_pos += m_dir * m_speed;

	//座標行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;

	//トレイルポリゴン　追加
	m_tPoly->AddPoint(m_mWorld);

}

void Bullet::PostUpdate()
{
	//球判定★
	//球判定用　変数
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos;//中心点
	//sphere.m_sphere.Center.y += 1.0f;//中心点
	sphere.m_type = KdCollider::TypeDamage | KdCollider::TypeGround;//攻撃判定

	//デバック
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	//球と当たり判定
	std::list<KdCollider::CollisionResult> retSpherelist;
	//全オブジェクトと当たり判定を行う
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSpherelist);
	}
	float overLap = 0.0f;
	bool hit = false;
	Math::Vector3 noemal;
	for (auto& result : retSpherelist)
	{
		if (overLap < result.m_overlapDistance)
		{
			//更新
			overLap = result.m_overlapDistance;

			//法線取得
			noemal = result.m_hitNDir;
			hit = true;
		}
	}
	if (hit == true)
	{
		//反射ベクトルを求める
		float dot = -m_dir.Dot(noemal);
		Math::Vector3 R = m_dir + 2.0f * dot * noemal;
		R.Normalize();

		m_dir = R;
		//法線をない席の長さにする
	}

}

void Bullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);

}

void Bullet::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
	
	//トレイルポリゴン　表示
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_tPoly);
}
