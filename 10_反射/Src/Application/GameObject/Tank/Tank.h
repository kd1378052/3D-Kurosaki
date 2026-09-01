#pragma once
class TPSCamera;
class Tank : public KdGameObject
{
public:
	Tank()					 {}
	~Tank()			override {}

	void Init()		override;
	void Update()	override;
	void PostUpdate() override;
	void DrawLit()	override;
	void DrawSprite()	override;

	void SetCamera(const std::weak_ptr<TPSCamera> camera)
	{
		m_camera = camera;
	}
private:
	// カメラ情報 ポインタ 
	//参照だけなら weak_ptr で十分
	std::weak_ptr<TPSCamera> m_camera;

	//モデル
	std::shared_ptr<KdModelData> m_model;

	float m_angle = 0.0f;
	Math::Vector3 m_pos;
	bool m_stkFlg = false;

	//レティクル
	std::shared_ptr<KdTexture> m_tex;
	//KdTexture m_tex;

};