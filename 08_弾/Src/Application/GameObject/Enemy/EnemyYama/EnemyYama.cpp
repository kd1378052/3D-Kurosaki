#include "EnemyYama.h"

void EnemyYama::Init()
{
	//メモリ確保
	m_model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model->Load("Asset/Models/enemy/yama/yama.gltf");

	// 「当てられる側」の処理======

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	// 当たり判定用に球登録
	m_pCollider->RegisterCollisionShape
	(
		"YamaCollision",				// 識別用の名前
		m_model,							// 球の半径
		KdCollider::Type::TypeDamage	//当たり判定の種類
	);
	// ============================
	
}

void EnemyYama::Update()
{
	//ターゲットが生きているか確認
	Math::Vector3 targetPos;
	//アドレス先が実在するかどうか調べる
	if (m_target.expired() == false)
	{
		//領域が存在している
		targetPos = m_target.lock()->GetPos();
		// shared_ptrに登録

	}
	//ターゲットへの方向ベクトルを算出
	//移動 ゴイスー
	Math::Vector3 targetDir = targetPos - m_pos;

	//targetDirは正規化前に自分とターゲットの距離がとれる
	//　　　　↓　　距離を保存
	//float distance = targetDir.Length();
	if (targetDir.Length() < 20.0f)
	{
		//ベクトルの正規化　長さを1にする
		targetDir.Normalize();//ノーマライズ

		//敵を時機に向かって移動させる
		m_pos += targetDir * 0.05f;
	}

	//今の向いている方向ベクトル
	Math::Vector3 nowDir = m_mWorld.Backward();

	//向きたい方向
	Math::Vector3 toDir = targetDir;

	//内積を出す
	float dot = nowDir.Dot(toDir);
	//    ↑cos(なす角)
	//角度に変換（ラジアン角）
	float angle = DirectX::XMConvertToDegrees(acos(dot));

	if (angle >= 0.1f)
	{
		//回転角度の上限
		if (angle > 5)
		{
			angle = 5;
		}

		//外積：２つのベクトルに対して垂直なベクトルを算出
		Math::Vector3 cross = nowDir.Cross(toDir);
		//外積のY成分が正なら左回転、負なら右
		if (cross.y >= 0.0f) {
			m_angle += angle;
			//外積が上を向いている場合は右回転
			if (m_angle > 360)
			{
				m_angle -= 360;
			}
		}
		else {
			m_angle -= angle;
			//外積が下を向いている場合は左回転

			if (m_angle < 0)
			{
				m_angle += 360;
			}
		}
	}
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	//座標行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	// 行列合成 (S * R * T)
	m_mWorld = rotMat * transMat;
}

void EnemyYama::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void EnemyYama::OnHit()
{
	//敵が当たった時の処理
	//↓　オブジェクトの生存フラグ
	m_isExpired = true;
	//Expired = 有効期限
}
