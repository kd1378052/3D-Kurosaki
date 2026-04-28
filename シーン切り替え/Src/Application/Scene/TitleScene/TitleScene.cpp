#include "TitleScene.h"

#include "../SceneManager.h"

void TitleScene::Init()
{
	m_tex.Load("Asset/Textures/title.png");
	m_starttex.Load("Asset/Textures/start.png");
	
	m_alphaAdd = -0.01f;
	m_alpha = 1;

}

void TitleScene::Update()
{
	//ここで不透明度いじる
	m_alpha += m_alphaAdd;

	if (m_alpha < 0.5f)
	{
		m_alpha = 0.5f;
		m_alphaAdd *= -1;

	}
	else if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_alphaAdd *= -1;
	}

	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0);
	Math::Color color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_starttex, 0, -200 ,nullptr,&color);

}

void TitleScene::Release()
{
}
