#include "Tank.h"
#include"../Camera/TPSCamera/TPSCamera.h"

void Tank::Init()
{
	//メモリ確保
	m_model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model->Load("Asset/Models/tank/tank.gltf");

	//座標行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 0);

	// 行列合成 (S * R * T)
	m_mWorld = transMat;
}

void Tank::Update()
{
	//カメラの回転行列
	Math::Matrix camRotYMat;
	//カメラが存在しているか確認
	if (m_camera.expired() == false)
	{
		//カメラが存在しているか
		camRotYMat = m_camera.lock()->GetRotationYMatrix();
	}

	//方向設定してうごかしたりしてる
	//方向ベクトル
	Math::Vector3 dir;
	bool moveFlg = false;

	if (GetAsyncKeyState('W') & 0x8000) {
		dir +=Math::Vector3::TransformNormal({0,0,1}, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		dir += Math::Vector3::TransformNormal({1,0,0}, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		dir += Math::Vector3::TransformNormal({0,0,-1}, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		dir += Math::Vector3::TransformNormal({-1,0,0}, camRotYMat);
		moveFlg = true;
	}

	if(moveFlg == true)
	{
		//方向ベクトルを正規化
		dir.Normalize();

		//内積：ベクトルA * ベクトルB * COS(なす角)
		//　＝　　　1　　　*　　1　　　* COS(なす角)
		//＝　COS(なす角)
		//COSをACOSで計算すると角度

		//今向いている方向
		//1キャラの回転行列を作る
		Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		//2ベクトルを変形される(new)							変形基準は0，0，1
		Math::Vector3 nowDir = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowRotMat);

		//※もっと簡単に正面をとる方法　おすすめはせん
		//dir = m_mWorld.Backward();

		//向きたい方向
		Math::Vector3 toDir = dir;

		//内積を出す
		float dot = nowDir.Dot(toDir);
		//    ↑cos(なす角)
		//角度を出す（ラジアン角）
		float angle = (acos(dot));
		angle = DirectX::XMConvertToDegrees(acos(dot));

		if (angle >= 0.1f)
		{
			if (angle > 5)
			{
				angle = 5;
			}

			//外積：２つのベクトルに対して垂直なベクトルを算出
			Math::Vector3 cross = nowDir.Cross(toDir);
			//外積のY成分が正なら左回転、負なら右
			if (cross.y >= 0.0f) {
				//外積が上を向いている
				m_angle += angle;

				if (m_angle > 360)
				{
					m_angle -= 360;
				}
			}
			else {
				//外積が下を向いている
				m_angle -= angle;
				if (m_angle < 0)
				{
					m_angle += 360;
				}
			}
		}

		KdDebugGUI::Instance().AddLog("%f\n", m_angle);

		//回転
		Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		//移動処理
		m_pos += dir * 0.3f;
		//座標
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
		
		m_mWorld = rotMat * transMat;
	}

}

void Tank::DrawLit()
{
	//地面描画
	//地面には陰影がつくべきなのでDrawLit（）で描画する
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

