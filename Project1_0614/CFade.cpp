#include "CFade.h"
#include "Application.h"

void CFade::Init(bool init)
{
	m_fade.Init(1400, 750, XMFLOAT4(0, 0, 0, 1), m_uv);
	m_fade.LoadTexture("assets/white.bmp");
	if (init)
		m_fadeCount = 0.99f;
	else
		m_fadeCount = -0.01f;
	m_IsStart = false;
}

void CFade::Init()
{
	m_fade.Init(1400, 750, XMFLOAT4(0, 0, 0, 1), m_uv);
	m_fade.LoadTexture("assets/white.bmp");
}

void CFade::UnInit()
{
	m_fade.UnInit();
}

void CFade::Draw()
{
	m_fade.updateVertex(1300, 760, color, m_uv);
	m_fade.updateVbuffer();
	m_fade.SetPosition(650, 380,0);
	m_fade.Draw();
}

void CFade::Update()
{
	/*m_fade.SetPosition(Application::CLIENT_WIDTH / static_cast<float>(2), Application::CLIENT_HEIGHT / static_cast<float>(2), 0);
	m_fade.updateVertex(1400, 750, XMFLOAT4(0, 0, 0, m_fadeCount), m_uv);
	m_fade.updateVbuffer();

	if (m_fadeCount > 0 && m_IsStart == true)
		m_fadeCount += 0.01f;
	else
		if (m_fadeCount > 0) m_fadeCount -= 0.01f;

	if (m_fadeCount > 1)
		return true;
	return false;*/

	float& alpha = Alpha(); // パネルの透明度への参照を取得

	switch (GetState())
	{
	case FADE_STATE::FADEIN:
		alpha -= 0.01f;
		if (alpha <= 0.0f)
		{
			mState = FADE_STATE::NONE;
		}
		break;

	case FADE_STATE::FADEOUT:
		alpha += 0.005f;
		if (alpha >= 1.0f)
		{
			mState = FADE_STATE::NONE;
		}
		break;
	}

	//m_fade->Update();
}

void CFade::FadeIn()
{
	mState = FADE_STATE::FADEIN;
	Alpha() = 1.0f;
}

void CFade::FadeOut()
{
	mState = FADE_STATE::FADEOUT;
	Alpha() = 0.0f;
}

CFade::FADE_STATE CFade::GetState()
{
	return mState;
}

void CFade::Start()
{
	if (m_fadeCount < 0) {
		m_fadeCount = 0.01f;
		m_IsStart = true;
	}
}

float& CFade::Alpha()
{
	return color.w;
	// TODO: return ステートメントをここに挿入します
}
