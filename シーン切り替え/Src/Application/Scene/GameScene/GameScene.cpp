#include "GameScene.h"
#include "../SceneManager.h"

void GameScene::Init()
{

}

void GameScene::Update()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::DrawSprite()
{
	// キャラ表示もどき 円表示
	KdShaderManager::Instance().m_spriteShader.DrawCircle(0, 0, 100);

	////画面クリア
	//color = { 0.29f, 0.15f, 0.65f,1 }; //紫
	//SHADER.m_spriteShader.DrawBox(0, 0, 320, 180, &color, true);
	////円
	//color = { 0,0,1,1 };
	//SHADER.m_spriteShader.DrawCircle(0, 0, 50, &color, true);
}

void GameScene::Release()
{

}
