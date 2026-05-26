#include "GameScene.h"
#include "../SceneManager.h"

void GameScene::Init()
{
	//カメラ初期化
	m_camera.SetProjectionMatrix(60);
	m_model.Load("Asset/Models/Ship/ship.gltf");
	
}

void GameScene::Update()
{
	//カメラの位置を調整
	Math::Vector3 camPos = { 0,10,-40 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	m_camera.SetCameraMatrix(transMat);

	//船の処理
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pos.z += 0.1f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pos.z -= 0.1f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_angleY -= 1;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_angleY += 1;
	}
}

void GameScene::DrawSprite()
{

}

//3Dモデル表示
void GameScene::DrawLit()
{
	m_camera.SetToShader();

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));

	Math::Matrix worldMat = rotMat * transMat;

	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, worldMat);
	
}

void GameScene::Release()
{

}
