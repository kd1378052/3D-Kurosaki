#include "Ghost.h"

void Ghost::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_ghost = std::make_shared<KdSquarePolygon>();
	m_ghost->SetMaterial("Asset/Textures/char.png");

	// 画像を分割
	m_ghost->SetSplit(6, 6);

}

void Ghost::Update()
{
	m_ghost->SetUVRect(34);

	//ターゲットが生きているか確認
	Math::Vector3 targetPos;
	if (m_target.expired() == false)
	{
		//領域が存在している
		targetPos = m_target.lock()->GetPos();
		// shared_ptrに登録

	}

	//	//移動 ゴイスー
	Math::Vector3 dir = targetPos - m_pos;

	//////ベクトルの正規化　長さを1にする
	dir.Normalize();

	//////敵を時機に向かって移動させる
	m_pos += dir * 0.02;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	//行列合成
	m_mWorld = transMat;
}

void Ghost::DrawLit()
{
	//ブレンディング方法を変える								↓加算
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Add);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_ghost, m_mWorld);
	//表示し終わったら元に戻す
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Alpha);

}
