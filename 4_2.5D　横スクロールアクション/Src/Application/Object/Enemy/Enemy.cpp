#include "Enemy.h"
#include"../../Scene/SceneManager.h"

void Enemy::Init()
{
	//デバック　可視化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_enemy = std::make_shared<KdSquarePolygon>();
	m_enemy->SetMaterial("Asset/Textures/char.png");

	//画像分割
	m_enemy->SetSplit(6, 6);

	m_enemy->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);


	m_pos = { -20,3,0 };
}

void Enemy::Update()
{
	int Walk[4] = { 3,4,3,5 };
	//アニメーション
	m_enemy->SetUVRect(Walk[(int)m_anime]);

	m_anime += 0.1;//速度
	if (m_anime >= 4)
	{
		m_anime = 0;
	}

	//落下処理　重力
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;//重力の加速度


	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	//行列合成はUpdateの最後
	//行列合成　順番は　拡大S→回転R→移動T　の順番で行う
	m_mWorld = transMat;
}

void Enemy::PostUpdate()
{
	//当たり判定（レイ判定）

	//当たり判定を実装する時は、当たる側・当たられる側が存在する
	//「当たる側」の処理

	//***********
	//レイ判定　当たり判定
	//***********
	//レイ判定用変数
	KdCollider::RayInfo ray;
	//レイ判定　発射位置　プレイヤーの位置から例を出す
	ray.m_pos = m_pos;
	//プレイヤーのちょっと上からの位置にする
	ray.m_pos.y += 0.1f;
	//段差の許容範囲
	//段差を上がれるようにするための高さ
	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;

	//レイ　発射方向判定
	ray.m_dir = { 0, -1, 0 };
	//レイ　長さを設定
	ray.m_range = m_gravity + enableStepHigh;
	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	//★デバック表示するならInitに呼びに行く
	//デバック　可視化 m_pDebugWireをInitで宣言必須　実体化
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//レイに当たったオブジェクト情報を格納する
	std::list<KdCollider::CollisionResult> retRayList1;
	//全オブジェクトと当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//レイと当たり判定
		obj->Intersects(ray, &retRayList1);
	}

	//レイにあたったリストから一番近いオブジェクトを探す
	float mextOverLap = 0;
	Math::Vector3 hitPos;
	bool hit = false;
	for (auto& ret : retRayList1)
	{
		//レイを遮断しオーバーした長さが一番長いものを探す
		if (mextOverLap < ret.m_overlapDistance)
		{
			//更新
			mextOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}
	//一番近いとこの座標
	if (hit == true)
	{
		//当たっていたら当たった座標にプレイヤーの座標をセット
		m_pos = hitPos + Math::Vector3(0.0f, -0.1f, 0.0f);
		m_gravity = 0;//重力を無効化にする
	}
	//***********

	//球判定　(スフィア)判定
	//***********
	//球判定用変数
	KdCollider::SphereInfo sphere;
	//球の中止座標　設定
	//キャラクターの位置を中止にする
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 0.5f;//ちょっと上にする
	//球の半径　設定
	//キャラクターの足元から半径0.3の球を出す
	sphere.m_sphere.Radius = 0.3f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	//★デバック表示するならInitに呼びに行く
	//デバック　可視化
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList1;
	//全オブジェクトと当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//球と当たり判定
		obj->Intersects(sphere, &retSphereList1);
	}
	//球にあたったリストから一番近いオブジェクトを探す
	//レイ判定の時に宣言している
	mextOverLap = 0;	//球の時はめりこんだ長さ
	//レイ判定の時に宣言している
	hit = false;
	//当たった方向を格納する変数
	Math::Vector3 hitDir;
	for (auto& ret : retSphereList1)
	{
		//球にめり込んだ長さが一番長いものを探す
		if (mextOverLap < ret.m_overlapDistance)
		{
			//更新
			mextOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true)
	{
		//2.5Dを作るなら
		//Z方向への押出無効
		hitDir.z = 0;
		//正規化　長さを1にする
		hitDir.Normalize();

		//当たっていたら押し戻し
		m_pos += hitDir * mextOverLap;
		//hitDir　当たった方向(方向ベクトルは長さ1)
		//mextOverLap　めり込んだ長さ
	}

}

void Enemy::DrawLit()
{
	//表示
	// m_model　は　ポインタだから　*　がいる
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_enemy, m_mWorld);
}
