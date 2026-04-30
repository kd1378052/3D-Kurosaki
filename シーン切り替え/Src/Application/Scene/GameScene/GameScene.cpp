#include "GameScene.h"
#include "../SceneManager.h"

void GameScene::Init()
{
	m_tex.Load("Asset/Textures/TitleScene/title.png");
	m_tex.Load("Asset/Textures/numbers.png");

}

void GameScene::Update()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_score += 100;
		if (m_score > 9999999999)
		{
			m_score = 9999999999;
		}
	}

	//配列に各桁の数値を格納
	unsigned long tep = m_score;

	for (int i = maxDigits - 1; i >= 0; --i)
	{
		//下位の桁から抽出し、配列に格納
		m_digits[i] = tep % 10;
		tep /= 10;
	}
}

void GameScene::DrawSprite()
{
	// キャラ表示もどき 円表示
	KdShaderManager::Instance().m_spriteShader.DrawCircle(0, 0, 100);

	//スコア表示
	for(int i = 0; i < maxDigits; ++i)
	{
		Math::Rectangle rc = { 7 * m_digits[i],0,7,10 };

		float posX = -350;

		//桁別に表示(0)
		KdShaderManager::Instance().m_spriteShader.
		DrawTex(&m_tex,
			posX +( i * 70)//ｘ
			,0,//ｙ
			70, //幅
			100,//高さ
			&rc);
		
	}

	

}

void GameScene::Release()
{

}
