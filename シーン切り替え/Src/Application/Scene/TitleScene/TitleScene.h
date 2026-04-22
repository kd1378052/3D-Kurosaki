#pragma once

class TitleScene
{
public:
	TitleScene() {}
	~TitleScene() {}

	void Init();
	void Update();
	void DrawSprite();
	void Release();

private:

	KdTexture m_tex;
	KdTexture m_starttex;

	float m_alpha;
	float m_alphaAdd;
};
