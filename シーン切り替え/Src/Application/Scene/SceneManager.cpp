#include "SceneManager.h"

#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"

void SceneManager::PreUpdate()
{
	//シーン切り替え
	if(m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	m_currentScene->Update();

}

void SceneManager::Draw()
{
	m_currentScene->DrawSprite();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{

}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	//1　次のシーン作成
	switch (_sceneType)
	{
	case SceneManager::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneManager::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	
	}

	//Init関数はここで呼ぶ
	//m_currentScene->Init();
	
	//2　シーン管理フラグ更新
	m_currentSceneType = _sceneType;

}
