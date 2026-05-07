#pragma once

//前方宣言
class BaseScene;

class SceneManager
{
public:

	//シーン情報
	//enum = 列挙型…int型の羅列(られつ)
	enum SceneType
	{
		Title,
		Game
	};

	void PreUpdate();//Updateの前にやってほしいアップデート
	void Update();
	void Draw();

	//次のシーンの予約をする
	void SetNextScene(SceneType _nextScene) 
	{
		m_nextSceneType = _nextScene;
	}

	SceneType GetCurrentSceneType()const
	{
		return m_currentSceneType;
	}
	

private:

	//保守性を高めるために、他で呼べないようにする
	void Init();
	void Release();
	void ChangeScene(SceneType _sceneType);

	std::shared_ptr<BaseScene> m_currentScene; //現在のシーンを管理しているポインタ

	SceneType m_currentSceneType = SceneType::Title; //現在のシーンの種類
	SceneType m_nextSceneType = m_currentSceneType; //次のシーンの種類

	//シングルトンパターン(デザインパターン)
	//実態が１つしかないことを保証するデザインパターン
	//何でもかんでもシングルトンにしない
public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}

private:
	SceneManager() { Init(); }
	~SceneManager() { Release(); }

};
