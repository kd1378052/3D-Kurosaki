#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"
#include "../../GameObject/MyPolygon/MyPolygon.h"

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

	//板ポリ
	std::shared_ptr< MyPolygon> myPolygon;
	myPolygon = std::make_shared< MyPolygon>();
	myPolygon->Init();
	m_objList.push_back(myPolygon);

	//戦車
	std::shared_ptr< Tank> tank;
	tank = std::make_shared< Tank>();
	tank->Init();
	m_objList.push_back(tank);

	//カメラに戦車をセット　カメラが戦車を追従する
	camera->SetTarget(tank);

	//戦車にカメラをセット　tankクラスでカメラの情報を使えるようにする
	tank->SetCamera(camera);

}
