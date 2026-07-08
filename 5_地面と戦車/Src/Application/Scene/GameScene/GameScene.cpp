#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
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

}
