#pragma once
#include "quad2d.h"
class CFade
{
public:
	void Init(bool init);
	void Init();
	void UnInit();
	void Draw();
	void Update();

	void FadeIn();
	void FadeOut();

	enum class FADE_STATE {
		NONE,
		FADEIN,
		FADEOUT
	};
	FADE_STATE GetState();

	void Start();
	bool IsStart() {
		return m_IsStart;
	}
	int GetAlpha() {
		return m_fadeCount;
	}

private:
	Quad2D		m_fade;
	FADE_STATE mState;

	float& Alpha();

	float		m_fadeCount;

	bool		m_IsStart;

	XMFLOAT2	m_uv[4] = {
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 1.0f}
	};

	XMFLOAT4 color = { 1,1,1,1 };
};

