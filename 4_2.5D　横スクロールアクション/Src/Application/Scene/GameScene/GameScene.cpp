#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Player/Player.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Cannon/Cannon.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Object/Ghost/Ghost.h"

void GameScene::Event()
{
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("%d", m_objList.size());

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

	//被写界深度      ↓ピンと合わせる処理
	//m_camera->SetFocus(5, 3,		8);
	//　　　　　　　　　　↑手前　↑奥

	//画面全体をちょっとぼかして光らせる
	KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7);

}

void GameScene::Init()
{
	//平行光(ディレク所なるライト)　光をどこからあてるか設定できる
	//																　↓光の方向	↓色
	//KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0, -1, 0.1 },{1,1,1});
	//3,1,0 ←オレンジ　夕焼け
	
	//アンビエントライト
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({1,1,1,1});
	
	//fog(霧)														↓距離↓高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	//距離フォグの設定														　↓色　　↓密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0,0,0 }, 0.1);
	//高さフォグの設定												↓色　↓上↓下↓距離↓
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0,0,0 }, 2, -2, 0);
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

	for (int i = 0; i < 5; ++i)
	{
		ground = std::make_shared< Ground>();
		//Init
		//先++しているから+5をする
		ground->SetPos(Math::Vector3(0,0,i*5 + 5));
		m_objList.push_back(ground);

	}
	//手前
	ground = std::make_shared< Ground>();
	//Init
	ground->SetPos(Math::Vector3(0, 0,-3));
	m_objList.push_back(ground);

	//上
	ground = std::make_shared< Ground>();
	//Init
	ground->SetPos(Math::Vector3(0, 5,0));
	m_objList.push_back(ground);

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

	//ゴーストを追加　表示
	std::shared_ptr< Ghost> ghost;
	ghost = std::make_shared< Ghost>();
	//↓　ここでプレイヤーの座標を投げてる
	ghost->SetTarget(m_player);
	m_objList.push_back(ghost);


	//Enemyを追加　表示
	//敵5体追加
	std::shared_ptr< Enemy> enemy;

	//オブジェクト思考
	for (int i = 0; i < 10; ++i)
	{
		enemy = std::make_shared< Enemy>();
		enemy->SetPos({ -20 +(float)i ,3 , 0 });
		m_objList.push_back(enemy);
	}

	
}
