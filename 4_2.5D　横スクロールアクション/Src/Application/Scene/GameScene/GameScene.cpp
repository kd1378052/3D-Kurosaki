#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Player/Player.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Cannon/Cannon.h"
#include"../../Object/Enemy/Enemy.h"

void GameScene::Event()
{
	//タイトルに戻る
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	//カメラ処理
	Math::Vector3 camPos = {0,1,-5};
	//ここでPlayerの座標を足している　これでPlayerの位置にカメラがついてくる↓
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos+ m_player->GetPos());
	m_camera->SetCameraMatrix(transMat);

}

void GameScene::Init()
{
	//カメラを実体化
	m_camera = std::make_unique<KdCamera>();

	//地面を追加
	//1ポインタを作る
	std::shared_ptr< Ground> ground;
	//2実体化
	ground = std::make_shared< Ground>();
	//3初期化
	//黒崎授業ではコンストラクタでInitを読んでいるから不要
	//4オブジェクトリストに追加
	m_objList.push_back(ground);
	//AddObject(ground);	↑こっちを使うと処理不可軽減

	//背景を追加
	std::shared_ptr< Back> back;
	back = std::make_shared< Back>();
	m_objList.push_back(back);

	//Playerを追加　表示
	//std::shared_ptr< Player> player;
	m_player = std::make_shared< Player>();
	m_objList.push_back(m_player);

	//Cannonを追加　表示
	std::shared_ptr< Cannon> cannon;
	cannon = std::make_shared< Cannon>();
	m_objList.push_back(cannon);

	//Enemyを追加　表示
	std::shared_ptr< Enemy> enemy;
	enemy = std::make_shared< Enemy>();
	m_objList.push_back(enemy);

}
