#include "Player.h"

#include"../../Scene/SceneManager.h"

void Player::Init()
{
	//デバック用のポインタを実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//実体化
	m_polygon = std::make_shared<KdSquarePolygon>();
	//テクスチャ
	m_polygon->SetMaterial("Asset/Textures/char.png");

	//画像分割
	m_polygon->SetSplit(6,6);
}

void Player::Update()
{
	//Math::Vector3 camPos = { 0,10,-40 };
	//Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	//m_polygon->SetCameraMatrix(transMat);

	int Run[4] = { 24,25,24,26 };
	//アニメーション
	m_polygon->SetUVRect(Run[(int)m_anime]);
	
	m_anime += 0.2;//速度
	if (m_anime >= 4)
	{
		m_anime = 0;
	}
	//m_anime↑を0にしているからここで０にしたらアニメーショが動く

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 0.05f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 0.05f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 0.05f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 0.05f;
	}
	//座標行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	//行列合成
	m_mWorld = transMat;
}

void Player::PostUpdate()
{
	//当たり判定（レイ判定）
	
	//当たり判定を実装する時は、当たる側・当たられる側が存在する
	//「当たる側」の処理
	
	//***********
	//レイ判定　当たり判定
	//***********
	//レイ判定用変数
	KdCollider::RayInfo ray;
	//レイ判定　発射位置
	ray.m_pos = m_pos;
	//レイ　発射方向判定
	ray.m_dir = { 0, -1, 0 };
	//レイ　長さを設定
	ray.m_range = 1;
	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	//デバック　可視化 m_pDebugWireをInitで宣言必須　実体化
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);
	
	//レイに当たったオブジェクト情報を格納する
	std::list<KdCollider::CollisionResult> retRayList;
	//全オブジェクトと当たり判定
	for(auto& obj : SceneManager::Instance().GetObjList())
	{
		//レイと当たり判定
		obj->Intersects(ray, &retRayList);
	}

	//レイにあたったリストから一番近いオブジェクトを探す
	float mextOverLap = 0;
	Math::Vector3 hitPos;
	bool hit = false;
	for (auto& ret : retRayList)
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
	if(hit == true)
	{
		m_pos = hitPos;
	}

}

void Player::DrawLit()
{

	//表示
	// m_model　は　ポインタだから　*　がいる
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}