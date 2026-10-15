#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"
#include"../../GameObject/Grass/Grass.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
	//黒崎授業11
	//風を操作
	static int ang = 0;
	ang++;
	if (ang > 360)
	{
		ang -= 360;
	}
	//サインカーブ
	float w = sin(DirectX::XMConvertToRadians(ang));
	KdShaderManager::Instance().SetWindValue({ w,0,0 });
}

void GameScene::Init()
{
	//黒崎授業10
	//風有効化
	KdShaderManager::Instance().m_StandardShader.SetWindEnable(true);

	//カメラ
	std::shared_ptr< TPSCamera> camera;
	camera = std::make_shared< TPSCamera>();
	camera->Init();
	m_objList.push_back(camera);

	//道
	std::shared_ptr< Ground> ground;
	ground = std::make_shared< Ground>();
	ground->Init();
	m_objList.push_back(ground);

	//戦車
	std::shared_ptr< Tank> tank;
	tank = std::make_shared< Tank>();
	tank->Init();
	m_objList.push_back(tank);

	//草
	std::shared_ptr< Grass> grass;
	for(int i = 0; i < 1000; i++)
	{
		grass = std::make_shared< Grass>();
		grass->Init();
		m_objList.push_back(grass);
	}

	//カメラに戦車をセット　カメラが戦車を追従する
	camera->SetTarget(tank);

	//戦車にカメラをセット　tankクラスでカメラの情報を使えるようにする
	tank->SetCamera(camera);

}
