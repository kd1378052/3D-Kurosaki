#include "Enemy.h"

#include "../../Scene/SceneManager.h"

void Enemy::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_enemy = std::make_shared<KdSquarePolygon>();
	m_enemy->SetMaterial("Asset/Textures/char.png");

	// 画像を分割
	m_enemy->SetSplit(6, 6);

	// 原点変更(真ん中→真ん中)
	m_enemy->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// 「当てられる側」の処理======

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	// 当たり判定用に球登録
	m_pCollider->RegisterCollisionShape
	(
		"EnemyCollision",				// 識別用の名前
		{ 0,0.5,0 },					// 球の中心座標
		0.2,							// 球の半径
		KdCollider::Type::TypeDamage	//当たり判定の種類
	);
	// ============================
}

void Enemy::Update()
{
	// 当たり判定を見える化
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.5, 0), 0.2f, kRedColor);

	int Walk[4] = { 3, 4, 3, 5 };
	m_enemy->SetUVRect(Walk[(int)m_anime]);
	m_anime += 0.1;
	if (m_anime >= 4)
	{
		m_anime = 0;
	}

	// 移動処理
	m_pos.x += m_speed * m_dir;
	m_goal += m_speed;

	if (m_goal >= 5.0f)
	{
		m_dir *= -1;
		m_goal = 0;
	}


	// 落下処理
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	// 行列合成　←こいつは絶対Updateの最後!!!!!
	m_mWorld = transMat;
}

void Enemy::PostUpdate()
{
	// ==============
	//	レイ判定
	// ==============
	// レイ判定用の変数を作成
	KdCollider::RayInfo ray;
	// レイの発射位置を設定
	ray.m_pos = m_pos;
	// ちょっと上からの位置にする
	ray.m_pos.y += 0.1;
	// 
	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;

	// レイの発射方向を設定
	ray.m_dir = { 0, -1, 0 };
	// レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;
	// 当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;
	// デバッグ
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	// レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;
	// 全オブジェクトと当たり判定を行う
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		// レイと当たり判定!!!!!!
		obj->Intersects(ray, &retRayList);
	}

	// レイに当たったリストから一番近いオブジェクトを探す
	// どうやってわかる？→一番遠い距離からの余りを算出して比較する
	//		↓レイの時は余った長さ
	float maxOverLap = 0;	// 初期化！
	Math::Vector3 hitPos;
	bool hit = false;		// 初期化！
	for (auto& ret : retRayList)
	{
		// レイを遮断しオーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			// 更新
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}

	if (hit == true)
	{
		// 当たっていたら当たった座標をプレイヤー座標にセット
		m_pos = hitPos + Math::Vector3(0, -0.1, 0);
		m_gravity = 0;	//重力を無効化
	}

	// ==============
	//	球(スフィア)判定
	// ==============
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	// 球の中心座標
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 0.5;
	// 球の半径を設定
	sphere.m_sphere.Radius = 0.3;
	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::Type::TypeGround;

	// デバッグ
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	// 球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;
	// 全オブジェクトと当たり判定を行う
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		// 球と当たり判定!!!!!!
		obj->Intersects(sphere, &retSphereList);
	}

	// 球に当たったリストから一番近いオブジェクトを探す！
	//	↓こいつ　レイ判定の時に宣言してるので使いまわす
	maxOverLap = 0;	// 球の時はめり込んだ長さ
	//	↓こいつ　レイ判定の時に宣言してるので使いまわす
	hit = false;
	// 当たった方向を格納する変数
	Math::Vector3 hitDir;
	for (auto& ret : retSphereList)
	{
		// 球にめり込んだ長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			// 更新
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true)
	{
		// Z方向への押し戻し無効
		hitDir.z = 0;
		// 正規化（長さを１にする）
		hitDir.Normalize();
		// 押し戻し処理			↓めり込んだ長さ
		m_pos += hitDir * maxOverLap;
		//		↑当たった方向(方向ベクトルは長さ１)
	}
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_enemy, m_mWorld);
}