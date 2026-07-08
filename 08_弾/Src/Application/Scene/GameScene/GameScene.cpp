#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"
#include"../../GameObject/Enemy/EnemyMoto/EnemyMoto.h"
#include"../../GameObject/Enemy/EnemyYama/EnemyYama.h"

void GameScene::Event()
{
	//オブジェクト数表示
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("obj=%d\n", m_objList.size());


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

	//カメラに戦車をセット　カメラが戦車を追従する
	camera->SetTarget(tank);

	//戦車にカメラをセット　tankクラスでカメラの情報を使えるようにする
	tank->SetCamera(camera);

	//敵 moto
	std::shared_ptr< EnemyMoto> enemymoto;
	enemymoto = std::make_shared< EnemyMoto>();
	enemymoto->Init();
	enemymoto->SetPos({ 10,0,20 });
	//ここでターゲットをセットしてる　アドレス渡しが便利だね
	enemymoto->SetTarget(tank);
	m_objList.push_back(enemymoto);

	//敵 Yama
	std::shared_ptr< EnemyYama> enemyyama;
	enemyyama = std::make_shared< EnemyYama>();
	enemyyama->Init();
	enemyyama->SetPos({-10, 0, 20});
	//ここでターゲットをセットしてる　アドレス渡しが便利だね
	enemyyama->SetTarget(tank);//ターゲットを戦車にする
	m_objList.push_back(enemyyama);

	

}
